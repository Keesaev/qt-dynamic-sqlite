#pragma once

class CacheWindow {
    int _size;
    int _left;
    int _right;

public:
    /**
     * @brief Construct an interval of specified \arg \c size with \arg \c id located in center
     * i.e calling CacheWindow(100, 10) will construct window interval [90, 110]
     */
    CacheWindow(int id, int size = 50000)
        : _size { size }
        , _left { (id - _size / 2) < 0 ? 0 : (id - _size / 2) }
        , _right { id + _size / 2 }
    {
    }
    /**
     * @brief check if id is contained in window interval
     */
    bool contains(int id) const
    {
        return (id <= _right && id >= _left);
    }
    int left() const { return _left; }
    int right() const { return _right; }
    constexpr int size() const { return _size; }
};