#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define CALC_POINT(dimension, verts, old_dim) ((old_dim.dimension + verts[v].dimension) / 2)

struct point3d
{
    float x, y, z;
};

struct point2d
{
    float x, y;
};

struct point2d vertices2d[3] =
{
    { 0, 0 },
    { 500, 0 },
    { 250, 1000.0 / 3.0 }
};

struct point3d vertices3d[4] =
{
    { 0, 0, 0 },
    { 250, 500, 250 },
    { 500, 250, 250 },
    { 250, 100, 250 }
};

int v;
struct point3d new3d, old3d;
struct point2d new2d, old2d;

void clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void display2d(void)
{
    v = rand() % 3;

    new2d.x = CALC_POINT(x, vertices2d, old2d);
    new2d.y = CALC_POINT(y, vertices2d, old2d);

    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(new2d.x, new2d.y);
    glEnd();

    old2d = new2d;

    glFlush();
}

void display3d(void)
{
    v = rand() % 4;

    new3d.x = CALC_POINT(x, vertices3d, old3d);
    new3d.y = CALC_POINT(y, vertices3d, old3d);
    new3d.z = CALC_POINT(z, vertices3d, old3d);

    glBegin(GL_POINTS);
    glColor3f(1.0 - new3d.z / 250.0, new3d.z / 250.0, 0.0);
    glVertex3f(new3d.x, new3d.y, new3d.z);
    glEnd();

    old3d = new3d;

    glFlush();
}

int main(int argc, char **argv)
{
    void *disp = (argc > 1) ? display2d : display3d;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Sierpinski Triangle/Gasket Test OpenGL");

    glutIdleFunc(disp);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 500.0, 0.0, 500.0, -500.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(clear);

    glutMainLoop();

    return 0;
}
