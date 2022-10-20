#pragma once

#include <sqlite3.h>
#include <string>

class db_instance {
    const std::string _path;
    sqlite3* _connection;

public:
    db_instance(std::string db_path);

    bool connect();
    sqlite3* connection() const;
    ~db_instance();
};