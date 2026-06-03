// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/ecs/entity.hpp"

#include "msquared/ecs/world.hpp"

namespace msq::ecs {

Entity Entity::clone() const {
    return m_world->clone_entity(m_id);
}

void Entity::destroy() const {
    return m_world->destroy_entity(m_id);
}

bool Entity::is_alive() const noexcept {
    return m_world->is_entity_alive(m_id);
}

} // namespace msq::ecs
