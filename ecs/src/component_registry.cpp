// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/ecs/detail/component_registry.hpp"

namespace msq::ecs::detail {

std::size_t ComponentRegistry::component_size(ComponentType type) const {
    return m_info.at(type).size;
}

void ComponentRegistry::send_was_added_event(EventQueue& event_queue, ComponentType type, Entity e) const {
    m_info.at(type).was_added_event(event_queue, e);
}

void ComponentRegistry::send_was_removed_event(EventQueue& event_queue, ComponentType type, Entity e) const {
    m_info.at(type).was_removed_event(event_queue, e);
}

} // namespace msq::ecs::detail
