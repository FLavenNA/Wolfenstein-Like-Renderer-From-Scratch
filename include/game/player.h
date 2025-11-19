#ifndef PLAYER_H
#define PLAYER_H

#include "u_math.h"
#include "type_defs.h"

struct player {
    vec2_t position;
    double dir_angle;
};

void player_init(player_t *player, double x, double y, double angle);

void draw_minimap_player(uint32_t *frame_buffer, int frame_buffer_width, int frame_buffer_height, const player_t *player, int offset_x, int offset_y, float tile_size);
#endif