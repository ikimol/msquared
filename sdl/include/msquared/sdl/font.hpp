// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/sdl/detail/pointer.hpp"

#include <SDL3_ttf/SDL_ttf.h>

namespace msq::sdl {
namespace detail {

template <>
struct Deleter<TTF_Font> {
    void operator()(TTF_Font* ptr) const noexcept { TTF_CloseFont(ptr); }
};

} // namespace detail

/// Alias for managed TTF_Font
using Font = detail::Pointer<TTF_Font>;

} // namespace msq::sdl
