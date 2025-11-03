#include "application.h"

bool app_init(app_t *app)
{
    if(!sdl_init(&app->sdl)) 
        return false;


    app->state = RUNNING;
    return true;
}

void app_run(app_t *app)
{
    while(app->state != QUIT) {
        handle_input(app);
    }
}

void app_cleanup(const app_t *app)
{
    sdl_cleanup(&app->sdl);
}