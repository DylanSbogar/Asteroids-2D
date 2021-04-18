#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "ship.h"

#if _WIN32
# include <windows.h>
#endif
#if __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

int particle_cooldown = 0;
int current_particle = 0;

particle particles[MAX_PARTICLES];

void init_ship(ship *ship, int w, int h)
{
    // Setting the initial co-ords of the ship
    ship->pos.x = (w * 0.05) + (SHIP_NEARBY_RADIUS * 1.1);
    ship->pos.y = (h * 0.05) + (SHIP_NEARBY_RADIUS * 1.1);

    // Setting the velocity of the ship.
    ship->velocity = SHIP_MAX_MOVE_SPEED;

    // Set the coordinates for the ship's direction to face the upper-right corner of the screen.
    vector2d direction;
    direction.x = w;
    direction.y = h;

    // Determine the length of the vector to prep for normalisation.
    vector2d direction2 = direction_between_points(ship->pos, direction);
    float length = pythagoras(direction2.x, direction2.y);

    // Normalising the unit vector representing direction.
    ship->dir.x = (direction2.x / length);
    ship->dir.y = (direction2.y / length);

    // Configurability for ship fill colour (R,G,B)
    ship->fill_r = 0.0;
    ship->fill_g = 0.0;
    ship->fill_b = 1.0;

    // Configurability for ship outline colour (R,G,B)
    ship->outline_r = 255.0;
    ship->outline_g = 255.0;
    ship->outline_b = 255.0;
}

void draw_ship(ship *ship)
{
    glMatrixMode(GL_MODELVIEW);
 
    // Convert the direction unit vector to degrees.
    float angle = convert_to_angle(ship->dir.x, ship->dir.y) - 90;

    glPushMatrix();

    // Translate and rotate the ship.
    glTranslatef(ship->pos.x, ship->pos.y, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);

    // Draw the ship inside.
    glColor3f(ship->fill_r, ship->fill_g, ship->fill_b);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(0 - SHIP_WIDTH, 0 - SHIP_HEIGHT);
        glVertex2f(0, 0 + SHIP_HEIGHT);
        glVertex2f(0, 0 - SHIP_HEIGHT * 0.5);
        glVertex2f(0 + SHIP_WIDTH, 0 - SHIP_HEIGHT);
    glEnd();

    // Draw the ship outline.
    glColor3f(ship->outline_r, ship->outline_g, ship->outline_b);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0 - SHIP_WIDTH, 0 - SHIP_HEIGHT);
        glVertex2f(0, 0 - SHIP_HEIGHT * 0.5);
        glVertex2f(0 + SHIP_WIDTH, 0 - SHIP_HEIGHT);
        glVertex2f(0, 0 + SHIP_HEIGHT);
    glEnd();
    glPopMatrix();
}

void rotate_ship(ship* ship, int turn_val, float dt)
{
    // Convert the unit vector into an angle in degrees.
    float new_angle = convert_to_angle(ship->dir.x, ship->dir.y);

    // Increment/Decrement the angle depending on whether the player is turning left/right.
    new_angle += turn_val * SHIP_ROTATE_VELOCITY;

    // Convert the angle back to radians for functions.
    float new_angle_rad = DEG_TO_RAD(new_angle);

    // Update the co-ordinates of the unit vector.
    ship->dir.x = cos(new_angle_rad);
    ship->dir.y = sin(new_angle_rad);
}

void move_ship(ship* ship, float dt)
{
    vector2d result;

    // Multiply the ships direction vector by the ships velocity.
    result.x = ship->dir.x * ship->velocity;
    result.y = ship->dir.y * ship->velocity;

    // Add the resultant vector with the ships corrent position vector,
    // then set that as the ships current postiion.
    ship->pos.x = ship->pos.x + result.x;
    ship->pos.y = ship->pos.y + result.y;
}