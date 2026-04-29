// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/sdl/detail/pointer.hpp"

#include <SDL3_ttf/SDL_ttf.h>

namespace msq::sdl {
namespace detail {

struct GPUTextEngineDeleter {
    void operator()(TTF_TextEngine* ptr) const noexcept { TTF_DestroyGPUTextEngine(ptr); }
};

struct SurfaceTextEngineDeleter {
    void operator()(TTF_TextEngine* ptr) const noexcept { TTF_DestroySurfaceTextEngine(ptr); }
};

struct RendererTextEngineDeleter {
    void operator()(TTF_TextEngine* ptr) const noexcept { TTF_DestroyRendererTextEngine(ptr); }
};

} // namespace detail

/// Alias for managed GPU-based TTF_TextEngine
using GPUTextEngine = detail::Pointer<TTF_TextEngine, detail::GPUTextEngineDeleter>;

/// Alias for managed surface-based TTF_TextEngine
using SurfaceTextEngine = detail::Pointer<TTF_TextEngine, detail::SurfaceTextEngineDeleter>;

/// Alias for managed renderer-based TTF_TextEngine
using RendererTextEngine = detail::Pointer<TTF_TextEngine, detail::RendererTextEngineDeleter>;

// operations

/// Create a text engine using the GPU
GPUTextEngine create_gpu_text_engine(SDL_GPUDevice* device);

/// Create a text engine for a surface
SurfaceTextEngine create_surface_text_engine();

/// Create a text engine using a renderer
RendererTextEngine create_renderer_text_engine(SDL_Renderer* renderer);

} // namespace msq::sdl
