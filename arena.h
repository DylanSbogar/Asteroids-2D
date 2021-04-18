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

// Initialise the arena.
void init_arena(arena *arena, int w, int h);

// Draw the arena.
void draw_arena(arena *arena);

// Check if the ship is close to the arena wall.
void ship_wall_warning(arena *arena, ship *ship);

// Check if the ship has collided with the wall.
bool ship_wall_collision(arena *arena, ship *ship);

// Draw strings at a given location on the screen.
void draw_string(float x, float y, char* string, int w, int h);

#endif // ARENA_H