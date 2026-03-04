#ifndef PRIMITIVE_RENDERER_H
#define PRIMITIVE_RENDERER_H

#include "type_defs.h"

// Primitive Types
void draw_filled_circle(uint32_t *fb, int frame_buffer_width, int frame_buffer_height, int circle_x, int circle_y, int radius, uint32_t color);
void draw_line(uint32_t *fb, int frame_buffer_width, int frame_buffer_height, int x0, int y0, int x1, int y1, uint32_t color);
void put_pixel(uint32_t *fb, int x, int y, uint32_t color);

#endif