#pragma once

#include <sqlite3.h>

#include <memory>
#include <string>

namespace db_helper{
    struct statement_deleter{
        void operator()(sqlite3_stmt* statement){
            sqlite3_finalize(statement);
        }
    };

    using scoped_statement = std::unique_ptr<sqlite3_stmt, statement_deleter>;
    scoped_statement make_statement(sqlite3* connection, std::string query);
};
