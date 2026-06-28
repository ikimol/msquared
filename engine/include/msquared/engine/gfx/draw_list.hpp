// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/engine/gfx/mesh_handle.hpp"
#include "msquared/engine/gfx/texture_handle.hpp"

#include <msquared/core/color.hpp>
#include <msquared/core/rect2.hpp>
#include <msquared/core/transform.hpp>

#include <algorithm>
#include <array>
#include <variant>
#include <vector>

namespace msq {

/// A command for drawing a single quad
struct DrawQuadCommand {
    TextureHandle texture;
    Rect2i texture_rect;
    Color color;
};

/// A command for drawing a mesh
struct DrawMeshCommand {
    TextureHandle texture;
    MeshHandle mesh;
};

/// Holds the list of draw commands issued in a single frame
class DrawList {
    friend class Renderer;

public:
    using Layer = std::uint8_t;

public:
    /// Add a command for drawing a single quad
    void add_command(DrawQuadCommand command, Transform transform = Transform::identity, Layer layer = 0);

    /// Add a command for drawing mesh
    void add_command(DrawMeshCommand command, Transform transform = Transform::identity, Layer layer = 0);

    /// Sort draw commands per-layer by texture to minimise batch breaks
    void sort();

    /// Discard all draw commands without rendering
    void clear();

public:
    static constexpr std::uint8_t max_layers = 32;

private:
    using DrawCommand = std::variant<DrawQuadCommand, DrawMeshCommand>;

private:
    std::array<std::vector<std::pair<DrawCommand, Transform>>, max_layers> m_layers;
};

} // namespace msq
