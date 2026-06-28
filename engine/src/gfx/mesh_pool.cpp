// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/engine/gfx/mesh_pool.hpp"

#include <msquared/core/assert.hpp>

#include <limits>

namespace msq {

bool MeshPool::contains(MeshHandle handle) const noexcept {
    return handle.id < m_meshes.size() && m_meshes[handle.id] != nullptr;
}

const Mesh* MeshPool::get(MeshHandle handle) const noexcept {
    MSQ_ASSERT(contains(handle), "invalid mesh handle");
    return m_meshes[handle.id];
}

MeshHandle MeshPool::add(const Mesh* mesh) {
    MSQ_ASSERT(m_meshes.size() < std::numeric_limits<std::uint16_t>::max(), "mesh pool is full");
    std::uint16_t id;
    if (!m_recycled.empty()) {
        id = m_recycled.back();
        m_meshes[id] = mesh;
        m_recycled.pop_back();
    } else {
        id = m_meshes.size();
        m_meshes.push_back(mesh);
    }
    return MeshHandle {id};
}

void MeshPool::remove(MeshHandle handle) {
    MSQ_ASSERT(contains(handle), "invalid mesh handle");
    m_meshes[handle.id] = nullptr;
    m_recycled.push_back(handle.id);
}

} // namespace msq
