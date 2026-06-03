// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/ecs/detail/archetype_registry.hpp"

namespace msq::ecs::detail {

ArchetypeRegistry::ArchetypeRegistry(EntityIndexMap& entity_indices, const ComponentRegistry& component_registry)
: m_entity_indices(entity_indices)
, m_component_registry(component_registry) {
    m_masks.emplace_back();
    m_archetypes.push_back(std::make_unique<Archetype>(m_entity_indices, m_component_registry, ComponentMask {}));
}

ArchetypeRegistry::GetOrCreateResult ArchetypeRegistry::get_or_create(const ComponentMask& mask) {
    for (std::size_t i = 0; i < m_masks.size(); ++i) {
        if (m_masks[i] == mask) {
            return {*m_archetypes[i], false};
        }
    }
    m_masks.push_back(mask);
    m_archetypes.push_back(std::make_unique<Archetype>(m_entity_indices, m_component_registry, mask));
    return {*m_archetypes.back(), true};
}

void ArchetypeRegistry::collect(const ComponentMask& mask, std::vector<Archetype*>& archetypes) const {
    for (std::size_t i = 0; i < m_masks.size(); ++i) {
        if (m_masks[i].contains(mask)) {
            archetypes.push_back(m_archetypes[i].get());
        }
    }
}

Archetype& ArchetypeRegistry::empty_archetype() const {
    return *m_archetypes[0];
}

} // namespace msq::ecs::detail
