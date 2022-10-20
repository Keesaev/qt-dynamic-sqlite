#include "db_instance.h"

DbInstance::DbInstance(std::string db_path)
    : _path(db_path)
{
}

DbInstance::~DbInstance()
{
    if (_connection) {
        sqlite3_close(_connection);
    }
}

sqlite3* DbInstance::connection() const
{
    return _connection;
}

bool DbInstance::connect()
{
    int res = sqlite3_open_v2(_path.c_str(), &_connection,
        SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX,
        NULL);
    return res == SQLITE_OK;
}