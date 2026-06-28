// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include <msquared/core/math/angle.hpp>
#include <msquared/core/math/point2.hpp>
#include <msquared/core/transform.hpp>

namespace msq {

/// A 2D camera
struct Camera {
    Point2f center;
    Angle rotation;
    float zoom = 1.f;

    /// Get the view transformation to be applied to drawables
    Transform view_transform() const;

    /// Reset the camera to its original position
    void reset();
};

} // namespace msq
