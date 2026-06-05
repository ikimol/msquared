// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/core/transform.hpp"

namespace msq {

const Transform Transform::identity;

Transform& Transform::translate(float x, float y) {
    // clang-format off
    Transform t(
        1.f, 0.f, x,
        0.f, 1.f, y,
        0.f, 0.f, 1.f
    );
    // clang-format on
    return combine(t);
}

Transform& Transform::translate(const Vector2f& v) {
    return translate(v.x, v.y);
}

Transform& Transform::rotate(Angle angle) {
    auto rad = angle.as_radians();
    auto cos = std::cos(rad);
    auto sin = std::sin(rad);
    // clang-format off
    Transform t(
        cos, -sin, 0.f,
        sin, cos,  0.f,
        0.f, 0.f,  1.f
    );
    // clang-format on
    return combine(t);
}

Transform& Transform::rotate(Angle angle, const Vector2f& center) {
    auto rad = angle.as_radians();
    auto cos = std::cos(rad);
    auto sin = std::sin(rad);
    // clang-format off
    Transform t(
        cos, -sin, center.x * (1 - cos) + center.y * sin,
        sin, cos,  center.y * (1 - cos) - center.x * sin,
        0.f, 0.f,  1.f
    );
    // clang-format on
    return combine(t);
}

Transform& Transform::scale(float x, float y) {
    // clang-format off
    Transform t(
        x,   0.f, 0.f,
        0.f, y,   0.f,
        0.f, 0.f, 1.f
    );
    // clang-format on
    return combine(t);
}

Transform& Transform::scale(float s) {
    return scale(s, s);
}

Transform& Transform::scale(const Vector2f& v) {
    return scale(v.x, v.y);
}

Transform& Transform::scale(float x, float y, const Vector2f& center) {
    // clang-format off
    Transform t(
        x,   0.f, center.x * (1 - x),
        0.f, y,   center.y * (1 - y),
        0.f, 0.f, 1.f
    );
    // clang-format on
    return combine(t);
}

Transform& Transform::scale(float s, const Vector2f& center) {
    return scale(s, s, center);
}

Transform& Transform::scale(const Vector2f& v, const Vector2f& center) {
    return scale(v.x, v.y, center);
}

Point2f Transform::apply_to(const Point2f& point) const {
    return m_matrix * point;
}

Vector2f Transform::apply_to(const Vector2f& vector) const {
    return m_matrix * vector;
}

Rect2f Transform::apply_to(const Rect2f& rect) const {
    // transform the 4 corners of the rectangle
    Vector2f points[] = {
        apply_to(Point2f(rect.x, rect.y)),
        apply_to(Point2f(rect.x + rect.w, rect.y)),
        apply_to(Point2f(rect.x + rect.w, rect.y + rect.h)),
        apply_to(Point2f(rect.x, rect.y + rect.h)),
    };

    auto l = points[0].x;
    auto t = points[0].y;
    auto r = points[0].x;
    auto b = points[0].y;

    // compute the bounding rectangle of the transformed points
    for (int i = 1; i < 4; ++i) {
        if (points[i].x < l) {
            l = points[i].x;
        } else if (points[i].x > r) {
            r = points[i].x;
        }
        if (points[i].y < t) {
            t = points[i].y;
        } else if (points[i].y > b) {
            b = points[i].y;
        }
    }

    return Rect2f(Point2f(l, t), Size2f(r - l, b - t));
}

Transform& Transform::combine(const Transform& other) {
    m_matrix = m_matrix * other.m_matrix;
    return *this;
}

} // namespace msq
