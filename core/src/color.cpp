// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/core/color.hpp"

#include <algorithm>

namespace msq {

Color Color::from_hex(std::uint32_t hex) {
    std::uint8_t r = hex >> 16u & 255u;
    std::uint8_t g = hex >> 8u & 255u;
    std::uint8_t b = hex >> 0u & 255u;
    return {r, g, b, 255};
}

Color Color::grayscale(std::uint8_t value) {
    return {value, value, value, 255};
}

std::uint32_t Color::to_hex() const {
    return (r << 16u) + (g << 8u) + b;
}

Color Color::with_alpha(float alpha) const {
    return {r, g, b, static_cast<std::uint8_t>(std::clamp(alpha, 0.f, 1.f) * 255.f)};
}

Color blend(Color lhs, const Color& rhs, float p) {
    p = std::clamp(p, 0.f, 1.f);
    auto p1 = 1.f - p;
    lhs.r = static_cast<std::uint8_t>(p1 * static_cast<float>(lhs.r) + p * static_cast<float>(rhs.r));
    lhs.g = static_cast<std::uint8_t>(p1 * static_cast<float>(lhs.g) + p * static_cast<float>(rhs.g));
    lhs.b = static_cast<std::uint8_t>(p1 * static_cast<float>(lhs.b) + p * static_cast<float>(rhs.b));
    lhs.a = static_cast<std::uint8_t>(p1 * static_cast<float>(lhs.a) + p * static_cast<float>(rhs.a));
    return lhs;
}

Color brighten(Color color, std::uint8_t amount) {
    color.r = static_cast<std::uint8_t>(std::min(255, color.r + amount));
    color.g = static_cast<std::uint8_t>(std::min(255, color.g + amount));
    color.b = static_cast<std::uint8_t>(std::min(255, color.b + amount));
    return color;
}

Color darken(Color color, std::uint8_t amount) {
    color.r = static_cast<std::uint8_t>(color.r > amount ? color.r - amount : 0);
    color.g = static_cast<std::uint8_t>(color.g > amount ? color.g - amount : 0);
    color.b = static_cast<std::uint8_t>(color.b > amount ? color.b - amount : 0);
    return color;
}

} // namespace msq
