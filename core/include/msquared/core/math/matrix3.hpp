// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/core/math/point2.hpp"
#include "msquared/core/math/vector2.hpp"
#include "msquared/core/math/vector3.hpp"

#include <array>
#include <cstddef>
#include <type_traits>

namespace msq {

/// Represents a 3-by-3 matrix
template <typename T>
struct Matrix3 {
    // constrain type to be standard layout
    static_assert(std::is_standard_layout_v<T>);

    /// Default constructor
    constexpr Matrix3() noexcept = default;

    /// Constructor with values
    constexpr Matrix3(T n00, T n01, T n02, T n10, T n11, T n12, T n20, T n21, T n22);

    /// Constructor with column vectors
    constexpr Matrix3(const Vector3<T>& a, const Vector3<T>& b, const Vector3<T>& c);

    /// Return a matrix with all elements set to zero
    static constexpr Matrix3 zero() noexcept { return {0, 0, 0, 0, 0, 0, 0, 0, 0}; }

    /// Return the identity matrix
    static constexpr Matrix3 identity() noexcept { return {1, 0, 0, 0, 1, 0, 0, 0, 1}; }

    /// Get the determinant of the matrix
    T determinant() const;

    /// Get the inverse of the matrix
    Matrix3 inverse() const;

    /// Get a value of the matrix at row \p i and column \p j
    T& operator()(std::size_t i, std::size_t j) { return data[j][i]; }

    /// Get a value of the matrix at row \p i and column \p j
    const T& operator()(std::size_t i, std::size_t j) const { return data[j][i]; }

    /// Get a column of the matrix as a vector
    Vector3<T>& operator[](std::size_t j) { return *reinterpret_cast<Vector3<T>*>(data[j].data()); }

    /// Get a column of the matrix as a vector
    const Vector3<T>& operator[](std::size_t j) const { return *reinterpret_cast<const Vector3<T>*>(data[j].data()); }

    // members

    // column major representation
    std::array<std::array<T, 3>, 3> data = {};
};

// common aliases

using Matrix3f = Matrix3<float>;
using Matrix3i = Matrix3<int>;
using Matrix3u = Matrix3<unsigned int>;

// operators

template <typename T>
bool operator==(const Matrix3<T>& lhs, const Matrix3<T>& rhs) {
    return lhs.data == rhs.data;
}

template <typename T>
bool operator!=(const Matrix3<T>& lhs, const Matrix3<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
Matrix3<T> operator*(const Matrix3<T>& lhs, const Matrix3<T>& rhs) {
    return {
        lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0),
        lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1),
        lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2),
        lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0),
        lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1),
        lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2),
        lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0) + lhs(2, 2) * rhs(2, 0),
        lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1),
        lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2) + lhs(2, 2) * rhs(2, 2),
    };
}

template <typename T>
Point2<T> operator*(const Matrix3<T>& m, const Point2<T>& p) {
    // translation is applied (w = 1)
    return {
        m(0, 0) * p.x + m(0, 1) * p.y + m(0, 2),
        m(1, 0) * p.x + m(1, 1) * p.y + m(1, 2),
    };
}

template <typename T>
Vector2<T> operator*(const Matrix3<T>& m, const Vector2<T>& v) {
    // translation is ignored (w = 0)
    return {
        m(0, 0) * v.x + m(0, 1) * v.y,
        m(1, 0) * v.x + m(1, 1) * v.y,
    };
}

template <typename T>
Vector3<T> operator*(const Matrix3<T>& m, const Vector3<T>& v) {
    return {
        m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z,
        m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z,
        m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z,
    };
}

// implementation

template <typename T>
constexpr Matrix3<T>::Matrix3(T n00, T n01, T n02, T n10, T n11, T n12, T n20, T n21, T n22) {
    // clang-format off
    data[0][0] = n00; data[0][1] = n10; data[0][2] = n20;
    data[1][0] = n01; data[1][1] = n11; data[1][2] = n21;
    data[2][0] = n02; data[2][1] = n12; data[2][2] = n22;
    // clang-format on
}

template <typename T>
constexpr Matrix3<T>::Matrix3(const Vector3<T>& a, const Vector3<T>& b, const Vector3<T>& c) {
    // clang-format off
    data[0][0] = a.x; data[0][1] = a.y; data[0][2] = a.z;
    data[1][0] = b.x; data[1][1] = b.y; data[1][2] = b.z;
    data[2][0] = c.x; data[2][1] = c.y; data[2][2] = c.z;
    // clang-format on
}

template <typename T>
T Matrix3<T>::determinant() const {
    // clang-format off
    return data[0][0] * (data[1][1] * data[2][2] - data[2][1] * data[1][2])
         + data[1][0] * (data[2][1] * data[0][2] - data[0][1] * data[2][2])
         + data[2][0] * (data[0][1] * data[1][2] - data[1][1] * data[0][2]);
    // clang-format on
}

template <typename T>
Matrix3<T> Matrix3<T>::inverse() const {
    auto& a = *reinterpret_cast<const Vector3<T>*>(data[0].data());
    auto& b = *reinterpret_cast<const Vector3<T>*>(data[1].data());
    auto& c = *reinterpret_cast<const Vector3<T>*>(data[2].data());

    auto r0 = b.cross(c);
    auto r1 = c.cross(a);
    auto r2 = a.cross(b);

    auto inv_det = T(1) / r2.dot(c);

    // clang-format off
    return {
        r0.x * inv_det, r0.y * inv_det, r0.z * inv_det,
        r1.x * inv_det, r1.y * inv_det, r1.z * inv_det,
        r2.x * inv_det, r2.y * inv_det, r2.z * inv_det,
    };
    // clang-format on
}

} // namespace msq
