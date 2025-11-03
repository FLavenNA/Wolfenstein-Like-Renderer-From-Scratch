#ifndef SDL_H
#define SDL_H

#include <SDL3/SDL.h>
#include <stdbool.h>

#include "type_defs.h"

struct sdl {
    SDL_Window *window;
    SDL_Renderer *renderer;
};

bool sdl_init(sdl_t *sdl);
void sdl_cleanup(const sdl_t *sdl);

void handle_input(app_t *app);

#endif