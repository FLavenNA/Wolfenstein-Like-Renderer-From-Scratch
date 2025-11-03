#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdbool.h>

#include "type_defs.h"
#include "sdl.h"

enum app_state
{
    PAUSED,
    RUNNING,
    QUIT
};

struct app 
{
    app_state_t state;
    sdl_t sdl;
};

bool app_init(app_t *app);
void app_run(app_t *app);
void app_cleanup(const app_t *app);

#endif