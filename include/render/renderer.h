#ifndef RENDERER_H
#define RENDERER_H

#include "type_defs.h"

void render(const engine_t *engine);
void clear_screen_buffer(const graphics_t * graphics);
void update_screen(const graphics_t *graphics);
void draw_fps_counter(const graphics_t *graphics);

#endif