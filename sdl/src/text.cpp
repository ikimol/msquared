// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/sdl/text.hpp"

namespace msq::sdl {

Text create_text(TTF_TextEngine* engine, TTF_Font* font, const char* text, std::size_t length) {
    return Text(TTF_CreateText(engine, font, text, length));
}

Color get_text_color(TTF_Text* text) {
    Color color;
    TTF_GetTextColor(text, &color.r, &color.g, &color.b, &color.a);
    return color;
}

void set_text_color(TTF_Text* text, const Color& color) {
    TTF_SetTextColor(text, color.r, color.g, color.b, color.a);
}

bool set_text_position(TTF_Text* text, const Point2i& p) {
    return TTF_SetTextPosition(text, p.x, p.y);
}

} // namespace msq::sdl
