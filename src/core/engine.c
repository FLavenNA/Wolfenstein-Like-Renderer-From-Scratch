#include "engine.h"
#include "renderer.h"

bool engine_init(engine_t *engine)
{
    if(!graphics_init(&engine->graphics)) 
        return false;

    input_init(&engine->key_map, &engine->key_states);
    player_init(&engine->player, 1.0, 1.0, M_PI / 2);
    map_init(&engine->map);

    engine->state = RUNNING;
    return true;
}

void engine_run(engine_t *engine)
{
    const float frame_time = 1000.0f / TARGET_FPS;
    float fps_timer = 0.0f;
    int frame_count = 0;
    float fps = 0.0f;
    float delta_time = 0.0f;

    uint64_t last_counter = SDL_GetPerformanceCounter();

    while(engine->state != QUIT) {
        uint64_t current_counter = SDL_GetPerformanceCounter();
        delta_time = (float)((current_counter - last_counter) * 1000.0)
                           / SDL_GetPerformanceFrequency();
        last_counter = current_counter;

        handle_input(engine, delta_time);

        if(engine->state == PAUSED) continue;

        render(engine);

        // Frame pacing
        uint64_t frame_end = SDL_GetPerformanceCounter();
        float frame_elapsed = (float)((frame_end - current_counter) * 1000.0)
                              / SDL_GetPerformanceFrequency();

        // Delay just enough to hit 60 fps
        if (frame_elapsed < frame_time)
        {
            SDL_Delay((uint32_t)(frame_time - frame_elapsed));
        }

        fps_timer += delta_time;
        frame_count++;

        if (fps_timer >= 1000.0f)
        {
            fps = (float)frame_count * (1000.0f / fps_timer);
            frame_count = 0;
            fps_timer = 0.0f;
            engine->graphics.avg_fps = fps;
        }
    }
}

void engine_cleanup(engine_t *engine)
{
    graphics_cleanup(&engine->graphics);
}