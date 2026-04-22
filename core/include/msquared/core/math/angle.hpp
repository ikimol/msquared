// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/core/math/constants.hpp"

namespace msq {

class Angle {
    friend Angle degrees(float);
    friend Angle radians(float);

public:
    /// Default constructor
    constexpr Angle() noexcept = default;

    /// Get the value in degrees
    float as_degrees() const { return m_degrees; }

    /// Get the value in radians
    float as_radians() const { return m_degrees * pi / 180.f; }

private:
    // private value constructor
    constexpr explicit Angle(float degrees)
    : m_degrees(degrees) {}

private:
    float m_degrees = 0;
};

// factory functions

/// Create an angle from a value in degrees
inline Angle degrees(float deg) {
    return Angle(deg);
}

/// Create an angle from a value in radians
inline Angle radians(float rad) {
    return Angle(rad * 180.f / pi);
}

// operators

inline bool operator==(const Angle& lhs, const Angle& rhs) {
    return lhs.as_degrees() == rhs.as_degrees();
}

inline bool operator!=(const Angle& lhs, const Angle& rhs) {
    return lhs.as_degrees() != rhs.as_degrees();
}

inline bool operator<(const Angle& lhs, const Angle& rhs) {
    return lhs.as_degrees() < rhs.as_degrees();
}

inline bool operator<=(const Angle& lhs, const Angle& rhs) {
    return lhs.as_degrees() <= rhs.as_degrees();
}

inline bool operator>(const Angle& lhs, const Angle& rhs) {
    return lhs.as_degrees() > rhs.as_degrees();
}

inline bool operator>=(const Angle& lhs, const Angle& rhs) {
    return lhs.as_degrees() >= rhs.as_degrees();
}

inline Angle operator-(const Angle& angle) {
    return degrees(-angle.as_degrees());
}

inline Angle operator+(const Angle& lhs, const Angle& rhs) {
    return degrees(lhs.as_degrees() + rhs.as_degrees());
}

inline Angle& operator+=(Angle& lhs, const Angle& rhs) {
    lhs = lhs + rhs;
    return lhs;
}

inline Angle operator-(const Angle& lhs, const Angle& rhs) {
    return degrees(lhs.as_degrees() - rhs.as_degrees());
}

inline Angle& operator-=(Angle& lhs, const Angle& rhs) {
    lhs = lhs - rhs;
    return lhs;
}

inline Angle operator*(const Angle& lhs, float rhs) {
    return degrees(lhs.as_degrees() * rhs);
}

inline Angle operator*(float lhs, const Angle& rhs) {
    return rhs * lhs;
}

inline Angle& operator*=(Angle& lhs, float rhs) {
    lhs = lhs * rhs;
    return lhs;
}

inline Angle operator/(const Angle& lhs, float rhs) {
    return degrees(lhs.as_degrees() / rhs);
}

inline Angle& operator/=(Angle& lhs, float rhs) {
    lhs = lhs / rhs;
    return lhs;
}

} // namespace msq
