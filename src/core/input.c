#include <SDL3/SDL.h>

#include "input.h"
#include "engine.h"

void handle_input(engine_t *engine)
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        // TODO: Handle events here
        switch(event.type) 
        {
            case SDL_EVENT_QUIT:
                engine->state = QUIT;
                break;
        }
    }
}