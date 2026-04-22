// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include <cstdint>

namespace msq {

/// Represents a 32-bit RGBA color
struct Color {
    /// Create a default (black) color
    constexpr Color() noexcept = default;

    /// Create a color with the values of its channels
    constexpr Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255) noexcept
    : r(r)
    , g(g)
    , b(b)
    , a(a) {}

    /// Create a color from an RGB hexadecimal literal
    /// \note Does not parse alpha channel value
    static Color from_hex(std::uint32_t hex);

    /// Create a grayscale color with the given value
    static Color grayscale(std::uint8_t value);

    /// Convert the color to its RGB hexadecimal value
    std::uint32_t to_hex() const;

    /// Create a new color with modified alpha channel value
    ///
    /// \param alpha The alpha value in the range [0, 1]
    [[nodiscard]] Color with_alpha(float alpha) const;

    std::uint8_t r = 0;
    std::uint8_t g = 0;
    std::uint8_t b = 0;
    std::uint8_t a = 255;
};

// helpers

/// Create a new color by blending two colors
///
/// \note If p = 0, returns \p lhs, if p = 1 returns \p rhs.
Color blend(Color lhs, const Color& rhs, float p);

/// Create a new color by brightening one
Color brighten(Color color, std::uint8_t amount);

/// Create a new color by darkening one
Color darken(Color color, std::uint8_t amount);

// operators

inline bool operator==(const Color& lhs, const Color& rhs) {
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
}

inline bool operator!=(const Color& lhs, const Color& rhs) {
    return !(lhs == rhs);
}

} // namespace msq
