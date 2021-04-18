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

int round_num = 0;
int temp_round_num = 0;
bool game_over = false;

int cur_time = 0;
int time_on_death = 0;

int screen_width = 0;
int screen_height = 0;
float g_last_time = 0.0;

// Instantiate various game elements.
key_handler kh_obj;
arena arena_obj;
ship ship_obj;
particle particles[MAX_PARTICLES];
asteroid asteroids[MAX_ASTEROIDS];

void on_reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0, 1.0); // range from 0 -> screen width, 0 -> screen_height

    screen_width = w;
    screen_height = h;

    // Initialise the random number generator.
    time_t t;
    srand((unsigned) time(&t));

    // Initialise the various game elements.
    init_ship(&ship_obj, screen_width, screen_height);
    init_arena(&arena_obj, screen_width, screen_height);

    for(int i = 0; i < round_num; i++)
    {
        init_asteroid(&asteroids[i], &ship_obj, screen_width, screen_height);
    }
}

void on_display()
{
    // Clear the display in time for the next frame.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    for(int j = 0; j < MAX_PARTICLES; j++)
    {
        draw_particle(&particles[j]);
    }

    // Draw the various game elements.
    draw_ship(&ship_obj);
    
    draw_arena(&arena_obj);
    for(int i = 0; i < round_num; i++)
    {
        draw_asteroid(&asteroids[i]);
    }

    string_manager();

    // Check for and print out any errors.
    int err;
    while ((err = glGetError()) != GL_NO_ERROR)
    printf("error: %s\n", gluErrorString(err));

    // Swap buffers.
    glutSwapBuffers();
}

void update_game_state(ship *ship, asteroid *asteroid, arena *arena, float dt)
{
    if(!game_over)
    {
        if(kh_obj.moving_forward)
        {
            move_ship(ship, dt);
            init_particle(particles, &ship_obj);
        }
        if(kh_obj.turning_left)
        {
            rotate_ship(ship, -1, dt);
        }
        if(kh_obj.turning_right)
        {
            rotate_ship(ship, 1, dt);
        }
        if(kh_obj.restart_game)
        {
            reset_game();
            set_restart_time();
        }

        // Check to see whether the ship is nearing any walls.
        ship_wall_warning(arena, ship);

        // Check to see whether the ship has collided with the wall.
        if(ship_wall_collision(arena, ship))
        {
            // reset_game();
            
            game_over = true;
        }

        for(int i = 0; i < round_num; i++)
        {
            // Rotate the asteroid in its given direction.
            // rotate_asteroid(&asteroid[i].rotate_dir)

            // If an asteroid collides with the ship
            if(ship_asteroid_collision(&asteroids[i], ship))
            {
                // Start the game over again.
                // reset_game();
                game_over = true;
            }
        }

        // For each asteroid in the round
        for(int i = 0; i < round_num; i++)
        {
            // Return an int representing how many asteroids are 'active' on the field.
            temp_round_num = checkActivated(&asteroids[i], screen_width, screen_height, temp_round_num);
        }

        // If the number of active asteroids is 0, meaning the wave is complete.
        if(temp_round_num == 0)
        {
            // Increment the round number.
            round_num++;
            temp_round_num = round_num;

            // TODO: Insert a way to wait x amount of seconds?

            // Create x amount of new asteroids corresponding with the round number.
            for(int i = 0; i < round_num; i++)
            {
                init_asteroid(&asteroids[i], ship, screen_width, screen_height);
            }
        }
    }
    else
    {
        ship->velocity = 0;
        for(int i = 0; i < round_num; i++)
        {
            asteroids[i].velocity = 0;
            asteroids[i].turn_val = 0;
        }
    }
}

void on_idle()
{
    cur_time = glutGet(GLUT_ELAPSED_TIME);
    float dt = cur_time - g_last_time;
    update_game_state(&ship_obj, asteroids, &arena_obj, dt);

    for(int i = 0; i < MAX_PARTICLES; i++)
    {
        move_particle(&particles[i], &ship_obj, dt);
    }

    // Move the asteroids.
    move_asteroid(asteroids, dt, round_num);

    // Rotate the asteroids around their center.
    for(int i = 0; i < round_num; i++)
    {
        rotate_asteroid(&asteroids[i], asteroids[i].turn_val, dt);
    }

    g_last_time = cur_time;
    glutPostRedisplay();
}

void on_key_press(unsigned char key, int x, int y)
{
    float dt = glutGet(GLUT_ELAPSED_TIME) - g_last_time;

    switch(toupper(key))
    {  
        // Exit the game if the user hits the escape key.
        case KEY_ESC:
            exit(EXIT_SUCCESS);
            break;
        case 'W':
        // Move the ship forward if the user hits the w key.
            kh_obj.moving_forward = true;
            glutPostRedisplay();
            break;
        case 'A':
        // Turn the ship to the left if the user hits the a key.
            kh_obj.turning_right = true;
            glutPostRedisplay();
            break;
        case 'D':
        // Turn the ship to the right if the user hits the d key.
            kh_obj.turning_left = true;
            glutPostRedisplay();
            break;
        case 'R':
        // Restart the game.
            game_over = false;
            kh_obj.restart_game = true;
            break;
    }
}

void on_key_up(unsigned char key, int x, int y)
{
    switch(toupper(key))
    {
        case 'W':
        kh_obj.moving_forward = false;
        break;
        case 'A':
        kh_obj.turning_right = false;
        break;
        case 'D':
        kh_obj.turning_left = false;
        break;
        case 'R':
        game_over = false;
        kh_obj.restart_game = false;
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
    round_num = 1;
    temp_round_num = 1;

    // Setting up the window.
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Asteroids - Assignment 1");
    glutFullScreen();

    kh_obj.moving_forward = false;
    kh_obj.turning_left = false;
    kh_obj.turning_right = false;

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

int get_time()
{
    return (glutGet(GLUT_ELAPSED_TIME) / 1000) - time_on_death;
}

void string_manager()
{
    // Get the current round number and draw it.
    char round[10] = "Round: ";
    round[6] = round_num % 10 + '0';
    glColor3f(1,1,1);
    draw_string(screen_width * 0.05, screen_height * 0.975, round, screen_width, screen_height);

    // Get the current time and draw it.
    cur_time = get_time();
    char time[10] = "Time: ";
    time[6] = cur_time / 100 + '0';
    time[7] =(cur_time % 100) / 10 + '0';
    time[8] = cur_time % 10 + '0';
    glColor3f(1,1,1);
    draw_string(screen_width * 0.9, screen_height * 0.975, time, screen_width, screen_height);

    if(game_over)
    {
        draw_string(screen_width * 0.375, screen_height * 0.975, "GAME OVER - Hold 'R' to restart.", screen_width, screen_height);
    }

}

void set_restart_time()
{
    time_on_death += get_time();
}

