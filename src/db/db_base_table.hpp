#pragma once

#include "db_instance.h"
#include "select_query.hpp"

#include <QVariant>
#include <vector>

using TableRow = std::vector<QVariant>;

class DbBaseTable {
protected:
    DbInstance const& _instance;
    const std::string _tableName;

public:
    DbBaseTable(DbInstance const& instance, std::string tableName)
        : _instance(instance)
        , _tableName(tableName)
    {
    }
    virtual ~DbBaseTable()
    {
    }

    std::string tableName() const { return _tableName; }

    virtual int rowCount() const = 0;
    virtual int columnCount() const = 0;
    virtual std::vector<TableRow> select(SelectQuery query) const = 0;
    virtual void insert(std::vector<TableRow> rows) = 0;
};