// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/sdl/surface.hpp"

#include <SDL3_image/SDL_image.h>

namespace msq::sdl {

Surface load_surface(const char* path) {
    return Surface(IMG_Load(path));
}

Surface load_surface(const void* memory, std::size_t size) {
    return Surface(IMG_Load_IO(SDL_IOFromConstMem(memory, static_cast<int>(size)), true));
}

Color read_pixel(SDL_Surface* surface, const Point2i& p) {
    Color color;
    SDL_ReadSurfacePixel(surface, p.x, p.y, &color.r, &color.g, &color.b, &color.a);
    return color;
}

void write_pixel(SDL_Surface* surface, const Point2i& p, const Color& color) {
    SDL_WriteSurfacePixel(surface, p.x, p.y, color.r, color.g, color.b, color.a);
}

} // namespace msq::sdl
