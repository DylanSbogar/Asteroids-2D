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

// Initialises the  asteroids
void init_asteroid(struct asteroid *asteroid, struct ship *ship, int w, int h)
{
    // Set the color of the asteroids.
    asteroid->outline_r = 1;
    asteroid->outline_g = 1;
    asteroid->outline_b = 1;

    // Set the size of the asteroid.
    asteroid->size = 75;

    // Set the velocity of the asteroid.
    asteroid->velocity = (rand() % (20 + 1 - 5) + 5);

    // 2.1. Launch Position
    // Define a random position around the arena for an asteroid to spawn at.
    asteroid->starting_pos = (rand() % (360 - 1 + 1)) + 1;
    float theta = DEG_TO_RAD(asteroid->starting_pos);
    
    // Set the x and y co-ordinates of the asteroid.
    asteroid->pos.x = 
        (w * 1.1) * cos(theta)  + (w/2);
    asteroid->pos.y =
        (w * 1.1) * sin(theta) + (h/2);

    // Determine the angle of the asteroid, so its facing the ships current position.
    struct vector2d test = direction_between_points(asteroid->pos, ship->pos);
    float length = pythagoras(test.x,test.y);

    // Normalise the direction vector of the asteroid.
    asteroid->dir.x = (test.x / length);
    asteroid->dir.y = (test.y / length);

    // Start asteroids as deactivated.
    asteroid->activated = false;
}

void draw_asteroid(struct asteroid *asteroid)
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

void move_asteroid(struct asteroid *asteroid, float dt, int round)
{
    for(int i = 0; i < round; i++)
    {
        struct vector2d result;

        result.x = asteroid[i].dir.x * asteroid[i].velocity;
        result.y = asteroid[i].dir.y * asteroid[i].velocity;

        asteroid[i].pos.x = asteroid[i].pos.x + result.x;
        asteroid[i].pos.y = asteroid[i].pos.y + result.y;
    }
}

bool ship_asteroid_collision(struct asteroid *asteroid, struct ship *ship)
{
    float length = 0;
    struct vector2d test = direction_between_points(asteroid->pos, ship->pos);

    length = pythagoras(test.x, test.y);

    if(length <= asteroid->size + SHIP_COLLISION_RADIUS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int checkActivated(struct asteroid *asteroid, int w, int h, int temp)
{
        // If the asteroid is on-screen.
        if((asteroid->pos.x <= w && asteroid->pos.x >= 0) && (asteroid->pos.y <=h && asteroid->pos.y >= 0))
        {
            // Activate the asteroid, so we know to track its movements.
            asteroid->activated = true;
            // printf("its in the ring baby\n");
        }
        // If the asteroid is activated
        if(asteroid->activated)
        {
            // Check if the asteroid is to the right of left of the screen respectively.
            if(w <= asteroid->pos.x || 0 >= asteroid->pos.x)
            {
                // asteroid->velocity = 0;
                asteroid->activated = false;
                temp--;
                return temp;
            }
            // Check if the asteroid is above or below the screen respectively.
            if(h <= asteroid->pos.y || 0 >= asteroid->pos.y)
            {
                // asteroid->velocity = 0;
                asteroid->activated = false;
                temp--;
                return temp;
            }
        }

        return temp;
}
