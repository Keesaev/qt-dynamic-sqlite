#include "row_fetcher.h"

RowFetcher::RowFetcher(const DbBaseTable* const table)
    : QObject(nullptr)
    , _table(table)
{
}

RowFetcher::~RowFetcher(){
    stop();
}

void RowFetcher::stop(){
    std::unique_lock<std::mutex> lock(_taskMutex);
    _running = false;
    _task_cv.notify_all();
}

/**
 * @brief RowFetcher::run
 * Sleeps untill new tasks arrives via push_back call or _running set to false
 * After task is done, checks if it is still required by comparing it to latest new task,
 * if last executed task is required, emits rowsFetched and clears task queue, otherwise starts executing next one
 */
void RowFetcher::run(){
    _running = true;
    while (true) {
        std::unique_lock<std::mutex> lock(_taskMutex);
        _task_cv.wait(lock, [this]() {
            return !_tasks.empty() || !_running;
        });

        if(!_running){
            return;
        }

        // Pick last task only, skip the others
        auto task = _tasks.back();
        _tasks.clear();
        lock.unlock();

        auto rows = _table->select(task.query());
        task.window().complete(rows);

        lock.lock();
        if(!_tasks.empty()){
            // If last fetched window doesn't contain new task's id, don't emit rowsFetched
            // because received rows are no longer required
            if (task.window().contains(_tasks.back().window().id())) {
                _tasks.clear();
                emit rowsFetched(task.window(), std::move(rows));
            }
        }
        else{
            emit rowsFetched(task.window(), std::move(rows));
        }
    }
}

void RowFetcher::push_back(FetchTask task){
    {
        std::unique_lock<std::mutex> lock(_taskMutex);
        _tasks.push_back(task);
    }
    _task_cv.notify_one();
}

