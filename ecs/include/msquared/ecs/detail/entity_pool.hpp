
// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/ecs/entity_id.hpp"

#include <cstdint>
#include <vector>

namespace msq::ecs::detail {

class EntityPool {
public:
    EntityID next_id();

    void recycle(EntityID entity_id);

    bool is_valid(EntityID entity_id) const;

    EntityID retrieve(std::uint32_t entity_id_index) const;

    void reserve(std::size_t num_new_entities);

    std::size_t next_index() const { return m_next_index; }

    std::size_t alive_count() const { return m_next_index - m_recycled.size(); }

private:
    void grow_if_needed(std::size_t min_capacity);

private:
    std::uint32_t m_next_index = 0;           // counter for new indices
    std::vector<std::uint32_t> m_recycled;    // stack of indices to be reused
    std::vector<std::uint32_t> m_generations; // currently active generations
};

} // namespace msq::ecs::detail
