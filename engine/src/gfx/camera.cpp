// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/engine/gfx/camera.hpp"

namespace msq {

Transform Camera::view_transform() const {
    return Transform {}.scale(zoom).rotate(-rotation).translate(-center);
}

void Camera::reset() {
    center.reset();
    rotation = degrees(0);
    zoom = 1.f;
}

} // namespace msq
