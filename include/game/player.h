#ifndef PLAYER_H
#define PLAYER_H

#include "u_math.h"
#include "type_defs.h"

struct player {
    vec2_t position;
    double dir_angle;
};

void player_init(player_t *player, double x, double y, double angle);
#endif