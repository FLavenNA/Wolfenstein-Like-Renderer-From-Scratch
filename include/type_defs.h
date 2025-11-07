#ifndef TYPE_DEFS_H
#define TYPE_DEFS_H

#include <stdbool.h>
#include <stdint.h>

// Core type defs
typedef struct graphics graphics_t;
typedef enum engine_state engine_state_t;
typedef struct engine engine_t;

// Render type defs
typedef struct plane plane_lut_t; // Lookup table
typedef struct wall wall_t;
typedef struct sector sector_t;
typedef struct sectors_queue sectors_queue_t;

// Utils type defs
typedef struct vec2 vec2_t;

// Game type defs
typedef struct map map_t;

#endif