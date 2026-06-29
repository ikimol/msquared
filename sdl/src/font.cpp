// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/sdl/font.hpp"

namespace msq::sdl {

Font load_font(const char* path, float font_size) {
    return Font(TTF_OpenFont(path, font_size));
}

Font load_font(const void* memory, std::size_t size, float font_size) {
    return Font(TTF_OpenFontIO(SDL_IOFromConstMem(memory, static_cast<int>(size)), true, font_size));
}

} // namespace msq::sdl
