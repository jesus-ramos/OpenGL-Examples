#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void sierpinski2d(float vert1[], float vert2[], float vert3[], int depth)
{
    float next_vert1[3];
    float next_vert2[3];
    float next_vert3[3];

    if (depth >= 10)
        return;

    glBegin(GL_LINES);
    glVertex3fv(vert1);
    glVertex3fv(vert2);
    glVertex3fv(vert3);
    glEnd();

    next_vert1[0] = (vert1[0] + vert2[0]) / 2;
    next_vert1[1] = (vert1[1] + vert2[1]) / 2;
    next_vert1[2] = (vert1[2] + vert2[2]) / 2;

    next_vert2[0] = (vert1[0] + vert3[0]) / 2;
    next_vert2[1] = (vert1[1] + vert3[1]) / 2;
    next_vert2[2] = (vert1[2] + vert3[2]) / 2;
    
    next_vert3[0] = (vert2[0] + vert3[0]) / 2;
    next_vert3[1] = (vert2[1] + vert3[1]) / 2;
    next_vert3[2] = (vert2[2] + vert3[2]) / 2;

    sierpinski2d(next_vert1, vert1, next_vert2, depth + 1);
    sierpinski2d(next_vert1, vert2, next_vert3, depth + 1);
    sierpinski2d(next_vert3, vert3, next_vert2, depth + 1);
}

void display(void)
{
    float vert1[3] = { 5.0, 0.0, 0.0 };
    float vert2[3] = { -5.0, 0.0, 0.0 };
    float vert3[3] = { 0.0, 5.0, 0.0 };

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5.0, 5.0, 0.0, 5.0);
    glMatrixMode(GL_MODELVIEW);

    sierpinski2d(vert1, vert2, vert3, 0);

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Sierpinski Triangle Recursive 2D");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
