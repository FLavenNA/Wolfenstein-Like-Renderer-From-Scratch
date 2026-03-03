#include "map_renderer.h"
#include "graphics.h"
#include "colors.h"
#include "map.h"
#include "player.h"
#include "primitive_renderer.h"

void draw_map(const graphics_t *graphics, const map_t *map, const player_t *player)
{
    if (!graphics || !graphics->frame_buffer || !map)
        return;

    if (!map->isVisible)
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
}

void draw_minimap_player(uint32_t *frame_buffer, const int frame_buffer_width, const int frame_buffer_height, const player_t *player, const int offset_x, const int offset_y, const float tile_size) {
    // Convert world → minimap pixel coordinates
    const int px = (int)(offset_x + player->position.x * tile_size + tile_size * 0.5f);
    const int py = (int)(offset_y + player->position.y * tile_size + tile_size * 0.5f);

    // Player dot radius
    const int radius = (int)(tile_size * 0.25f);

    // 🔥 Direction line
    const float dir_length = tile_size * 0.75f;

    const int dir_x = (int)(px + cosf(player->dir_angle) * dir_length);
    const int dir_y = (int)(py + sinf(player->dir_angle) * dir_length);

    const float half_fov = FOV * 0.5f;

    // FOV Lines
    const float left_angle  = player->dir_angle - half_fov;
    const float right_angle = player->dir_angle + half_fov;

    const float fov_length = tile_size * 1.5f;

    const int left_fov_x  = (int)(px + cosf(left_angle)  * fov_length);
    const int left_fov_y  = (int)(py + sinf(left_angle)  * fov_length);

    const int right_fov_x = (int)(px + cosf(right_angle) * fov_length);
    const int right_fov_y = (int)(py + sinf(right_angle) * fov_length);

    // Draw the player (yellow)
    draw_filled_circle(frame_buffer, frame_buffer_width, frame_buffer_height, px, py, radius, MINI_MAP_PLAYER_COLOR);

    // Draw direction line
    draw_line(frame_buffer,
          frame_buffer_width,
          frame_buffer_height,
          px,
          py,
          dir_x,
          dir_y,
          MINI_MAP_PLAYER_COLOR);

    // Draw FOV lines
    draw_line(frame_buffer, frame_buffer_width, frame_buffer_height,
              px, py, left_fov_x, left_fov_y, MINI_MAP_FOV_LINE_COLOR);

    draw_line(frame_buffer, frame_buffer_width, frame_buffer_height,
              px, py, right_fov_x, right_fov_y, MINI_MAP_FOV_LINE_COLOR);
}