#include "map.h"
#include "player.h"

void map_init(map_t *map)
{
    // Simple rectangular room
    static const int layout[MAP_HEIGHT][MAP_WIDTH] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,7,7,0,0,0,0,0,2,2,0,0,0,1},
        {1,0,0,7,0,0,0,0,0,0,0,2,0,0,0,1},
        {1,0,0,7,0,0,1,0,3,0,0,2,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,3,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,5,5,0,0,0,0,4,4,0,1,0,1},
        {1,0,1,0,5,5,0,6,6,0,4,4,0,1,0,1},
        {1,0,1,0,0,0,0,6,6,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,1,6,6,0,0,0,0,0,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };

    for (int y = 0; y < MAP_HEIGHT; ++y)
        for (int x = 0; x < MAP_WIDTH; ++x)
            map->data[y][x] = layout[y][x];

    map->isVisible = true;
}

bool map_is_wall(const map_t *map, const int x, const int y)
{
    if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT)
        return 1;

    return map->data[y][x] != 0;
}