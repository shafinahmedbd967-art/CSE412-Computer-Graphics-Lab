//Shafin Ahmed 232-15-184 65-M1
//Reflection
#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
// Original triangle coordinates
float x1 = 50, y1 = 50;
float x2 = 150, y2 = 50;
float x3 = 100, y3 = 150;

// Reflected coordinates
float rx1, ry1, rx2, ry2, rx3, ry3;

int choice;

void init(void)
{
  glClearColor(0.0,0.0,0.0,0.0); //GLfloat red,green,blue,alpha initial value 0 alpha values used by glclear to clear the color buffers
  glMatrixMode(GL_PROJECTION);  // To specify which matrix is the current matrix & projection applies subsequent matrix to projecton matrix stack
  glLoadIdentity();
  glOrtho(-400.0, 400.0, -400.0, 400.0, -1.0, 1.0);
  //gluOrtho2D(0.0,300.0,0.0,300.0); // Orthographic representation; multiply the current matrix by an orthographic matrix 2D= left right,bottom,top equivalent near=-1,far=1
}


void Draw()
{
glClear(GL_COLOR_BUFFER_BIT);

    // Draw Original Triangle (Blue)
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    glEnd();

    // Draw Reflected Triangle (Red)
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(rx1, ry1);
        glVertex2f(rx2, ry2);
        glVertex2f(rx3, ry3);
    glEnd();

    glutSwapBuffers();

}

int main(int argc,char **argv){
    printf("Choose Reflection Type:\n");
    printf("1. Reflection about X-axis\n");
    printf("2. Reflection about Y-axis\n");
    printf("3. Reflection about Diagonal (Origin)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if(choice == 1)
    {
        // Reflection about X-axis (x, y) -> (x, -y)
        rx1 = x1; ry1 = -y1;
        rx2 = x2; ry2 = -y2;
        rx3 = x3; ry3 = -y3;
    }
    else if(choice == 2)
    {
        // Reflection about Y-axis (x, y) -> (-x, y)
        rx1 = -x1; ry1 = y1;
        rx2 = -x2; ry2 = y2;
        rx3 = -x3; ry3 = y3;
    }
    else if(choice == 3)
    {
        // Reflection about diagonal / origin (x, y) -> (-x, -y)
        rx1 = -x1; ry1 = -y1;
        rx2 = -x2; ry2 = -y2;
        rx3 = -x3; ry3 = -y3;
    }
    else
    {
         printf("Invalid choice!");
         return 0;
    }
    glutInit(&argc,argv);
    glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("Lab Final");
    init();
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}
