// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/engine/input/input_state.hpp"

namespace msq {

bool InputState::is_pressed() const {
    return m_pressed;
}

bool InputState::is_held() const {
    return m_was_pressed && m_pressed;
}

bool InputState::was_just_pressed() const {
    return !m_was_pressed && m_pressed;
}

bool InputState::was_just_released() const {
    return m_was_pressed && !m_pressed;
}

void InputState::begin_frame() {
    m_was_pressed = m_pressed;
}

void InputState::update(bool pressed) {
    m_pressed = pressed;
}

void InputState::reset() {
    m_pressed = false;
    m_was_pressed = false;
}

} // namespace msq
