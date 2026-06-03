// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/ecs/entity_id.hpp"

#include <functional>

namespace msq::ecs {

class World;

/// Represents a single entity in the world
class Entity {
    friend class World;

public:
    /// Default constructor
    constexpr Entity() noexcept = default;

    /// Get the unique ID of this entity
    constexpr EntityID id() const noexcept { return m_id; }

    /// Create a clone of this entity
    Entity clone() const;

    /// Destroy this entity
    void destroy() const;

    /// Check if this entity is alive
    bool is_alive() const noexcept;

    // component management

    /// Check if a component is present on this entity
    template <typename C>
    bool has_component() const;

    /// Check if all components are present on this entity
    template <typename... Cs>
    bool has_components() const;

    /// Get a component of this entity
    template <typename C>
    C& get_component() const;

    /// Create a new component and add it to this entity
    template <typename C, typename... Args>
    void add_component(Args&&... args);

    /// Remove a component from this entity and destroy it
    template <typename C>
    void remove_component();

private:
    Entity(EntityID id, World* world) noexcept
    : m_id(id)
    , m_world(world) {}

private:
    EntityID m_id;
    World* m_world = nullptr;
};

// operators

inline bool operator==(const Entity& lhs, const Entity& rhs) noexcept {
    return lhs.id() == rhs.id();
}

inline bool operator!=(const Entity& lhs, const Entity& rhs) noexcept {
    return !(lhs == rhs);
}

inline bool operator<(const Entity& lhs, const Entity& rhs) noexcept {
    return lhs.id() < rhs.id();
}

inline bool operator<=(const Entity& lhs, const Entity& rhs) noexcept {
    return !(rhs < lhs);
}

inline bool operator>(const Entity& lhs, const Entity& rhs) noexcept {
    return rhs < lhs;
}

inline bool operator>=(const Entity& lhs, const Entity& rhs) noexcept {
    return !(lhs < rhs);
}

} // namespace msq::ecs

template <>
struct std::hash<msq::ecs::Entity> {
    std::size_t operator()(const msq::ecs::Entity& e) const noexcept { return hash<msq::ecs::EntityID> {}(e.id()); }
};
