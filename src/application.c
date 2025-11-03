#include <stdio.h>

#include "application.h"

bool app_init(app_t *app)
{
    if(!sdl_init(&app->graphics)) 
        return false;


    app->state = RUNNING;
    return true;
}

void app_run(app_t *app)
{
    const float frame_time = 1000 / TARGET_FPS;
    float delta_time = 0.0f;
    float fps_timer = 0.0f;
    int frame_count = 0;
    float fps = 0.0f;
    while(app->state != QUIT) {

        // get_time() before running instructions;
        const uint64_t start_frame_time = SDL_GetPerformanceCounter();

        handle_input(app);
        render(app->graphics);

        const uint64_t end_frame_time = SDL_GetPerformanceCounter();

        // Delay if needed 
        delta_time =  (float)((end_frame_time - start_frame_time) * 1000) / SDL_GetPerformanceFrequency();

        // FPS Calculation (averaged every second)
        frame_count++;
        fps_timer += delta_time;
        if (fps_timer >= 1000.0f) {
            fps = (float)frame_count * (1000.0f / fps_timer);
            frame_count = 0;
            fps_timer = 0.0f;
            printf("FPS: %.1f\n", fps); // optional console print
            const char* test = "This is a test";
            SDL_RenderDebugText(app->graphics.renderer, 5, 5, test);
        }

       SDL_Delay((uint32_t)(frame_time > delta_time ? frame_time - delta_time : 0));
    }
}

void app_cleanup(const app_t *app)
{
    sdl_cleanup(&app->graphics);
}