#ifndef WORLD_H
#define WORLD_H

#include "type_defs.h"

#define TEXTURE_WIDTH   64
#define TEXTURE_HEIGHT  64
#define TEXTURE_COUNT   11

struct world {
    uint32_t textures[TEXTURE_COUNT][TEXTURE_WIDTH * TEXTURE_HEIGHT];
};

void init_textures(uint32_t [TEXTURE_COUNT][TEXTURE_WIDTH * TEXTURE_HEIGHT]);

#endif //WORLD_H