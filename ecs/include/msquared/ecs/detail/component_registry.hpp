// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/ecs/component_type.hpp"
#include "msquared/ecs/entity.hpp"

#include <cstddef>
#include <unordered_map>

namespace msq {

class EventQueue;

} // namespace msq

namespace msq::ecs::detail {

class ComponentRegistry {
public:
    template <typename C>
    void register_component();

    std::size_t component_size(ComponentType type) const;

    void send_was_added_event(EventQueue& event_queue, ComponentType type, Entity e) const;
    void send_was_removed_event(EventQueue& event_queue, ComponentType type, Entity e) const;

private:
    struct ComponentInfo {
        std::size_t size;

        void (*was_added_event)(EventQueue&, Entity);
        void (*was_removed_event)(EventQueue&, Entity);
    };

private:
    std::unordered_map<ComponentType, ComponentInfo> m_info;
};

} // namespace msq::ecs::detail
