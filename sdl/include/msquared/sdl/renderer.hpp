// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/sdl/detail/pointer.hpp"
#include "msquared/sdl/window.hpp"

#include <SDL3/SDL_render.h>

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
bool get_draw_color(SDL_Renderer* renderer, SDL_Color& color);

/// Set the draw color from an SDL_Color
bool set_draw_color(SDL_Renderer* renderer, SDL_Color color);

/// Get the draw color as an SDL_FColor
bool get_draw_color(SDL_Renderer* renderer, SDL_FColor& color);

/// Set the draw color from an SDL_FColor
bool set_draw_color(SDL_Renderer* renderer, SDL_FColor color);

/// Draw an array of vertices
bool render_vertices(SDL_Renderer* renderer, const SDL_Vertex* vertices, int num_vertices);

/// Draw an array of indexed vertices
bool render_vertices(SDL_Renderer* renderer,
                     const SDL_Vertex* vertices,
                     int num_vertices,
                     const int* indices,
                     int num_indices);

/// Draw an array of vertices with a texture
bool render_vertices(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Vertex* vertices, int num_vertices);

/// Draw some text for debugging purposes
bool render_debug_text(SDL_Renderer* renderer, const SDL_FPoint& p, const char* str);

/// Draw some formatted text for debugging purposes
template <typename... Args>
bool render_debug_text_format(SDL_Renderer* renderer, const SDL_FPoint& p, const char* fmt, Args&&... args) {
    return SDL_RenderDebugTextFormat(renderer, p.x, p.y, fmt, std::forward<Args>(args)...);
}

} // namespace msq::sdl
