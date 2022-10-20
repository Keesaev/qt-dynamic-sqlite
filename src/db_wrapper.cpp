#include "db_wrapper.h"

#include <iostream> // TODO rm

db_wrapper::db_wrapper(std::string path_to_db)
    : _path(path_to_db)
{
}

db_wrapper::~db_wrapper()
{
    sqlite3_close(_db);
}

bool db_wrapper::init()
{
    int res = sqlite3_open_v2(_path.c_str(), &_db,
        SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX,
        NULL);
    if (res == SQLITE_OK) {
        return true;
    } else {
        return false;
    }
}

int db_wrapper::count() const
{
    const static std::string sql = "SELECT COUNT(*) FROM TEST_TABLE;";
    sqlite3_stmt* statement;
    int ret = sqlite3_prepare_v2(_db, sql.c_str(), -1, &statement, nullptr);

    if (ret != SQLITE_OK) {
        std::cerr << "sqlite3_prepare_v2 " << ret << std::endl;
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

std::vector<db_row> db_wrapper::select(int size, int offset) const
{
    std::string sql = "SELECT * FROM TEST_TABLE ORDER BY ROWID DESC LIMIT "
        + std::to_string(offset) + ',' + std::to_string(size) + ';';

    std::vector<db_row> out;

    sqlite3_stmt* statement;
    int ret = sqlite3_prepare_v2(_db, sql.c_str(), -1, &statement, nullptr);

    if (ret != SQLITE_OK) {
        std::cerr << "sqlite3_prepare_v2 " << ret << std::endl;
        sqlite3_finalize(statement);
        return out;
    }

    out.reserve(size);

    ret = sqlite3_step(statement);
    while (ret == SQLITE_ROW) {
        db_row row;

        row.id = sqlite3_column_int(statement, 0);
        row.name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
        row.code = sqlite3_column_int(statement, 2);
        out.emplace_back(std::move(row));

        ret = sqlite3_step(statement);
    }
    out.shrink_to_fit();
    sqlite3_finalize(statement);

    return out;
}

void db_wrapper::insert(std::vector<db_row> rows) { }
