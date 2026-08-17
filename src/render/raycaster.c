#include <stdlib.h>
#include <stdio.h>

#include "raycaster.h"
#include "graphics.h"
#include "map.h"
#include "player.h"
#include "primitive_renderer.h"
#include "sprite.h"
#include "world.h"

void init_camera_table(raycaster_t *raycaster) {
    for (int x = 0; x < FRAME_BUFFER_WIDTH; x++) {
        raycaster->camera_x_table[x] = 2.0 * x / (double) FRAME_BUFFER_WIDTH - 1.0;
    }
}

void init_raycast_hits(raycaster_t *raycaster) {
    for (int x = 0; x < FRAME_BUFFER_WIDTH; x++) {
        raycaster->ray_hits[x].hit_x = 0;
        raycaster->ray_hits[x].hit_y = 0;
    }
}

void raycast(const graphics_t *graphics, raycaster_t *raycaster, const player_t *player, const map_t *map, const world_t *world, sprite_manager_t *sprite_manager) {
    for (int x = 0; x < FRAME_BUFFER_WIDTH; x++)
        shoot_one_ray(graphics, raycaster, player, map, world, sprite_manager, x);

    // Sprite Casting
    //sort sprites from far to close
    for(int i = 0; i < NUM_SPRITES; i++)
    {
        sprite_manager->sprite_order[i] = i;
        sprite_manager->sprite_distance[i] = ((player->position.x - sprite_manager->sprites[i].x) * (player->position.x - sprite_manager->sprites[i].x) +
            (player->position.y - sprite_manager->sprites[i].y) * (player->position.y - sprite_manager->sprites[i].y));
    }

    sort_sprites(sprite_manager->sprite_order, sprite_manager->sprite_distance, NUM_SPRITES);

    for(int i = 0; i < NUM_SPRITES; i++)
    {
      //translate sprite position to relative to camera
      const double sprite_x = sprite_manager->sprites[sprite_manager->sprite_order[i]].x - player->position.x;
      const double sprite_y = sprite_manager->sprites[sprite_manager->sprite_order[i]].y - player->position.y;

      //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

      const double inv_det = 1.0 / (player->plane.x * player->dir.y - player->dir.x * player->plane.y); //required for correct matrix multiplication

      const double transform_x = inv_det * (player->dir.y * sprite_x - player->dir.x * sprite_y);
      const double transform_y = inv_det * (-player->plane.y * sprite_x + player->plane.x * sprite_y); //this is actually the depth inside the screen, that what Z is in 3D

      const int sprite_screen_x = (int)((FRAME_BUFFER_WIDTH / 2) * (1 + transform_x / transform_y));

      //calculate height of the sprite on screen
      const int sprite_height = abs((int)(FRAME_BUFFER_HEIGHT / (transform_y))); //using 'transformY' instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -sprite_height / 2 + FRAME_BUFFER_HEIGHT / 2;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = sprite_height / 2 + FRAME_BUFFER_HEIGHT / 2;
      if(drawEndY >= FRAME_BUFFER_HEIGHT) drawEndY = FRAME_BUFFER_HEIGHT - 1;

      //calculate width of the sprite
      int spriteWidth = abs( (int) (FRAME_BUFFER_HEIGHT / (transform_y)));
      int drawStartX = -spriteWidth / 2 + sprite_screen_x;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + sprite_screen_x;
      if(drawEndX >= FRAME_BUFFER_WIDTH) drawEndX = FRAME_BUFFER_WIDTH - 1;

      //loop through every vertical stripe of the sprite on screen
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int sprite_tex_x = (int)(256 * (stripe - (-spriteWidth / 2 + sprite_screen_x)) * TEXTURE_WIDTH / spriteWidth) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        if(transform_y > 0 && stripe > 0 && stripe < FRAME_BUFFER_WIDTH && transform_y < sprite_manager->z_buffer[stripe])
        for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
          int d = (y) * 256 - FRAME_BUFFER_HEIGHT * 128 + sprite_height * 128; //256 and 128 factors to avoid floats
          int sprite_tex_y = ((d * TEXTURE_HEIGHT) / sprite_height) / 256;
          uint32_t color = world->textures[sprite_manager->sprites[sprite_manager->sprite_order[i]].texture][
              TEXTURE_WIDTH * sprite_tex_y + sprite_tex_x];
          if ((color & 0x00FFFFFF) != 0) put_pixel(graphics->frame_buffer, stripe, y, color);
          //paint pixel if it isn't black, black is the invisible color
        }
      }
    }
}

