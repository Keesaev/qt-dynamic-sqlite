#include "db_instance.h"

db_instance::db_instance(std::string db_path)
    : _path(db_path)
{
}

db_instance::~db_instance()
{
    if (_connection) {
        sqlite3_close(_connection);
    }
}

sqlite3* db_instance::connection() const
{
    return _connection;
}

bool db_instance::connect()
{
    int res = sqlite3_open_v2(_path.c_str(), &_connection,
        SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX,
        NULL);
    return res == SQLITE_OK;
}