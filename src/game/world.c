#include "world.h"
#include "colors.h"
#include "u_image.h"

void init_textures(uint32_t textures[8][TEXTURE_WIDTH * TEXTURE_HEIGHT]) {
    load_into_texture(textures[0],  "assets/textures/eagle.png");
    load_into_texture(textures[1],  "assets/textures/redbrick.png");
    load_into_texture(textures[2],  "assets/textures/purplestone.png");
    load_into_texture(textures[3],  "assets/textures/greystone.png");
    load_into_texture(textures[4],  "assets/textures/bluestone.png");
    load_into_texture(textures[5],  "assets/textures/mossy.png");
    load_into_texture(textures[6],  "assets/textures/wood.png");
    load_into_texture(textures[7],  "assets/textures/colorstone.png");
}
