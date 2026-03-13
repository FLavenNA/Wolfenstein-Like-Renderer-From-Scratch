#ifndef PLAYER_H
#define PLAYER_H

#include "graphics.h"
#include "u_math.h"
#include "raycaster.h"
#include "type_defs.h"

#define MOV_SPEED       (2.0f)
#define ROT_SPEED       (2.0f)
#define FOV             (M_PI / 3.0f)       // 60 degrees
#define PLANE_LEN       (tan(FOV / 2.0))
#define PLAYER_RADIUS   (0.2f)              // Player radius for basic collision check

struct player {
    vec2_t position;                            // Player position
    vec2_t dir;                                 // Direction vector
    vec2_t plane;                               // Camera plane
};

void player_init(player_t *player, double x, double y, double angle);
void update_player_position(const map_t *map, player_t *player, const key_states_t *key_states, float delta_time);
void rotate_player(player_t *player, double angle);

#endif