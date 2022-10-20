#pragma once

#include <string>
#include <vector>

#include "db_row.hpp"

#include <sqlite3.h>

class db_wrapper {
    sqlite3* _db { nullptr };
    const std::string _path;

public:
    db_wrapper(std::string path_to_db);
    ~db_wrapper();

    bool init();

    int count() const;
    std::vector<db_row> select(int size, int offset = 1) const;
    void insert(std::vector<db_row> rows);
};
