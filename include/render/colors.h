#ifndef COLORS_H
#define COLORS_H

// Even we use RGBA32 SDL decides depending on machine is little endian or big endian
// For my machine it stores as ABGR
#define RGBA_TO_ABGR_COLOR(r,g,b,a) ((uint32_t)((a) << 24) | ((b) << 16) | ((g) << 8) | (r))

// Mini map colors
#define MINI_MAP_WALL_COLOR     RGBA_TO_ABGR_COLOR(64,64,64,255)
#define MINI_MAP_PATH_COLOR     RGBA_TO_ABGR_COLOR(220,220,220,255)
#define MINI_MAP_PLAYER_COLOR   RGBA_TO_ABGR_COLOR(255,255,0,255)


// Graphics colors
#define FPS_COUNTER_BG          RGBA_TO_ABGR_COLOR(50, 50, 50, 128)

#endif