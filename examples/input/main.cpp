// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include <msquared/engine/input/input_system.hpp>

#include <SDL3/SDL.h>

namespace {

enum class Action {
    Jump = 0,
    Interact = 1,
    Shoot = 2,
};

msq::Binding key(SDL_Scancode code, msq::Modifiers modifiers = {}) {
    return {code, modifiers};
}

msq::Binding mouse_button(msq::MouseButton button, msq::Modifiers modifiers = {}) {
    return {button, modifiers};
}

} // namespace

#define ACTION_ID(action) static_cast<msq::ActionID>(action)

int main(int /*argc*/, char* /*argv*/[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer("Input Example", 1280, 720, SDL_WINDOW_RESIZABLE, &window, &renderer);

    msq::InputSystem input_system;
    auto gameplay_context = input_system.register_context("gameplay");
    input_system.set_active_context(gameplay_context);
    auto& inputs = input_system.input_map_for(gameplay_context);
    inputs.bind(ACTION_ID(Action::Jump), key(SDL_SCANCODE_SPACE));
    inputs.bind(ACTION_ID(Action::Interact), key(SDL_SCANCODE_E));
    inputs.bind(ACTION_ID(Action::Shoot), mouse_button(msq::MouseButton::Left));

    SDL_Event event;
    bool is_running = true;

    while (is_running) {
        input_system.begin_frame();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                is_running = false;
            }

            input_system.handle_event(event);
        }

        if (input_system.was_just_pressed(ACTION_ID(Action::Jump))) {
            std::printf("jump: start\n");
        }
        if (input_system.was_just_released(ACTION_ID(Action::Jump))) {
            std::printf("jump: end\n");
        }
        if (input_system.is_held(ACTION_ID(Action::Shoot))) {
            std::printf("shooting\n");
        }

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
