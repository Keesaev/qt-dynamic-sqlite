#pragma once

#include <string>

class SelectQuery {
    std::string tableName;
    // TODO:
    // ORDER BY ROWID DESC/ASC
    // WHERE <colname> LIKE *<pattern>*
    int _offset = 1;
    int _limit = 0;

public:
    SelectQuery(std::string tableName, int limit, int offset = 1)
        : tableName(tableName)
        , _limit(limit)
        , _offset(offset)
    {
    }
    int limit() const { return _limit; }
    operator std::string() const
    {
        auto res = "SELECT * FROM " + tableName;
        if (_limit) {
            res += " LIMIT "
                + std::to_string(_offset == 0 ? 1 : _offset)
                + ',' + std::to_string(_limit);
        }
        return res;
    }
};