#include "graphics.h"

#include <stdio.h>

bool graphics_init(graphics_t *graphics) 
{
    if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Failed to init SDL !");
        return false;
    }

    if(!TTF_Init()) {
        SDL_Log("Failed to init SDL_ttf !");
        return false;
    }

    graphics->window = SDL_CreateWindow("Wolfenstein Like Renderer", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

    if(!graphics->window) {
        SDL_Log("Could not create SDL window !");
        return false;
    }

    if(!SDL_SetWindowMinimumSize(graphics->window, MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT)) {
        SDL_Log("Failed to set minimum window size !");
        return false;
    }

    graphics->renderer = SDL_CreateRenderer(graphics->window, NULL);

    if(!graphics->renderer) {
        SDL_Log("Could not create SDL renderer !");
        return false;
    }

    graphics->font = TTF_OpenFont("assets/fonts/ComicSans.ttf", 32);

    if(!graphics->font) {
        SDL_Log("TTF_OpenFont() error !");
        return false;
    }

    return true;
}

void graphics_cleanup(const graphics_t *graphics) 
{
    SDL_DestroyWindow(graphics->window);
    SDL_DestroyRenderer(graphics->renderer);
    TTF_Quit();
    SDL_Quit();
}

void draw_fps_counter(const graphics_t *graphics)
{
    if (!graphics || !graphics->avg_fps || !graphics->font || !graphics->renderer)
        return;

    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%.2f", graphics->avg_fps);

    SDL_Color white = {255, 255, 255, 255};

    SDL_Surface *surface = TTF_RenderText_Blended(graphics->font, buffer, strlen(buffer), white);

    if (!surface) {
        SDL_Log("TTF_RenderText_Blended failed");
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(graphics->renderer, surface);
    if (!texture) {
        SDL_Log("SDL_CreateTextureFromSurface failed: %s", SDL_GetError());
        SDL_DestroySurface(surface);
        return;
    }

    // Use text size to set correct rects
    float margin = 10.0f;   // margin from window edge
    float padding = 6.0f;   // padding inside the background box

    float text_w = (float)surface->w;
    float text_h = (float)surface->h;

    SDL_FRect dstRect = {
        margin + padding,
        margin + padding,
        text_w,
        text_h
    };

    SDL_FRect bgRect = {
        margin,
        margin,
        text_w + padding * 2.0f,
        text_h + padding * 2.0f
    };

    SDL_DestroySurface(surface);

    SDL_SetRenderDrawBlendMode(graphics->renderer, SDL_BLENDMODE_BLEND);

    // Half-transparent dark gray background
    SDL_SetRenderDrawColor(graphics->renderer, 50, 50, 50, 150);
    SDL_RenderFillRect(graphics->renderer, &bgRect); // Must use &bgRect!

    // Draw the text on top
    SDL_RenderTexture(graphics->renderer, texture, NULL, &dstRect);

    // Cleanup texture
    SDL_DestroyTexture(texture);
}