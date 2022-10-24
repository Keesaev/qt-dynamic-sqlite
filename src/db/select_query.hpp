#pragma once

#include <string>
#include <vector>
#include <cassert>

class SelectQuery {
    std::string _tableName;
    // TODO:
    // ORDER BY ROWID DESC/ASC ?
    int _offset = -1;
    int _limit = -1;
    std::vector<std::string> _filters;
    std::vector<std::string> _columnNames;

public:
    /**
     * @brief Constructs SQLite 'select *' statement with specified
     *  table name, offset and limit
     * @param assert not empty
     */
    SelectQuery(std::string tableName)
        : _tableName(tableName)
    {
        assert(!tableName.empty());
    }
    /**
     * @brief adds 'LIMIT' logic, if offset is not set, defaults to 0
     */
    SelectQuery& limit(int l){
        _limit = l;
        return *this;
    }
    /**
     * @brief adds 'OFFSET' logic, if LIMIT is not set, defaults to 1
     */
    SelectQuery& offset(int o){
        _offset = o;
        return *this;
    }
    /**
     * @brief set tablename
     */
    SelectQuery& table_name(int o){
        _offset = o;
        return *this;
    }
    // TODO ESCAPE CHARACTERS
    /**
     * @brief set '%like%' wildcard
     * @param filters - string filters, size must be same as @param columnNames, empty strings will be ignored
     * @param columnNames - column names
     */
    SelectQuery& like(std::vector<std::string> filters,
                      std::vector<std::string> columnNames){
        assert(filters.size() == columnNames.size());
        _filters = filters;
        _columnNames = columnNames;
        return *this;
    }
    /**
     * @brief returns constructed query containing offset and limit if specified
     * doesn't guarantee correctness if tableName is incorrect
     */
    operator std::string() const
    {
        auto res = "SELECT * FROM " + _tableName;

        // LIKE
        if(!_filters.empty()){
            std::vector<std::string> queries;

            for(int i = 0; i < _filters.size(); i++){
                if(!_filters[i].empty()){
                    queries.push_back(' ' + _columnNames[i] + "LIKE %" + _filters[i] + '%');
                }
            }

            if(!queries.empty()){
                res += " WHERE" + queries.front();
                for(int i = 1; i < queries.size(); i++){
                    res += " AND" + queries[i] + ' ';
                }
            }
        }

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
    // getters
    int limit() const{
        return std::max(_limit, 1);
    }
    std::string tableName() const{
        return _tableName;
    }
};
