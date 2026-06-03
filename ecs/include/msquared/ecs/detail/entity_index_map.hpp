// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/ecs/entity_id.hpp"

#include <vector>

namespace msq::ecs::detail {

class EntityIndexMap {
public:
    std::size_t index_of(EntityID entity_id) const;

    void update(EntityID entity_id, std::size_t index);

    void remove(EntityID entity_id);

    void reserve(std::size_t min_capacity);

private:
    void ensure_capacity(std::size_t min_capacity);
    void grow(std::size_t min_capacity);

private:
    static constexpr auto invalid_index = static_cast<std::size_t>(-1);

private:
    std::vector<std::size_t> m_indices;
};

} // namespace msq::ecs::detail
