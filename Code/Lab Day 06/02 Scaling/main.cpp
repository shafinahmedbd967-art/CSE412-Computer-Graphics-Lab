//Shafin Ahmed 232-15-184 65-M1
//Scaling
#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
// Original coordinates
float x1 = 50, y1 = 50;
float x2 = 150, y2 = 50;
float x3 = 100, y3 = 150;

// Scaling factors
float sx, sy;

// Scaled coordinates
float sx1, sy1, sx2, sy2, sx3, sy3;

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

    // Draw Scaled Triangle (Red)
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(sx1, sy1);
        glVertex2f(sx2, sy2);
        glVertex2f(sx3, sy3);
    glEnd();

    glutSwapBuffers();

}

int main(int argc,char **argv){
    printf("Enter scaling factor along X-axis (sx): ");
    scanf("%f", &sx);
    printf("Enter scaling factor along Y-axis (sy): ");
    scanf("%f", &sy);

    // Apply Scaling Transformation
    sx1 = sx * x1;
    sy1 = sy * y1;
    sx2 = sx * x2;
    sy2 = sy * y2;
    sx3 = sx * x3;
    sy3 = sy * y3;

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

