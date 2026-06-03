// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "archetype.hpp"

#include "msquared/ecs/component_mask.hpp"

#include <memory>
#include <vector>

namespace msq::ecs::detail {

class ComponentRegistry;
class EntityIndexMap;

class ArchetypeRegistry {
public:
    struct GetOrCreateResult {
        Archetype& archetype;
        bool inserted;
    };

public:
    ArchetypeRegistry(EntityIndexMap& entity_indices, const ComponentRegistry& component_registry);

    GetOrCreateResult get_or_create(const ComponentMask& mask);

    void collect(const ComponentMask& mask, std::vector<Archetype*>& archetypes) const;

    Archetype& empty_archetype() const;

private:
    EntityIndexMap& m_entity_indices;
    const ComponentRegistry& m_component_registry;

    std::vector<ComponentMask> m_masks;
    std::vector<std::unique_ptr<Archetype>> m_archetypes;
};

} // namespace msq::ecs::detail
