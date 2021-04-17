#include <stdlib.h>
#include <stdio.h>

#include "game_init.h"

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

#define KEY_ESC 27

int rounds = 0;
int temprounds = 0;
int screen_width = 0;
int screen_height = 0;
float g_last_time = 0.0;

// Instantiate various game elements.
struct key_handler kh;
struct arena arena;
struct ship ship;
struct asteroid asteroids[MAX_ASTEROIDS];

void on_reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0, 1.0); // range from 0 -> screen width, 0 -> screen_height

    screen_width = w;
    screen_height = h;

    time_t t;

    // Initialise the random number generator.
    srand((unsigned) time(&t));

    // Initialise the various game elements.
    init_ship(&ship, screen_width, screen_height);
    init_arena(&arena, screen_width, screen_height);
    for(int i = 0; i < rounds; i++)
    {
        init_asteroid(&asteroids[i], &ship, screen_width, screen_height);
    }
}

void on_display()
{
    // Clear the display in time for the next frame.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw the various game elements.
    draw_ship(&ship);
    draw_arena(&arena);
    for(int i = 0; i < rounds; i++)
    {
        draw_asteroid(&asteroids[i]);
    }

    // Check for and print out any errors.
    int err;
    while ((err = glGetError()) != GL_NO_ERROR)
    printf("error: %s\n", gluErrorString(err));

    // Swap buffers.
    glutSwapBuffers();
}

void update_game_state(struct ship *ship, struct asteroid *asteroid, struct arena *arena, float dt)
{
    if(kh.moving_forward)
    {
        move_ship(ship, dt);
    }
    if(kh.turning_left)
    {
        rotate_ship(ship, -1, dt);
    }
    if(kh.turning_right)
    {
        rotate_ship(ship, 1, dt);
    }

    // Check to see whether the ship is nearing any walls.
    ship_wall_warning(arena, ship);

    // Check to see whether the ship has collided with the wall.
    if(ship_wall_collision(arena, ship))
    {
        reset_game();
    }

    for(int i = 0; i < rounds; i++)
    {
        if(ship_asteroid_collision(&asteroids[i], ship))
        {
            reset_game();
        }
    }

    for(int i = 0; i < rounds; i++)
    {
        temprounds = checkActivated(&asteroids[i], screen_width, screen_height, temprounds);
    }

    if(temprounds == 0)
    {
        printf("ROUND OVER\n");
        rounds++;
        temprounds = rounds;
        printf("STARTING ROUND %d\n",rounds);

        for(int i = 0; i < rounds; i++)
        {
            init_asteroid(&asteroids[i], ship, screen_width, screen_height);
        }
    }
}

void on_idle()
{
    float cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    float dt = cur_time - g_last_time;
    update_game_state(&ship, asteroids, &arena, dt);
    move_asteroid(asteroids, dt, rounds);
    g_last_time = cur_time;
    glutPostRedisplay();
}

void on_key_press(unsigned char key, int x, int y)
{
    float dt = glutGet(GLUT_ELAPSED_TIME) / 1000.0 - g_last_time;

    switch(toupper(key))
    {  
        // Exit the game if the user hits the escape key.
        case KEY_ESC:
            exit(EXIT_SUCCESS);
            break;
        case 'W':
        // Move the ship forward if the user hits the w key.
            kh.moving_forward = true;
            glutPostRedisplay();
            break;
        case 'A':
        // Turn the ship to the left if the user hits the a key.
            kh.turning_right = true;
            glutPostRedisplay();
            break;
        case 'D':
        // Turn the ship to the right if the user hits the d key.
            kh.turning_left = true;
            glutPostRedisplay();
            break;
    }
}

void on_key_up(unsigned char key, int x, int y)
{
    switch(toupper(key))
    {
        case 'W':
        kh.moving_forward = false;
        break;
        case 'A':
        kh.turning_right = false;
        break;
        case 'D':
        kh.turning_left = false;
        break;
    }
}

// void on_mouse_press()
// {

// }

void reset_game()
{
    init_game();
}

void init_game()
{
    rounds = 1;
    temprounds = 1;

    // Setting up the window.
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Asteroids - Assignment 1");
    glutFullScreen();

    kh.moving_forward = false;
    kh.turning_left = false;
    kh.turning_right = false;

    // Various glut functions for gameplay.
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_key_press);
    glutKeyboardUpFunc(on_key_up);
    // glutMouseFunc(on_mouse_press);
    glutDisplayFunc(on_display);
    glutIdleFunc(on_idle);

    // Calculate the time since the last update in seconds.
    g_last_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
}

