#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "arena.h"

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

void init_arena(arena *arena, int w, int h)
{
    // Set the bottom left corner of the arena.
    arena->pos1.x = w * (1 - ARENA_PERCENTAGE);
    arena->pos1.y = h * (1 - ARENA_PERCENTAGE);

    // Set the top right corner of the arena.
    arena->pos2.x = w * ARENA_PERCENTAGE;
    arena->pos2.y = h * ARENA_PERCENTAGE;
}

void draw_arena(arena *arena)
{
    // Using the 2 corners from the init method, draw each
    // of the 4 wall segments.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // Draw each line separately as they need to be individually changed,
    // same goes for colours, set the color of each line individually as well.
    glBegin(GL_LINES);
        // Draw the southern wall of the arena.
        glColor3f(arena->south_r, arena->south_g, arena->south_b);
        glVertex2f(arena->pos1.x, arena->pos1.y);
        glVertex2f(arena->pos2.x, arena->pos1.y);
        
        // Draw the eastern wall of the arena.
        glColor3f(arena->east_r, arena->east_g, arena->east_b);
        glVertex2f(arena->pos2.x, arena->pos1.y);
        glVertex2f(arena->pos2.x, arena->pos2.y);

        // Draw the northern wall of the arena.
        glColor3f(arena->north_r, arena->north_g, arena->north_b);
        glVertex2f(arena->pos2.x, arena->pos2.y);
        glVertex2f(arena->pos1.x, arena->pos2.y);

        // Draw the western wall of the arena.
        glColor3f(arena->west_r, arena->west_g, arena->west_b);
        glVertex2f(arena->pos1.x, arena->pos2.y);
        glVertex2f(arena->pos1.x, arena->pos1.y);
    glEnd();

    glPopMatrix();
}

void ship_wall_warning(arena *arena, ship *ship)
{
    // Checking collisions at the northern wall.
    if(arena->pos2.y <= ship->pos.y + SHIP_NEARBY_RADIUS)
    {
        // Change the wall segment to red if collision is detected.
        arena->north_r = 1;
        arena->north_g = 0;
        arena->north_b = 0;
    }
    else
    {
        // Change the wall segment to white if no collision is detected.
        arena->north_r = 1;
        arena->north_g = 1;
        arena->north_b = 1;
    }

    // Checking collisions at the southern wall.
    if(arena->pos1.y >= ship->pos.y - SHIP_NEARBY_RADIUS)
    {
        // Change the wall segment to red if collision is detected.
        arena->south_r = 1;
        arena->south_g = 0;
        arena->south_b = 0;
    }
    else
    {
        // Change the wall segment to white if no collision is detected.
        arena->south_r = 1;
        arena->south_g = 1;
        arena->south_b = 1;
    }

    // Checking collisions at the western wall.
    if(arena->pos1.x >= ship->pos.x - SHIP_NEARBY_RADIUS)
    {
        // Change the wall segment to red if collision is detected.
        arena->west_r = 1;
        arena->west_g = 0;
        arena->west_b = 0;
    }
    else
    {
        // Change the wall segment to white if no collision is detected.
        arena->west_r = 1;
        arena->west_g = 1;
        arena->west_b = 1;
    }

    // Checking collisions at the eastern wall.
    if(arena->pos2.x <= ship->pos.x + SHIP_NEARBY_RADIUS)
    {
        // Change the wall segment to red if collision is detected.
        arena->east_r = 1;
        arena->east_g = 0;
        arena->east_b = 0;
    }
    else
    {
        // Change the wall segment to white if no collision is detected.
        arena->east_r = 1;
        arena->east_g = 1;
        arena->east_b = 1;
    }
}

bool ship_wall_collision(arena *arena, ship *ship)
{
    // Checking collisions at the northern wall.
    if(arena->pos2.y <= ship->pos.y + SHIP_COLLISION_RADIUS)
    {
        return true;
    }

    // Checking collisions at the southern wall.
    if(arena->pos1.y >= ship->pos.y - SHIP_COLLISION_RADIUS)
    {
        return true;
    }

    // Checking collisions at the western wall.
    if(arena->pos1.x >= ship->pos.x - SHIP_COLLISION_RADIUS)
    {
        return true;
    }

    // Checking collisions at the eastern wall.
    if(arena->pos2.x <= ship->pos.x + SHIP_COLLISION_RADIUS)
    {
        return true;
    }
    else
    {
        return false;
    }
}