#ifndef INPUT_H
#define INPUT_H

#include <SDL3/SDL.h>

#include "type_defs.h"

#define MOV_SPEED (10.0f / 1000.0f)
#define ROT_SPEED (4.0f / 1000.0f)

struct keymap {
    SDL_Scancode left;
    SDL_Scancode right;
    SDL_Scancode forward;
    SDL_Scancode backward;
    SDL_Scancode strafe_left;
    SDL_Scancode strafe_right;
    SDL_Scancode toggle_map;
    SDL_Scancode quit;
};

struct key_states {
    bool left;
    bool right;
    bool forward;
    bool backward;
    bool strafe_left;
    bool strafe_right;
    bool map_state;
    bool quit;
};

enum kdb_key_state {
    KEY_STATE_UP = 0,
    KEY_STATE_DOWN,
};

void input_init(keymap_t *key_map, key_states_t *key_states);
void handle_input(engine_t *engine, float delta_time);
void process_key_states(const key_states_t *key_states, player_t *player, float delta_time);
void handle_real_time_keys(SDL_Scancode scan_code, enum kdb_key_state_t state, const keymap_t *key_map,  key_states_t *key_states);

#endif