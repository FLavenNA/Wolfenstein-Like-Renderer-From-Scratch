#ifndef MAP_H
#define MAP_H

#include <SDL3/SDL.h>

#include "type_defs.h"

#define MAP_WIDTH   16
#define MAP_HEIGHT  12
#define TILE_SIZE   16 // Pixels in map view

struct map {
    int32_t data[MAP_HEIGHT] [MAP_WIDTH];
};

void map_init(map_t *map);
void map_draw(const graphics_t *graphics, const map_t *map, const player_t *player);

#endif