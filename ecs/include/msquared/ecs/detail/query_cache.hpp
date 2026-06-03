// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/ecs/component_mask.hpp"

#include <unordered_map>
#include <vector>

namespace msq::ecs::detail {

class Archetype;
class ArchetypeRegistry;

class QueryCache {
public:
    explicit QueryCache(const ArchetypeRegistry& archetype_registry);

    void insert(ComponentMask mask, Archetype& new_archetype);

    const std::vector<Archetype*>& matching(ComponentMask mask);

private:
    const ArchetypeRegistry& m_archetype_registry;

    std::unordered_map<ComponentMask, std::vector<Archetype*>> m_cache;
};

} // namespace msq::ecs::detail
