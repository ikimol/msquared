// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/engine/gfx/renderer.hpp"

#include <limits>

#include <shard/algorithm/variant_switch.hpp>

namespace msq {
namespace {

constexpr auto max_draw_index = std::numeric_limits<DrawIndex>::max();

} // namespace

Renderer::Renderer(SDL_Renderer* renderer, const TexturePool& texture_pool, const MeshPool& mesh_pool)
: m_renderer(renderer)
, m_texture_pool(texture_pool)
, m_mesh_pool(mesh_pool) {
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
}

void Renderer::set_clear_color(Color color) {
    m_clear_color = color;
}

void Renderer::begin_frame() {
    SDL_SetRenderDrawColor(m_renderer, m_clear_color.r, m_clear_color.g, m_clear_color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
}

void Renderer::end_frame() {
    SDL_SetRenderViewport(m_renderer, nullptr);
    SDL_RenderPresent(m_renderer);
}

void Renderer::flush(const DrawList& draw_list, const Viewport& viewport) {
    SDL_Rect viewport_rect {viewport.area.x, viewport.area.y, viewport.area.w, viewport.area.h};
    SDL_SetRenderViewport(m_renderer, &viewport_rect);

    auto submit_batch = [this](SDL_Texture* texture) {
        const auto* base = reinterpret_cast<const std::byte*>(m_vertices.data());
        auto* xy = reinterpret_cast<const float*>(base + offsetof(Vertex, xy));
        auto* uv = reinterpret_cast<const float*>(base + offsetof(Vertex, uv));

        SDL_RenderGeometryRaw(m_renderer,
                              texture,
                              xy,
                              sizeof(Vertex),
                              m_colors.data(),
                              sizeof(SDL_FColor),
                              uv,
                              sizeof(Vertex),
                              static_cast<int>(m_vertices.size()),
                              m_indices.data(),
                              static_cast<int>(m_indices.size()),
                              sizeof(DrawIndex));

        m_vertices.clear();
        m_indices.clear();
        m_colors.clear();
    };

    auto add_quad_vertices = [this](const DrawQuadCommand& command, const Transform& transform, Size2f texture_size) {
        MSQ_ASSERT(m_vertices.size() < max_draw_index, "vertex buffer is full");

        Rect2f rect(command.texture_rect);

        Point2f xy[4] = {
            transform.apply_to(Point2f(0.f, 0.f)),
            transform.apply_to(Point2f(rect.w, 0.f)),
            transform.apply_to(Point2f(rect.w, rect.h)),
            transform.apply_to(Point2f(0.f, rect.h)),
        };

        Point2f uv[4] = {
            {           rect.x / texture_size.w,            rect.y / texture_size.h},
            {(rect.x + rect.w) / texture_size.w,            rect.y / texture_size.h},
            {(rect.x + rect.w) / texture_size.w, (rect.y + rect.h) / texture_size.h},
            {           rect.x / texture_size.w, (rect.y + rect.h) / texture_size.h},
        };

        SDL_FColor sdl_color {
            static_cast<float>(command.color.r) / 255.f,
            static_cast<float>(command.color.g) / 255.f,
            static_cast<float>(command.color.b) / 255.f,
            static_cast<float>(command.color.a) / 255.f,
        };

        const auto base_index = static_cast<DrawIndex>(m_vertices.size());

        for (auto i = 0; i < 4; ++i) {
            m_vertices.push_back({xy[i], uv[i], command.color});
            m_colors.push_back(sdl_color);
        }

        for (auto i = 0; i < 2; ++i) {
            m_indices.push_back(base_index);
            m_indices.push_back(base_index + i + 1);
            m_indices.push_back(base_index + i + 2);
        }
    };

    auto add_mesh_vertices = [this](const DrawMeshCommand& c, const Transform& transform) {
        const auto* mesh = m_mesh_pool.get(c.mesh);

        MSQ_ASSERT(m_vertices.size() + mesh->vertices.size() < max_draw_index, "vertex buffer is full");

        const auto base_index = static_cast<DrawIndex>(m_vertices.size());

        for (const auto& v : mesh->vertices) {
            m_vertices.push_back({transform.apply_to(v.xy), v.uv, v.color});
            m_colors.push_back({
                static_cast<float>(v.color.r) / 255.f,
                static_cast<float>(v.color.g) / 255.f,
                static_cast<float>(v.color.b) / 255.f,
                static_cast<float>(v.color.a) / 255.f,
            });
        }

        for (auto index : mesh->indices) {
            m_indices.push_back(base_index + index);
        }
    };

    auto viewport_center = Vector2f(static_cast<float>(viewport.area.w), static_cast<float>(viewport.area.h)) / 2.f;
    auto view_transform = Transform {}.translate(viewport_center).combine(viewport.camera.view_transform());

    TextureHandle current_texture_handle;
    SDL_Texture* current_texture = nullptr;
    Size2f current_texture_size;

    auto update_texture = [&](TextureHandle handle) {
        current_texture_handle = handle;
        current_texture = m_texture_pool.contains(handle) ? m_texture_pool.get(handle) : nullptr;
        if (current_texture) {
            SDL_GetTextureSize(current_texture, &current_texture_size.w, &current_texture_size.h);
        } else {
            current_texture_size.set(1, 1);
        }
    };

    for (auto& layer : draw_list.m_layers) {
        for (auto& [command, drawable_transform] : layer) {
            auto texture = std::visit([](const auto& c) { return c.texture; }, command);

            if (m_vertices.empty()) {
                update_texture(texture);
            } else if (texture != current_texture_handle) {
                submit_batch(current_texture);
                update_texture(texture);
            }

            auto transform = view_transform * drawable_transform;

            shard::variant_switch(
                command,
                [&](const DrawQuadCommand& c) { add_quad_vertices(c, transform, current_texture_size); },
                [&](const DrawMeshCommand& c) { add_mesh_vertices(c, transform); });
        }
    }

    if (!m_vertices.empty()) {
        submit_batch(current_texture);
    }
}

} // namespace msq
