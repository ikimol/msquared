// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include <msquared/core/colors.hpp>
#include <msquared/engine/gfx/renderer.hpp>

#include <SDL3/SDL.h>

int main(int /*argc*/, char* /*argv*/[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer("Graphics Example", 1280, 720, SDL_WINDOW_RESIZABLE, &window, &renderer);

    msq::Mesh mesh;
    mesh.vertices = {
        {  msq::Point2f(0,  0), {},   msq::colors::red},
        {msq::Point2f(200, 50), {}, msq::colors::green},
        {  msq::Point2f(0, 50), {},  msq::colors::blue},
    };
    mesh.indices = {0, 1, 2};

    msq::TexturePool texture_pool;
    msq::MeshPool mesh_pool;
    auto mesh_handle = mesh_pool.add(&mesh);

    msq::Renderer main_renderer(renderer, texture_pool, mesh_pool);
    main_renderer.set_clear_color(msq::colors::dark_gray);

    msq::Size2i window_size;
    SDL_GetWindowSize(window, &window_size.w, &window_size.h);

    msq::Camera world_camera;
    world_camera.center = msq::Point2f(window_size.w / 2, window_size.h / 2);

    msq::Viewport world_viewport {
        msq::Rect2i {{}, window_size},
        world_camera
    };
    msq::DrawList world_draw_list;

    SDL_Event event;
    bool is_running = true;

    while (is_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                is_running = false;
            }
        }

        world_draw_list.clear();
        world_draw_list.add_command(
            msq::DrawQuadCommand {
                msq::TextureHandle {},
                msq::Rect2i {0, 0, 200, 40},
                msq::colors::blue
        },
            msq::Transform {}.translate(50, 50),
            0);
        world_draw_list.add_command(msq::DrawMeshCommand {msq::TextureHandle {}, mesh_handle},
                                    msq::Transform {}.translate(50, 100),
                                    0);
        world_draw_list.sort();

        main_renderer.begin_frame();
        main_renderer.flush(world_draw_list, world_viewport);
        main_renderer.end_frame();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
