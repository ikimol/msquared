// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include <shard/meta/type_id.hpp>

namespace msq::ecs {
namespace detail {

// used by the component type ID generator
struct ComponentTag final {};

} // namespace detail

/// Represents the type ID of a component
using ComponentType = shard::type_id<std::uint8_t, detail::ComponentTag>;

/// Get the type ID of the component
template <typename C>
ComponentType component_type() {
    return SHARD_TYPEID(ComponentType, C);
}

} // namespace msq::ecs
