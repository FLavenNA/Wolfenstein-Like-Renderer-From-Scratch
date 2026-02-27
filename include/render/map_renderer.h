#ifndef MAP_RENDERER_H
#define MAP_RENDERER_H

#include "type_defs.h"

void draw_map(const graphics_t *graphics, const map_t *map, const player_t *player);
void draw_minimap_player(uint32_t *frame_buffer, int frame_buffer_width, int frame_buffer_height, const player_t *player, int offset_x, int offset_y, float tile_size);

#endif