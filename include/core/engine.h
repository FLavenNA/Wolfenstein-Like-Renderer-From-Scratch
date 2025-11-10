#ifndef ENGINE_H
#define ENGINE_H

#include "type_defs.h"
#include "graphics.h"
#include "map.h"
#include "player.h"
#include "input.h"

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
    map_t map;
    player_t player;
    keymap_t key_map;
    key_states_t key_states;
};

bool engine_init(engine_t *engine);
void engine_run(engine_t *engine);
void engine_cleanup(const engine_t *engine);

#endif