// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include <msquared/engine/imgui/interop.hpp>

#include <SDL3/SDL.h>
#include <imgui.h>

int main(int /*argc*/, char* /*argv*/[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer("ImGui Example", 1280, 720, SDL_WINDOW_RESIZABLE, &window, &renderer);

    msq::imgui::init(window, renderer);

    SDL_Event event;
    bool is_running = true;
    bool show_demo_window = true;

    while (is_running) {
        while (SDL_PollEvent(&event)) {
            msq::imgui::process_event(event);

            if (event.type == SDL_EVENT_QUIT) {
                is_running = false;
            }
        }

        msq::imgui::new_frame();

        if (show_demo_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        msq::imgui::prepare_draw_data();
        SDL_RenderClear(renderer);
        msq::imgui::render_draw_data(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
