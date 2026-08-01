// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/engine/input/input_state.hpp"
#include "msquared/engine/input/mouse_button.hpp"

#include <array>

namespace msq {

class Mouse {
public:
    /// Check if the button is pressed this frame
    bool is_pressed(MouseButton button) const;

    /// Check if the button was pressed the previous frame and is still pressed
    bool is_held(MouseButton button) const;

    /// Check if the button was not pressed the previous frame but is pressed
    /// now
    bool was_just_pressed(MouseButton button) const;

    /// Check if the button was pressed the previous frame but is not pressed
    /// now
    bool was_just_released(MouseButton button) const;

    /// Call once every frame before input handling
    void begin_frame();

    /// Call once every frame to update the state of a button
    void update(MouseButton button, bool pressed);

    /// Reset the states to non-pressed
    void reset();

private:
    std::array<InputState, 5> m_button_states;
};

} // namespace msq
