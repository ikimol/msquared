// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include <msquared/core/color.hpp>
#include <msquared/core/math/point2.hpp>

namespace msq {

/// A single vertex used for rendering
struct Vertex {
    Point2f xy;
    Point2f uv;
    Color color;
};

} // namespace msq
