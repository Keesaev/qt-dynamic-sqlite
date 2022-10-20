#pragma once

#include "cache_window.hpp"

#include <QVariant>
#include <vector>

using TableRow = std::vector<QVariant>;

class CacheController : public QObject {

    CacheWindow _window;
    std::vector<TableRow> _data;
    const int _column_count; // TODO use db_base_table API

    void fetch(int id);

public:
    CacheController(int column_count);
    TableRow get(int id);

signals:
    void cacheCompleted(CacheWindow window);
};