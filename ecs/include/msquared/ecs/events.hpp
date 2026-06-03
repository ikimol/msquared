// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/ecs/entity.hpp"

namespace msq::ecs {

/// Event sent just before an entity is destroyed
struct EntityWillBeDestroyedEvent {
    explicit EntityWillBeDestroyedEvent(Entity e)
    : entity(e) {}

    Entity entity;
};

/// Event sent when a component is added to an entity
template <typename C>
struct ComponentWasAddedEvent {
    using Component = C;

    explicit ComponentWasAddedEvent(Entity e)
    : entity(e) {}

    Entity entity;
};

/// Event sent just after a component was removed from an entity
template <typename C>
struct ComponentWasRemovedEvent {
    using Component = C;

    explicit ComponentWasRemovedEvent(Entity e)
    : entity(e) {}

    Entity entity;
};

} // namespace msq::ecs
