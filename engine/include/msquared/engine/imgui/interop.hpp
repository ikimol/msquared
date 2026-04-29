// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

union SDL_Event;
struct SDL_Window;
struct SDL_Renderer;

namespace msq::imgui {

/// Initialize the ImGui context
void init(SDL_Window* window, SDL_Renderer* renderer);

/// Pass the event to ImGui
void process_event(const SDL_Event& event);

/// Let ImGui know a new frame started
void new_frame();

/// Prepare the ImGui state for rendering
void prepare_draw_data();

/// Render ImGui
void render_draw_data(SDL_Renderer* renderer);

/// Clean up the ImGui GUI context
void shutdown();

} // namespace msq::imgui
