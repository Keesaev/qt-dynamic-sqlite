#pragma once

#include <string>
#include <vector>

#include <cassert>

class LikeQuery{
    std::vector<std::string> _filters;
    std::vector<std::string> _columnNames;

public:
    LikeQuery() = default;
    LikeQuery(std::vector<std::string> columnNames) : _columnNames(columnNames)
    {
    }
    /**
     * @brief addFilter - adds a filter at specified column
     * @param filter - ignored if empty
     * @param column - must be in range [0, columnNames)
     */
    LikeQuery& addFilter(std::string filter, int column){
        assert(column >= 0 && column < _columnNames.size());
        _filters[column] = filter;
        return *this;
    }
    /**
     * @brief addFilters - adds several filters where columns are vector indexes
     * @param filters - size must be same as columnCount, index is column id
     */
    LikeQuery& addFilters(std::vector<std::string> filters){
        assert(filters.size() == _columnNames.size());
        _filters = filters;
        return *this;
    }
    /**
     * @brief dump - returns statement that looks like " WHERE COLUMN_NAME LIKE '%PATTERN%' AND ..."
     */
    std::string dump() const
    {
        if(_filters.empty()){
            return "";
        }

        std::vector<std::string> queries;

        for(int i = 0; i < _filters.size(); i++){
            if(!_filters[i].empty()){
                queries.push_back(' ' + _columnNames[i] + " LIKE '%" + _filters[i] + "%'");
            }
        }

        std::string res;
        if(!queries.empty()){
            res += " WHERE" + queries.front();
            for(int i = 1; i < queries.size(); i++){
                res += " AND" + queries[i] + ' ';
            }
        }
        return res;
    }
};
