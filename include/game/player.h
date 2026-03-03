#ifndef PLAYER_H
#define PLAYER_H

#include "u_math.h"
#include "type_defs.h"

#define MOV_SPEED   (2.0f / 1000.0f) // In ms so we divide it by 1000
#define ROT_SPEED   (2.0f / 1000.0f) // In ms so we divide it by 1000
#define FOV         (M_PI / 3.0f)  // 60 degrees

struct player {
    vec2_t position;
    double dir_angle;
};

void player_init(player_t *player, double x, double y, double angle);
void update_player_position(player_t *player, const key_states_t *key_states, float delta_time);

#endif