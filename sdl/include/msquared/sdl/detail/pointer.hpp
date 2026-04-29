// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include <memory>

namespace msq::sdl::detail {

/// Deleter type to be specialized for SDL types
template <typename>
struct Deleter;

/// Managed pointer for SDL types
template <typename T, typename D = Deleter<T>>
using Pointer = std::unique_ptr<T, D>;

} // namespace msq::sdl::detail
