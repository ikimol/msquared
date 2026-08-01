// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/engine/input/keyboard.hpp"

namespace msq {

bool Keyboard::is_pressed(SDL_Scancode key) const {
    return m_key_states[key].is_pressed();
}

bool Keyboard::is_held(SDL_Scancode key) const {
    return m_key_states[key].is_held();
}

bool Keyboard::was_just_pressed(SDL_Scancode key) const {
    return m_key_states[key].was_just_pressed();
}

bool Keyboard::was_just_released(SDL_Scancode key) const {
    return m_key_states[key].was_just_released();
}

void Keyboard::begin_frame() {
    for (auto& state : m_key_states) {
        state.begin_frame();
    }
}

void Keyboard::update(SDL_Scancode key, bool pressed) {
    m_key_states[key].update(pressed);
}

void Keyboard::reset() {
    for (auto& state : m_key_states) {
        state.reset();
    }
}

} // namespace msq
