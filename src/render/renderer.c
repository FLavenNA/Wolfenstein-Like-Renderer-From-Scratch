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
    map_draw(engine->graphics.renderer, &engine->map);
    draw_fps_counter(&engine->graphics);

    SDL_RenderPresent(engine->graphics.renderer);
}