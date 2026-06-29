// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/sdl/detail/pointer.hpp"
#include "msquared/sdl/renderer.hpp"

#include <msquared/core/math/point2.hpp>
#include <msquared/core/size2.hpp>

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
Window create_window(const char* title, const Size2i& size, SDL_WindowFlags flags);

/// Create a window and a renderer
std::pair<Window, Renderer> create_window_and_renderer(const char* title, const Size2i& size, SDL_WindowFlags flags);

/// Create a popup style window
Window create_popup_window(SDL_Window* parent, const Point2i& offset, const Size2i& size);

/// Create a tooltip style window
Window create_tooltip_window(SDL_Window* parent, const Point2i& offset, const Size2i& size);

} // namespace msq::sdl
