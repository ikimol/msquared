// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/engine/gfx/camera.hpp"

#include <msquared/core/rect2.hpp>

namespace msq {

/// An area of the screen drawing happens in
struct Viewport {
    Rect2i area;
    Camera camera;

    /// Map a screen coordinate to a world coordinate
    ///
    /// \note This is the opposite of what the renderer is doing under the hood,
    Point2f map_screen_to_world(Point2f screen_pos) const;

    /// Map a world coordinate to a screen coordinate
    ///
    /// \note This is what the renderer is doing under the hood,
    Point2f map_world_to_screen(Point2f world_pos) const;
};

} // namespace msq
