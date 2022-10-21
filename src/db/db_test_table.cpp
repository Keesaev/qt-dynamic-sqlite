#include "db_test_table.h"

#include <iostream>
#include <memory>

DbTestTable::DbTestTable(DbInstance const& instance, std::string tableName)
    : DbBaseTable(instance, tableName)
{
}

DbTestTable::~DbTestTable() { }

int DbTestTable::rowCount() const
{
    std::scoped_lock<std::mutex> lock(_mutex);
    // TODO RAII sqlite3_stm
    const static std::string sql = "SELECT COUNT(*) FROM TEST_TABLE;";
    sqlite3_stmt* statement;
    int ret = sqlite3_prepare_v2(_instance.connection(), sql.c_str(), -1, &statement, nullptr);

    if (ret != SQLITE_OK) {
        std::cerr << __FUNCTION__ << ": " << __LINE__ << " - "
                  << "sqlite3_prepare_v2 " << ret << std::endl;
        sqlite3_finalize(statement);
        return 0;
    }

    ret = sqlite3_step(statement);
    int count { 0 };
    if (ret == SQLITE_ROW) {
        count = sqlite3_column_int(statement, 0);
    }
    sqlite3_finalize(statement);

    return count;
}

int DbTestTable::columnCount() const
{
    return _columnCount;
}

std::vector<TableRow> DbTestTable::select(SelectQuery query) const
{
    std::scoped_lock<std::mutex> lock(_mutex);
    std::vector<TableRow> out;

    auto statement_deleter = [](sqlite3_stmt* statement) {
        if (statement != nullptr) {
            sqlite3_finalize(statement);
        }
    };

    using scoped_statement = std::unique_ptr<sqlite3_stmt, decltype(statement_deleter)>;

    auto make_statement = [&statement_deleter](DbInstance const& instance, SelectQuery const& query) -> scoped_statement {
        sqlite3_stmt* raw_statement;
        int ret = sqlite3_prepare_v2(instance.connection(), std::string(query).c_str(), -1, &raw_statement, nullptr);

        if (ret != SQLITE_OK) {
            std::cerr << __FUNCTION__ << ": " << __LINE__ << " - "
                      << "sqlite3_prepare_v2 " << ret << std::endl;
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
        out.emplace_back(TableRow {
            sqlite3_column_int(statement.get(), 0),
            reinterpret_cast<const char*>(sqlite3_column_text(statement.get(), 1)),
            sqlite3_column_int(statement.get(), 2) });

        ret = sqlite3_step(statement.get());
    }
    out.shrink_to_fit();

    return out;
}

void DbTestTable::insert(std::vector<TableRow> rows)
{
}
