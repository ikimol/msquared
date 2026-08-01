// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/engine/input/mouse.hpp"

#include <shard/enums/type.hpp>

namespace msq {
namespace {

std::size_t button_index(MouseButton button) {
    return static_cast<std::size_t>(shard::to_underlying(button) - 1);
}

} // namespace

bool Mouse::is_pressed(MouseButton button) const {
    return m_button_states[button_index(button)].is_pressed();
}

bool Mouse::is_held(MouseButton button) const {
    return m_button_states[button_index(button)].is_held();
}

bool Mouse::was_just_pressed(MouseButton button) const {
    return m_button_states[button_index(button)].was_just_pressed();
}

bool Mouse::was_just_released(MouseButton button) const {
    return m_button_states[button_index(button)].was_just_released();
}

void Mouse::begin_frame() {
    for (auto& state : m_button_states) {
        state.begin_frame();
    }
}

void Mouse::update(MouseButton button, bool pressed) {
    m_button_states[button_index(button)].update(pressed);
}

void Mouse::reset() {
    for (auto& state : m_button_states) {
        state.reset();
    }
}

} // namespace msq
