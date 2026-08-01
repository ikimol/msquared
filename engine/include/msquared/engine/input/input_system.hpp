// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/engine/input/action_id.hpp"
#include "msquared/engine/input/input_context.hpp"
#include "msquared/engine/input/keyboard.hpp"
#include "msquared/engine/input/mouse.hpp"

#include <SDL3/SDL_events.h>

#include <vector>

namespace msq {

/// The unique ID of a context
using ContextID = std::uint8_t;

class InputSystem {
public:
    /// Register an input context
    [[nodiscard]] ContextID register_context(std::string name);

    /// Set the active input context
    void set_active_context(ContextID context_id);

    /// Get the input map for a registerd context
    InputMap& input_map_for(ContextID context_id);

    /// Check if the action is pressed this frame
    bool is_pressed(ActionID action_id) const;

    /// Check if the action was pressed the previous frame and is still pressed
    bool is_held(ActionID action_id) const;

    /// Check if the action was not pressed the previous frame but is pressed
    /// now
    bool was_just_pressed(ActionID action_id) const;

    /// Check if the action was pressed the previous frame but is not pressed
    /// now
    bool was_just_released(ActionID action_id) const;

    /// Call once every frame before input handling
    void begin_frame();

    /// Handle a single event
    void handle_event(const SDL_Event& event);

    /// Reset every input state
    void reset();

private:
    constexpr static ContextID invalid_context = static_cast<ContextID>(-1);

private:
    Mouse m_mouse;
    Keyboard m_keyboard;
    ContextID m_active_context_id = invalid_context;
    std::vector<InputContext> m_contexts;
};

} // namespace msq
