#ifndef U_IMAGE_H
#define U_IMAGE_H

#include "type_defs.h"
#include "colors.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdlib.h>

int load_into_texture(uint32_t *texture_out, const char *filename) {
    int w, h, channels;
    unsigned char *data = stbi_load(filename, &w, &h, &channels, 4);

    if (data == NULL) return false;

    for (int i = 0; i < w * h; i++) {
        texture_out[i] = RGBA_TO_ABGR_COLOR(data[i*4], data[i*4+1], data[i*4+2], data[i*4+3]);
    }

    stbi_image_free(data);
    return true;
}

#endif //U_IMAGE_H