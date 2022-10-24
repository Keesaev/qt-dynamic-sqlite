#include "cache_controller.h"

#include <iostream> // <TODO rm all stdout

#include <QtConcurrent/QtConcurrent>

CacheController::CacheController(const DbBaseTable* const table, SelectQuery query)
    : _table(table)
    , _query(query)
    , _window(0),
      _fetcherThread(this),
      _fetcher(table)
{
    assert(table != nullptr);
    assert(!_query.tableName().empty());

    qRegisterMetaType<CacheWindow>("CacheWindow");

    _fetcher.moveToThread(&_fetcherThread);
    connect(&_fetcherThread, &QThread::started, &_fetcher, &RowFetcher::run);
    connect(&_fetcher, &RowFetcher::rowsFetched,
        this, &CacheController::fetchCompleted,
        Qt::QueuedConnection);
    _fetcherThread.start();
}

CacheController::~CacheController(){
    _fetcher.stop();
    _fetcherThread.quit();
}

void CacheController::fetch(int id, bool force)
{
    if (!force) {
        if (!_window.completed()) {
            return;
        }
    }

    _window = CacheWindow(id); // completed = false
    _fetcher.push_back({_window, _query});
}

void CacheController::fetchCompleted(CacheWindow window, std::vector<TableRow> rows){
    std::cout << "fetchCompleted" << std::endl;
    _data = rows;
    _window = window;
    emit cacheCompleted(window);
}


void CacheController::query(SelectQuery query)
{
    _query = query;
    fetch(_window.id(), true);
}

TableRow CacheController::get(int id)
{
    if (!_window.completed()) {
        // first fetch
        if(_data.empty()){
            fetch(id, true);
        }
        return TableRow(_table->columnCount(), tr("Загрузка"));
    } else {
        if (_window.contains(id)) {
            int offset_index = id - _window.left();
            return _data[offset_index];
        } else {
            fetch(id, false);
            return TableRow(_table->columnCount(), tr("Загрузка"));
        }
    }
}
