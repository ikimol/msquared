// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include <SDL3/SDL_mouse.h>

namespace msq {

/// Supported buttons on a mouse
enum class MouseButton {
    Left = SDL_BUTTON_LEFT,
    Middle = SDL_BUTTON_MIDDLE,
    Right = SDL_BUTTON_RIGHT,
    Extra1 = SDL_BUTTON_X1,
    Extra2 = SDL_BUTTON_X2,
};

} // namespace msq
