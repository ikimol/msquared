// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/sdl/surface.hpp"

namespace msq::sdl {

bool read_pixel(SDL_Surface* surface, int x, int y, SDL_Color& color) {
    return SDL_ReadSurfacePixel(surface, x, y, &color.r, &color.g, &color.b, &color.a);
}

bool write_pixel(SDL_Surface* surface, int x, int y, const SDL_Color& color) {
    return SDL_WriteSurfacePixel(surface, x, y, color.r, color.g, color.b, color.a);
}

bool read_pixel(SDL_Surface* surface, int x, int y, SDL_FColor& color) {
    return SDL_ReadSurfacePixelFloat(surface, x, y, &color.r, &color.g, &color.b, &color.a);
}

bool write_pixel(SDL_Surface* surface, int x, int y, const SDL_FColor& color) {
    return SDL_WriteSurfacePixelFloat(surface, x, y, color.r, color.g, color.b, color.a);
}

} // namespace msq::sdl
