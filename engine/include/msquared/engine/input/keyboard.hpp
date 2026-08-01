// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/engine/input/input_state.hpp"

#include <SDL3/SDL_scancode.h>

#include <array>

namespace msq {

class Keyboard {
public:
    /// Check if the key is pressed this frame
    bool is_pressed(SDL_Scancode key) const;

    /// Check if the key was pressed the previous frame and is still pressed
    bool is_held(SDL_Scancode key) const;

    /// Check if the key was not pressed the previous frame but is pressed now
    bool was_just_pressed(SDL_Scancode key) const;

    /// Check if the key was pressed the previous frame but is not pressed now
    bool was_just_released(SDL_Scancode key) const;

    /// Call once every frame before input handling
    void begin_frame();

    /// Call once every frame to update the state of a key
    void update(SDL_Scancode key, bool pressed);

    /// Reset the states to non-pressed
    void reset();

private:
    std::array<InputState, SDL_SCANCODE_COUNT> m_key_states;
};

} // namespace msq
