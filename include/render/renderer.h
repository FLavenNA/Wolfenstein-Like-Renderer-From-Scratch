#ifndef RENDERER_H
#define RENDERER_H

#include "u_math.h"
#include "type_defs.h"

struct plane {
    int t[1024]; // Top
    int b[1024]; // Bottom
};

struct wall {
    vec2_t a;
    vec2_t b;
    double portal_top_height;
    double portal_bottom_height;
    bool is_portal;
};

struct sector {
    int id;
    wall_t walls[10];
    int num_walls;
    int height;
    int elevation;
    double dist;
    uint32_t color;
    uint32_t floor_clr;
    uint32_t ceil_clr;

    plane_lut_t portals_floor_xylut;
    plane_lut_t portals_ceiling_xylut;
    plane_lut_t floor_xylut;
    plane_lut_t ceiling_xylut;
};

struct sectors_queue {
    sector_t sectors[1024];
    int num_sectors;
};

void render(const graphics_t *graphics);

#endif