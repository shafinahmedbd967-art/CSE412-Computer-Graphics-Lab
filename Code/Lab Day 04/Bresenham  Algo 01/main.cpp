// Shafin Ahmed 232-15-184  65-M1
// FOR 0 < m <= 1
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float x0, y0, x1, y1;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 1.0, 0.0);

    glBegin(GL_POINTS);

    int dx = abs((int)x1 - (int)x0);
    int dy = abs((int)y1 - (int)y0);

    int xc;
    if (x1 > x0)
    {
        xc = 1;
    }
    else
    {
        xc = -1;
    }

    int yc;
    if (y1 > y0)
    {
        yc = 1;
    }
    else
    {
        yc = -1;
    }

    int x = (int)x0;
    int y = (int)y0;

    glVertex2i(x, y);

    if (dx > dy)
    {
        int p = 2 * dy - dx;

        while (x != (int)x1)
        {
            x += xc;

            if (p < 0)
            {
                p = p + 2 * dy;
            }
            else
            {
                y += yc;
                p = p + 2 * dy - 2 * dx;
            }
            glVertex2i(x, y);
        }
    }
    else
    {
        int p = 2 * dx - dy;

        while (y != (int)y1)
        {
            y += yc;

            if (p < 0)
            {
                p = p + 2 * dx;
            }
            else
            {
                x += xc;
                p = p + 2 * dx - 2 * dy;
            }
            glVertex2i(x, y);
        }
    }

    glEnd();

    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, 100, 0, 100, -1, 1);
}

int main(int argc, char** argv)
{
    printf("Enter First Point (x0 y0): ");
    scanf("%f %f", &x0, &y0);

    printf("Enter Second Point (x1 y1): ");
    scanf("%f %f", &x1, &y1);

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(600, 600);

    glutInitWindowPosition(100, 100);

    glutCreateWindow("Bresenham Line Drawing");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}