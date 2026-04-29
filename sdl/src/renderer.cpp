// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/sdl/renderer.hpp"

namespace msq::sdl {

Renderer create_renderer(SDL_Window* window, const char* name) {
    return Renderer(SDL_CreateRenderer(window, name));
}

bool get_draw_color(SDL_Renderer* renderer, SDL_Color& color) {
    return SDL_GetRenderDrawColor(renderer, &color.r, &color.g, &color.b, &color.a);
}

bool set_draw_color(SDL_Renderer* renderer, SDL_Color color) {
    return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

bool get_draw_color(SDL_Renderer* renderer, SDL_FColor& color) {
    return SDL_GetRenderDrawColorFloat(renderer, &color.r, &color.g, &color.b, &color.a);
}

bool set_draw_color(SDL_Renderer* renderer, SDL_FColor color) {
    return SDL_SetRenderDrawColorFloat(renderer, color.r, color.g, color.b, color.a);
}

bool render_vertices(SDL_Renderer* renderer, const SDL_Vertex* vertices, int num_vertices) {
    return SDL_RenderGeometry(renderer, nullptr, vertices, num_vertices, nullptr, 0);
}

bool render_vertices(SDL_Renderer* renderer,
                     const SDL_Vertex* vertices,
                     int num_vertices,
                     const int* indices,
                     int num_indices) {
    return SDL_RenderGeometry(renderer, nullptr, vertices, num_vertices, indices, num_indices);
}

bool render_vertices(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Vertex* vertices, int num_vertices) {
    return SDL_RenderGeometry(renderer, texture, vertices, num_vertices, nullptr, 0);
}

bool render_debug_text(SDL_Renderer* renderer, const SDL_FPoint& p, const char* str) {
    return SDL_RenderDebugText(renderer, p.x, p.y, str);
}

} // namespace msq::sdl
