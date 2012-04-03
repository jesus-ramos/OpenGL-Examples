#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif /* __APPLE__ */

#include <stdio.h>

#include "shader_utils.h"

#define VERT_SHADER_FILE "shader.vert"
#define FRAG_SHADER_FILE "alphashader.frag"

GLuint program;

int init()
{
    GLuint fs, vs;
    
    program = glCreateProgram();

    if (!(vs = create_shader(VERT_SHADER_FILE, GL_VERTEX_SHADER)))
        return 0;
    if (!(fs = create_shader(FRAG_SHADER_FILE, GL_FRAGMENT_SHADER)))
        return 0;

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    if (!link_shaders(program))
        return 0;

    return 1;
}

void display()
{
    
}

int main(int argc, char **argv)
{
    GLenum glew_status;

    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Alpha Blending Example");

    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glew_status = glewInit();
    if (glew_status != GLEW_OK)
    {
        printf("Failed to initalize GLEW extensions\n");
        return 1;
    }

    if (!init())
        return 1;

    glutDisplayFunc(display);

    glutMainLoop();
        
    return 0;
}
