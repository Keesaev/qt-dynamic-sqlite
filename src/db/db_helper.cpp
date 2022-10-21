#include "db_helper.h"

#include <iostream>

namespace db_helper{
scoped_statement make_statement(sqlite3* connection, std::string query){
    sqlite3_stmt* raw_statement;
    int ret = sqlite3_prepare_v2(connection, query.c_str(), -1, &raw_statement, nullptr);

    if (ret != SQLITE_OK) {
        std::cerr << __FUNCTION__ << ": " << __LINE__ << " - "
                  << "sqlite3_prepare_v2 " << ret << std::endl;
        sqlite3_finalize(raw_statement);
        return scoped_statement(nullptr, statement_deleter());
    } else {
        return scoped_statement(raw_statement, statement_deleter());
    }
}
};
