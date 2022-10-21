#pragma once

#include <algorithm>

class Window{
    int _left;
    int _right;
    static constexpr int _size { 1000 };

public:
    Window(int id)
        : _left { std::max(0, id - _size / 2) }
        , _right { id + _size / 2 }
    {}

    bool contains(int id){
        return id >= _left && id < _right;
    }
    int left() const { return _left; }
    int right() const { return _right; }
};
