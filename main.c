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

int main(int argc, char **argv)
{
    // Call glutInit here, so the init_game method does not need to pass in
    // any values, therefore making it easier to call upon when resetting the game.
    glutInit(&argc, argv);
    init_game();
    glutMainLoop();
    return(EXIT_SUCCESS);
}


