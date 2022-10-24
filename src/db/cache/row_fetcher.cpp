#include "row_fetcher.h"

#include <iostream> // TODO rm

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

void RowFetcher::run(){
    _running = true;
    while (true) {
        std::unique_lock<std::mutex> lock(_taskMutex);
        std::cout << "waiting..." << std::endl;
        _task_cv.wait(lock, [this]() {
            return !_tasks.empty() || !_running;
        });

        if(!_running){
            return;
        }

        auto task = _tasks.back();
        _tasks.clear();
        lock.unlock();

        auto rows = _table->select(task.query());
        task.window().complete(rows);
        // TODO check queue once again and don't emit if rows is not in new window
        emit rowsFetched(task.window(), std::move(rows));

        std::cout << "processed " << task.window().left() << ", " << task.window().right() << std::endl;
    }
}

void RowFetcher::push_back(FetchTask task){
    {
        std::unique_lock<std::mutex> lock(_taskMutex);
        _tasks.push_back(task);
        std::cout << "push_back" << std::endl;
    }
    _task_cv.notify_one();
}

