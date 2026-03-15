#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "type_defs.h"
#include "graphics.h"

struct ray_hit {
    double hit_x;
    double hit_y;
};

struct raycaster {
    double camera_x_table[FRAME_BUFFER_WIDTH];
};

void init_camera_table(raycaster_t *raycaster);
void raycast(const graphics_t *graphics, const raycaster_t *raycaster, const player_t *player, const map_t *map);
void shoot_one_ray(const graphics_t *graphics, const raycaster_t *raycaster, const player_t *player, const map_t *map, int x);

#endif