#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>

#include "u_math.h"
#include "type_defs.h"

void render(const engine_t *engine);

// Helper function
void SDL_RenderFillCircleF(SDL_Renderer *renderer, float cx, float cy, float radius);

#endif