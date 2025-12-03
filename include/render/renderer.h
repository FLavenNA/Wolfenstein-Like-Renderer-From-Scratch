#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>

#include "u_math.h"
#include "type_defs.h"

void render(const engine_t *engine);
void clear_screen_buffer(const graphics_t * graphics);
void update_screen(const graphics_t *graphics);
void draw_fps_counter(const graphics_t *graphics);

// Helper function
void draw_filled_circle(uint32_t *fb, int frame_buffer_width, int frame_buffer_height, int circle_x, int circle_y, int radius, uint32_t color);

#endif