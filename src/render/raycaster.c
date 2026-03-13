#include <stdlib.h>

#include "raycaster.h"

#include "colors.h"
#include "graphics.h"
#include "map.h"
#include "player.h"
#include "primitive_renderer.h"

void raycast(const graphics_t *graphics, const player_t *player, const map_t *map) {
    for (int x = 0; x < FRAME_BUFFER_WIDTH; x++)
        shoot_one_ray(graphics, player, map, x);
}

void shoot_one_ray(const graphics_t *graphics, const player_t *player, const map_t *map, int x) {

    // 1. Camera space x-coordinate (-1 to 1)
    const double cameraX = 2.0 * x / (double)FRAME_BUFFER_WIDTH - 1.0;

    // 2. Ray direction
    vec2_t rayDir;
    rayDir.x = player->dir.x + player->plane.x * cameraX;
    rayDir.y = player->dir.y + player->plane.y * cameraX;

    // 3. Current map square
    int mapX = (int)player->position.x;
    int mapY = (int)player->position.y;

    // 4. Calculate distance to next side
    double deltaDistX = (rayDir.x == 0) ? 1e30 : fabs(1.0 / rayDir.x);
    double deltaDistY = (rayDir.y == 0) ? 1e30 : fabs(1.0 / rayDir.y);

    // Which direction to step in x or y-direction (either +1 or -1)
    int stepX, stepY;

    // Length of ray from current position to next x or y-side
    double sideDistX, sideDistY;

    if (rayDir.x < 0)
    {
        stepX = -1;
        sideDistX = (player->position.x - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - player->position.x) * deltaDistX;
    }

    if (rayDir.y < 0)
    {
        stepY = -1;
        sideDistY = (player->position.y - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - player->position.y) * deltaDistY;
    }

    // 5. Perform DDA
    int hit = 0;
    int side; // If X side is hit = 0, If Y side is hit = 1

    while (!hit)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }

        if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT)
        {
            hit = 1;
            break;
        }

        if (map->data[mapY][mapX] > 0)
            hit = 1;
    }

    // 6. Perpendicular wall distance (to avoid fish-eye)
    double perpWallDist;
    if (side == 0)
        perpWallDist = (mapX - player->position.x + (1 - stepX) / 2.0) / rayDir.x;
    else
        perpWallDist = (mapY - player->position.y + (1 - stepY) / 2.0) / rayDir.y;

    // 7. Calculate line height
    const int lineHeight = (int)(FRAME_BUFFER_HEIGHT / perpWallDist);

    // 8. Determine start and end of wall
    const int y0 = -lineHeight / 2 + FRAME_BUFFER_HEIGHT / 2;
    const int y1 = lineHeight / 2 + FRAME_BUFFER_HEIGHT / 2;

    // 9. Draw Ceiling
    for (int y = 0; y < y1; y++)
        put_pixel(graphics->frame_buffer, x, y, CEILING_COLOR);

    // 10. Draw Wall
    for (int y = y0; y <= y1; y++)
        put_pixel(graphics->frame_buffer, x, y, side == 0 ? WALL_DARK_COLOR : WALL_COLOR);

    // 11. Draw Floor
    for (int y = y1 + 1; y < FRAME_BUFFER_HEIGHT; y++)
        put_pixel(graphics->frame_buffer, x, y, FLOOR_COLOR);
}