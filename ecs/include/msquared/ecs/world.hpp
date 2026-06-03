// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/ecs/component_type.hpp"
#include "msquared/ecs/entity.hpp"
#include "msquared/ecs/events.hpp"
#include "msquared/ecs/query.hpp"

#include "msquared/ecs/detail/archetype_registry.hpp"
#include "msquared/ecs/detail/component_registry.hpp"
#include "msquared/ecs/detail/entity_archetype_map.hpp"
#include "msquared/ecs/detail/entity_index_map.hpp"
#include "msquared/ecs/detail/entity_pool.hpp"
#include "msquared/ecs/detail/query_cache.hpp"

#include <msquared/core/event_queue.hpp>

#include <shard/memory/dynamic_data.hpp>
#include <shard/utility/function_ref.hpp>
#include <shard/utility/span.hpp>

#include <variant>
#include <vector>

namespace msq::ecs {

/// Container for all the entities
class World {
public:
    class EntityBuilder;

public:
    /// Create a new world
    explicit World(EventQueue& event_queue);

    /// Destroy the world with all its entities, components, etc.
    ~World();

    /// Create a new entity
    Entity create_entity();

    /// Create a new pre-configured entity
    ///
    /// \note The entity will not be usable and the components will not be
    /// added until apply_changes() is called.
    Entity create_entity_with(shard::function_ref<void(EntityBuilder&)> build);

    /// Create a number of pre-configured entities
    ///
    /// \note The entities will not be usable and the components will not be
    /// added until apply_changes() is called.
    ///
    /// \warning The provided builder function is invoked only once to create a
    /// list of components that will be added to each entity. It is *NOT*
    /// evaluated separately for every entity.
    void create_entities_with(std::size_t count, shard::function_ref<void(EntityBuilder&)> build);

    /// Create a clone of the entity
    Entity clone_entity(EntityID entity_id);

    /// Destroy the entity
    ///
    /// \note This will not take effect until apply_changes() is called.
    void destroy_entity(EntityID entity_id);

    /// Check if the entity is alive
    bool is_entity_alive(EntityID entity_id) const;

    /// Get the number of alive entities
    ///
    /// \note This count reflects only committed state. Entities created or
    /// destroyed won't be reflected until apply_changes() is called.
    std::size_t entity_count() const;

    // component management

    /// Check if a component is present on the entity
    template <typename C>
    bool has_component(EntityID entity_id) const;

    /// Check if all components are present on the entity
    template <typename... Cs>
    bool has_components(EntityID entity_id) const;

    /// Get a component of the entity
    template <typename C>
    C& get_component(EntityID entity_id) const;

    /// Create a new component and add it to the entity
    ///
    /// \note This will not take effect until apply_changes() is called.
    template <typename C, typename... Args>
    void add_component(EntityID entity_id, Args&&... args);

    /// Remove a component from the entity and destroy it
    ///
    /// \note This will not take effect until apply_changes() is called.
    template <typename C>
    void remove_component(EntityID entity_id);

    // queries

    /// Create a query that can be used to iterate entities
    template <typename... Cs>
    ComponentQuery<Cs...> query();

    /// Create a query that yields the entity ID alongside its components
    template <typename... Cs>
    EntityQuery<Cs...> query_with_entity();

    // other

    /// Register the component to be usable
    template <typename C>
    void register_component();

    /// Apply any changes made since the last call
    ///
    /// \warning This *MUST NOT* be called while iterating a query. Doing so
    /// is undefined behavior that will likely result in a crash.
    void apply_changes();

private:
    struct Component;

public:
    /// Used for building entities with multiple components
    class EntityBuilder {
        friend class World;

    public:
        /// Create a new component and add it to the entity
        template <typename C, typename... Args>
        void add_component(Args&&... args);

    private:
        std::vector<Component> m_components;
    };

private:
    struct Component {
        ComponentType type;
        shard::dynamic_data data;
    };

    struct BuildEntityChange {
        EntityID entity_id;
        std::vector<Component> components;
    };

    struct BuildEntitiesChange {
        std::vector<EntityID> entity_ids;
        std::vector<Component> components;
    };

    struct DestroyEntityChange {
        EntityID entity_id;
    };

