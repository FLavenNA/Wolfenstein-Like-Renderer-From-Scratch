#include <stdio.h>

#include "renderer.h"
#include "graphics.h"
#include "engine.h"
#include "map.h"
#include  "colors.h"

void render(const engine_t *engine) {
    clear_screen_buffer(&engine->graphics);
    map_draw(&engine->graphics, &engine->map, &engine->player);
    draw_fps_counter(&engine->graphics);
    update_screen(&engine->graphics);
}

void clear_screen_buffer(const graphics_t *graphics) {
    // Clear SDL_Renderer too
    // Because it keeps old frames
    SDL_SetRenderDrawColor(graphics->renderer, 0, 0, 0, 255);
    SDL_RenderClear(graphics->renderer);

    // Clear CPU buffer each time as well
    // TODO : Don't know if its right.
    memset(graphics->frame_buffer, 0, FRAME_BUFFER_WIDTH * FRAME_BUFFER_HEIGHT * sizeof(uint32_t));
}

void update_screen(const graphics_t *graphics) {
    SDL_UpdateTexture(graphics->texture, NULL, graphics->frame_buffer, WINDOW_WIDTH * sizeof(uint32_t));
    SDL_RenderTexture(graphics->renderer, graphics->texture, NULL, NULL);
    SDL_RenderPresent(graphics->renderer);
}

void draw_fps_counter(const graphics_t *graphics) {
    if (!graphics || !graphics->font || !graphics->frame_buffer)
        return;

    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%.2f", graphics->avg_fps);

    const SDL_Color white = {255, 255, 255, 255};

    SDL_Surface *surface = TTF_RenderText_Blended(graphics->font, buffer, 0, white);

    if (!surface) {
        SDL_Log("TTF_RenderText_Blended failed");
        return;
    }

    const int margin = 10;

    const int x0 = margin;
    const int y0 = margin;
    uint32_t *fb = graphics->frame_buffer;

    // Draw background rectangle for text surface
    for (int y = 0; y < surface->h; y++) {
        const int yy = y0 + y;
        if (yy < 0 || yy >= FRAME_BUFFER_HEIGHT) continue;

        for (int x = 0; x < surface->w; x++) {
            const int xx = x0 + x;
            if (xx < 0 || xx >= FRAME_BUFFER_WIDTH) continue;

            fb[yy * FRAME_BUFFER_WIDTH + xx] = FPS_COUNTER_BG;
        }
    }

    const SDL_PixelFormatDetails *format_details = SDL_GetPixelFormatDetails(surface->format);

    // Correct pixel blending using pitch and format
    for (int y = 0; y < surface->h; y++) {
        const int yy = y0 + y;
        if (yy < 0 || yy >= FRAME_BUFFER_HEIGHT) continue;

        // Pointer to start of the row (use pitch!)
        uint8_t *row = (uint8_t *)surface->pixels + y * surface->pitch;

        for (int x = 0; x < surface->w; x++) {
            const int xx = x0 + x;
            if (xx < 0 || xx >= FRAME_BUFFER_WIDTH) continue;

            const uint32_t *pixel_ptr = (uint32_t *)(row + x * format_details->bytes_per_pixel);
            const uint32_t src_pixel = *pixel_ptr;

            uint8_t src_r, src_g, src_b, src_a;
            SDL_GetRGBA(src_pixel, format_details, NULL, &src_r, &src_g, &src_b, &src_a);
            if (src_a == 0) continue;

            // Read current background
            uint32_t *dst = &fb[yy * FRAME_BUFFER_WIDTH + xx];
            const uint8_t dst_r = (*dst >> 16) & 0xFF;
            const uint8_t dst_g = (*dst >> 8) & 0xFF;
            const uint8_t dst_b = (*dst) & 0xFF;

            // Blend in with background
            const float alpha = (float)src_a / 255.0f;
            const uint8_t out_r = (uint8_t)((float)src_r * alpha + (float)dst_r * (1.0f - alpha));
            const uint8_t out_g = (uint8_t)((float)src_g * alpha + (float)dst_g * (1.0f - alpha));
            const uint8_t out_b = (uint8_t)((float)src_b * alpha + (float)dst_b * (1.0f - alpha));
            const uint8_t out_a = 255;

            // Write to destination
            *dst = RGBA_TO_ABGR_COLOR(out_r, out_g, out_b, out_a);
        }
    }

    SDL_DestroySurface(surface);
}

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