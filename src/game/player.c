#include "player.h"
#include  "renderer.h"
#include  "colors.h"

void player_init(player_t *player, const double x, const double y, const double angle)
{
    player->position.x = x;
    player->position.y = y;
    player->dir_angle = angle;
}

void draw_minimap_player(uint32_t *frame_buffer, const int frame_buffer_width, const int frame_buffer_height, const player_t *player, const int offset_x, const int offset_y, const float tile_size) {
    // Convert world → minimap pixel coordinates
    const int px = (int)(offset_x + player->position.x * tile_size + tile_size * 0.5f);
    const int py = (int)(offset_y + player->position.y * tile_size + tile_size * 0.5f);

    // Player dot radius
    const int radius = (int)(tile_size * 0.25f);

    // Draw the player (red)
    draw_filled_circle(frame_buffer, frame_buffer_width, frame_buffer_height, px, py, radius, MINI_MAP_PLAYER_COLOR);
}