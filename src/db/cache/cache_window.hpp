#pragma once

class CacheWindow {
    int _id;
    int _size;
    int _left;
    int _right;
    bool _completed;

public:
    /**
     * @brief Construct an interval of specified \arg \c size with \arg \c id located in center
     * i.e calling CacheWindow(100, 10) will construct window interval [90, 110) (110 excluded)
     */
    CacheWindow(int id, int size = 500)
        : _id(id)
        , _size { size }
        , _left { std::max(id - _size / 2, 0) }
        , _right { id + _size / 2 }
        , _completed { false }
    {
    }
    /**
     * @brief check if id is contained in window interval
     */
    bool contains(int id) const
    {
        return (id < _right && id >= _left);
    }
    int id() const { return _id; }
    int left() const { return _left; }
    int right() const { return _right; }
    constexpr int size() const { return _size; }
    /**
     * @brief check if range present in window is completed
     * @return false until \c complete called
     */
    bool completed() const { return _completed; };
    /**
     * @brief call when caching is completed
     */
    void complete() { _completed = true; };
};
