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
    /**
     * @brief Constructs CacheController, doesn't query anything
     * @param must be connected by the time @c get() gets called
     * @param assert contains table name
     */
    CacheController(const DbBaseTable* const table, SelectQuery query);
    /**
     * @brief returns a specified row if cached, otherwise returns
     *  row containing empty cells (can be displayed) and triggers cache fetching
     * @param row id, must be in bounds [0, table.row_count)
     */
    TableRow get(int id);
    /**
     * @brief update query (limit and offset fields will be ignored and overriden)
     * @param must contain at least table name
     */
    void query(SelectQuery query);

signals:
    /**
     * @brief emited when rows are fetched from the table
     * @param window - contains indexes of fetched rows
     */
    void cacheCompleted(CacheWindow window);
};
