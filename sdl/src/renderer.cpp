// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/sdl/renderer.hpp"

namespace msq::sdl {

Renderer create_renderer(SDL_Window* window, const char* name) {
    return Renderer(SDL_CreateRenderer(window, name));
}

Color get_draw_color(SDL_Renderer* renderer) {
    Color color;
    SDL_GetRenderDrawColor(renderer, &color.r, &color.g, &color.b, &color.a);
    return color;
}

void set_draw_color(SDL_Renderer* renderer, const Color& color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

Rect2i get_viewport(SDL_Renderer* renderer) {
    SDL_Rect rect;
    SDL_GetRenderViewport(renderer, &rect);
    return Rect2i(rect.x, rect.y, rect.w, rect.h);
}

void set_viewport(SDL_Renderer* renderer, const Rect2i& rect) {
    SDL_Rect r {rect.x, rect.y, rect.w, rect.h};
    SDL_SetRenderViewport(renderer, &r);
}

void reset_viewport(SDL_Renderer* renderer) {
    SDL_SetRenderViewport(renderer, nullptr);
}

std::optional<Rect2i> get_clip_rect(SDL_Renderer* renderer) {
    if (SDL_RenderClipEnabled(renderer)) {
        SDL_Rect rect;
        SDL_GetRenderClipRect(renderer, &rect);
        return Rect2i(rect.x, rect.y, rect.w, rect.h);
    }
    return std::nullopt;
}

void set_clip_rect(SDL_Renderer* renderer, const Rect2i& rect) {
    SDL_Rect r {rect.x, rect.y, rect.w, rect.h};
    SDL_SetRenderClipRect(renderer, &r);
}

void clear_clip_rect(SDL_Renderer* renderer) {
    SDL_SetRenderClipRect(renderer, nullptr);
}

void render_debug_text(SDL_Renderer* renderer, const Point2f& p, const char* str) {
    SDL_RenderDebugText(renderer, p.x, p.y, str);
}

} // namespace msq::sdl
