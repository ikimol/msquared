// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/sdl/detail/pointer.hpp"

#include <msquared/core/color.hpp>
#include <msquared/core/math/point2.hpp>
#include <msquared/core/rect2.hpp>

#include <SDL3/SDL_render.h>

#include <optional>

namespace msq::sdl {
namespace detail {

template <>
struct Deleter<SDL_Renderer> {
    void operator()(SDL_Renderer* ptr) const noexcept { SDL_DestroyRenderer(ptr); }
};

} // namespace detail

/// Alias for managed SDL_Renderer
using Renderer = detail::Pointer<SDL_Renderer>;

// operations

/// Create a renderer for the window
Renderer create_renderer(SDL_Window* window, const char* name);

/// Get the draw color as an SDL_Color
Color get_draw_color(SDL_Renderer* renderer);

/// Set the draw color from an SDL_Color
void set_draw_color(SDL_Renderer* renderer, const Color& color);

/// Get the active viewport
Rect2i get_viewport(SDL_Renderer* renderer);

/// Set a new viewport
void set_viewport(SDL_Renderer* renderer, const Rect2i& rect);

/// Reset the active viewport to its default
void reset_viewport(SDL_Renderer* renderer);

/// Get the active clipping rectangle, if one is set
std::optional<Rect2i> get_clip_rect(SDL_Renderer* renderer);

/// Set a clipping rectangle
void set_clip_rect(SDL_Renderer* renderer, const Rect2i& rect);

/// Clear the active clipping rectangle
void clear_clip_rect(SDL_Renderer* renderer);

/// Draw some text for debugging purposes
void render_debug_text(SDL_Renderer* renderer, const Point2f& p, const char* str);

/// Draw some formatted text for debugging purposes
template <typename... Args>
void render_debug_text_format(SDL_Renderer* renderer, const Point2f& p, const char* fmt, Args&&... args) {
    SDL_RenderDebugTextFormat(renderer, p.x, p.y, fmt, std::forward<Args>(args)...);
}

} // namespace msq::sdl
