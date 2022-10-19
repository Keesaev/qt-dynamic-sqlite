#pragma once

#include <string>

// TODO
// introduce some kind of interface like
/*
 * int db_id
 * std::vector<T> data ?
 *
 */

struct db_row {
    int db_id; // < ID in db
    // Actual col data for test.db
    int id;
    std::string name;
    int code;
};
