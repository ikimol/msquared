// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/sdl/detail/pointer.hpp"

#include <msquared/core/color.hpp>
#include <msquared/core/math/point2.hpp>

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

/// Load a surface from an image file
Surface load_surface(const char* path);

/// Load a surface from memory
Surface load_surface(const void* memory, std::size_t size);

/// Read the color value of a single pixel
Color read_pixel(SDL_Surface* surface, const Point2i& p);

/// Modify the color value of a single pixel
void write_pixel(SDL_Surface* surface, const Point2i& p, const Color& color);

} // namespace msq::sdl
