#ifndef COLORS_H
#define COLORS_H

#include <SDL3/SDL.h>

// Even we use RGBA32 SDL decides depending on machine is little endian or big endian
// For my machine it stores as ARGB

// Mini map colors
#define MINI_MAP_WALL_COLOR 0xFF646464
#define MINI_MAP_PATH_COLOR 0xFFDCDCDC

// FPS COLORS
#define FPS_COUNTER_BG 0x80323232 // FPS Background color - Transparent Gray

#endif