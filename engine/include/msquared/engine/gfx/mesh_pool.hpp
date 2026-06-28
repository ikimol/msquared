// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/engine/gfx/mesh.hpp"
#include "msquared/engine/gfx/mesh_handle.hpp"

#include <vector>

namespace msq {

/// A pool used to assign and recycle mesh handles
class MeshPool {
public:
    /// Check if a mesh has been added
    bool contains(MeshHandle handle) const noexcept;

    /// Retrieve a previously added mesh
    const Mesh* get(MeshHandle handle) const noexcept;

    /// Add a mesh and get a handle
    [[nodiscard]] MeshHandle add(const Mesh* mesh);

    /// Remove a previously added mesh and recycle its ID
    void remove(MeshHandle handle);

private:
    std::vector<const Mesh*> m_meshes;
    std::vector<std::uint16_t> m_recycled;
};

} // namespace msq
