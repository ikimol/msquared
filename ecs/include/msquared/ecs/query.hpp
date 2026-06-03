// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/ecs/component_type.hpp"
#include "msquared/ecs/detail/archetype.hpp"
#include "msquared/ecs/entity_id.hpp"

#include <tuple>
#include <vector>

namespace msq::ecs {

/// Used to iterate entities with a given set of components
template <typename... Cs>
class ComponentQuery {
    friend class World;

public:
    class Iterator {
    public:
        using ValueType = std::tuple<std::add_lvalue_reference_t<Cs>...>;

    public:
        Iterator(const std::vector<detail::Archetype*>& archetypes, std::size_t archetype_index);

        ValueType operator*() const;

        Iterator& operator++();

        bool operator==(const Iterator& other) const;

        bool operator!=(const Iterator& other) const;

    private:
        void store_base_ptrs();

    private:
        const std::vector<detail::Archetype*>& m_archetypes;
        std::size_t m_archetype_index;
        std::size_t m_entity_index = 0;
        std::tuple<Cs*...> m_components;
    };

public:
    Iterator begin() const { return {m_archetypes, index_skipping_empty_archetypes()}; }

    Iterator end() const { return {m_archetypes, m_archetypes.size()}; }

private:
    std::size_t index_skipping_empty_archetypes() const;

private:
    explicit ComponentQuery(const std::vector<detail::Archetype*>& archetypes)
    : m_archetypes(archetypes) {}

    const std::vector<detail::Archetype*>& m_archetypes;
};

/// Used to iterate entities with a given set of components
template <typename... Cs>
class EntityQuery {
    friend class World;

public:
    class Iterator {
    public:
        using ValueType = std::tuple<EntityID, std::add_lvalue_reference_t<Cs>...>;

    public:
        Iterator(const std::vector<detail::Archetype*>& archetypes, std::size_t archetype_index);

        ValueType operator*() const;

        Iterator& operator++();

        bool operator==(const Iterator& other) const;

        bool operator!=(const Iterator& other) const;

    private:
        void store_base_ptrs();

    private:
        const std::vector<detail::Archetype*>& m_archetypes;
        std::size_t m_archetype_index;
        std::size_t m_entity_index = 0;
        const EntityID* m_entity_ids = nullptr;
        std::tuple<Cs*...> m_components;
    };

public:
    Iterator begin() const { return {m_archetypes, index_skipping_empty_archetypes()}; }

    Iterator end() const { return {m_archetypes, m_archetypes.size()}; }

private:
    std::size_t index_skipping_empty_archetypes() const;

private:
    explicit EntityQuery(const std::vector<detail::Archetype*>& archetypes)
    : m_archetypes(archetypes) {}

    const std::vector<detail::Archetype*>& m_archetypes;
};

// implementation

// ComponentQuery

template <typename... Cs>
ComponentQuery<Cs...>::Iterator::Iterator(const std::vector<detail::Archetype*>& archetypes,
                                          std::size_t archetype_index)
: m_archetypes(archetypes)
, m_archetype_index(archetype_index) {
    if (m_archetype_index < m_archetypes.size()) {
        store_base_ptrs();
    }
}

template <typename... Cs>
void ComponentQuery<Cs...>::Iterator::store_base_ptrs() {
    auto* archetype = m_archetypes[m_archetype_index];
    m_components = std::make_tuple(static_cast<Cs*>(archetype->components(component_type<Cs>()))...);
}

template <typename... Cs>
typename ComponentQuery<Cs...>::Iterator::ValueType ComponentQuery<Cs...>::Iterator::operator*() const {
    return std::forward_as_tuple(*(std::get<Cs*>(m_components) + m_entity_index)...);
}

template <typename... Cs>
typename ComponentQuery<Cs...>::Iterator& ComponentQuery<Cs...>::Iterator::operator++() {
    ++m_entity_index;
    while (m_archetype_index < m_archetypes.size() && m_entity_index >= m_archetypes[m_archetype_index]->count()) {
        ++m_archetype_index;
        if (m_archetype_index < m_archetypes.size()) {
            store_base_ptrs();
        }
        m_entity_index = 0;
    }
    return *this;
}

template <typename... Cs>
bool ComponentQuery<Cs...>::Iterator::operator==(const Iterator& other) const {
    return m_archetype_index == other.m_archetype_index && m_entity_index == other.m_entity_index;
}

template <typename... Cs>
bool ComponentQuery<Cs...>::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

template <typename... Cs>
std::size_t ComponentQuery<Cs...>::index_skipping_empty_archetypes() const {
    std::size_t index = 0;
    while (index < m_archetypes.size() && m_archetypes[index]->is_empty()) {
        ++index;
    }
    return index;
}

// EntityQuery

template <typename... Cs>
EntityQuery<Cs...>::Iterator::Iterator(const std::vector<detail::Archetype*>& archetypes, std::size_t archetype_index)
: m_archetypes(archetypes)
, m_archetype_index(archetype_index) {
    if (m_archetype_index < m_archetypes.size()) {
        store_base_ptrs();
    }
}

template <typename... Cs>
void EntityQuery<Cs...>::Iterator::store_base_ptrs() {
    auto* archetype = m_archetypes[m_archetype_index];
    m_entity_ids = archetype->entity_ids();
    m_components = std::make_tuple(static_cast<Cs*>(archetype->components(component_type<Cs>()))...);
}

template <typename... Cs>
typename EntityQuery<Cs...>::Iterator::ValueType EntityQuery<Cs...>::Iterator::operator*() const {
    return std::forward_as_tuple(m_entity_ids[m_entity_index], *(std::get<Cs*>(m_components) + m_entity_index)...);
}

template <typename... Cs>
typename EntityQuery<Cs...>::Iterator& EntityQuery<Cs...>::Iterator::operator++() {
    ++m_entity_index;
    while (m_archetype_index < m_archetypes.size() && m_entity_index >= m_archetypes[m_archetype_index]->count()) {
        ++m_archetype_index;
        if (m_archetype_index < m_archetypes.size()) {
            store_base_ptrs();
        }
        m_entity_index = 0;
    }
    return *this;
}

template <typename... Cs>
bool EntityQuery<Cs...>::Iterator::operator==(const Iterator& other) const {
    return m_archetype_index == other.m_archetype_index && m_entity_index == other.m_entity_index;
}

template <typename... Cs>
bool EntityQuery<Cs...>::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

template <typename... Cs>
std::size_t EntityQuery<Cs...>::index_skipping_empty_archetypes() const {
    std::size_t index = 0;
    while (index < m_archetypes.size() && m_archetypes[index]->is_empty()) {
        ++index;
    }
    return index;
}

} // namespace msq::ecs
