// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include <msquared/core/color.hpp>

#include <SDL3/SDL_pixels.h>

namespace msq::sdl {

/// Convert a color to an SDL color type
SDL_Color to_color(const Color& color);

/// Convert a color to an SDL float color type
SDL_FColor to_fcolor(const Color& color);

} // namespace msq::sdl
