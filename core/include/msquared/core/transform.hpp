// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/core/math/angle.hpp"
#include "msquared/core/math/matrix3.hpp"
#include "msquared/core/math/point2.hpp"
#include "msquared/core/rect2.hpp"

namespace msq {

/// Represents a 2D transformation
class Transform {
public:
    /// Create an identity transform
    constexpr Transform() noexcept;

    /// Create a transform by setting the values of the matrix
    // clang-format off
    constexpr Transform(float n00, float n01, float n02,
                        float n10, float n11, float n12,
                        float n20, float n21, float n22);
    // clang-format on

    /// Create a transform by providing the matrix
    constexpr explicit Transform(Matrix3f matrix) noexcept;

    /// Get the underlying matrix
    const Matrix3f& matrix() const noexcept { return m_matrix; }

    /// Get the inverse transform
    Transform inverse() const noexcept { return Transform(m_matrix.inverse()); }

    // modifications

    /// Combine the current transform with a translation
    Transform& translate(float x, float y);

    /// Combine the current transform with a translation
    Transform& translate(const Vector2f& v);

    /// Combine the current transform with a rotation
    Transform& rotate(Angle angle);

    /// Combine the current transform with a rotation
    Transform& rotate(Angle angle, const Vector2f& center);

    /// Combine the current transform with a scaling
    Transform& scale(float x, float y);

    /// Combine the current transform with a scaling
    Transform& scale(float s);

    /// Combine the current transform with a scaling
    Transform& scale(const Vector2f& v);

    /// Combine the current transform with a scaling
    Transform& scale(float x, float y, const Vector2f& center);

    /// Combine the current transform with a scaling
    Transform& scale(float s, const Vector2f& center);

    /// Combine the current transform with a scaling
    Transform& scale(const Vector2f& v, const Vector2f& center);

    // usage

    /// Transform a point
    [[nodiscard]] Point2f apply_to(const Point2f& point) const;

    /// Transform a direction vector
    [[nodiscard]] Vector2f apply_to(const Vector2f& vector) const;

    /// Transform a rectangle
    [[nodiscard]] Rect2f apply_to(const Rect2f& rect) const;

    /// Combine the current transform with another
    Transform& combine(const Transform& other);

public:
    /// The identity transform
    static const Transform identity;

private:
    Matrix3f m_matrix;
};

// operators

[[nodiscard]] inline Transform operator*(Transform lhs, const Transform& rhs) {
    return lhs.combine(rhs);
}

inline Transform& operator*=(Transform& lhs, const Transform& rhs) {
    return lhs.combine(rhs);
}

template <typename T>
Point2<T> operator*(const Transform& t, const Point2<T>& p) {
    return t.apply_to(p);
}

template <typename T>
Vector2<T> operator*(const Transform& t, const Vector2<T>& v) {
    return t.apply_to(v);
}

inline bool operator==(const Transform& lhs, const Transform& rhs) {
    return lhs.matrix() == rhs.matrix();
}

inline bool operator!=(const Transform& lhs, const Transform& rhs) {
    return lhs.matrix() != rhs.matrix();
}

// implementation

constexpr Transform::Transform() noexcept
: m_matrix(1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f) {}

// clang-format off
constexpr Transform::Transform(float n00, float n01, float n02,
                               float n10, float n11, float n12,
                               float n20, float n21, float n22)
: m_matrix(n00, n01, n02, n10, n11, n12, n20, n21, n22) {}

// clang-format on

constexpr Transform::Transform(Matrix3f matrix) noexcept
: m_matrix(matrix) {}

} // namespace msq
