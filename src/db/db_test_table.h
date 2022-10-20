#pragma once

#include "db_base_table.hpp"

class db_test_table final : public db_base_table {
    static constexpr int _column_count { 3 };

public:
    db_test_table(db_instance const& instance, std::string table_name);
    virtual ~db_test_table();

    virtual int row_count() const final;
    virtual int column_count() const final;
    virtual std::vector<TableRow> select(select_query query) const final;
    virtual void insert(std::vector<TableRow> rows) final;
};