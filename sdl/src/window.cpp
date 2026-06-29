// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/sdl/window.hpp"

namespace msq::sdl {

Window create_window(const char* title, const Size2i& size, SDL_WindowFlags flags) {
    return Window(SDL_CreateWindow(title, size.w, size.h, flags));
}

std::pair<Window, Renderer> create_window_and_renderer(const char* title, const Size2i& size, SDL_WindowFlags flags) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(title, size.w, size.h, flags, &window, &renderer);
    return std::make_pair(Window(window), Renderer(renderer));
}

Window create_popup_window(SDL_Window* parent, const Point2i& offset, const Size2i& size) {
    return Window(SDL_CreatePopupWindow(parent, offset.x, offset.y, size.w, size.h, SDL_WINDOW_POPUP_MENU));
}

Window create_tooltip_window(SDL_Window* parent, const Point2i& offset, const Size2i& size) {
    return Window(SDL_CreatePopupWindow(parent, offset.x, offset.y, size.w, size.h, SDL_WINDOW_TOOLTIP));
}

} // namespace msq::sdl
