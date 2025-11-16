#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>

#include "u_math.h"
#include "type_defs.h"

void render(const engine_t *engine);
void clear_screen_buffer(const graphics_t * graphics);
void update_screen(const graphics_t *graphics);
void draw_fps_counter(const graphics_t *graphics);

// Helper function
void SDL_RenderFillCircleF(SDL_Renderer *renderer, float cx, float cy, float radius);

#endif