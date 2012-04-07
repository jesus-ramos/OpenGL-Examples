#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif /* __APPLE__ */

#include <stdio.h>

int screen_width = 800;
int screen_height = 600;
float angle = 0;

unsigned int fps_time;
unsigned int fps_frames = 0;
float fps = 0;

void draw_string(float x, float y, void *font, char *string)
{
    char *c;

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3f(x, y, 0);
    for (c = string; *c; c++)
        glutBitmapCharacter(font, *c);
}

void display()
{
    float cube_vertices[] =
        {
            -1.0, -1.0,  1.0,
            1.0, -1.0,  1.0,
            1.0,  1.0,  1.0,
            -1.0,  1.0,  1.0,

            -1.0, -1.0, -1.0,
            1.0, -1.0, -1.0,
            1.0,  1.0, -1.0,
            -1.0,  1.0, -1.0
        };
    float cube_colors[] =
        {
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0,

            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0
        };
    int elements[] =
        {
            0, 1, 2,
            2, 3, 0,

            1, 5, 6,
            6, 2, 1,

            7, 6, 5,
            5, 4, 7,

            4, 0, 3,
            3, 7, 4,

            4, 5, 1,
            1, 0, 4,

            3, 2, 6,
            6, 7, 3
        };
    int i, j;
    char buf[16];

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0f * screen_width / screen_height, 0.1, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 2.0, 0.0,
              0.0, 0.0, -4.0,
              0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, -4.0);
    glRotatef(angle, 1.0, 1.0, 0.0);

    glBegin(GL_TRIANGLES);
    for (i = 0; i < 6; i++)
        for (j = 0; j < 6; j++)
        {
            glColor3fv(&cube_colors[elements[i * 6 + j] * 3]);
            glVertex3fv(&cube_vertices[elements[i * 6 + j] * 3]);
        }
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    snprintf(buf, 16, "FPS: %.1f", fps);
    draw_string(-0.9, -0.9, GLUT_BITMAP_HELVETICA_18, buf);
    
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    screen_width = width;
    screen_height = height;
    glViewport(0, 0, screen_width, screen_height);
}

void idle()
{
    int d_time;
    
    angle = glutGet(GLUT_ELAPSED_TIME) / 1000.0 * 45;

    fps_frames++;
    d_time = glutGet(GLUT_ELAPSED_TIME) - fps_time;
    if (d_time > 1000.0)
    {
        fps = fps_frames / (d_time / 1000.0);
        fps_time = glutGet(GLUT_ELAPSED_TIME);
        fps_frames = 0;
    }
    
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(screen_width, screen_height);
    glutCreateWindow("3D Cube");

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    fps_time = glutGet(GLUT_ELAPSED_TIME);

    glutMainLoop();

    return 0;
}
