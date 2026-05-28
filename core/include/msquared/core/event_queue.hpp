// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/core/event_type.hpp"

#include <shard/signal.hpp>

#include <cstddef>
#include <functional>
#include <type_traits>
#include <unordered_map>

namespace msq {

class EventSubscription;

/// A queue that events are sent to and then get dispatched all at once
class EventQueue {
public:
    explicit EventQueue(std::size_t capacity);

    /// Subscribe to events of the given type
    template <typename E>
    [[nodiscard]] EventSubscription subscribe(std::function<void(const E&)> callback);

    /// Subscribe to events of the given type
    [[nodiscard]] EventSubscription subscribe(EventType type, std::function<void(const void*)> callback);

    /// Enqueue an event, constructed in-place
    template <typename E, typename... Args, typename = std::enable_if_t<std::is_trivially_copyable_v<E>>>
    void send(Args&&... args);

    /// Dispatch all queued events to subscribers
    void dispatch();

private:
    using EventSizeType = std::uint16_t;
    using EventAlignType = std::uint8_t;

    struct Header {
        EventType event_type;
        EventAlignType event_align;
        EventSizeType event_size;
    };

private:
    void* get_ptr(EventType type, EventSizeType size, EventAlignType align);

private:
    std::vector<std::byte> m_buffers[2];
    std::size_t m_offset = 0;

    std::unordered_map<EventType, shard::signal<const void*>> m_signals;
};

/// Represents a single active subscription to an event
class EventSubscription {
    friend class EventQueue;

public:
    EventSubscription() = default;

    /// Move constructor
    EventSubscription(EventSubscription&& other) noexcept;

    /// Destroy the underlying connection
    ~EventSubscription();

    /// Move assignment operator
    EventSubscription& operator=(EventSubscription&& other) noexcept;

    /// Check if the subscription is enabled
    bool is_enabled() const { return m_connection.is_enabled(); }

    /// Enable or disable the subscription
    void set_enabled(bool enabled) { m_connection.set_enabled(enabled); }

private:
    explicit EventSubscription(shard::connection&& connection);

private:
    shard::connection m_connection;
};

// implementation

template <typename E>
EventSubscription EventQueue::subscribe(std::function<void(const E&)> callback) {
    return subscribe(event_type<E>(), [cb = std::move(callback)](const void* e) { cb(*static_cast<const E*>(e)); });
}

template <typename E, typename... Args, typename>
void EventQueue::send(Args&&... args) {
    auto ptr = get_ptr(event_type<E>(), sizeof(E), alignof(E));
    new (ptr) E(std::forward<Args>(args)...);
}

} // namespace msq
