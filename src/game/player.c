#include "player.h"

void player_init(player_t *player, double x, double y, double angle)
{
    player->position.x = x;
    player->position.y = y;
    player->dir_angle = angle;
}