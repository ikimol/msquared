// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/engine/imgui/interop.hpp"

#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>

#include <SDL3/SDL_render.h>

namespace msq::imgui {

void init(SDL_Window* window, SDL_Renderer* renderer) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // load the default font
    ImGui::GetIO().Fonts->AddFontDefault();

    // set the dark theme
    ImGui::StyleColorsDark();

    // initialize the SDL2 backends
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
}

void process_event(const SDL_Event& event) {
    ImGui_ImplSDL3_ProcessEvent(&event);
}

void new_frame() {
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void prepare_draw_data() {
    ImGui::Render();
}

void render_draw_data(SDL_Renderer* renderer) {
    // save original scale
    ImVec2 old_scale;
    SDL_GetRenderScale(renderer, &old_scale.x, &old_scale.y);

    // update scale from ImGui
    auto new_scale = ImGui::GetIO().DisplayFramebufferScale;
    SDL_SetRenderScale(renderer, new_scale.x, new_scale.y);
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

    // restore original scale
    SDL_SetRenderScale(renderer, old_scale.x, old_scale.y);
}

void shutdown() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

} // namespace msq::imgui
