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

time_t t;

// Initialises the asteroids
void init_asteroids(struct asteroid *asteroid, struct ship *ship, int w, int h)
{
    // Initialise the random number generator.
    srand((unsigned) time(&t));

    // Set the color of the asteroids.
    asteroid->outline_r = 1;
    asteroid->outline_g = 1;
    asteroid->outline_b = 1;

    // Set the size of the asteroid.
    asteroid->size = 75;

    // Set the velocity of the asteroid.
    asteroid->velocity = (rand() % (20 + 1 - 5) + 5);
    // asteroid->velocity = 0;

    // Define a random position around the arena for an asteroid to spawn at.
    asteroid->starting_pos = (rand() % (360 - 1 + 1)) + 1;

    float theta = DEG_TO_RAD(asteroid->starting_pos);

    // Set the x and y co-ordinates of the asteroid.
    asteroid->pos.x = 
        (w * 1.1) * cos(theta)  + w/2;
    asteroid->pos.y =
        (w * 1.1) * sin(theta) + h/2;
    // asteroid->pos.x = w/2;
    // asteroid->pos.y = w/2;

    // Determine the angle of the asteroid, so its facing the ships current position.
    struct vector2d test = direction_between_points(asteroid->pos, ship->pos);

    float length = pythagoras(test.x,test.y);

    asteroid->dir.x = (test.x / length);
    asteroid->dir.y = (test.y / length);
}

void draw_asteroids(struct asteroid *asteroid)
{
    // Convert the direction unit vector to degrees.
    float angle = convert_to_angle(asteroid->dir.x, asteroid->dir.y) - 90;

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(asteroid->pos.x, asteroid->pos.y, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);

    float theta;

    // Draw the asteroid.
    glColor3f(asteroid->outline_r, asteroid->outline_g, asteroid->outline_b);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 360; i++)
    {
        theta = DEG_TO_RAD(i);
        glVertex2f(asteroid->size * cos(theta), asteroid->size *  sin(theta));
    }
    glEnd();
    glPopMatrix();
}

void move_asteroids(struct asteroid *asteroid, float dt)
{
    for(int i = 0; i < NUM_ASTEROIDS; i++)
    {
        struct vector2d result;

        result.x = asteroid[i].dir.x * asteroid->velocity;
        result.y = asteroid[i].dir.y * asteroid->velocity;

        asteroid[i].pos.x = asteroid[i].pos.x + result.x;
        asteroid[i].pos.y = asteroid[i].pos.y + result.y;
    }
}

bool ship_asteroid_collision(struct asteroid *asteroid, struct ship *ship)
{
    float length = 0;
    struct vector2d test = direction_between_points(asteroid->pos, ship->pos);

    length = pythagoras(test.x, test.y);
    // printf("length=%f\n",length);
    // printf("distance=%f\n",asteroid[i].size + SHIP_COLLISION_RADIUS);

    if(length <= asteroid->size + SHIP_COLLISION_RADIUS)
    {
        return true;
    }
    else
    {
        return false;
    }
}
