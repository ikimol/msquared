// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/core/assert.hpp"

#include <cmath>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace msq {

/// Represents a 2-dimensional vector
template <typename T>
struct Vector2 {
    // constrain type to be standard layout
    static_assert(std::is_standard_layout_v<T>);

    /// Default constructor
    constexpr Vector2() noexcept = default;

    /// Constructor with values
    constexpr Vector2(T x, T y) noexcept
    : x(x)
    , y(y) {}

    /// Converting constructor
    template <typename U>
    constexpr explicit Vector2(const Vector2<U>& other) noexcept
    : x(other.x)
    , y(other.y) {}

    /// Check if any of the x or y elements are zero
    bool is_zero() const { return x == 0 || y == 0; }

    /// Set both the x and y elements to zero
    void reset() { set(0, 0); }

    /// Set both the x and y elements to the values
    void set(T p_x, T p_y) {
        x = p_x;
        y = p_y;
    }

    /// Get an element of the vector by index
    T& operator[](std::size_t index) { return const_cast<T&>(std::as_const(*this).operator[](index)); }

    /// Get an element of the vector by index
    const T& operator[](std::size_t index) const {
        MSQ_ASSERT(index < 2, "element index out of range");
        const T* data[] = {&x, &y};
        return *data[index];
    }

    /// Calculate the dot product of the vectors
    T dot(const Vector2& other) { return x * other.x + y * other.y; }

    /// Get the squared length of the vector
    T length_sq() const { return x * x + y * y; }

    /// Get the length of the vector
    float length() const { return std::sqrtf(x * x + y * y); }

    // members

    T x = 0;
    T y = 0;
};

// common aliases

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
using Vector2u = Vector2<unsigned int>;

// operators

template <typename T>
Vector2<T> operator-(const Vector2<T>& v) {
    return {-v.x, -v.y};
}

template <typename T>
bool operator==(const Vector2<T>& lhs, const Vector2<T>& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

template <typename T>
bool operator!=(const Vector2<T>& lhs, const Vector2<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
Vector2<T> operator+(const Vector2<T>& lhs, const Vector2<T>& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

template <typename T>
Vector2<T> operator-(const Vector2<T>& lhs, const Vector2<T>& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

template <typename T>
Vector2<T> operator*(const Vector2<T>& v, T s) {
    return {v.x * s, v.y * s};
}

template <typename T>
Vector2<T> operator*(T s, const Vector2<T>& v) {
    return {s * v.x, s * v.y};
}

template <typename T>
Vector2<T> operator/(const Vector2<T>& v, T s) {
    return {v.x / s, v.y / s};
}

template <typename T>
Vector2<T>& operator+=(Vector2<T>& lhs, const Vector2<T>& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

template <typename T>
Vector2<T>& operator-=(Vector2<T>& lhs, const Vector2<T>& rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}

template <typename T>
Vector2<T>& operator*=(Vector2<T>& v, T s) {
    v.x *= s;
    v.y *= s;
    return v;
}

template <typename T>
Vector2<T>& operator/=(Vector2<T>& v, T s) {
    v.x /= s;
    v.y /= s;
    return v;
}

} // namespace msq
