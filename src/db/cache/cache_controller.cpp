#include "cache_controller.h"

#include <iostream> // <TODO rm all stdout

#include <QtConcurrent/QtConcurrent>

CacheController::CacheController(const DbBaseTable* const table, SelectQuery query)
    : _table(table)
    , _query(query)
    , _window(0)
{
    fetch(0);
}

void CacheController::fetch(int id, bool force)
{
    if (_fetching && _window.contains(id)) {
        return;
    }

    std::cout << "FETCHING WINDOW [" << _window.left() << ", " << _window.right() << "]" << std::endl;

    _window = CacheWindow(id);
    auto watcher = new QFutureWatcher<std::vector<TableRow>>;

    auto query = _query; // c++11
    auto future = QtConcurrent::run([this, query]() -> std::vector<TableRow> {
        return _table->select(query);
    });

    connect(watcher, &QFutureWatcher<std::vector<TableRow>>::finished, [=]() {
        watcher->deleteLater();

        _data = future.result();
        emit cacheCompleted(_window);
        _fetching = false;
    });

    _fetching = true;
    watcher->setFuture(future);
}

void CacheController::query(SelectQuery query)
{
    _query = query;
    fetch(_window.id(), true);
}

TableRow CacheController::get(int id)
{
    if (_fetching) {
        return TableRow(_table->columnCount(), tr("Загрузка"));
    } else {
        if (_window.contains(id)) {
            std::cout << "HIT " << id << std::endl;
            return _data[id];
        } else {
            fetch(id);
            return TableRow(_table->columnCount(), tr("Загрузка"));
        }
    }
}