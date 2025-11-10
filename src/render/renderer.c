#include "renderer.h"
#include "graphics.h"
#include "engine.h"
#include "map.h"

void render(const engine_t *engine)
{
    // Clear previous frame
    SDL_SetRenderDrawColor(engine->graphics.renderer, 0, 0, 0, 255); // black background (or whatever you want)
    SDL_RenderClear(engine->graphics.renderer);
    // TODO: Do rendering stuff in here
    map_draw(engine->graphics.renderer, &engine->map, &engine->player);
    draw_fps_counter(&engine->graphics);

    SDL_RenderPresent(engine->graphics.renderer);
}

void SDL_RenderFillCircleF(SDL_Renderer *renderer, float cx, float cy, float radius)
{
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            float dx = radius - w;
            float dy = radius - h;
            if (dx*dx + dy*dy <= radius * radius) {
                SDL_RenderPoint(renderer, cx + dx, cy + dy);
            }
        }
    }
}