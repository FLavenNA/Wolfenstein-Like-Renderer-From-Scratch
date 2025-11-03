#include <stdio.h>

#include "application.h"

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    app_t app;

    app_init(&app);
    app_run(&app);
    app_cleanup(&app);

    return 0;
}