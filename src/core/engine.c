#include "engine.h"
#include "renderer.h"

bool engine_init(engine_t *engine)
{
    if(!graphics_init(&engine->graphics)) 
        return false;

    map_init(&engine->map);

    engine->state = RUNNING;
    return true;
}

void engine_run(engine_t *engine)
{
    const float frame_time = 1000.0f / TARGET_FPS;
    float delta_time = 0.0f;
    float fps_timer = 0.0f;
    int frame_count = 0;
    float fps = 0.0f;

    while(engine->state != QUIT) {

        // get_time() before running instructions;
        const uint64_t start_frame_time = SDL_GetPerformanceCounter();

        handle_input(engine);
        render(engine);

        const uint64_t end_frame_time = SDL_GetPerformanceCounter();

        // Delay if needed 
        delta_time =  (float)((end_frame_time - start_frame_time) * 1000) / SDL_GetPerformanceFrequency();

        // Calculate AVG Fps and Delay to make sure it stays on 60 FPS if its needed
        frame_count++;
        if(frame_time > delta_time) {
            fps_timer += delta_time + frame_time - delta_time;
            SDL_Delay((uint32_t)(frame_time > delta_time ? frame_time - delta_time : 0));
        }
        else
            fps_timer += delta_time;

        if (fps_timer >= 1000.0f)
        {
            fps = (float)frame_count * (1000.0f / fps_timer);
            frame_count = 0;
            fps_timer = 0.0f;
            engine->graphics.avg_fps = fps;
        }
    }
}

void engine_cleanup(const engine_t *engine)
{
    graphics_cleanup(&engine->graphics);
}