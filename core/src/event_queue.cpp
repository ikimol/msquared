// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/core/event_queue.hpp"

#include "msquared/core/assert.hpp"

namespace msq {

EventQueue::EventQueue(std::size_t capacity) {
    m_buffers[0].resize(capacity);
    m_buffers[1].resize(capacity);
}

EventSubscription EventQueue::subscribe(EventType type, std::function<void(const void*)> callback) {
    return EventSubscription(m_signals[type].connect(std::move(callback)));
}

void EventQueue::dispatch() {
    // swap buffers so events sent during dispatch work as expected
    auto offset = std::exchange(m_offset, 0);
    std::swap(m_buffers[0], m_buffers[1]);

    std::byte* cursor = m_buffers[1].data();
    std::byte* end = cursor + offset;

    while (cursor < end) {
        // calculate base header pointer
        void* header_ptr = cursor;
        std::size_t space = end - cursor;
        header_ptr = std::align(alignof(Header), sizeof(Header), header_ptr, space);
        MSQ_ASSERT(header_ptr != nullptr, "not enough space to align event header");

        auto* header = std::launder(static_cast<Header*>(header_ptr));

        // retrieve event
        void* event_ptr = std::launder(reinterpret_cast<std::byte*>(header) + sizeof(Header));
        space = end - static_cast<std::byte*>(event_ptr);
        event_ptr = std::align(header->event_align, header->event_size, event_ptr, space);
        MSQ_ASSERT(event_ptr != nullptr, "not enough space to align event data");

        if (auto it = m_signals.find(header->event_type); it != m_signals.end()) {
            it->second.emit(event_ptr);
        }

        // advance cursor
        cursor = static_cast<std::byte*>(event_ptr) + header->event_size;
    }
}

void* EventQueue::get_ptr(EventType type, EventSizeType size, EventAlignType align) {
    auto& buffer = m_buffers[0];

    void* header_ptr = buffer.data() + m_offset;
    std::size_t space = buffer.size() - m_offset;
    header_ptr = std::align(alignof(Header), sizeof(Header), header_ptr, space);
    MSQ_ASSERT(header_ptr != nullptr, "not enough space to align event header");

    new (header_ptr) Header {type, align, size};
    m_offset = static_cast<std::byte*>(header_ptr) - buffer.data() + sizeof(Header);

    // align the event pointer
    void* event_ptr = buffer.data() + m_offset;
    space = buffer.size() - m_offset;
    event_ptr = std::align(align, size, event_ptr, space);
    MSQ_ASSERT(event_ptr != nullptr, "not enough space to align event data");

    // increment offset
    m_offset = static_cast<std::byte*>(event_ptr) - buffer.data() + size;

    return event_ptr;
}

EventSubscription::EventSubscription(shard::connection&& connection)
: m_connection(std::move(connection)) {}

EventSubscription::EventSubscription(EventSubscription&& other) noexcept
: m_connection(std::move(other.m_connection)) {}

EventSubscription::~EventSubscription() {
    m_connection.disconnect();
}

EventSubscription& EventSubscription::operator=(EventSubscription&& other) noexcept {
    m_connection = std::move(other.m_connection);
    return *this;
}

} // namespace msq
