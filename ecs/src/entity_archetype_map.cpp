// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/ecs/detail/entity_archetype_map.hpp"

#include <msquared/core/assert.hpp>

namespace msq::ecs::detail {

Archetype& EntityArchetypeMap::archetype_of(EntityID entity_id) const {
    MSQ_ASSERT(m_archetypes[entity_id.index()] != nullptr, "entity does not belong to an archetype");
    return *m_archetypes[entity_id.index()];
}

void EntityArchetypeMap::update(EntityID entity_id, Archetype& archetype) {
    auto id_index = entity_id.index();
    ensure_capacity(id_index + 1);
    m_archetypes[id_index] = &archetype;
}

void EntityArchetypeMap::remove(EntityID entity_id) {
    MSQ_ASSERT(m_archetypes[entity_id.index()] != nullptr, "entity does not belong to an archetype");
    m_archetypes[entity_id.index()] = nullptr;
}

void EntityArchetypeMap::reserve(std::size_t min_capacity) {
    ensure_capacity(min_capacity);
}

void EntityArchetypeMap::ensure_capacity(std::size_t min_capacity) {
    if (min_capacity > m_archetypes.size()) {
        grow(min_capacity);
    }
}

void EntityArchetypeMap::grow(std::size_t min_capacity) {
    std::size_t new_capacity = 128;
    while (new_capacity < min_capacity) {
        new_capacity *= 2;
    }
    m_archetypes.resize(new_capacity, nullptr);
}

} // namespace msq::ecs::detail
