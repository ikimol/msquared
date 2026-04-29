// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/sdl/window.hpp"

namespace msq::sdl {

Window create_window(const char* title, int w, int h, SDL_WindowFlags flags) {
    return Window(SDL_CreateWindow(title, w, h, flags));
}

Window create_popup_window(SDL_Window* parent, int offset_x, int offset_y, int w, int h) {
    return Window(SDL_CreatePopupWindow(parent, offset_x, offset_y, w, h, SDL_WINDOW_POPUP_MENU));
}

Window create_tooltip_window(SDL_Window* parent, int offset_x, int offset_y, int w, int h) {
    return Window(SDL_CreatePopupWindow(parent, offset_x, offset_y, w, h, SDL_WINDOW_TOOLTIP));
}

} // namespace msq::sdl
