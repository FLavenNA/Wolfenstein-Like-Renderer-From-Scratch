#ifndef ENGINE_H
#define ENGINE_H

#include "type_defs.h"
#include "graphics.h"
#include "map.h"
#include "player.h"
#include "input.h"
#include "time.h"

typedef enum engine_state
{
    PAUSED,
    RUNNING,
    QUIT
} engine_state_t;

struct engine 
{
    engine_state_t state;       // State of the engine
    graphics_t graphics;        // SDL Graphics related things
    map_t map;                  // Basic 2D map
    player_t player;            // Player
    keymap_t key_map;           // Key map and key codes
    key_states_t key_states;    // Key states Up-Down
    etime_t time;               // Time related things for engine
};

bool engine_init(engine_t *engine);
void engine_run(engine_t *engine);
void engine_cleanup(engine_t *engine);

#endif