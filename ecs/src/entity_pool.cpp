// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/ecs/detail/entity_pool.hpp"

#include <msquared/core/assert.hpp>

namespace msq::ecs::detail {

EntityID EntityPool::next_id() {
    std::uint32_t index;
    std::uint32_t generation;
    if (!m_recycled.empty()) {
        index = m_recycled.back();
        m_recycled.pop_back();
        generation = m_generations[index]; // incremented already
    } else {
        index = m_next_index++;
        generation = 1; // generation 0 is invalid
        grow_if_needed(index + 1);
        m_generations[index] = generation;
    }
    return {index, generation};
}

void EntityPool::recycle(EntityID entity_id) {
    MSQ_ASSERT(is_valid(entity_id), "recycling an invalid entity");
    ++m_generations[entity_id.index()]; // invalidates the ID
    m_recycled.push_back(entity_id.index());
}

bool EntityPool::is_valid(EntityID entity_id) const {
    return entity_id.index() < m_generations.size() && m_generations[entity_id.index()] == entity_id.generation();
}

EntityID EntityPool::retrieve(std::uint32_t entity_id_index) const {
    MSQ_ASSERT(entity_id_index < m_generations.size(), "entity index out of range");
    return {entity_id_index, m_generations[entity_id_index]};
}

void EntityPool::reserve(std::size_t num_new_entities) {
    if (num_new_entities > m_recycled.size()) {
        grow_if_needed(m_next_index + num_new_entities - m_recycled.size());
    }
}

void EntityPool::grow_if_needed(std::size_t min_capacity) {
    if (min_capacity > m_generations.capacity()) {
        std::size_t new_capacity = 4;
        while (new_capacity < min_capacity) {
            new_capacity *= 2;
        }
        m_generations.reserve(new_capacity);
    }
    m_generations.resize(min_capacity);
}

} // namespace msq::ecs::detail
