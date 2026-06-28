// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/engine/gfx/draw_index.hpp"
#include "msquared/engine/gfx/draw_list.hpp"
#include "msquared/engine/gfx/mesh_pool.hpp"
#include "msquared/engine/gfx/texture_pool.hpp"
#include "msquared/engine/gfx/vertex.hpp"
#include "msquared/engine/gfx/viewport.hpp"

#include <msquared/core/color.hpp>

#include <SDL3/SDL_render.h>

#include <vector>

namespace msq {

/// Renderer used for drawing objects
class Renderer {
public:
    explicit Renderer(SDL_Renderer* renderer, const TexturePool& texture_pool, const MeshPool& mesh_pool);

    /// Set the color to use for clearing the target
    void set_clear_color(Color color);

    /// Call once every frame before rendering
    void begin_frame();

    /// Call once every frame after rendering
    void end_frame();

    /// Render the contents of a drawlist using the viewport
    void flush(const DrawList& draw_list, const Viewport& viewport);

private:
    SDL_Renderer* m_renderer;
    const TexturePool& m_texture_pool;
    const MeshPool& m_mesh_pool;

    Color m_clear_color;

    std::vector<Vertex> m_vertices;
    std::vector<DrawIndex> m_indices;
    std::vector<SDL_FColor> m_colors;
};

} // namespace msq
