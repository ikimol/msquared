// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include <shard/meta/type_id.hpp>

namespace msq {
namespace detail {

// used by the event type ID generator
struct EventTag final {};

} // namespace detail

/// Represents the type ID of an event
using EventType = shard::type_id<std::uint8_t, detail::EventTag>;

/// Get the type ID of the event
template <typename C>
EventType event_type() {
    return SHARD_TYPEID(EventType, C);
}

} // namespace msq
