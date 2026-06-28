// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/engine/gfx/draw_index.hpp"
#include "msquared/engine/gfx/vertex.hpp"

#include <vector>

namespace msq {

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<DrawIndex> indices;
};

} // namespace msq
