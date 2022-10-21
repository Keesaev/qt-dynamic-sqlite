#pragma once

#include <string>

class SelectQuery {
    std::string _tableName;
    // TODO:
    // ORDER BY ROWID DESC/ASC
    // WHERE <colname> LIKE *<pattern>*
    int _offset = -1;
    int _limit = -1;

public:
    SelectQuery(std::string tableName)
        : _tableName(tableName)
    {
    }
    int limit() const{
        return std::max(_limit, 1);
    }
    SelectQuery& limit(int l){
        _limit = l;
        return *this;
    }
    SelectQuery& offset(int o){
        _offset = o;
        return *this;
    }
    SelectQuery& table_name(int o){
        _offset = o;
        return *this;
    }
    operator std::string() const
    {
        auto res = "SELECT * FROM " + _tableName;
        if (_limit >= 0) {
            res += " LIMIT "
                + std::to_string(std::max(_offset, 0))
                + ',' + std::to_string(_limit);
        }
        else if(_offset >= 0){
            res += " LIMIT "
                + std::to_string(_offset)
                + ',' + std::to_string(std::max(_limit, 1));
        }
        return res;
    }
};
