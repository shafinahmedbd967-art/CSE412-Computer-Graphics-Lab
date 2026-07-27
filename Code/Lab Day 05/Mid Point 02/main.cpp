// Mid Point Circle Drawing Algorithm 
// Shafin Ahmed 232-15-184 65-M1
// For Center (xc,yc)

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

int r;
int xc, yc;

void init()
{
    glClearColor(0,0,0,0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-100,100,-100,100,-1,1);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 255, 255);

    glBegin(GL_POINTS);

    int x = 0;
    int y = r;
    int p = 1 - r;
    while (x <= y)
    {
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc - y, yc - x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc - x, yc + y);

        if (p < 0)
        {
            x = x + 1;
            p = p + 2 * x + 1;
        }
        else
        {
            x = x + 1;
            y = y - 1;
            p = p + 2 * x + 1 - 2 * y;
        }
    }

    glEnd();

    glFlush();
}

int main(int argc,char** argv)
{
    printf("Enter Radius : ");
    scanf("%d",&r);
    printf("Enter Center (X Axis) : ");
    scanf("%d",&xc);
    printf("Enter Center (Y Axis) : ");
    scanf("%d",&yc);

    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowSize(600,600);

    glutCreateWindow("Midpoint Circle by Shafin Ahmed 232-15-184 65-M1");

    init();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}