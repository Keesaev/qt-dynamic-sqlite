#pragma once

#include <string>

class select_query {
    const std::string _table_name;
    // std::string order_by " ORDER BY ROWID DESC/ASC " // TODO
    const int _offset = 1;
    const int _limit = 0;

public:
    select_query(std::string table_name, int limit, int offset = 1)
        : _table_name(table_name)
        , _limit(limit)
        , _offset(offset)
    {
    }
    int limit() const { return _limit; }
    operator std::string() const
    {
        auto res = "SELECT * FROM " + _table_name;
        if (_limit) {
            res += " LIMIT "
                + std::to_string(_offset == 0 ? 1 : _offset)
                + ',' + std::to_string(_limit);
        }
        return res;
    }
};