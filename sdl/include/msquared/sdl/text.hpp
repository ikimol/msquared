// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/sdl/detail/pointer.hpp"

#include <msquared/core/color.hpp>
#include <msquared/core/math/point2.hpp>

#include <SDL3_ttf/SDL_ttf.h>

namespace msq::sdl {
namespace detail {

template <>
struct Deleter<TTF_Text> {
    void operator()(TTF_Text* ptr) const noexcept { TTF_DestroyText(ptr); }
};

} // namespace detail

/// Alias for managed TTF_Text
using Text = detail::Pointer<TTF_Text>;

// operations

/// Create text
Text create_text(TTF_TextEngine* engine, TTF_Font* font, const char* text, std::size_t length);

/// Get the color of the text
Color get_text_color(TTF_Text* text);

/// Set the color of the text
void set_text_color(TTF_Text* text, const Color& color);

/// Set the position of the text
bool set_text_position(TTF_Text* text, const Point2i& p);

} // namespace msq::sdl
