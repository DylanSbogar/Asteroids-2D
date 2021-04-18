#ifndef ASTEROID_H
#define ASTEROID_H

#define ASTEROID_MIN_SIZE 60
#define ASTEROID_MAX_SIZE 75

#define ASTEROID_ROTATE_MIN_SPEED 5
#define ASTEROID_ROTATE_MAX_SPEED 8
#define ASTEROID_SPAWN_RADIUS 0.75

#define MAX_ASTEROIDS 10 // Defines the max number of rounds, since the number of asteroids increments each round from 1.
#define ASTEROID_POINTS 24

#include <stdbool.h>
#include "game_math.h"
#include "ship.h"

typedef struct {
    float outline_r,outline_g,outline_b; // Colour code for the asteroid.
    int starting_pos; // Starting point from the outer circle. (between 1 and 360).
    float angle;
    int turn_val;
    int size; // Size of the asteroid.
    vector2d pos; // Contains co-ordinates, angle and velocity.
    vector2d dir; // Unit vector containing direction of the asteroid.
    float velocity; 
    float rotate_velocity;
    bool activated; // Is true when the asteroid is on screen.
    float points[ASTEROID_POINTS];
} asteroid;

void init_asteroid(asteroid *asteroid, ship *ship, int w, int h);

void draw_asteroid(asteroid *asteroid);

void move_asteroid(asteroid *asteroid, float dt, int round);

void rotate_asteroid(asteroid *asteroid, int turn_val, float dt);

bool ship_asteroid_collision(asteroid *asteroid, ship *ship);

int checkActivated(asteroid *asteroid, int w, int h, int num_detected);

#endif // ASTEROID_H