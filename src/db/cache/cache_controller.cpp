#include "cache_controller.h"

#include <iostream> // <TODO rm all stdout

#include <QtConcurrent/QtConcurrent>

CacheController::CacheController(const DbBaseTable* const table, SelectQuery query)
    : _table(table)
    , _query(query)
    , _window(0)
{
    assert(table != nullptr);
    assert(!_query.tableName().empty());
}

void CacheController::fetch(int id, bool force)
{
    if (!force) {
        if (!_window.completed()) {
            return;
        }
    }

    _window = CacheWindow(id); // completed = false
    auto watcher = new QFutureWatcher<std::vector<TableRow>>;


    _query = _query.offset(_window.left()).limit(_window.size());
    auto query = _query; // c++11
    auto future = QtConcurrent::run([this, query]() -> std::vector<TableRow> {
        return _table->select(query);
    });

    connect(watcher, &QFutureWatcher<std::vector<TableRow>>::finished, [=]() {
        watcher->deleteLater();

        _data = future.result();
        if(_data.empty()){
            qDebug() << "REFETCHING";
            fetch(id, true);
        }
        else{
            _window.complete(_data);
            emit cacheCompleted(_window);
        }
    });

    watcher->setFuture(future);
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
