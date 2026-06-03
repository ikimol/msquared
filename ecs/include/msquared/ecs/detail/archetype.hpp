// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/ecs/component_mask.hpp"
#include "msquared/ecs/entity_id.hpp"

#include <shard/memory/dynamic_data.hpp>

#include <vector>

namespace msq::ecs::detail {

class ComponentRegistry;
class EntityIndexMap;

class Archetype {
public:
    explicit Archetype(EntityIndexMap& entity_indices, const ComponentRegistry& component_registry, ComponentMask mask);

    ~Archetype();

    Archetype(const Archetype&) = delete;
    Archetype& operator=(const Archetype&) = delete;
    Archetype(Archetype&&) = delete;
    Archetype& operator=(Archetype&&) = delete;

    void add_entity(EntityID entity_id);

    void remove_entity(EntityID entity_id);

    void clone_entity(EntityID entity_id, EntityID clone_id);

    void move_entity(EntityID entity_id, Archetype& new_archetype);

    void reserve(std::size_t num_new_entities);

    const ComponentMask& mask() const { return m_mask; }

    const EntityID* entity_ids() const { return m_entity_ids; }

    std::size_t count() const { return m_count; }

    bool is_empty() const { return m_count == 0; }

    void* component(EntityID entity_id, ComponentType type);

    const void* component(EntityID entity_id, ComponentType type) const;

    void* components(ComponentType type);

    const void* components(ComponentType type) const;

private:
    struct Column {
        explicit Column(ComponentType type, std::size_t element_size);

        ComponentType type() const { return m_type; }

        std::byte* at(std::size_t index) const;

        void remove(std::size_t index, std::size_t last_index);

        void reallocate(std::size_t new_capacity);

    private:
        ComponentType m_type;
        shard::dynamic_data m_data;
        std::size_t m_element_size = 0;
    };

private:
    void initialize_columns();

    void remove_at(std::size_t index);

    Column& get_column(ComponentType type);
    const Column& get_column(ComponentType type) const;

    void ensure_capacity();
    void grow(std::size_t min_capacity);
    void reallocate(std::size_t new_capacity);
    void reallocate_entity_ids(std::size_t new_capacity);
    void reallocate_columns(std::size_t new_capacity);

private:
    EntityIndexMap& m_entity_indices;
    const ComponentRegistry& m_component_registry;

    ComponentMask m_mask;

    std::vector<Column> m_columns;

    std::size_t m_count = 0;
    std::size_t m_capacity = 0;

    EntityID* m_entity_ids = nullptr;
};

} // namespace msq::ecs::detail
