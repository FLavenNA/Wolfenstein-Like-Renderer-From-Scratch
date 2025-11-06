#include "renderer.h"
#include "graphics.h"

void render(const graphics_t *graphics)
{
    // Clear previous frame
    SDL_SetRenderDrawColor(graphics->renderer, 0, 0, 0, 255); // black background (or whatever you want)
    SDL_RenderClear(graphics->renderer);
    // TODO: Do rendering stuff in here
    draw_fps_counter(graphics);
    SDL_RenderPresent(graphics->renderer);
}