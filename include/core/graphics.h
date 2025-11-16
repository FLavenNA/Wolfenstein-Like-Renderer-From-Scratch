#ifndef SDL_H
#define SDL_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "type_defs.h"

#define WINDOW_WIDTH            1280
#define WINDOW_HEIGHT           720
#define FRAME_BUFFER_WIDTH      1280
#define FRAME_BUFFER_HEIGHT     720
#define MIN_WINDOW_WIDTH        640
#define MIN_WINDOW_HEIGHT       380
#define TARGET_FPS              60

struct graphics {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    TTF_Font *font;
    float avg_fps;
    int window_width;
    int window_height;
    uint32_t *frame_buffer;
};

bool graphics_init(graphics_t *graphics);
void graphics_cleanup(graphics_t *graphics);
void graphics_resize(graphics_t *graphics, const int width, const int height);

#endif