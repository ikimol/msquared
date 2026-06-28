// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/engine/gfx/texture_handle.hpp"

#include <SDL3/SDL_render.h>

#include <vector>

namespace msq {

/// A pool used to assign and recycle texture handles
class TexturePool {
public:
    /// Check if a texture has been added
    bool contains(TextureHandle handle) const noexcept;

    /// Retrieve a previously added texture
    SDL_Texture* get(TextureHandle handle) const noexcept;

    /// Add a texture and get a handle
    [[nodiscard]] TextureHandle add(SDL_Texture* texture);

    /// Remove a previously added texture and recycle its ID
    void remove(TextureHandle handle);

private:
    std::vector<SDL_Texture*> m_textures;
    std::vector<std::uint16_t> m_recycled;
};

} // namespace msq
