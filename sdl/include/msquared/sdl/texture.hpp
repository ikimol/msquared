// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/sdl/detail/pointer.hpp"

#include <SDL3/SDL_render.h>

namespace msq::sdl {
namespace detail {

template <>
struct Deleter<SDL_Texture> {
    void operator()(SDL_Texture* ptr) const noexcept { SDL_DestroyTexture(ptr); }
};

} // namespace detail

/// Type of managed SDL_Texture
using Texture = detail::Pointer<SDL_Texture>;

// operations

/// Create a target texture using a renderer
Texture create_target_texture(SDL_Renderer* renderer);

} // namespace msq::sdl
