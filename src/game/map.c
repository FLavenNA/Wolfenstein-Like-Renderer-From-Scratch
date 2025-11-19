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
    if (!graphics || !graphics->frame_buffer || !map)
        return;

    const int margin = 10;
    const int map_px_w = MAP_WIDTH * TILE_SIZE;

    // Starting pixels
    const int x0 = FRAME_BUFFER_WIDTH - map_px_w - margin;
    const int y0 = margin;

    uint32_t *fb = graphics->frame_buffer;

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        const int tile_y = y0 + y * TILE_SIZE;

        // If tile is completely outside vertical bounds, skip tile entirely
        if (tile_y >= FRAME_BUFFER_HEIGHT || tile_y + TILE_SIZE < 0)
            continue;

        for (int x = 0; x < MAP_WIDTH; ++x) {
            const uint32_t color = (map->data[y][x] == 1)
                                       ? MINI_MAP_WALL_COLOR
                                       : MINI_MAP_PATH_COLOR;

            const int tile_x = x0 + x * TILE_SIZE;

            // Skip tile if completely outside horizontal bounds
            if (tile_x >= FRAME_BUFFER_WIDTH || tile_x + TILE_SIZE < 0)
                continue;

            for (int py = 0; py < TILE_SIZE; py++) {
                int yy = tile_y + py;

                if (yy < 0 || yy >= FRAME_BUFFER_HEIGHT) continue;

                int row_offset = yy * FRAME_BUFFER_WIDTH;

                for (int px = 0; px < TILE_SIZE; px++) {
                    int xx = tile_x + px;

                    if (xx < 0 || xx >= FRAME_BUFFER_WIDTH) continue;

                    fb[row_offset + xx] = color;
                }
            }
        }
    }

    if (player)
        draw_minimap_player(fb, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, player, x0, y0, TILE_SIZE);

    // TODO: Implement software rendering for player on map
}