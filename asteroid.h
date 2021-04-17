#ifndef ASTEROID_H
#define ASTEROID_H

#define ASTEROID_ROTATE_VELOCITY 10
#define ASTEROID_SPAWN_RADIUS 0.75
#define MAX_ASTEROIDS 10 // Defines the max number of rounds, since the number of asteroids increments each round from 1.

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
    bool activated; // Is true when the asteroid is on screen.
};

void init_asteroid(struct asteroid *asteroid, struct ship *ship, int w, int h);

void draw_asteroid(struct asteroid *asteroid);

void move_asteroid(struct asteroid *asteroid, float dt, int round);

bool ship_asteroid_collision(struct asteroid *asteroid, struct ship *ship);

int checkActivated(struct asteroid *asteroid, int w, int h, int temp);

#endif // ASTEROID_H