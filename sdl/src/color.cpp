// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/sdl/color.hpp"

namespace msq::sdl {

SDL_Color to_color(const Color& color) {
    return SDL_Color {color.r, color.g, color.b, color.a};
}

SDL_FColor to_fcolor(const Color& color) {
    return SDL_FColor {
        static_cast<float>(color.r) / 255.f,
        static_cast<float>(color.g) / 255.f,
        static_cast<float>(color.b) / 255.f,
        static_cast<float>(color.a) / 255.f,
    };
}

} // namespace msq::sdl
