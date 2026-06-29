// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/sdl/texture.hpp"

#include <SDL3_image/SDL_image.h>

namespace msq::sdl {

Texture load_texture(SDL_Renderer* renderer, const char* path) {
    return Texture(IMG_LoadTexture(renderer, path));
}

Texture load_texture(SDL_Renderer* renderer, const void* memory, std::size_t size) {
    return Texture(IMG_LoadTexture_IO(renderer, SDL_IOFromConstMem(memory, static_cast<int>(size)), true));
}

Texture create_target_texture(SDL_Renderer* renderer) {
    auto window = SDL_GetRenderWindow(renderer);
    auto format = SDL_GetWindowPixelFormat(window);
    int w, h;
    SDL_GetRenderOutputSize(renderer, &w, &h);
    return Texture(SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET, w, h));
}

Size2f get_texture_size(SDL_Texture* texture) {
    Size2f size;
    SDL_GetTextureSize(texture, &size.w, &size.h);
    return size;
}

} // namespace msq::sdl
