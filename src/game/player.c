#include "player.h"
#include "input.h"

void player_init(player_t *player, const double x, const double y, const double angle)
{
    player->position.x = x;
    player->position.y = y;

    player->dir.x = cos(angle);
    player->dir.y = sin(angle);

    player->plane.x = -player->dir.y * PLANE_LEN;
    player->plane.y =  player->dir.x * PLANE_LEN;
}

void update_player_position(player_t *player, const key_states_t *key_states, const float delta_time) {
    if (key_states->forward)
    {
        player->position.x += MOV_SPEED * player->dir.x * delta_time;
        player->position.y += MOV_SPEED * player->dir.y * delta_time;
    }
    else if (key_states->backward)
    {
        player->position.x -= MOV_SPEED * player->dir.x * delta_time;
        player->position.y -= MOV_SPEED * player->dir.y * delta_time;
    }

    if (key_states->left)
        rotate_player(player, -ROT_SPEED * delta_time);
    else if (key_states->right)
        rotate_player(player, ROT_SPEED * delta_time);

    if (key_states->strafe_right)
    {
        player->position.x += player->plane.x * MOV_SPEED * delta_time;
        player->position.y += player->plane.y * MOV_SPEED * delta_time;
    }
    if (key_states->strafe_left)
    {
        player->position.x -= player->plane.x * MOV_SPEED * delta_time;
        player->position.y -= player->plane.y * MOV_SPEED * delta_time;
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