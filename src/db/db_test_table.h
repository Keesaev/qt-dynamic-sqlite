#pragma once

#include "db_base_table.hpp"
#include <mutex>

class DbTestTable final : public DbBaseTable {
    static constexpr int _columnCount { 3 };
    mutable std::mutex _mutex;

    const std::vector<std::string> _columnNames {
        "ID", "NAME", "CODE"
    };

public:
    DbTestTable(DbInstance const& instance, std::string tableName);
    virtual ~DbTestTable();

    virtual int rowCount() const final;
    virtual int columnCount() const final;
    virtual std::vector<std::string> columnNames() const final;

    virtual std::vector<TableRow> select(SelectQuery query) const final;
    virtual void insert(std::vector<TableRow> rows) final;
};
