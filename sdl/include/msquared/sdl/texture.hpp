// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/sdl/detail/pointer.hpp"

#include <msquared/core/size2.hpp>

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

/// Load a texture from an image file
Texture load_texture(SDL_Renderer* renderer, const char* path);

/// Load a texture from memory
Texture load_texture(SDL_Renderer* renderer, const void* memory, std::size_t size);

/// Create a target texture using a renderer
Texture create_target_texture(SDL_Renderer* renderer);

/// Get the size of the texture
Size2f get_texture_size(SDL_Texture* texture);

} // namespace msq::sdl
