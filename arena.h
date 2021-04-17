#ifndef ARENA_H
#define ARENA_H

#include <stdbool.h>
#include "game_math.h"
#include "ship.h"

// Percentage of the screen width and height that the arena will encompass.
#define ARENA_PERCENTAGE 0.95

typedef struct
{
    float north_r, north_g, north_b; // Color values for the northern wall.
    float south_r, south_g, south_b; // Color values for the southern wall.
    float east_r, east_g, east_b; // Color values for the western wall.
    float west_r, west_g, west_b; // Color values for the eastern wall.
    vector2d pos1, pos2; // Co-ordinates for the south-west and north-east corners of the wall.
} arena;

void init_arena(arena *arena, int w, int h);

void draw_arena(arena *arena);

void ship_wall_warning(arena *arena, ship *ship);

bool ship_wall_collision(arena *arena, ship *ship);

#endif // ARENA_H