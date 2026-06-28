// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/core/math/point2.hpp"
#include "msquared/core/size2.hpp"

#include <algorithm>
#include <optional>
#include <type_traits>

namespace msq {

/// Represents a 2-dimensional rectangle
template <typename T>
struct Rect2 {
    // constrain type to be standard layout
    static_assert(std::is_standard_layout_v<T>);

    /// Default constructor
    constexpr Rect2() noexcept = default;

    /// Constructor with values
    constexpr Rect2(T x, T y, T w, T h) noexcept
    : x(x)
    , y(y)
    , w(w)
    , h(h) {}

    /// Converting constructor
    template <typename U>
    constexpr explicit Rect2(const Rect2<U>& other) noexcept
    : x(other.x)
    , y(other.y)
    , w(other.w)
    , h(other.h) {}

    /// Constructor with a position and size
    constexpr explicit Rect2(const Point2<T>& p, const Size2<T>& s) noexcept
    : x(p.x)
    , y(p.y)
    , w(s.w)
    , h(s.h) {}

    /// Constructor with min and max points
    constexpr explicit Rect2(const Point2<T>& min, const Point2<T>& max) noexcept
    : x(min.x)
    , y(min.y)
    , w(max.x - min.x)
    , h(max.y - min.y) {}

    /// Get the center point of the rectangle
    Point2<T> center() const { return {x + w / T(2), y + h / T(2)}; }

    /// Get the position of the rectangle
    const Point2<T>& position() const { return *reinterpret_cast<const Point2<T>*>(&x); }

    /// Set the position of the rectangle
    void set_position(const Point2<T>& position) { set_position(position.x, position.y); }

    /// Set the position of the rectangle
    void set_position(T p_x, T p_y) {
        x = p_x;
        y = p_y;
    }

    /// Get the size of the rectangle
    const Size2<T>& size() const { return *reinterpret_cast<const Size2<T>*>(&w); }

    /// Set the size of the rectangle
    void set_size(const Size2<T>& size) { set_size(size.w, size.h); }

    /// Set the size of the rectangle
    void set_size(T p_w, T p_h) {
        w = p_w;
        h = p_h;
    }

    /// Set both the position and the size to zero
    void reset() {
        x = T(0);
        y = T(0);
        w = T(0);
        h = T(0);
    }

    // extremes

    T min_x() const { return std::min(x, x + w); }

    T max_x() const { return std::max(x, x + w); }

    T min_y() const { return std::min(y, y + h); }

    T max_y() const { return std::max(y, y + h); }

    Point2<T> min() const { return {min_x(), min_y()}; }

    Point2<T> max() const { return {max_x(), max_y()}; }

    /// Check whether the point is contained
    bool contains(T p_x, T p_y) { return (p_x >= min_x()) && (p_x < max_x()) && (p_y >= min_y()) && (p_y < max_y()); }

    /// Check whether the point is contained
    bool contains(const Point2<T>& point) { return contains(point.x, point.y); }

    /// Get the intersection of two rectangles
    std::optional<Rect2> intersection(const Rect2& other) {
        // compute the intersection boundaries
        auto inter_min_x = std::max(min_x(), other.min_x());
        auto inter_max_x = std::min(max_x(), other.max_x());
        auto inter_min_y = std::max(min_y(), other.min_y());
        auto inter_max_y = std::min(max_y(), other.max_y());

        // check if the intersection has a positive non-zero area
        if ((inter_min_x < inter_max_x) && (inter_min_y < inter_max_y)) {
            return Rect2(inter_min_x, inter_min_y, inter_max_x - inter_min_x, inter_max_y - inter_min_y);
        }

        return std::nullopt;
    }

    /// Check if the two rectangles intersect
    bool intersects(const Rect2& other) { return intersection(other).has_value(); }

    // members

    T x = 0;
    T y = 0;
    T w = 0;
    T h = 0;
};

// common aliases

using Rect2f = Rect2<float>;
using Rect2i = Rect2<int>;
using Rect2u = Rect2<unsigned int>;

// operators

template <typename T>
bool operator==(const Rect2<T>& lhs, const Rect2<T>& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.w == rhs.w && lhs.h == rhs.h;
}

template <typename T>
bool operator!=(const Rect2<T>& lhs, const Rect2<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
Rect2<T> operator+(const Rect2<T>& lhs, const Vector2<T>& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.w, lhs.h};
}

template <typename T>
Rect2<T> operator-(const Rect2<T>& lhs, const Vector2<T>& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.w, lhs.h};
}

template <typename T>
Rect2<T>& operator+=(Rect2<T>& lhs, const Vector2<T>& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

template <typename T>
Rect2<T>& operator-=(Rect2<T>& lhs, const Vector2<T>& rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}

} // namespace msq
