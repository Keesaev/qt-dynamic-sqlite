#include "db_wrapper.h"

db_wrapper::db_wrapper(std::string path_to_db)
    : _path(path_to_db)
{
}

bool db_wrapper::init(){
    int res = sqlite3_open_v2(_path.c_str(), &_db,
        SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX,
        NULL);
    if (res == SQLITE_OK) {
        return true;
    } else {
        return false;
    }
}

static int select_callback(void *count, int argc, char **argv, char **azColName) {
    *((int*)(count)) = ::atoi(argv[0]);
    return 0;
}
#include <iostream> // TODO rm
std::vector<db_row> db_wrapper::select(int size, int offset) const {
    std::string sql = "SELECT * FROM TEST_TABLE ORDER BY ROWID DESC LIMIT "
        + std::to_string(offset) + ',' + std::to_string(size) + ';';

    std::cout << sql << std::endl;

    std::vector<db_row> out;

    sqlite3_stmt* statement;
    int ret = sqlite3_prepare_v2(_db, sql.c_str(), -1, &statement, nullptr);

    if (ret != SQLITE_OK)
    {
        std::cerr << "sqlite3_prepare_v2 " << ret << std::endl;
        // finalize
        return out;
    }

    out.reserve(size);

    ret = sqlite3_step(statement);
    while (ret == SQLITE_ROW)
    {
        db_row row;

        row.id = sqlite3_column_int(statement, 0);
        row.name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
        row.code = sqlite3_column_int(statement, 2);
        out.emplace_back(std::move(row));

        ret = sqlite3_step(statement);
    }
    out.shrink_to_fit();

    return out; // TODO
}

void db_wrapper::insert(std::vector<db_row> rows){}
