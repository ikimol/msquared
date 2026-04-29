// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/sdl/detail/pointer.hpp"

#include <SDL3/SDL_video.h>

namespace msq::sdl {
namespace detail {

template <>
struct Deleter<SDL_Window> {
    void operator()(SDL_Window* ptr) const noexcept { SDL_DestroyWindow(ptr); }
};

} // namespace detail

/// Alias for managed SDL_Window
using Window = detail::Pointer<SDL_Window>;

// operations

/// Create a window
Window create_window(const char* title, int w, int h, SDL_WindowFlags flags);

/// Create a popup style window
Window create_popup_window(SDL_Window* parent, int offset_x, int offset_y, int w, int h);

/// Create a tooltip style window
Window create_tooltip_window(SDL_Window* parent, int offset_x, int offset_y, int w, int h);

} // namespace msq::sdl
