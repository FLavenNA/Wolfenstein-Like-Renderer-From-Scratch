#include "sdl.h"
#include "application.h"

bool sdl_init(graphics_t *graphics) 
{
    if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Failed to init SDL !");
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

    return true;
}

void sdl_cleanup(const graphics_t *graphics) 
{
    SDL_DestroyWindow(graphics->window);
    SDL_DestroyRenderer(graphics->renderer);
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

void update()
{

}

void render(const graphics_t *graphics)
{
    SDL_RenderClear(graphics->renderer);
    SDL_SetRenderDrawColor(graphics->renderer, 0, 255, 0, 255);
    SDL_RenderPresent(graphics->renderer);
}