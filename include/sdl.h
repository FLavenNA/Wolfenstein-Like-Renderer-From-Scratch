#ifndef SDL_H
#define SDL_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>

#include "type_defs.h"

#define WINDOW_WIDTH        1280
#define WINDOW_HEIGHT       720
#define MIN_WINDOW_WIDTH    640
#define MIN_WINDOW_HEIGHT   380
#define TARGET_FPS          60

struct graphics {
    SDL_Window *window;
    SDL_Renderer *renderer;

    TTF_Font *font;

    float avg_fps;
};

bool sdl_init(graphics_t *graphics);
void sdl_cleanup(const graphics_t *graphics);

void handle_input(app_t *app);
void render(graphics_t *graphics);

void draw_fps_counter(const graphics_t *graphics);

#endif