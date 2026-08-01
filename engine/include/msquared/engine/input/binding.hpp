// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/engine/input/mouse_button.hpp"

#include <shard/enums/flags.hpp>

#include <SDL3/SDL_scancode.h>

#include <cstdint>
#include <variant>

namespace msq {

/// A raw digital input
using Input = std::variant<SDL_Scancode, MouseButton>;

/// A bitset of modifier keys
enum class Modifier : std::uint8_t {
    None = 0,
    Shift = 1 << 0,
    Ctrl = 1 << 1,
    Alt = 1 << 2,
    System = 1 << 3,
};
SHARD_DECLARE_FLAGS(Modifiers, Modifier)
SHARD_DECLARE_FLAG_OPERATORS(Modifiers)

/// Some raw input that can be bound to an action
struct Binding {
    Input input;
    Modifiers modifiers = Modifier::None;
};

// operators

bool operator==(Binding lhs, Binding rhs);

bool operator!=(Binding lhs, Binding rhs);

} // namespace msq
