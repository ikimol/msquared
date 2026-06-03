// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/ecs/entity_id.hpp"

#include <vector>

namespace msq::ecs::detail {

class Archetype;

class EntityArchetypeMap {
public:
    Archetype& archetype_of(EntityID entity_id) const;

    void update(EntityID entity_id, Archetype& archetype);

    void remove(EntityID entity_id);

    void reserve(std::size_t min_capacity);

private:
    void ensure_capacity(std::size_t min_capacity);
    void grow(std::size_t min_capacity);

private:
    std::vector<Archetype*> m_archetypes;
};

} // namespace msq::ecs::detail
