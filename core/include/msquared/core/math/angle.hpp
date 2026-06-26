// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/core/math/constants.hpp"

namespace msq {

class Angle {
    friend constexpr Angle degrees(float);
    friend constexpr Angle radians(float);

public:
    /// Default constructor
    constexpr Angle() noexcept = default;

    /// Get the value in degrees
    constexpr float as_degrees() const { return m_degrees; }

    /// Get the value in radians
    constexpr float as_radians() const { return m_degrees * pi / 180.f; }

private:
    // private value constructor
    constexpr explicit Angle(float degrees)
    : m_degrees(degrees) {}

private:
    float m_degrees = 0;
};

// factory functions

/// Create an angle from a value in degrees
constexpr Angle degrees(float deg) {
    return Angle(deg);
}

/// Create an angle from a value in radians
constexpr Angle radians(float rad) {
    return Angle(rad * 180.f / pi);
}

// operators

constexpr bool operator==(const Angle& lhs, const Angle& rhs) {
    return lhs.as_degrees() == rhs.as_degrees();
}

constexpr bool operator!=(const Angle& lhs, const Angle& rhs) {
    return lhs.as_degrees() != rhs.as_degrees();
}

constexpr bool operator<(const Angle& lhs, const Angle& rhs) {
    return lhs.as_degrees() < rhs.as_degrees();
}

constexpr bool operator<=(const Angle& lhs, const Angle& rhs) {
    return lhs.as_degrees() <= rhs.as_degrees();
}

constexpr bool operator>(const Angle& lhs, const Angle& rhs) {
    return lhs.as_degrees() > rhs.as_degrees();
}

constexpr bool operator>=(const Angle& lhs, const Angle& rhs) {
    return lhs.as_degrees() >= rhs.as_degrees();
}

constexpr Angle operator-(const Angle& angle) {
    return degrees(-angle.as_degrees());
}

constexpr Angle operator+(const Angle& lhs, const Angle& rhs) {
    return degrees(lhs.as_degrees() + rhs.as_degrees());
}

constexpr Angle& operator+=(Angle& lhs, const Angle& rhs) {
    lhs = lhs + rhs;
    return lhs;
}

constexpr Angle operator-(const Angle& lhs, const Angle& rhs) {
    return degrees(lhs.as_degrees() - rhs.as_degrees());
}

constexpr Angle& operator-=(Angle& lhs, const Angle& rhs) {
    lhs = lhs - rhs;
    return lhs;
}

constexpr Angle operator*(const Angle& lhs, float rhs) {
    return degrees(lhs.as_degrees() * rhs);
}

constexpr Angle operator*(float lhs, const Angle& rhs) {
    return rhs * lhs;
}

constexpr Angle& operator*=(Angle& lhs, float rhs) {
    lhs = lhs * rhs;
    return lhs;
}

constexpr Angle operator/(const Angle& lhs, float rhs) {
    return degrees(lhs.as_degrees() / rhs);
}

constexpr Angle& operator/=(Angle& lhs, float rhs) {
    lhs = lhs / rhs;
    return lhs;
}

// literals

namespace literals {

constexpr Angle operator""_deg(long double angle) {
    return degrees(static_cast<float>(angle));
}

constexpr Angle operator""_deg(unsigned long long angle) {
    return degrees(static_cast<float>(angle));
}

constexpr Angle operator""_rad(long double angle) {
    return radians(static_cast<float>(angle));
}

constexpr Angle operator""_rad(unsigned long long angle) {
    return radians(static_cast<float>(angle));
}

} // namespace literals
} // namespace msq
