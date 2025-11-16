#include <stdio.h>

#include "map.h"
#include "colors.h"
#include "player.h"
#include "graphics.h"

void map_init(map_t *map)
{
    // Simple rectangular room
    int layout[MAP_HEIGHT][MAP_WIDTH] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,1},
        {1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
        {1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,1,0,0,0,0,1,1,0,1,0,1},
        {1,0,1,0,1,1,0,1,1,0,1,1,0,1,0,1},
        {1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };

    for (int y = 0; y < MAP_HEIGHT; ++y)
        for (int x = 0; x < MAP_WIDTH; ++x)
            map->data[y][x] = layout[y][x];
}

void map_draw(const graphics_t *graphics, const map_t *map, const player_t *player)
{
    if (!graphics || !map)
        return;

    const int margin = 10;
    int map_px_w = MAP_WIDTH * TILE_SIZE;

    int x0 = FRAME_BUFFER_WIDTH - map_px_w - margin;
    int y0 = margin;

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            uint32_t color = (map->data[y][x] == 1) ? MINI_MAP_PATH_COLOR
                                                    : MINI_MAP_WALL_COLOR;

            for (int py = 0; py < TILE_SIZE; py++) {
                int yy = y0 + y * TILE_SIZE + py;

                if (yy < 0 || yy >= FRAME_BUFFER_HEIGHT) continue;

                for (int px = 0; px < TILE_SIZE; px++) {
                    int xx = x0 + x * TILE_SIZE + px;

                    if (xx < 0 || xx >= FRAME_BUFFER_WIDTH) continue;

                    graphics->frame_buffer[yy * FRAME_BUFFER_WIDTH + xx] = color;
                }
            }
        }
    }

    // TODO: Implement software rendering for player on map
}