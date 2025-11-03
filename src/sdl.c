#include "sdl.h"
#include "application.h"

bool sdl_init(sdl_t *sdl) 
{
    if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Failed to init SDL !");
        return false;
    }

    sdl->window = SDL_CreateWindow("Wolfenstein Like Renderer", 1280, 720, SDL_WINDOW_RESIZABLE);

    if(!sdl->window) {
        SDL_Log("Could not create SDL window !");
        return false;
    }

    sdl->renderer = SDL_CreateRenderer(sdl->window, NULL);

    if(!sdl->renderer) {
        SDL_Log("Could not create SDL renderer !");
        return false;
    }

    return true;
}

void sdl_cleanup(const sdl_t *sdl) 
{
    SDL_DestroyWindow(sdl->window);
    SDL_DestroyRenderer(sdl->renderer);
    SDL_Quit();
}

void handle_input(app_t *app)
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        // TODO: Handle events here
        switch(event.type) 
        {
            case SDL_EVENT_QUIT:
                app->state = QUIT;
                break;
        }
    }
}