#include "player.h"
#include "input.h"

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