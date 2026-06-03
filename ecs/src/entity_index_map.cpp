// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/ecs/detail/entity_index_map.hpp"

#include <msquared/core/assert.hpp>

namespace msq::ecs::detail {

std::size_t EntityIndexMap::index_of(EntityID entity_id) const {
    MSQ_ASSERT(m_indices[entity_id.index()] != invalid_index, "entity does not belong to an archetype");
    return m_indices[entity_id.index()];
}

void EntityIndexMap::update(EntityID entity_id, std::size_t index) {
    auto id_index = entity_id.index();
    ensure_capacity(id_index + 1);
    m_indices[id_index] = index;
}

void EntityIndexMap::remove(EntityID entity_id) {
    MSQ_ASSERT(m_indices[entity_id.index()] != invalid_index, "entity does not belong to an archetype");
    m_indices[entity_id.index()] = invalid_index;
}

void EntityIndexMap::reserve(std::size_t min_capacity) {
    ensure_capacity(min_capacity);
}

void EntityIndexMap::ensure_capacity(std::size_t min_capacity) {
    if (min_capacity > m_indices.size()) {
        grow(min_capacity);
    }
}

void EntityIndexMap::grow(std::size_t min_capacity) {
    std::size_t new_capacity = 128;
    while (new_capacity < min_capacity) {
        new_capacity *= 2;
    }
    m_indices.resize(new_capacity, invalid_index);
}

} // namespace msq::ecs::detail
