// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/ecs/component_type.hpp"

#include <bitset>

namespace msq::ecs {

/// The maximum number of distinct component types
inline constexpr std::size_t max_components = 64;

/// Represents a set of component type IDs
class ComponentMask {
    friend struct std::hash<ComponentMask>;
    friend bool operator==(const ComponentMask&, const ComponentMask&);

public:
    /// Used for iterating the components of a component set
    class Iterator {
        friend bool operator==(const Iterator&, const Iterator&);

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = ComponentType;
        using difference_type = std::ptrdiff_t;
        using pointer = const ComponentType*;
        using reference = ComponentType;

    public:
        Iterator(const ComponentMask& mask, std::size_t index);

        ComponentType operator*() const;

        Iterator& operator++();

    private:
        const ComponentMask& m_mask;
        std::size_t m_index;
    };

public:
    /// Create a new empty component mask
    ComponentMask() = default;

    /// Add a component to this component mask
    ComponentMask& set(ComponentType type);

    /// Remove a component from this component mask
    ComponentMask& unset(ComponentType type);

    /// Check if a component is present in the mask
    bool test(ComponentType type) const;

    /// Check if this component mask contains the given component mask
    bool contains(const ComponentMask& other) const;

    /// Check if the number of components is zero
    bool is_empty() const;

    /// Get the number of components
    std::size_t count() const;

    // iterators

    Iterator begin() const;

    Iterator end() const;

    // operators

    ComponentMask& operator&=(const ComponentMask& other);

    ComponentMask& operator|=(const ComponentMask& other);

    ComponentMask& operator^=(const ComponentMask& other);

    ComponentMask operator~() const;

private:
    std::bitset<max_components> m_bitset;
};

// operators

bool operator==(const ComponentMask& lhs, const ComponentMask& rhs);

bool operator!=(const ComponentMask& lhs, const ComponentMask& rhs);

ComponentMask operator&(ComponentMask lhs, const ComponentMask& rhs);

ComponentMask operator|(ComponentMask lhs, const ComponentMask& rhs);

ComponentMask operator^(ComponentMask lhs, const ComponentMask& rhs);

bool operator==(const ComponentMask::Iterator& lhs, const ComponentMask::Iterator& rhs);

bool operator!=(const ComponentMask::Iterator& lhs, const ComponentMask::Iterator& rhs);

// helpers

/// Create a component set from the given component types
template <typename... Components>
ComponentMask make_component_mask() {
    ComponentMask components;
    (components.set(component_type<Components>()), ...);
    return components;
}

} // namespace msq::ecs

template <>
struct std::hash<msq::ecs::ComponentMask> {
    std::size_t operator()(const msq::ecs::ComponentMask& mask) const noexcept {
        return std::hash<std::bitset<msq::ecs::max_components>> {}(mask.m_bitset);
    }
};
