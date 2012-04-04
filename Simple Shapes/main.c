#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif /* __APPLE__ */

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.7f, -0.1f);
    glVertex2f(-0.1f, -0.1f);
    glVertex2f(-0.1f, 0.5f);
    glVertex2f(-0.7f, 0.5f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.2f, -0.3f);
    glVertex2f(0.8f, -0.3f);
    glVertex2f(0.5f, 0.2f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.2f, 0.3f);
    glVertex2f(0.4f, 0.3f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.4f, 0.7f);
    glVertex2f(0.2f, 0.7f);
    glVertex2f(0.1f, 0.5f);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(480, 480);
    glutCreateWindow("Simple Shapes Example");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