    struct AddComponentChange {
        EntityID entity_id;
        Component component;
    };

    struct RemoveComponentChange {
        EntityID entity_id;
        ComponentType component_type;
    };

    using Change = std::variant<BuildEntityChange,
                                BuildEntitiesChange,
                                DestroyEntityChange,
                                AddComponentChange,
                                RemoveComponentChange>;

private:
    void apply_change(const BuildEntityChange& change);
    void apply_change(const BuildEntitiesChange& change);
    void apply_change(const DestroyEntityChange& change);
    void apply_change(const AddComponentChange& change);
    void apply_change(const RemoveComponentChange& change);

    void build_entities(shard::span<const EntityID> entity_ids, shard::span<const Component> components);

private:
    EventQueue& m_event_queue;

    detail::EntityPool m_entity_pool;
    detail::ComponentRegistry m_component_registry;
    detail::EntityIndexMap m_entity_indices;
    detail::EntityArchetypeMap m_entity_archetypes;
    detail::ArchetypeRegistry m_archetype_registry;
    detail::QueryCache m_query_cache;

    std::vector<Change> m_changes;
};

// implementation

template <typename C>
bool World::has_component(EntityID entity_id) const {
    return m_entity_archetypes.archetype_of(entity_id).mask().test(component_type<C>());
}

template <typename... Cs>
bool World::has_components(EntityID entity_id) const {
    return m_entity_archetypes.archetype_of(entity_id).mask().contains(make_component_mask<Cs...>());
}

template <typename C>
C& World::get_component(EntityID entity_id) const {
    return *static_cast<C*>(m_entity_archetypes.archetype_of(entity_id).component(entity_id, component_type<C>()));
}

template <typename C, typename... Args>
void World::add_component(EntityID entity_id, Args&&... args) {
    AddComponentChange change {
        entity_id,
        {component_type<C>(), shard::dynamic_data(sizeof(C))},
    };
    new (change.component.data.bytes()) C(std::forward<Args>(args)...);
    m_changes.emplace_back(std::move(change));
}

template <typename C>
void World::remove_component(EntityID entity_id) {
    m_changes.emplace_back(RemoveComponentChange {entity_id, component_type<C>()});
}

template <typename C>
void World::register_component() {
    static_assert(std::is_trivially_copyable_v<C>);
    m_component_registry.register_component<C>();
}

template <typename C, typename... Args>
void World::EntityBuilder::add_component(Args&&... args) {
    Component component {component_type<C>(), shard::dynamic_data(sizeof(C))};
    new (component.data.bytes()) C(std::forward<Args>(args)...);
    m_components.emplace_back(std::move(component));
}

template <typename... Cs>
ComponentQuery<Cs...> World::query() {
    return ComponentQuery<Cs...>(m_query_cache.matching(make_component_mask<Cs...>()));
}

template <typename... Cs>
EntityQuery<Cs...> World::query_with_entity() {
    return EntityQuery<Cs...>(m_query_cache.matching(make_component_mask<Cs...>()));
}

// Entity

template <typename C>
bool Entity::has_component() const {
    return m_world->has_component<C>(m_id);
}

template <typename... Cs>
bool Entity::has_components() const {
    return m_world->has_components<Cs...>(m_id);
}

template <typename C>
C& Entity::get_component() const {
    return m_world->get_component<C>(m_id);
}

template <typename C, typename... Args>
void Entity::add_component(Args&&... args) {
    m_world->add_component<C>(m_id, std::forward<Args>(args)...);
}

template <typename C>
void Entity::remove_component() {
    m_world->remove_component<C>(m_id);
}

// ComponentRegistry

namespace detail {

template <typename C>
void ComponentRegistry::register_component() {
    ComponentInfo info {};
    info.size = sizeof(C);
    info.was_added_event = [](EventQueue& eq, Entity e) { eq.send<ComponentWasAddedEvent<C>>(e); };
    info.was_removed_event = [](EventQueue& eq, Entity e) { eq.send<ComponentWasRemovedEvent<C>>(e); };
    m_info.emplace(component_type<C>(), info);
}

} // namespace detail
} // namespace msq::ecs
