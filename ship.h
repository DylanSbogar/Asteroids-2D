#ifndef SHIP_H
#define SHIP_H

#include "game_math.h"

#define SHIP_HEIGHT 24
#define SHIP_WIDTH  16

#define SHIP_MOVE_VELOCITY 7.5
#define SHIP_ROTATE_VELOCITY 5

#define SHIP_COLLISION 1.125
#define SHIP_NEARBY 5

#define SHIP_COLLISION_RADIUS SHIP_COLLISION * SHIP_HEIGHT
#define SHIP_NEARBY_RADIUS SHIP_NEARBY * SHIP_HEIGHT

struct ship
{
    struct vector2d pos; // Representing coords of the ship.
    struct vector2d dir; // Unit vector representing direction of the ship.
    float velocity;
    float fill_r, fill_g, fill_b; // Fill colour
    float outline_r, outline_g, outline_b; // Outline colour
};

struct particle
{
    struct vector2d pos;
    struct vector2d dir;
    float velocity;
    float lifespan;
    float fill_r, fill_g, fill_b;
    float outline_r, outline_g, outline_b;
    float size;
};

// Draws the ship.
void draw_ship(struct ship* ship);

// Initialises the ship.
void init_ship(struct ship* ship, int w, int h);

// Moves the ship.
void move_ship(struct ship* ship, float dt);

// Rotates the ship.
void rotate_ship(struct ship* ship, int turn_val, float dt);

#endif // SHIP_H