// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/sdl/detail/pointer.hpp"

#include <SDL3/SDL_surface.h>

namespace msq::sdl {
namespace detail {

template <>
struct Deleter<SDL_Surface> {
    void operator()(SDL_Surface* ptr) const noexcept { SDL_DestroySurface(ptr); }
};

} // namespace detail

/// Alias for managed SDL_Surface
using Surface = detail::Pointer<SDL_Surface>;

// operations

/// Read the color value of a single pixel
bool read_pixel(SDL_Surface* surface, int x, int y, SDL_Color& color);

/// Modify the color value of a single pixel
bool write_pixel(SDL_Surface* surface, int x, int y, const SDL_Color& color);

/// Read the color value of a single pixel
bool read_pixel(SDL_Surface* surface, int x, int y, SDL_FColor& color);

/// Modify the color value of a single pixel
bool write_pixel(SDL_Surface* surface, int x, int y, const SDL_FColor& color);

} // namespace msq::sdl
