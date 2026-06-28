// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/engine/gfx/viewport.hpp"

namespace msq {

Point2f Viewport::map_screen_to_world(Point2f screen_pos) const {
    auto center = Vector2f(static_cast<float>(area.w), static_cast<float>(area.h)) / 2.f;
    auto transform = Transform {}.translate(center).combine(camera.view_transform());
    auto local = screen_pos - Vector2f(static_cast<float>(area.x), static_cast<float>(area.y));
    return transform.inverse().apply_to(local);
}

Point2f Viewport::map_world_to_screen(Point2f world_pos) const {
    auto center = Vector2f(static_cast<float>(area.w), static_cast<float>(area.h)) / 2.f;
    auto transform = Transform {}.translate(center).combine(camera.view_transform());
    auto local = transform.apply_to(world_pos);
    return local + Vector2f(static_cast<float>(area.x), static_cast<float>(area.y));
}

} // namespace msq
