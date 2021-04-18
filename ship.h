#ifndef SHIP_H
#define SHIP_H

#include "game_math.h"
#include <stdbool.h>

#define SHIP_HEIGHT 24
#define SHIP_WIDTH  16

#define SHIP_MIN_MOVE_SPEED 5
#define SHIP_MAX_MOVE_SPEED 9
#define SHIP_ROTATE_VELOCITY 5

#define SHIP_COLLISION 1.125 // Multiplier for the collision radius
#define SHIP_NEARBY 5 // Multiplier for the nearby radius
#define SHIP_COLLISION_RADIUS SHIP_COLLISION * SHIP_HEIGHT
#define SHIP_NEARBY_RADIUS SHIP_NEARBY * SHIP_HEIGHT

#define MAX_PARTICLES 100
#define PARTICLE_START_SIZE 10
#define PARTICLE_LIFESPAN 100
#define PARTICLE_VELOCITY 2
#define PARTICLE_FREQ 10


typedef struct
{
    vector2d pos; // Vector representing the ship's co-ordinates.
    vector2d dir; // Unit vector representing direction of the ship.
    float velocity; // Velocity of the ship.
    float fill_r, fill_g, fill_b; // Fill colour.
    float outline_r, outline_g, outline_b; // Outline colour.
} ship;

typedef struct
{
    vector2d pos; // Vector representing the particle's co-ordinates.
    vector2d dir; // Unit vector representing direction of the vector.
    float velocity; // Velocity of the particle.
    float radius;
    int lifespan; // Lifespan of the particle.
    float size; // Radius of the particle.
    float fill_r, fill_g, fill_b; // Fill colour
    bool activated;
} particle;

// Draws the ship.
void draw_ship(ship* ship);

// Initialises the ship.
void init_ship(ship* ship, int w, int h);

// Moves the ship.
void move_ship(ship* ship, float dt);

// Rotates the ship.
void rotate_ship(ship* ship, int turn_val, float dt);

#endif // SHIP_H