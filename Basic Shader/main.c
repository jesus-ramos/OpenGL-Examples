#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif /* __APPLE__ */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char *frag_shader_src =
    "void main(void)"
    "{"
    "    gl_FragColor[0] = gl_FragCoord.x / 640.0;"
    "    gl_FragColor[1] = gl_FragCoord.y / 480.0;"
    "    gl_FragColor[2] = 0.5;"
    "}";

GLuint program;

GLint attribute_coord2d;

void init_shaders()
{
    GLuint fs;
    GLint compiled, linked;

    fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fs, 1, &frag_shader_src, NULL);

    glCompileShader(fs);

    glGetShaderiv(fs, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE)
        goto bad_shader;

    program = glCreateProgram();
    glAttachShader(program, fs);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE)
        goto bad_link;
    
    return;

bad_shader:
    printf("BAD SHADER\n");
    exit(EXIT_FAILURE);

bad_link:
    printf("COULDN'T LINK SHADERS\n");
    exit(EXIT_FAILURE);
}

void display()
{
    GLfloat verts[] =
        {
            0.0, 0.8,
            -0.8, -0.8,
            0.8, -0.8
        };
    int i;
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);

    glBegin(GL_TRIANGLES);
    for (i = 0; i < 6; i += 2)
        glVertex2f(verts[i], verts[i + 1]);
    glEnd();
    
    glFlush();
}

void init()
{
    init_shaders();
}

int main(int argc, char **argv)
{
    GLenum glew_status;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Basic Shaders Example");

    glew_status = glewInit();
    if (glew_status != GLEW_OK)
    {
        printf("FAILED TO INIT GLEW\n");
        return 1;
    }

    init();
    
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
