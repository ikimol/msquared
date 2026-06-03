// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include <cstdint>
#include <functional>

namespace msq::ecs {

/// The unique ID of an entity
class EntityID {
public:
    /// Construct an invalid ID
    constexpr EntityID() noexcept = default;

    /// Constructor with index and generation
    constexpr EntityID(std::uint32_t index, std::uint32_t generation) noexcept
    : m_raw_value((generation & generation_mask) << index_bits | (index & index_mask)) {}

    /// Get the index part of the ID
    constexpr std::uint32_t index() const noexcept { return m_raw_value & index_mask; }

    /// Get the generation part of the ID
    constexpr std::uint32_t generation() const noexcept { return (m_raw_value >> index_bits) & generation_mask; }

    /// Get the raw value of the ID
    constexpr std::uint32_t raw_value() const noexcept { return m_raw_value; }

private:
    static constexpr auto index_bits = 20u;
    static constexpr auto generation_bits = 12u;

    static constexpr auto index_mask = (1u << index_bits) - 1;
    static constexpr auto generation_mask = (1u << generation_bits) - 1;

private:
    std::uint32_t m_raw_value = 0;
};

// operators

constexpr bool operator==(const EntityID& lhs, const EntityID& rhs) noexcept {
    return lhs.raw_value() == rhs.raw_value();
}

constexpr bool operator!=(const EntityID& lhs, const EntityID& rhs) noexcept {
    return !(lhs == rhs);
}

constexpr bool operator<(const EntityID& lhs, const EntityID& rhs) noexcept {
    return lhs.raw_value() < rhs.raw_value();
}

constexpr bool operator<=(const EntityID& lhs, const EntityID& rhs) noexcept {
    return !(rhs < lhs);
}

constexpr bool operator>(const EntityID& lhs, const EntityID& rhs) noexcept {
    return rhs < lhs;
}

constexpr bool operator>=(const EntityID& lhs, const EntityID& rhs) noexcept {
    return !(lhs < rhs);
}

} // namespace msq::ecs

template <>
struct std::hash<msq::ecs::EntityID> {
    std::size_t operator()(const msq::ecs::EntityID& id) const noexcept {
        return hash<std::uint32_t> {}(id.raw_value());
    }
};
