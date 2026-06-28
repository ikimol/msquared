// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include <cstdint>

namespace msq {

/// An opaque handle for a loaded texture
struct TextureHandle {
    std::uint16_t id = invalid_id;

    /// The invalid texture handle
    static constexpr std::uint16_t invalid_id = -1;

    /// Check if the texture handle is valid
    bool is_valid() const { return id != invalid_id; }

    /// Check if the texture handle is valid
    explicit operator bool() const { return is_valid(); }
};

inline bool operator==(const TextureHandle& lhs, const TextureHandle& rhs) {
    return lhs.id == rhs.id;
}

inline bool operator!=(const TextureHandle& lhs, const TextureHandle& rhs) {
    return !(lhs == rhs);
}

inline bool operator<(const TextureHandle& lhs, const TextureHandle& rhs) {
    return lhs.id < rhs.id;
}

} // namespace msq
