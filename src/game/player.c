#include "player.h"

#include <stdio.h>

#include "input.h"
#include "map.h"

void player_init(player_t *player, const double x, const double y, const double angle)
{
    player->position.x = x;
    player->position.y = y;

    player->dir.x = cos(angle);
    player->dir.y = sin(angle);

    player->plane.x = -player->dir.y * PLANE_LEN;
    player->plane.y =  player->dir.x * PLANE_LEN;
}
void update_player_position(const map_t *map, player_t *player, const key_states_t *key_states, const float delta_time) {

    if (key_states->left)
        rotate_player(player, -ROT_SPEED * delta_time);

    if (key_states->right)
        rotate_player(player, ROT_SPEED * delta_time);

    double move_x = 0.0;
    double move_y = 0.0;

    if (key_states->forward)        { move_x += player->dir.x; move_y += player->dir.y; }

    if (key_states->backward)       { move_x -= player->dir.x; move_y -= player->dir.y; }

    if (key_states->strafe_right)   { move_x += player->plane.x; move_y += player->plane.y; }

    if (key_states->strafe_left)    { move_x -= player->plane.x; move_y -= player->plane.y; }


    // Normalize it to prevent over speed
    double mag = sqrt(move_x * move_x + move_y * move_y);
    if (mag > 0) {
        move_x /= mag;
        move_y /= mag;
    }

    const double new_x = player->position.x + move_x * MOV_SPEED * delta_time;
    const double new_y = player->position.y + move_y * MOV_SPEED * delta_time;

    // X Collision
    double check_x = (move_x > 0) ? new_x + PLAYER_RADIUS : new_x - PLAYER_RADIUS;
    if (!map_is_wall(map, (int)check_x, (int)player->position.y)) {
        player->position.x = new_x;
    }

    // Y Collision
    double check_y = (move_y > 0) ? new_y + PLAYER_RADIUS : new_y - PLAYER_RADIUS;
    if (!map_is_wall(map, (int)player->position.x, (int)check_y)) {
        player->position.y = new_y;
    }
}

void rotate_player(player_t *player, const double angle)
{
    const double old_dir_x = player->dir.x;

    player->dir.x = player->dir.x * cos(angle) - player->dir.y * sin(angle);
    player->dir.y = old_dir_x * sin(angle) + player->dir.y * cos(angle);

    const double old_plane_x = player->plane.x;

    player->plane.x = player->plane.x * cos(angle) - player->plane.y * sin(angle);
    player->plane.y = old_plane_x * sin(angle) + player->plane.y * cos(angle);
}