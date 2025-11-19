#include "graphics.h"

bool graphics_init(graphics_t *graphics) {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Failed to init SDL !");
        return false;
    }

    if (!TTF_Init()) {
        SDL_Log("Failed to init SDL_ttf !");
        return false;
    }

    graphics->window = SDL_CreateWindow("Wolfenstein Like Renderer", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

    if (!graphics->window) {
        SDL_Log("Could not create SDL window !");
        return false;
    }

    graphics->window_width = WINDOW_WIDTH;
    graphics->window_height = WINDOW_HEIGHT;

    if (!SDL_SetWindowMinimumSize(graphics->window, MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT)) {
        SDL_Log("Failed to set minimum window size !");
        return false;
    }

    graphics->renderer = SDL_CreateRenderer(graphics->window, NULL);

    if (!graphics->renderer) {
        SDL_Log("Could not create SDL renderer !");
        return false;
    }

    graphics->texture = SDL_CreateTexture(
        graphics->renderer,
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STREAMING,
        FRAME_BUFFER_WIDTH,
        FRAME_BUFFER_HEIGHT
    );

    if (!graphics->texture)
        return false;

    graphics->frame_buffer = malloc(FRAME_BUFFER_WIDTH * FRAME_BUFFER_HEIGHT * sizeof(uint32_t));

    if (!graphics->frame_buffer)
        return false;

    memset(graphics->frame_buffer, 0, FRAME_BUFFER_WIDTH * FRAME_BUFFER_HEIGHT * sizeof(uint32_t));

    graphics->font = TTF_OpenFont("assets/fonts/ComicSans.ttf", 32);

    if (!graphics->font) {
        SDL_Log("TTF_OpenFont() error !");
        return false;
    }

    return true;
}

void graphics_cleanup(graphics_t *graphics) {
    if (graphics->frame_buffer)
        free(graphics->frame_buffer);
    graphics->frame_buffer = NULL;

    if (graphics->window)
        SDL_DestroyWindow(graphics->window);

    if (graphics->renderer)
        SDL_DestroyRenderer(graphics->renderer);

    if (graphics->texture)
        SDL_DestroyTexture(graphics->texture);
    TTF_Quit();
    SDL_Quit();
}

void graphics_resize(graphics_t *graphics, const int width, const int height) {
    if (width == graphics->window_width && height == graphics->window_height)
        return;

    graphics->window_width = width;
    graphics->window_height = height;
}
