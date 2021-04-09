#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "asteroid.h"

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

// Initialises the asteroids
void init_asteroids(struct asteroid *asteroid, struct ship *ship, int w)
{
    // Set the color of the asteroids.
    asteroid->outline_r = 1;
    asteroid->outline_g = 1;
    asteroid->outline_b = 1;

    // Set the size of the asteroid.
    asteroid->size = 50;

    // Set the velocity of the asteroid.
    asteroid->velocity = ASTEROID_MOVE_VELOCITY;

    // Define a random position around the arena for an asteroid to spawn at.
    asteroid->starting_pos = (rand() % (360 - 1 + 1)) + 1;

    float theta = DEG_TO_RAD(asteroid->starting_pos);

    // Set the x and y co-ordinates of the asteroid.
    // asteroid->pos.x = 
    //     (w * 0.1) * cos(theta);
    // asteroid->pos.y =
    //     (w * 0.1) * sin(theta);
    asteroid->pos.x = w/2;
    asteroid->pos.y = w/2;

    struct vector2d test = direction_between_points(asteroid->pos, ship->pos);

    float length = pythagoras(test.x,test.y);

    asteroid->dir.x = (test.x / length);
    asteroid->dir.y = (test.y / length);
}

void draw_asteroids(struct asteroid *asteroid)
{
    for(int i = 0; i < NUM_ASTEROIDS; i++)
    {
        // Convert the direction unit vector to degrees.
        float angle = convert_to_angle(asteroid->dir.x, asteroid->dir.y) - 90;

        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();
        glTranslatef(asteroid[i].pos.x, asteroid[i].pos.y, 0);
        glRotatef(angle, 0.0, 0.0, 1.0);

        float theta;

        // Draw the asteroid.
        glColor3f(asteroid[i].outline_r, asteroid[i].outline_g, asteroid[i].outline_b);
        // glBegin(GL_LINE_LOOP);
        //     glVertex2f(0 - SHIP_WIDTH, 0 - SHIP_HEIGHT);
        //     glVertex2f(0, 0 - SHIP_HEIGHT * 0.5);
        //     glVertex2f(0 + SHIP_WIDTH, 0 - SHIP_HEIGHT);
        //     glVertex2f(0, 0 + SHIP_HEIGHT);
        // glEnd();
        glBegin(GL_LINE_LOOP);
            for(int i = 0; i < 360; i++)
            {
                theta = DEG_TO_RAD(i);
                glVertex2f(asteroid->size * cos(theta), asteroid->size *  sin(theta));
            }
        glEnd();
    }
}

void move_asteroids(struct asteroid *asteroid, float dt)
{
    for(int i = 0; i < NUM_ASTEROIDS; i++)
    {
        struct vector2d result = vector2d_scalar_mult(&asteroid[i].dir, asteroid[i].velocity);
        result = vector2d_scalar_mult(&result, dt);

        asteroid[i].pos = vector2d_addition(&asteroid[i].pos, &result);
    }
}

bool ship_asteroid_collision()
{
    return true;
}
