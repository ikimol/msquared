// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/core/math/vector2.hpp"

namespace msq {

/// Represents a 2-dimensional point
template <typename T>
struct Point2 {
    // constrain type to be standard layout
    static_assert(std::is_standard_layout_v<T>);

    /// Default constructor
    constexpr Point2() noexcept = default;

    /// Constructor with values
    constexpr Point2(T x, T y) noexcept
    : x(x)
    , y(y) {}

    /// Converting constructor
    template <typename U>
    constexpr explicit Point2(const Point2<U>& other) noexcept
    : x(other.x)
    , y(other.y) {}

    /// Constructor with a vector
    constexpr explicit Point2(const Vector2<T>& v) noexcept
    : x(v.x)
    , y(v.y) {}

    /// Set both the x and y components to zero
    void reset() { set(0, 0); }

    /// Set both the x and y components to the values
    void set(T p_x, T p_y) {
        x = p_x;
        y = p_y;
    }

    /// Get an element of the vector by index
    T& operator[](std::size_t index) { return const_cast<T&>(std::as_const(*this).operator[](index)); }

    /// Get an element of the vector by index
    const T& operator[](std::size_t index) const {
        assert(index < 2);
        const T* data[] = {&x, &y};
        return *data[index];
    }

    // conversion

    /// Conversion operator to a vector
    /* implicit */ operator Vector2<T>() const { return {x, y}; }

    // members

    T x = 0;
    T y = 0;
};

// common aliases

using Point2f = Point2<float>;
using Point2i = Point2<int>;
using Point2u = Point2<unsigned int>;

// operators

template <typename T>
bool operator==(const Point2<T>& lhs, const Point2<T>& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

template <typename T>
bool operator!=(const Point2<T>& lhs, const Point2<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
Point2<T> operator+(const Point2<T>& lhs, const Vector2<T>& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

template <typename T>
Vector2<T> operator-(const Point2<T>& lhs, const Point2<T>& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

template <typename T>
Point2<T> operator-(const Point2<T>& lhs, const Vector2<T>& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

template <typename T>
Point2<T>& operator+=(Point2<T>& lhs, const Vector2<T>& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

template <typename T>
Point2<T>& operator-=(Point2<T>& lhs, const Vector2<T>& rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}

} // namespace msq
