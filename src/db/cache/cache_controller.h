#pragma once

#include "../db_base_table.hpp"
#include "cache_window.hpp"

#include <QVariant>

#include <vector>

using TableRow = std::vector<QVariant>;

class CacheController : public QObject {
    Q_OBJECT

    const DbBaseTable* const _table;
    SelectQuery _query;
    CacheWindow _window;

    std::vector<TableRow> _data;

    void fetch(int id, bool force = false);

public:
    CacheController(const DbBaseTable* const table, SelectQuery query);
    TableRow get(int id);
    void query(SelectQuery query);

signals:
    void cacheCompleted(CacheWindow window);
};
