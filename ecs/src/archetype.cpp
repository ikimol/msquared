// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/ecs/detail/archetype.hpp"

#include "msquared/ecs/detail/component_registry.hpp"
#include "msquared/ecs/detail/entity_index_map.hpp"

#include <msquared/core/assert.hpp>

#include <cstring>

namespace msq::ecs::detail {

Archetype::Archetype(EntityIndexMap& entity_indices, const ComponentRegistry& component_registry, ComponentMask mask)
: m_entity_indices(entity_indices)
, m_component_registry(component_registry)
, m_mask(mask) {
    initialize_columns();
}

Archetype::~Archetype() {
    std::free(m_entity_ids);
}

void Archetype::add_entity(EntityID entity_id) {
    ensure_capacity();
    m_entity_ids[m_count++] = entity_id;
    m_entity_indices.update(entity_id, m_count - 1);
}

void Archetype::remove_entity(EntityID entity_id) {
    auto index = m_entity_indices.index_of(entity_id);
    remove_at(index);
    m_entity_indices.remove(entity_id);
}

void Archetype::clone_entity(EntityID entity_id, EntityID clone_id) {
    add_entity(clone_id);

    auto entity_index = m_entity_indices.index_of(entity_id);
    auto clone_index = m_entity_indices.index_of(clone_id);

    for (auto type : m_mask) {
        auto& column = get_column(type);
        auto* src = column.at(entity_index);
        auto* dst = column.at(clone_index);
        std::memcpy(dst, src, m_component_registry.component_size(type));
    }
}

void Archetype::move_entity(EntityID entity_id, Archetype& new_archetype) {
    auto old_index = m_entity_indices.index_of(entity_id);
    new_archetype.add_entity(entity_id);
    auto new_index = m_entity_indices.index_of(entity_id);
    auto mask = m_mask & new_archetype.m_mask;

    for (auto type : mask) {
        auto* src = get_column(type).at(old_index);
        auto* dst = new_archetype.get_column(type).at(new_index);
        std::memcpy(dst, src, m_component_registry.component_size(type));
    }

    remove_at(old_index);
}

void Archetype::reserve(std::size_t num_new_entities) {
    if (num_new_entities > 0) {
        grow(m_count + num_new_entities);
    }
}

void* Archetype::component(EntityID entity_id, ComponentType type) {
    MSQ_ASSERT(m_mask.test(type), "archetype does not contain component type");
    return get_column(type).at(m_entity_indices.index_of(entity_id));
}

const void* Archetype::component(EntityID entity_id, ComponentType type) const {
    MSQ_ASSERT(m_mask.test(type), "archetype does not contain component type");
    return get_column(type).at(m_entity_indices.index_of(entity_id));
}

void* Archetype::components(ComponentType type) {
    MSQ_ASSERT(m_mask.test(type), "archetype does not contain component type");
    return get_column(type).at(0);
}

const void* Archetype::components(ComponentType type) const {
    MSQ_ASSERT(m_mask.test(type), "archetype does not contain component type");
    return get_column(type).at(0);
}

void Archetype::initialize_columns() {
    m_columns.reserve(m_mask.count());

    for (auto type : m_mask) {
        m_columns.emplace_back(type, m_component_registry.component_size(type));
    }
}

void Archetype::remove_at(std::size_t index) {
    MSQ_ASSERT(index < m_count, "remove index out of range");

    for (auto& column : m_columns) {
        column.remove(index, m_count - 1);
    }

    // only swap if it's not the last element
    if (index != m_count - 1) {
        std::swap(m_entity_ids[index], m_entity_ids[m_count - 1]);

        // update index mapping of swapped element
        m_entity_indices.update(m_entity_ids[index], index);
    }

    --m_count;
}

Archetype::Column& Archetype::get_column(ComponentType type) {
    return const_cast<Column&>(std::as_const(*this).get_column(type));
}

const Archetype::Column& Archetype::get_column(ComponentType type) const {
    for (auto& column : m_columns) {
        if (column.type() == type) {
            return column;
        }
    }
    throw std::out_of_range("archetype does not contain component");
}

void Archetype::ensure_capacity() {
    if (m_count + 1 > m_capacity) {
        grow(m_count + 1);
    }
}

void Archetype::grow(std::size_t min_capacity) {
    std::size_t new_capacity = 4;
    while (new_capacity < min_capacity) {
        new_capacity *= 2;
    }
    reallocate(new_capacity);
}

void Archetype::reallocate(std::size_t new_capacity) {
    reallocate_entity_ids(new_capacity);
    reallocate_columns(new_capacity);
    m_capacity = new_capacity;
}

void Archetype::reallocate_entity_ids(std::size_t new_capacity) {
    if (auto* p = std::realloc(m_entity_ids, new_capacity * sizeof(EntityID))) /* NOLINT */ {
        m_entity_ids = static_cast<EntityID*>(p);
        return;
    }
    throw std::bad_alloc();
}

void Archetype::reallocate_columns(std::size_t new_capacity) {
    for (auto& column : m_columns) {
        column.reallocate(new_capacity);
    }
}

// Column

Archetype::Column::Column(ComponentType type, std::size_t element_size)
: m_type(type)
, m_element_size(element_size) {}

std::byte* Archetype::Column::at(std::size_t index) const {
    return m_data.bytes() + index * m_element_size;
}

void Archetype::Column::remove(std::size_t index, std::size_t last_index) {
    std::memmove(at(index), at(last_index), m_element_size);
}

void Archetype::Column::reallocate(std::size_t new_capacity) {
    m_data.reallocate(new_capacity * m_element_size);
}

} // namespace msq::ecs::detail
