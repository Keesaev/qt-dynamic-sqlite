#pragma once

#include <sqlite3.h>
#include <string>

class DbInstance {
    const std::string _path;
    sqlite3* _connection;

public:
    DbInstance(std::string db_path);

    bool connect();
    sqlite3* connection() const;
    ~DbInstance();
};