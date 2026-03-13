#ifndef TIME_H
#define TIME_H

#include "type_defs.h"

// Engine time struct
struct time{
    uint64_t last_counter;
    float delta_time;

    float fps_timer;
    int frame_count;
    float fps;

    uint64_t perf_freq;
};

void time_init(etime_t *time);
void time_update(etime_t *time, graphics_t *graphics);

float time_delta(const etime_t *time);
float time_fps(const etime_t *time);

#endif