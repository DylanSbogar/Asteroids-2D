#ifndef GAME_INIT_H
#define GAME_INIT_H

#include "ship.h"
#include "asteroid.h"
#include "arena.h"
#include <time.h>
#include <stdbool.h>

struct key_handler
{
    bool moving_forward;
    bool turning_left;
    bool turning_right;
};

// Initialisation function.
void init_game();

// Glut reshape function.
void on_reshape(int w, int h);

// Glut display function.
void on_display();

// Glut idle function.
void on_idle();

// Checks for collisions between the ship and the wall.
void ship_wall_warning();

// Recalls the init_game method, starting the game anew.
void reset_game();

void update_game_state(struct ship *ship, struct asteroid *asteroid, struct arena *arena, float dt);

// Glut keyboard function.
void on_key_press(unsigned char key, int x, int y);

// Glut keyboard up function.
void on_key_up(unsigned char key, int x, int y);

// Glut mouse function.
void on_mouse_press();

#endif // GAME_INIT_H