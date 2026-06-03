// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/ecs/component_mask.hpp"

namespace msq::ecs {
namespace {

template <std::size_t N>
std::size_t find_next(const std::bitset<N>& bitset, std::size_t from) {
    for (std::size_t i = from; i < N; ++i) {
        if (bitset.test(i)) {
            return i;
        }
    }
    return N;
}

} // namespace

ComponentMask& ComponentMask::set(ComponentType type) {
    m_bitset.set(type.value());
    return *this;
}

ComponentMask& ComponentMask::unset(ComponentType type) {
    m_bitset.reset(type.value());
    return *this;
}

bool ComponentMask::test(ComponentType type) const {
    return m_bitset.test(type.value());
}

bool ComponentMask::contains(const ComponentMask& other) const {
    return (m_bitset & other.m_bitset) == other.m_bitset;
}

bool ComponentMask::is_empty() const {
    return m_bitset.count() == 0;
}

std::size_t ComponentMask::count() const {
    return m_bitset.count();
}

ComponentMask::Iterator ComponentMask::begin() const {
    return {*this, find_next(m_bitset, 0)};
}

ComponentMask::Iterator ComponentMask::end() const {
    return {*this, m_bitset.size()};
}

ComponentMask& ComponentMask::operator&=(const ComponentMask& other) {
    m_bitset &= other.m_bitset;
    return *this;
}

ComponentMask& ComponentMask::operator|=(const ComponentMask& other) {
    m_bitset |= other.m_bitset;
    return *this;
}

ComponentMask& ComponentMask::operator^=(const ComponentMask& other) {
    m_bitset ^= other.m_bitset;
    return *this;
}

ComponentMask ComponentMask::operator~() const {
    ComponentMask copy(*this);
    copy.m_bitset = ~m_bitset;
    return copy;
}

bool operator==(const ComponentMask& lhs, const ComponentMask& rhs) {
    return lhs.m_bitset == rhs.m_bitset;
}

bool operator!=(const ComponentMask& lhs, const ComponentMask& rhs) {
    return !(lhs == rhs);
}

ComponentMask operator&(ComponentMask lhs, const ComponentMask& rhs) {
    return lhs &= rhs;
}

ComponentMask operator|(ComponentMask lhs, const ComponentMask& rhs) {
    return lhs |= rhs;
}

ComponentMask operator^(ComponentMask lhs, const ComponentMask& rhs) {
    return lhs ^= rhs;
}

// iterator

ComponentMask::Iterator::Iterator(const ComponentMask& mask, std::size_t index)
: m_mask(mask)
, m_index(index) {}

ComponentType ComponentMask::Iterator::operator*() const {
    return ComponentType(m_index);
}

ComponentMask::Iterator& ComponentMask::Iterator::operator++() {
    m_index = find_next(m_mask.m_bitset, m_index + 1);
    return *this;
}

bool operator==(const ComponentMask::Iterator& lhs, const ComponentMask::Iterator& rhs) {
    return &lhs.m_mask == &rhs.m_mask && lhs.m_index == rhs.m_index;
}

bool operator!=(const ComponentMask::Iterator& lhs, const ComponentMask::Iterator& rhs) {
    return !(lhs == rhs);
}

} // namespace msq::ecs
