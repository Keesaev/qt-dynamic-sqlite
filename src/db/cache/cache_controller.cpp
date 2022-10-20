#include "cache_controller.h"

#include <iostream> // <TODO rm all stdout

CacheController::CacheController(int column_count)
    : _window(0)
    , _column_count(column_count)
{
    fetch(0);
}

void CacheController::fetch(int id)
{
    std::cout << "FETCHING WINDOW [" << _window.left() << ", " << _window.right() << "]" << std::endl;
    _window = CacheWindow(id);
}

TableRow CacheController::get(int id)
{
    if (_window.contains(id)) {
        std::cout << "HIT " << id << std::endl;
        return _data[id];
    } else {
        fetch(id);
        return TableRow(_column_count, tr("Загрузка"));
    }
}