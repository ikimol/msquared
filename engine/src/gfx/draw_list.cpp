// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/engine/gfx/draw_list.hpp"

#include <msquared/core/assert.hpp>

namespace msq {

void DrawList::add_command(DrawQuadCommand command, Transform transform, Layer layer) {
    MSQ_ASSERT(layer < max_layers, "layer index out of range");
    m_layers[layer].emplace_back(command, transform);
}

void DrawList::add_command(DrawMeshCommand command, Transform transform, Layer layer) {
    MSQ_ASSERT(layer < max_layers, "layer index out of range");
    m_layers[layer].emplace_back(command, transform);
}

void DrawList::sort() {
    auto get_texture = [](const auto& command) { return std::visit([](const auto& c) { return c.texture; }, command); };
    for (auto& layer : m_layers) {
        std::stable_sort(layer.begin(), layer.end(), [&](const auto& a, const auto& b) {
            return get_texture(a.first) < get_texture(b.first);
        });
    }
}

void DrawList::clear() {
    for (auto& layer : m_layers) {
        layer.clear();
    }
}

} // namespace msq
