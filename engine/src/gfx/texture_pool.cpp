// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/engine/gfx/texture_pool.hpp"

#include <msquared/core/assert.hpp>

#include <limits>

namespace msq {

bool TexturePool::contains(TextureHandle handle) const noexcept {
    return handle.id < m_textures.size() && m_textures[handle.id] != nullptr;
}

SDL_Texture* TexturePool::get(TextureHandle handle) const noexcept {
    MSQ_ASSERT(contains(handle), "invalid texture handle");
    return m_textures[handle.id];
}

TextureHandle TexturePool::add(SDL_Texture* texture) {
    MSQ_ASSERT(m_textures.size() < std::numeric_limits<std::uint16_t>::max(), "texture pool is full");
    std::uint16_t id;
    if (!m_recycled.empty()) {
        id = m_recycled.back();
        m_textures[id] = texture;
        m_recycled.pop_back();
    } else {
        id = m_textures.size();
        m_textures.push_back(texture);
    }
    return TextureHandle {id};
}

void TexturePool::remove(TextureHandle handle) {
    MSQ_ASSERT(contains(handle), "invalid texture handle");
    m_textures[handle.id] = nullptr;
    m_recycled.push_back(handle.id);
}

} // namespace msq
