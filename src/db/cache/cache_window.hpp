#pragma once

#include <algorithm>

#include <QObject>

class CacheWindow {
    int _id { 0 };
    int _size { 0 };
    int _left { 0 };
    int _right { 0 };
    bool _completed { false };

public:
    /**
     * @brief Construct an interval of specified \arg \c size with \arg \c id located in center
     * i.e calling CacheWindow(100, 10) will construct window interval [90, 110) (110 excluded)
     */
    CacheWindow(int id, int size = 1000 /*TODO SET DEFAULT SIZE TO LARGE NUMBER*/)
        : _id(id)
        , _size { size }
        , _left { std::max(id - _size / 2, 0) }
        , _right { id + _size / 2 }
        , _completed { false }
    {
    }
    CacheWindow() = default; // QMetaType limitation
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
     * @brief complete - call with received result to mark window as completed
     *  and shrink window if needed
     * @param result - container with size() method
     */
    template<typename Container>
    void complete(Container const& result) {
        static_assert(std::is_member_function_pointer
            <decltype(&Container::size)>::value, "Pass std container");
        _completed = true;
        _right = std::min(static_cast<std::size_t>(_right), result.size() + _left);
    };
};
