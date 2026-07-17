// Shafin Ahmed 232-15-184 65-M1

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>


void abc(float x1, float y_1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y_1;
    float steps;

    //max
    if (fabs(dx) > fabs(dy))
    {
        steps = fabs(dx);
    }
    else
    {
        steps = fabs(dy);
    }

    //inc
    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    // Start pos
    float x = x1;
    float y = y_1;

    //start point
    glVertex2f(x, y);

    // Loop
    for (int i = 0; i < steps; i++)
    {
        x += xIncrement;
        y += yIncrement;
        glVertex2f(x, y);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);

    glBegin(GL_POINTS);

    // ghor
    abc(15, 15, 75, 15); // niche
    abc(75, 15, 75, 50); // Dan
    abc(15, 50, 75, 50); // upor
    abc(15, 15, 15, 50); // bam

    //chal
    abc(15, 50, 45, 85); // bam
    abc(75, 50, 45, 85); // dan

    glEnd();
    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glLoadIdentity();
    glOrtho(0, 100, 0, 100, -1, 1);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Home Drawing by Shafin Ahmed (232-15-184 65-M1");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}