//Shafin Ahmed 232-15-184 65-M1
//Shear
#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
// Original triangle coordinates
float x1 = 50, y1 = 50;
float x2 = 150, y2 = 50;
float x3 = 100, y3 = 150;

// Shear factors
float shx = 0, shy = 0;
int choice;

// Sheared coordinates
float nx1, ny1, nx2, ny2, nx3, ny3;
void init(void)
{
  glClearColor(0.0,0.0,0.0,0.0); //GLfloat red,green,blue,alpha initial value 0 alpha values used by glclear to clear the color buffers
  glMatrixMode(GL_PROJECTION);  // To specify which matrix is the current matrix & projection applies subsequent matrix to projecton matrix stack
  glLoadIdentity();
  glOrtho(0.0, 400.0, 0.0, 400.0, -1.0, 1.0);
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

    // Draw Sheared Triangle (Red)
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(nx1, ny1);
        glVertex2f(nx2, ny2);
        glVertex2f(nx3, ny3);
    glEnd();

    glutSwapBuffers();

}

int main(int argc,char **argv){
    printf("Choose Reflection Type:\n");
    printf("Choose Shearing Type:\n");
    printf("1. Shearing along X-axis (Horizontal Shear)\n");
    printf("2. Shearing along Y-axis (Vertical Shear)\n");
    printf("Enter your choice (1 or 2): ");
   scanf("%d", &choice);

    if(choice == 1)
    {
        printf("Enter shear factor along X-axis (shx): ");
        scanf("%f", &shx);

        // Horizontal Shear Formula
        nx1 = x1 + shx * y1;
        ny1 = y1;

        nx2 = x2 + shx * y2;
        ny2 = y2;

        nx3 = x3 + shx * y3;
        ny3 = y3;
    }
    else if(choice == 2)
    {
        printf("Enter shear factor along Y-axis (shy): ");
        scanf("%f", &shy);

        // Vertical Shear Formula
        nx1 = x1;
        ny1 = y1 + shy * x1;

        nx2 = x2;
        ny2 = y2 + shy * x2;

        nx3 = x3;
        ny3 = y3 + shy * x3;
    }
    else
    {
        printf("Invalid choice! Program will exit.");
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
