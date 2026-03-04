#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "type_defs.h"

struct ray_hit {
    double hit_x;
    double hit_y;
};

void raycast(const graphics_t *graphics, player_t *player, const map_t *map);
void shoot_one_ray(const graphics_t *graphics, player_t *player, const map_t *map, int x);

#endif