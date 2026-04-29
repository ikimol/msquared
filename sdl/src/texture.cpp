// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/sdl/texture.hpp"

namespace msq::sdl {

Texture create_target_texture(SDL_Renderer* renderer) {
    auto window = SDL_GetRenderWindow(renderer);
    auto format = SDL_GetWindowPixelFormat(window);
    int w, h;
    SDL_GetRenderOutputSize(renderer, &w, &h);
    return Texture(SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET, w, h));
}

} // namespace msq::sdl
