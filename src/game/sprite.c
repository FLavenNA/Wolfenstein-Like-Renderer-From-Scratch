#include <string.h>

#include "sprite.h"

void init_sprites(sprite_t sprites[NUM_SPRITES]) {
    sprite_t data[NUM_SPRITES] =
    {
        {4.5, 1.5, 10},
        {4.5, 18.5, 10},
        {15.5, 3.5,10},

        //row of pillars in front of wall: fisheye test
        // Bottom-left room
        {2.5, 22.5, 9},
        {3.5, 22.5, 9},
        {4.5, 22.5, 9},
        {5.5, 22.5, 9},
        {6.5,22.5, 9},

        //some barrels around the map
        // Top-left room
        {21.5, 1.5, 8},
        {15.5, 1.5, 8},
        {16.0, 1.8, 8},
        {16.2, 1.2, 8},
      };

     memcpy(sprites, data, NUM_SPRITES * sizeof(sprite_t));
}

int compareSprites(const void *a, const void *b) {
    const sprite_sort_item_t *item_a = (sprite_sort_item_t *)a;
    const sprite_sort_item_t *item_b = (sprite_sort_item_t *)b;

    if (item_a->distance < item_b->distance) return 1;
    if (item_a->distance > item_b->distance) return -1;
    return 0;
}

void sort_sprites(int *order, double *dist, const int amount) {
    sprite_sort_item_t *sprites = malloc(sizeof(sprite_sort_item_t) * amount);

    for (int i = 0; i < amount; i++) {
        sprites[i].distance = dist[i];
        sprites[i].order = order[i];
    }

    qsort(sprites, amount, sizeof(sprite_sort_item_t), compareSprites);

    for (int i = 0; i < amount; i++) {
        dist[i] = sprites[i].distance;
        order[i] = sprites[i].order;
    }

    free(sprites);
}