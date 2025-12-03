#include "player.h"
#include "renderer.h"
#include "colors.h"
#include  "input.h"

void player_init(player_t *player, const double x, const double y, const double angle)
{
    player->position.x = x;
    player->position.y = y;
    player->dir_angle = angle;
}

void update_player_position(player_t *player, const key_states_t *key_states, const float delta_time) {
    if (key_states->forward)
    {
        player->position.x += MOV_SPEED * cos(player->dir_angle) * delta_time;
        player->position.y += MOV_SPEED * sin(player->dir_angle) * delta_time;
    }
    else if (key_states->backward)
    {
        player->position.x -= MOV_SPEED * cos(player->dir_angle) * delta_time;
        player->position.y -= MOV_SPEED * sin(player->dir_angle) * delta_time;
    }

    if (key_states->left)
        player->dir_angle -= ROT_SPEED * delta_time;
    else if (key_states->right)
        player->dir_angle += ROT_SPEED * delta_time;

    if (key_states->strafe_left)
    {
        player->position.x -= MOV_SPEED * cos(player->dir_angle + M_PI / 2) * delta_time;
        player->position.y -= MOV_SPEED * sin(player->dir_angle + M_PI / 2) * delta_time;
    }
    else if (key_states->strafe_right)
    {
        player->position.x += MOV_SPEED * cos(player->dir_angle + M_PI / 2) * delta_time;
        player->position.y += MOV_SPEED * sin(player->dir_angle + M_PI / 2) * delta_time;
    }
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