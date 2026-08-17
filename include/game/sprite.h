#ifndef SPRITE_H
#define SPRITE_H

#include <stdlib.h>

#include "type_defs.h"
#include "graphics.h"

#define NUM_SPRITES 12

struct sprite {
    double x;
    double y;
    int texture;
};

struct sprite_sort_item {
    double distance;
    int order;
};

struct sprite_manager {
    sprite_t sprites[NUM_SPRITES];
    double z_buffer[FRAME_BUFFER_WIDTH];
    int sprite_order[NUM_SPRITES];
    double sprite_distance[NUM_SPRITES];
};

void init_sprites(sprite_t sprites[NUM_SPRITES]);

int compare_sprites(const void *a, const void *b);
void sort_sprites(int *order, double *dist, const int amount);

#endif //SPRITE_H