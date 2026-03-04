#include <stdlib.h>

#include "primitive_renderer.h"
#include "graphics.h"

void draw_filled_circle(uint32_t *fb, const int frame_buffer_width, const int frame_buffer_height, const int circle_x, const int circle_y, const int radius, const uint32_t color) {
    const int radius2 = radius * radius;

    for (int dy = -radius; dy <= radius; dy++) {
        const int y = circle_y + dy;
        if (y < 0 || y >= frame_buffer_height) continue;

        for (int dx = -radius; dx <= radius; dx++) {
            const int x = circle_x + dx;
            if (x < 0 || x >= frame_buffer_width) continue;

            if (dx*dx + dy*dy <= radius2) {
                fb[y * frame_buffer_width + x] = color;
            }
        }
    }
}

void draw_line(uint32_t *fb, int frame_buffer_width, int frame_buffer_height, int x0, int y0, int x1, int y1, uint32_t color)
{
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;

    while (1)
    {
        if (x0 >= 0 && x0 < frame_buffer_width && y0 >= 0 && y0 < frame_buffer_height)
            fb[y0 * frame_buffer_width + x0] = color;

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void put_pixel(uint32_t *fb, int x, int y, uint32_t color) {

    if (x < 0 || x >= FRAME_BUFFER_WIDTH || y < 0 || y >= FRAME_BUFFER_HEIGHT)
        return;

    fb[y * FRAME_BUFFER_WIDTH + x] = color;
}