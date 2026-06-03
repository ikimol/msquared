// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/ecs/world.hpp"

#include <msquared/core/assert.hpp>

namespace msq::ecs {

World::World(EventQueue& event_queue)
: m_event_queue(event_queue)
, m_archetype_registry(m_entity_indices, m_component_registry)
, m_query_cache(m_archetype_registry) {}

World::~World() = default;

Entity World::create_entity() {
    Entity entity(m_entity_pool.next_id(), this);
    auto& empty_archetype = m_archetype_registry.empty_archetype();
    empty_archetype.add_entity(entity.id());
    m_entity_archetypes.update(entity.id(), empty_archetype);
    return entity;
}

Entity World::create_entity_with(shard::function_ref<void(EntityBuilder&)> build) {
    EntityBuilder builder;
    build(builder);
    Entity entity(m_entity_pool.next_id(), this);
    m_changes.emplace_back(BuildEntityChange {entity.id(), std::move(builder.m_components)});
    return entity;
}

void World::create_entities_with(std::size_t count, shard::function_ref<void(EntityBuilder&)> build) {
    EntityBuilder builder;
    build(builder);

    std::vector<EntityID> entity_ids;
    entity_ids.reserve(count);

    for (std::size_t i = 0; i < count; ++i) {
        entity_ids.push_back(m_entity_pool.next_id());
    }

    m_changes.emplace_back(BuildEntitiesChange {std::move(entity_ids), std::move(builder.m_components)});
}

Entity World::clone_entity(EntityID entity_id) {
    MSQ_ASSERT(is_entity_alive(entity_id), "entity is not alive");
    Entity clone(m_entity_pool.next_id(), this);
    auto& archetype = m_entity_archetypes.archetype_of(entity_id);
    archetype.clone_entity(entity_id, clone.id());
    m_entity_archetypes.update(clone.id(), archetype);
    return clone;
}

void World::destroy_entity(EntityID entity_id) {
    MSQ_ASSERT(is_entity_alive(entity_id), "entity is not alive");
    m_changes.emplace_back(DestroyEntityChange {entity_id});
}

bool World::is_entity_alive(EntityID entity_id) const {
    return m_entity_pool.is_valid(entity_id);
}

std::size_t World::entity_count() const {
    return m_entity_pool.alive_count();
}

void World::apply_changes() {
    for (auto& change : m_changes) {
        std::visit([this](auto& c) { apply_change(c); }, change);
    }
    m_changes.clear();
}

void World::apply_change(const BuildEntityChange& change) {
    build_entities({&change.entity_id, 1}, change.components);
}

void World::apply_change(const BuildEntitiesChange& change) {
    build_entities(change.entity_ids, change.components);
}

void World::apply_change(const DestroyEntityChange& change) {
    m_event_queue.send<EntityWillBeDestroyedEvent>(Entity(change.entity_id, this));
    auto& archetype = m_entity_archetypes.archetype_of(change.entity_id);
    archetype.remove_entity(change.entity_id);
    m_entity_archetypes.remove(change.entity_id);
    m_entity_pool.recycle(change.entity_id);
}

void World::apply_change(const AddComponentChange& change) {
    auto& old_archetype = m_entity_archetypes.archetype_of(change.entity_id);
    auto new_mask = ComponentMask(old_archetype.mask()).set(change.component.type);

    auto [new_archetype, inserted] = m_archetype_registry.get_or_create(new_mask);

    if (inserted) {
        m_query_cache.insert(new_mask, new_archetype);
    }

    old_archetype.move_entity(change.entity_id, new_archetype);

    Entity entity(change.entity_id, this);

    // copy component data
    auto memory = new_archetype.component(change.entity_id, change.component.type);
    std::memcpy(memory, change.component.data.bytes(), change.component.data.size());
    m_component_registry.send_was_added_event(m_event_queue, change.component.type, entity);

    m_entity_archetypes.update(change.entity_id, new_archetype);
}

void World::apply_change(const RemoveComponentChange& change) {
    auto& old_archetype = m_entity_archetypes.archetype_of(change.entity_id);
    auto new_mask = ComponentMask(old_archetype.mask()).unset(change.component_type);
    auto [new_archetype, inserted] = m_archetype_registry.get_or_create(new_mask);

    if (inserted) {
        m_query_cache.insert(new_mask, new_archetype);
    }

    Entity entity(change.entity_id, this);

    old_archetype.move_entity(change.entity_id, new_archetype);

    m_entity_archetypes.update(change.entity_id, new_archetype);

    m_component_registry.send_was_removed_event(m_event_queue, change.component_type, entity);
}

void World::build_entities(shard::span<const EntityID> entity_ids, shard::span<const Component> components) {
    auto new_mask = ComponentMask();

    for (const auto& [type, _] : components) {
        new_mask.set(type);
    }

    auto [new_archetype, inserted] = m_archetype_registry.get_or_create(new_mask);

    if (inserted) {
        m_query_cache.insert(new_mask, new_archetype);
    }

    new_archetype.reserve(entity_ids.size());

    for (auto entity_id : entity_ids) {
        // entities created this way were not added to the empty archetype
        new_archetype.add_entity(entity_id);

        Entity entity(entity_id, this);

        for (const auto& [type, data] : components) {
            auto memory = new_archetype.component(entity_id, type);
            std::memcpy(memory, data.bytes(), data.size());
            m_component_registry.send_was_added_event(m_event_queue, type, entity);
        }

        m_entity_archetypes.update(entity_id, new_archetype);
    }
}

} // namespace msq::ecs
