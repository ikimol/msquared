// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include <cstdint>

namespace msq {

/// An opaque handle for a mesh
struct MeshHandle {
    std::uint16_t id = invalid_id;

    /// The invalid mesh handle
    static constexpr std::uint16_t invalid_id = -1;

    /// Check if the mesh handle is valid
    bool is_valid() const { return id != invalid_id; }

    /// Check if the mesh handle is valid
    explicit operator bool() const { return is_valid(); }
};

inline bool operator==(const MeshHandle& lhs, const MeshHandle& rhs) {
    return lhs.id == rhs.id;
}

inline bool operator!=(const MeshHandle& lhs, const MeshHandle& rhs) {
    return !(lhs == rhs);
}

inline bool operator<(const MeshHandle& lhs, const MeshHandle& rhs) {
    return lhs.id < rhs.id;
}

} // namespace msq
