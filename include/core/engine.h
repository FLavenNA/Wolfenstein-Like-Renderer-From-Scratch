#ifndef ENGINE_H
#define ENGINE_H

#include "type_defs.h"
#include "graphics.h"

enum engine_state
{
    PAUSED,
    RUNNING,
    QUIT
};

struct engine 
{
    engine_state_t state;
    graphics_t graphics;
};

bool engine_init(engine_t *engine);
void engine_run(engine_t *engine);
void engine_cleanup(const engine_t *engine);

#endif