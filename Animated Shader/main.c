#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif /* __APPLE__ */

#include <math.h>
#include <stdio.h>

#include "shader_utils.h"

#define VERT_SHADER_FILE "shader.vert"
#define FRAG_SHADER_FILE "shader.frag"

struct attributes
{
    GLfloat coord2d[2];
    GLfloat vert_color[3];
};

GLuint program;
GLint uniform_fade;
GLuint vbo;
GLint attribute_coord2d, attribute_vert_color;

void bind_vbo_buffers()
{
    struct attributes triangle[] =
        {
            {{0.0, 0.8}, {1.0, 1.0, 0.0}},
            {{-0.8, -0.8}, {0.0, 1.0, 1.0}},
            {{0.8, -0.8}, {1.0, 0.0, 0.0}}
        };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE,
                          sizeof(struct attributes), (GLvoid *)offsetof(struct attributes, coord2d));
    glVertexAttribPointer(attribute_vert_color, 2, GL_FLOAT, GL_FALSE,
                          sizeof(struct attributes), (GLvoid *)offsetof(struct attributes, vert_color));
}

int bind_uniform(const char *name, GLint *uniform)
{
    *uniform = glGetUniformLocation(program, name);
    if (*uniform == -1)
    {
        printf("Could not bind uniform %s\n", name);
        return 0;
    }

    return 1;
}

int bind_attribute(const char *name, GLint *attrib)
{
    *attrib = glGetAttribLocation(program, name);
    if (*attrib == -1)
    {
        printf("Could not bind attribute %s\n", name);
        return 0;
    }

    return 1;
}

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

    if (!bind_uniform("fade", &uniform_fade))
        return 0;
    if (!bind_attribute("coord2d", &attribute_coord2d))
        return 0;
    if (!bind_attribute("vert_color", &attribute_vert_color))
        return 0;

    bind_vbo_buffers();

    return 1;
}

void display()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);
    glEnableVertexAttribArray(attribute_coord2d);
    glEnableVertexAttribArray(attribute_vert_color);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE,
                          sizeof(struct attributes), 0);
    glVertexAttribPointer(attribute_vert_color, 3, GL_FLOAT, GL_FALSE,
                          sizeof(struct attributes),
                          (GLvoid *)offsetof(struct attributes, vert_color));
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(attribute_coord2d);
    glDisableVertexAttribArray(attribute_vert_color);

    glFlush();
}

void idle()
{
    float cur_fade;

    cur_fade = sinf(glutGet(GLUT_ELAPSED_TIME) / 1000.0 * 2 * M_PI / 5) / 2 + 0.5;

    glUseProgram(program);
    glUniform1f(uniform_fade, cur_fade);
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    GLenum glew_status;

    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Shader Animation Example");
    
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glew_status = glewInit();
    if (glew_status != GLEW_OK)
    {
        printf("Failed to initialize GLEW extensions\n");
        return 1;
    }

    if (!init())
        return 1;

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}
