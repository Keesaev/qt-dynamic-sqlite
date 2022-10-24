#include "db_test_table.h"

#include "db_helper.h"

#include <iostream>
#include <memory>

DbTestTable::DbTestTable(DbInstance const& instance, std::string tableName)
    : DbBaseTable(instance, tableName)
{
}

DbTestTable::~DbTestTable() { }

int DbTestTable::rowCount(LikeQuery like) const
{
    std::unique_lock<std::mutex> lock(_mutex);
    const std::string sql = "SELECT COUNT(*) FROM TEST_TABLE " + like.dump();

    auto statement = db_helper::make_statement(_instance.connection(), sql);

    if (statement == nullptr) {
        return 0;
    }

    if (SQLITE_ROW == sqlite3_step(statement.get())) {
        return sqlite3_column_int(statement.get(), 0);
    }
    else{
        return 0;
    }
}

int DbTestTable::columnCount() const
{
    return _columnCount;
}

std::vector<std::string> DbTestTable::columnNames() const
{
    return _columnNames;
}

std::vector<TableRow> DbTestTable::select(SelectQuery query) const
{
    std::cout << std::string(query) << std::endl;

    std::unique_lock<std::mutex> lock(_mutex);
    std::vector<TableRow> out;

    auto statement = db_helper::make_statement(_instance.connection(), query);

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
