// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/core/math/vector2.hpp"

namespace msq {

/// Represents a 2-dimensional size
template <typename T>
struct Size2 {
    // constrain type to be standard layout
    static_assert(std::is_standard_layout_v<T>);

    /// Default constructor
    constexpr Size2() noexcept = default;

    /// Constructor with values
    constexpr Size2(T w, T h) noexcept
    : w(w)
    , h(h) {}

    /// Converting constructor
    template <typename U>
    constexpr explicit Size2(const Size2<U>& other) noexcept
    : w(other.w)
    , h(other.h) {}

    /// Constructor with a vector
    constexpr explicit Size2(const Vector2<T>& v) noexcept
    : w(v.x)
    , h(v.y) {}

    /// Check if any of the x or y components are zero
    bool is_zero() const { return w == 0 || h == 0; }

    /// Set both the x and y components to zero
    void reset() { set(0, 0); }

    /// Set both the x and y components to the values
    void set(T p_w, T p_h) {
        w = p_w;
        h = p_h;
    }

    /// Get an element of the size by index
    T& operator[](std::size_t index) { return const_cast<T&>(std::as_const(*this).operator[](index)); }

    /// Get an element of the size by index
    const T& operator[](std::size_t index) const {
        MSQ_ASSERT(index < 2, "element index out of range");
        const T* data[] = {&w, &h};
        return *data[index];
    }

    // conversion

    /// Conversion operator to a vector
    /* implicit */ operator Vector2<T>() const { return {w, h}; }

    // members

    T w = 0;
    T h = 0;
};

// common aliases

using Size2f = Size2<float>;
using Size2i = Size2<int>;
using Size2u = Size2<unsigned int>;

// operators

template <typename T>
bool operator==(const Size2<T>& lhs, const Size2<T>& rhs) {
    return lhs.w == rhs.w && lhs.h == rhs.h;
}

template <typename T>
bool operator!=(const Size2<T>& lhs, const Size2<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
bool operator<(const Size2<T>& lhs, const Size2<T>& rhs) {
    return lhs.w < rhs.w || (lhs.w == rhs.w && lhs.h < rhs.h);
}

template <typename T>
bool operator>(const Size2<T>& lhs, const Size2<T>& rhs) {
    return rhs < lhs;
}

template <typename T>
bool operator<=(const Size2<T>& lhs, const Size2<T>& rhs) {
    return !(rhs < lhs);
}

template <typename T>
bool operator>=(const Size2<T>& lhs, const Size2<T>& rhs) {
    return !(lhs < rhs);
}

template <typename T>
Size2<T> operator*(const Size2<T>& size, T value) {
    return {size.w * value, size.h * value};
}

template <typename T>
Size2<T> operator*(T value, const Size2<T>& size) {
    return size * value;
}

template <typename T>
Size2<T> operator/(const Size2<T>& size, T value) {
    return {size.w / value, size.h / value};
}

template <typename T>
Size2<T>& operator*=(Size2<T>& size, T value) {
    size.w *= value;
    size.h *= value;
    return size;
}

template <typename T>
Size2<T>& operator/=(Size2<T>& size, T value) {
    size.w /= value;
    size.h /= value;
    return size;
}

} // namespace msq
