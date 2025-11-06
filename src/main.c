#include "engine.h"

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    engine_t engine = {0};

    engine_init(&engine);
    engine_run(&engine);
    engine_cleanup(&engine);

    return 0;
}