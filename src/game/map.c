#include <stdio.h>

#include "map.h"
#include "colors.h"
#include "player.h"
#include "renderer.h"

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

void map_draw(SDL_Renderer *renderer, const map_t *map, const player_t *player)
{
    if (!renderer || !map)
        return;

    int window_w, window_h;
    SDL_GetCurrentRenderOutputSize(renderer, &window_w, &window_h);

    const float map_w_px = MAP_WIDTH * TILE_SIZE;
    const float map_h_px = MAP_HEIGHT * TILE_SIZE;
    const float padding = 10.0f;

    const float offset_x = (float)window_w - map_w_px - padding;
    const float offset_y = padding;

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            SDL_FRect r = { offset_x + (float)x * TILE_SIZE,
                            offset_y + (float)y * TILE_SIZE,
                            TILE_SIZE,
                            TILE_SIZE };

            if (map->data[y][x] == 1)
                SDL_SetRenderDrawColor(renderer, MINI_MAP_WALL_COLOR.r, MINI_MAP_WALL_COLOR.g, 
                                        MINI_MAP_WALL_COLOR.b, MINI_MAP_WALL_COLOR.a);
            else
                SDL_SetRenderDrawColor(renderer, MINI_MAP_PATH_COLOR.r, MINI_MAP_PATH_COLOR.g, 
                                        MINI_MAP_PATH_COLOR.b, MINI_MAP_PATH_COLOR.a);

            SDL_RenderFillRect(renderer, &r);
        }
    }

    if (player) {
        // Convert world (tile) coords -> minimap pixels and center in tile.
        // If your player coordinates are already in pixels, remove the * TILE_SIZE.
        const float player_map_x = offset_x + (float)player->position.x * TILE_SIZE + 0.5f * TILE_SIZE;
        const float player_map_y = offset_y + (float)player->position.y * TILE_SIZE + 0.5f * TILE_SIZE;

        const float player_radius = TILE_SIZE * 0.25f; // dot radius (adjust)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
        SDL_RenderFillCircleF(renderer, player_map_x, player_map_y, player_radius);

        // facing line
        const float line_length = TILE_SIZE * 0.8f;
        const float line_x = player_map_x + cosf((float)player->dir_angle) * line_length;
        const float line_y = player_map_y + sinf((float)player->dir_angle) * line_length;

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // yellow
        SDL_RenderLine(renderer,
                       roundf(player_map_x), roundf(player_map_y),
                       roundf(line_x), roundf(line_y));
    }
}