#ifndef WORLD_H
#define WORLD_H

#include "type_defs.h"

#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64

struct world {
    uint32_t textures[8][TEXTURE_WIDTH * TEXTURE_HEIGHT];
};

enum {
    FLAT_RED_WITH_BLACK_CROSS = 1,
    SLOPED_GREYSCALE,
    SLOPED_YELLOW_GRADIENT,
    XOR_GREYSCALE,
    XOR_GREEN,
    RED_BRICKS,
    RED_GRADIENT,
    FLAT_GREY,
};

void init_textures(uint32_t [8][TEXTURE_WIDTH * TEXTURE_HEIGHT]);

#endif //WORLD_H