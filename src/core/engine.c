#include "engine.h"
#include "renderer.h"

bool engine_init(engine_t *engine)
{
    if(!graphics_init(&engine->graphics)) 
        return false;

    input_init(&engine->key_map, &engine->key_states);
    player_init(&engine->player, 1.5, 1.5, M_PI / 2);
    map_init(&engine->map);
    time_init(&engine->time);

    engine->state = RUNNING;
    return true;
}

void engine_run(engine_t *engine)
{
    while(engine->state != QUIT) {
        const uint64_t frame_start = SDL_GetPerformanceCounter();

        time_update(&engine->time, &engine->graphics);

        const float dt = time_delta(&engine->time);

        handle_input(engine, dt);

        if(engine->state == PAUSED) {
            SDL_Delay(10);      // To prevent over usage when its paused
            continue;
        }

        render(engine);

        // Limit FPS to target FPS
        graphics_frame_pace(frame_start, engine->time.perf_freq);
    }
}

void engine_cleanup(engine_t *engine)
{
    graphics_cleanup(&engine->graphics);
}