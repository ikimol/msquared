// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

namespace msq {

/// The state of a single key or mouse button
class InputState {
public:
    /// Check if the input is pressed this frame
    bool is_pressed() const;

    /// Check if the input was pressed the previous frame and is still pressed
    bool is_held() const;

    /// Check if the input was not pressed the previous frame but is now pressed
    bool was_just_pressed() const;

    /// Check if the input was pressed the previous frame but is not pressed now
    bool was_just_released() const;

    /// Call once every frame before input handling
    void begin_frame();

    /// Call once every frame to update the state
    void update(bool pressed);

    /// Reset the state to non-pressed
    void reset();

private:
    bool m_pressed = false;
    bool m_was_pressed = false;
};

} // namespace msq
