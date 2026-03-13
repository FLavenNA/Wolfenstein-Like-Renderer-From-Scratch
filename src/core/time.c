#include <SDL3/SDL.h>

#include "time.h"

#include "graphics.h"

void time_init(etime_t *time)
{
    time->perf_freq = SDL_GetPerformanceFrequency();
    time->last_counter = SDL_GetPerformanceCounter();

    time->delta_time = 0.0;
    time->fps_timer = 0.0;
    time->frame_count = 0;
    time->fps = 0.0;
}

void time_update(etime_t *time, graphics_t *graphics)
{
    uint64_t current = SDL_GetPerformanceCounter();

    time->delta_time =
        (float)(current - time->last_counter) / time->perf_freq;

    time->last_counter = current;

    time->fps_timer += time->delta_time;
    time->frame_count++;

    if (time->fps_timer >= 1.0)
    {
        time->fps = time->frame_count / time->fps_timer;
        time->frame_count = 0;
        time->fps_timer = 0.0;
        graphics->avg_fps = time->fps;
    }
}

float time_delta(const etime_t *time)
{
    return time->delta_time;
}

float time_fps(const etime_t *time)
{
    return time->fps;
}