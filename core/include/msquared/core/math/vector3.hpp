// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/core/assert.hpp"

#include <cmath>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace msq {

/// Represents a 3-dimensional vector
template <typename T>
struct Vector3 {
    // constrain type to be standard layout
    static_assert(std::is_standard_layout_v<T>);

    /// Default constructor
    constexpr Vector3() noexcept = default;

    /// Constructor with values
    constexpr Vector3(T x, T y, T z) noexcept
    : x(x)
    , y(y)
    , z(z) {}

    /// Converting constructor
    template <typename U>
    constexpr explicit Vector3(const Vector3<U>& other) noexcept
    : x(other.x)
    , y(other.y)
    , z(other.z) {}

    /// Check if any of the x or y elements are zero
    bool is_zero() const { return x == 0 || y == 0 || z == 0; }

    /// Set both the x and y elements to zero
    void reset() { set(0, 0, 0); }

    /// Set both the x and y elements to the values
    void set(T p_x, T p_y, T p_z) {
        x = p_x;
        y = p_y;
        z = p_z;
    }

    /// Get an element of the vector by index
    T& operator[](std::size_t index) { return const_cast<T&>(std::as_const(*this).operator[](index)); }

    /// Get an element of the vector by index
    const T& operator[](std::size_t index) const {
        MSQ_ASSERT(index < 3, "element index out of range");
        const T* data[] = {&x, &y, &z};
        return *data[index];
    }

    /// Get the squared length of the vector
    T length_sq() const { return x * x + y * y + z * z; }

    /// Get the length of the vector
    float length() const { return std::sqrtf(x * x + y * y + z * z); }

    // members

    T x = 0;
    T y = 0;
    T z = 0;
};

// common aliases

using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;
using Vector3u = Vector3<unsigned int>;

// operators

template <typename T>
T dot(const Vector3<T>& lhs, const Vector3<T>& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

template <typename T>
Vector3<T> cross(const Vector3<T>& lhs, const Vector3<T>& rhs) {
    return {lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x};
}

template <typename T>
Vector3<T> operator-(const Vector3<T>& v) {
    return {-v.x, -v.y, -v.z};
}

template <typename T>
bool operator==(const Vector3<T>& lhs, const Vector3<T>& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

template <typename T>
bool operator!=(const Vector3<T>& lhs, const Vector3<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
Vector3<T> operator+(const Vector3<T>& lhs, const Vector3<T>& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

template <typename T>
Vector3<T> operator-(const Vector3<T>& lhs, const Vector3<T>& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

template <typename T>
Vector3<T> operator*(const Vector3<T>& v, T s) {
    return {v.x * s, v.y * s, v.z * s};
}

template <typename T>
Vector3<T> operator*(T s, const Vector3<T>& v) {
    return {s * v.x, s * v.y, s * v.z};
}

template <typename T>
Vector3<T> operator/(const Vector3<T>& v, T s) {
    return {v.x / s, v.y / s, v.z / s};
}

template <typename T>
Vector3<T>& operator+=(Vector3<T>& lhs, const Vector3<T>& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    return lhs;
}

template <typename T>
Vector3<T>& operator-=(Vector3<T>& lhs, const Vector3<T>& rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
    return lhs;
}

template <typename T>
Vector3<T>& operator*=(Vector3<T>& v, T s) {
    v.x *= s;
    v.y *= s;
    v.z *= s;
    return v;
}

template <typename T>
Vector3<T>& operator/=(Vector3<T>& v, T s) {
    v.x /= s;
    v.y /= s;
    v.z /= s;
    return v;
}

} // namespace msq
