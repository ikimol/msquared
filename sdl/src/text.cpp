// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/sdl/text.hpp"

namespace msq::sdl {

Text create_text(TTF_TextEngine* engine, TTF_Font* font, const char* text, std::size_t length) {
    return Text(TTF_CreateText(engine, font, text, length));
}

bool get_text_color(TTF_Text* text, SDL_Color& color) {
    return TTF_GetTextColor(text, &color.r, &color.g, &color.b, &color.a);
}

bool set_text_color(TTF_Text* text, const SDL_Color& color) {
    return TTF_SetTextColor(text, color.r, color.g, color.b, color.a);
}

bool get_text_color(TTF_Text* text, SDL_FColor& color) {
    return TTF_GetTextColorFloat(text, &color.r, &color.g, &color.b, &color.a);
}

bool set_text_color(TTF_Text* text, const SDL_FColor& color) {
    return TTF_SetTextColorFloat(text, color.r, color.g, color.b, color.a);
}

bool set_text_position(TTF_Text* text, const SDL_Point& p) {
    return TTF_SetTextPosition(text, p.x, p.y);
}

} // namespace msq::sdl
