// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/ecs/detail/query_cache.hpp"

#include "msquared/ecs/detail/archetype_registry.hpp"

namespace msq::ecs::detail {

QueryCache::QueryCache(const ArchetypeRegistry& archetype_registry)
: m_archetype_registry(archetype_registry) {}

void QueryCache::insert(ComponentMask mask, Archetype& new_archetype) {
    for (auto& [query_mask, cached_archetypes] : m_cache) {
        if (mask.contains(query_mask)) {
            cached_archetypes.push_back(&new_archetype);
        }
    }
}

const std::vector<Archetype*>& QueryCache::matching(ComponentMask mask) {
    auto [it, inserted] = m_cache.try_emplace(mask);
    if (!inserted) {
        return it->second;
    }

    auto& archetypes = it->second;
    m_archetype_registry.collect(mask, archetypes);

    return archetypes;
}

} // namespace msq::ecs::detail
