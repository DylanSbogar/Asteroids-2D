#ifndef ASTEROID_H
#define ASTEROID_H

#define ASTEROID_ROTATE_VELOCITY 10

#define ASTEROID_SPAWN_RADIUS 0.75

#define NUM_ASTEROIDS 10

#include <stdbool.h>
#include "game_math.h"
#include "ship.h"

struct asteroid {
    float outline_r,outline_g,outline_b; // Colour code for the asteroid.
    int starting_pos; // Starting point from the outer circle. (between 1 and 360).
    int size; // Size of the asteroid.
    struct vector2d pos; // Contains co-ordinates, angle and velocity.
    struct vector2d dir; // Unit vector containing direction of the asteroid.
    float velocity; 
    int seg; // Number of segments in the asteroid, used for random asteroid generation.
};

void init_asteroids(struct asteroid *asteroid, struct ship *ship, int w);

void draw_asteroids(struct asteroid *asteroid);

void move_asteroids(struct asteroid *asteroid, float dt);

bool ship_asteroid_collision();

#endif // ASTEROID_H