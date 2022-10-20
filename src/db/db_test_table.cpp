#include "db_test_table.h"

#include <iostream>
#include <memory>

db_test_table::db_test_table(db_instance const& instance, std::string table_name)
    : db_base_table(instance, table_name)
{
}

db_test_table::~db_test_table() { }

int db_test_table::row_count() const
{
    return 0; // <SQLITE COUNT
}

int db_test_table::column_count() const
{
    return _column_count;
}

std::vector<table_row> db_test_table::select(select_query query) const
{
    std::vector<table_row> out;

    auto statement_deleter = [](sqlite3_stmt* statement) {
        if (statement != nullptr) {
            sqlite3_finalize(statement);
        }
    };

    using scoped_statement = std::unique_ptr<sqlite3_stmt, decltype(statement_deleter)>;

    auto make_statement = [&statement_deleter](db_instance const& instance, select_query const& query) -> scoped_statement {
        sqlite3_stmt* raw_statement;
        int ret = sqlite3_prepare_v2(instance.connection(), std::string(query).c_str(), -1, &raw_statement, nullptr);

        if (ret != SQLITE_OK) {
            std::cerr << "sqlite3_prepare_v2 " << ret << std::endl;
            sqlite3_finalize(raw_statement);
            return scoped_statement(nullptr, statement_deleter);
        } else {
            return scoped_statement(raw_statement, statement_deleter);
        }
    };

    auto statement = make_statement(_instance, query);

    if (statement == nullptr) {
        return out;
    }

    out.reserve(query.limit());

    int ret = sqlite3_step(statement.get());
    while (ret == SQLITE_ROW) {
        out.emplace_back(table_row {
            sqlite3_column_int(statement.get(), 0),
            reinterpret_cast<const char*>(sqlite3_column_text(statement.get(), 1)),
            sqlite3_column_int(statement.get(), 2) });

        ret = sqlite3_step(statement.get());
    }
    out.shrink_to_fit();

    return out;
}

void db_test_table::insert(std::vector<table_row> rows)
{
}