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

void init_ship(struct ship *ship, int w, int h)
{
    // Setting the initial co-ords of the ship
    ship->pos.x = w * 0.25;
    ship->pos.y = h * 0.25;

    // Setting the velocity of the ship.
    ship->velocity = SHIP_MOVE_VELOCITY;

    // Same as above but unit vector for dir.
    struct vector2d temp;
    temp.x = w*0.75;
    temp.y = h*0.75;

    struct vector2d temp2 = direction_between_points(ship->pos, temp);

    float length = pythagoras(temp2.x, temp2.y);

    ship->dir.x = (temp2.x / length);
    ship->dir.y = (temp2.y / length);

    // Configurability for ship fill colour (R,G,B)
    ship->fill_r = 0.0;
    ship->fill_g = 1.0;
    ship->fill_b = 0.0;

    // Configurability for ship outline colour (R,G,B)
    ship->outline_r = 255.0;
    ship->outline_g = 255.0;
    ship->outline_b = 255.0;
}

void draw_ship(struct ship *ship)
{
    glMatrixMode(GL_MODELVIEW);
 
    // Convert the direction unit vector to degrees.
    float angle = convert_to_angle(ship->dir.x, ship->dir.y) - 90;

    glPushMatrix();
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

    float theta;

    // Draw the ship collision bubble (will make invisible later)
    glColor3f(1, 0, 1);
    glBegin(GL_LINE_LOOP);
        for(int i = 0; i < 360; i++)
        {
            theta = DEG_TO_RAD(i); 
            glVertex2f(SHIP_COLLISION_RADIUS * cos(theta), SHIP_COLLISION_RADIUS *  sin(theta));
        }
    glEnd();

    // // Draw the ship arena warning bubble (will make invisible later)
    // glColor3f(1, 0, 1);
    // glBegin(GL_LINE_LOOP);
    //     for(int i = 0; i < 360; i++)
    //     {
    //         theta = DEG_TO_RAD(i);
    //         glVertex2f(SHIP_NEARBY_RADIUS * cos(theta), SHIP_NEARBY_RADIUS *  sin(theta));
    //     }
    // glEnd();

    glPopMatrix();
}

void rotate_ship(struct ship* ship, int turn_val, float dt)
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

void move_ship(struct ship* ship, float dt)
{
    struct vector2d result;

    result.x = ship->dir.x * ship->velocity;
    result.y = ship->dir.y * ship->velocity;

    ship->pos.x = ship->pos.x + result.x;
    ship->pos.y = ship->pos.y + result.y;
}
