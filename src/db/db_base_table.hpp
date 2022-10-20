#pragma once

#include "db_instance.h"
#include "select_query.hpp"

#include <QVariant>
#include <vector>

using TableRow = std::vector<QVariant>;

class db_base_table {
protected:
    db_instance const& _instance;
    const std::string _table_name;

public:
    db_base_table(db_instance const& instance, std::string table_name)
        : _instance(instance)
        , _table_name(table_name)
    {
    }
    virtual ~db_base_table()
    {
    }

    std::string table_name() const { return _table_name; }

    virtual int row_count() const = 0;
    virtual int column_count() const = 0;
    virtual std::vector<TableRow> select(select_query query) const = 0;
    virtual void insert(std::vector<TableRow> rows) = 0;
};