void shoot_one_ray(const graphics_t *graphics, raycaster_t *raycaster, const player_t *player, const map_t *map,
                    const world_t *world, sprite_manager_t *sprite_manager, const int x) {
    // 1. Camera space x-coordinate (-1 to 1)
    const double cameraX = raycaster->camera_x_table[x];

    // 2. Ray direction
    vec2_t rayDir;
    rayDir.x = player->dir.x + player->plane.x * cameraX;
    rayDir.y = player->dir.y + player->plane.y * cameraX;

    // 3. Current map square
    int mapX = (int) player->position.x;
    int mapY = (int) player->position.y;

    // 4. Calculate distance to next side
    double deltaDistX = (rayDir.x == 0) ? 1e30 : fabs(1.0 / rayDir.x);
    double deltaDistY = (rayDir.y == 0) ? 1e30 : fabs(1.0 / rayDir.y);

    // Which direction to step in x or y-direction (either +1 or -1)
    int stepX, stepY;

    // Length of ray from current position to next x or y-side
    double sideDistX, sideDistY;

    if (rayDir.x < 0) {
        stepX = -1;
        sideDistX = (player->position.x - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - player->position.x) * deltaDistX;
    }

    if (rayDir.y < 0) {
        stepY = -1;
        sideDistY = (player->position.y - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - player->position.y) * deltaDistY;
    }

    // 5. Perform DDA
    int hit = 0;
    int side; // If X side is hit = 0, If Y side is hit = 1

    while (!hit) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }

        if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT) {
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

    // 7. Keep tracking of ray_hit infos so you can draw them on map
    ray_hit_t hit_info;
    hit_info.hit_x = player->position.x + rayDir.x * perpWallDist;
    hit_info.hit_y = player->position.y + rayDir.y * perpWallDist;

    raycaster->ray_hits[x] = hit_info;

    // 8. Calculate line height
    const int lineHeight = (int) (FRAME_BUFFER_HEIGHT / perpWallDist);

    // 9. Determine start and end of wall
    int drawStart = -lineHeight / 2 + FRAME_BUFFER_HEIGHT / 2;
    if (drawStart < 0)
        drawStart = 0;

    int drawEnd = lineHeight / 2 + FRAME_BUFFER_HEIGHT / 2;
    if (drawEnd >= FRAME_BUFFER_HEIGHT)
        drawEnd = FRAME_BUFFER_HEIGHT - 1;

    // 10 & 11. Draw Textured Floor and Ceiling
    for (int y = drawEnd + 1; y < FRAME_BUFFER_HEIGHT; y++) {
        // Current y distance relative to the center of the screen (horizon)
        const double p = y - FRAME_BUFFER_HEIGHT / 2.0;

        // Vertical distance from the camera to the floor (0.5 is the middle of the wall height)
        const double pos_z = 0.5 * FRAME_BUFFER_HEIGHT;

        // Horizontal distance from the camera to the floor for this row
        const double row_distance = pos_z / p;

        // Calculate the real world coordinates of the floor point
        // rayDir is the direction vector for the current column x
        const double floor_x = player->position.x + row_distance * rayDir.x;
        const double floor_y = player->position.y + row_distance * rayDir.y;

        // Get the texture coordinates from the fractional part of the world coordinates
        const int floor_text_x = (int)(TEXTURE_WIDTH * (floor_x - floor(floor_x))) & (TEXTURE_WIDTH - 1);
        const int floor_text_y = (int)(TEXTURE_HEIGHT * (floor_y - floor(floor_y))) & (TEXTURE_HEIGHT - 1);

        // Floor
        uint32_t color;
        color = world->textures[3][TEXTURE_WIDTH * floor_text_y + floor_text_x];
        //Apply shadowing
        color = (color >> 1) & 2139062143;
        put_pixel(graphics->frame_buffer, x, y, color);

        // Ceiling (Symmetrical to floor)
        color = world->textures[6][TEXTURE_WIDTH * floor_text_y + floor_text_x];
        //Apply shadowing
        color = (color >> 1) & 2139062143;
        put_pixel(graphics->frame_buffer, x, FRAME_BUFFER_HEIGHT - y, color);
    }

    // 12. Calculate wall texture coordinates and draw them
    double wall_x;
    if (side == 0)  wall_x = hit_info.hit_y;
    else            wall_x = hit_info.hit_x;
    wall_x -= floor(wall_x);

    // Calculate X coordinate of texture
    int texture_x = (int)(wall_x * (double)TEXTURE_WIDTH);
    if(side == 0 && rayDir.x > 0) texture_x = TEXTURE_WIDTH - texture_x - 1;
    if(side == 1 && rayDir.y < 0) texture_x = TEXTURE_WIDTH - texture_x - 1;

    const int texture_num = map->data[mapY][mapX] - 1;

    // Step for coordinates
    const double step = 1.0 * TEXTURE_HEIGHT / lineHeight;
    double texture_pos = (drawStart - FRAME_BUFFER_HEIGHT / 2 + lineHeight / 2) * step;

    for (int y = drawStart; y <= drawEnd; y++) {
        const int texture_y = (int)texture_pos & (TEXTURE_HEIGHT - 1);
        texture_pos += step;

        uint32_t color = world->textures[texture_num][TEXTURE_HEIGHT * texture_y + texture_x];
        
        // Apply shadowing to sides
        if(side == 1) color = (color >> 1) & 2139062143;

        put_pixel(graphics->frame_buffer, x, y, color);
    }

    // For sprite rendering
    sprite_manager->z_buffer[x] = perpWallDist;
}
