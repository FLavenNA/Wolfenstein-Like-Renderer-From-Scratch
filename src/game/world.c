#include "world.h"
#include "colors.h"

void init_textures(uint32_t textures[8][TEXTURE_WIDTH * TEXTURE_HEIGHT]) {
    for (int x  = 0; x < TEXTURE_WIDTH; x++) {
        for (int y = 0; y < TEXTURE_HEIGHT; y++) {

            // Got this code from somewhere on internet to generate textures
            int xor_color = (x * 0xFF / TEXTURE_WIDTH) ^ (y * 0xFF / TEXTURE_HEIGHT);
            int y_color = y * 0xFF / TEXTURE_HEIGHT;
            int xy_color = y * 0x7F / TEXTURE_HEIGHT + x * 0x7F / TEXTURE_WIDTH;

            // Flat red texture with black cross
            const uint8_t red_cross = (x != y && x != TEXTURE_WIDTH - y) ? 0xFE : 0X00;
            textures[0][TEXTURE_WIDTH * y + x] = RGBA_TO_ABGR_COLOR(red_cross, 0x00, 0x00, 0XFF);

            // Sloped greyscale
            textures[1][TEXTURE_WIDTH * y + x] = RGBA_TO_ABGR_COLOR(xy_color, xy_color, xy_color, 0xFF);

            // Sloped yellow gradient
            textures[2][TEXTURE_WIDTH * y + x] = RGBA_TO_ABGR_COLOR(xy_color, xy_color, 0x00, 0xFF);

            // Xor greyscale
            textures[3][TEXTURE_WIDTH * y + x] = RGBA_TO_ABGR_COLOR(xor_color, xor_color, xor_color, 0xFF);

            // Xor green
            textures[4][TEXTURE_WIDTH * y + x] = RGBA_TO_ABGR_COLOR(0x00, xor_color, 0x00, 0xFF);

            // Red bricks
            const uint8_t brick_red = (x % 0x10 && y % 0x10) ? 0xC0 : 0x00;
            textures[5][TEXTURE_WIDTH * y + x] = RGBA_TO_ABGR_COLOR(brick_red, 0, 0, 0xFF);

            // Red gradient
            textures[6][TEXTURE_WIDTH * y + x] = RGBA_TO_ABGR_COLOR(y_color, 0, 0, 0xFF);

            // Flat grey
            textures[7][TEXTURE_WIDTH * y + x] = RGBA_TO_ABGR_COLOR(0x80, 0x80, 0x80, 0xFF);
        }
    }
}