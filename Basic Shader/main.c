#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif /* __APPLE__ */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char *vert_shader_src =
    "attribute vec2 coord2d;"
    "void main(void)"
    "{"
    "    gl_Position = vec4(coord2d, 0.0, 1.0);"
    "}";

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
    GLuint fs, vs;
    GLint compiled, linked;

    fs = glCreateShader(GL_FRAGMENT_SHADER);
    vs = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(fs, 1, &frag_shader_src, NULL);
    glShaderSource(vs, 1, &vert_shader_src, NULL);

    glCompileShader(vs);
    glCompileShader(fs);

    glGetShaderiv(fs, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE)
        goto bad_shader;

    glGetShaderiv(vs, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE)
        goto bad_shader;

    program = glCreateProgram();
    glAttachShader(program, vs);
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
    
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);

    glEnableVertexAttribArray(attribute_coord2d);
    glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, verts);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(attribute_coord2d);

    glutSwapBuffers();
}

void init()
{
    const char *attribute_name = "coord2d";

    init_shaders();

    attribute_coord2d = glGetAttribLocation(program, attribute_name);
    if (attribute_coord2d == -1)
    {
        printf("COULND'T GET ATTRIBUTE_COORD2D\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    GLenum glew_status;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
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
