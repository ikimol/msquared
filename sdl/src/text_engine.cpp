// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/sdl/text_engine.hpp"

namespace msq::sdl {

GPUTextEngine create_gpu_text_engine(SDL_GPUDevice* device) {
    return GPUTextEngine(TTF_CreateGPUTextEngine(device));
}

SurfaceTextEngine create_surface_text_engine() {
    return SurfaceTextEngine(TTF_CreateSurfaceTextEngine());
}

RendererTextEngine create_renderer_text_engine(SDL_Renderer* renderer) {
    return RendererTextEngine(TTF_CreateRendererTextEngine(renderer));
}

} // namespace msq::sdl
