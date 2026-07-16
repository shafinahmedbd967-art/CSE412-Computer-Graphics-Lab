//Shafin Ahmed 232-15-184 65-M1
//Rotation
#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
GLfloat spin=0.00;
void init(void)
{
  glClearColor(0.0,0.0,0.0,0.0); //GLfloat red,green,blue,alpha initial value 0 alpha values used by glclear to clear the color buffers
  glMatrixMode(GL_PROJECTION);  // To specify which matrix is the current matrix & projection applies subsequent matrix to projecton matrix stack
  glLoadIdentity();
  glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
  //gluOrtho2D(0.0,300.0,0.0,300.0); // Orthographic representation; multiply the current matrix by an orthographic matrix 2D= left right,bottom,top equivalent near=-1,far=1
}
void Draw()
{
 glClear(GL_COLOR_BUFFER_BIT);

   glPushMatrix();
   glColor3f( 1 ,0, 0);
   glRotatef(spin, 0.0, 0.0, 1.0);
   glRectf(-75,-75,75,75);
   glPopMatrix();

   glPushMatrix();
   glColor3f( 0 ,1, 0);
   glRotatef(spin, 0.0, 0.0, 1.0);
   glRectf(-45,-45,45,45);
   glPopMatrix();

   glPushMatrix();
   glColor3f( 0 ,0, 1);
   glRotatef(spin, 0.0, 0.0, 1.0);
   glBegin(GL_POLYGON);
   glVertex2f(0.00,20.00);
   glVertex2f(-19.02,6.18);
   glVertex2f(-11.76,-16.18);
   glVertex2f(11.76,-16.18);
   glVertex2f(19.02,6.18);
   glEnd();
   glPopMatrix();

glutSwapBuffers();
}
void spinDisplay_left(void)
{
   spin = spin + 10;
   glutPostRedisplay();
}
void spinDisplay_right(void)
{
   spin = spin - 10;
   glutPostRedisplay();
}
void my_keyboard(unsigned char key,int x, int y)
{
	switch (key) {
		case 'l':
			spinDisplay_left();
			break;
		case 'r':
			spinDisplay_right();
			break;
		case 's':
			 glutIdleFunc(NULL);
			 break;
	  default:
			break;
	}
}
int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("Lab Final");
    init();
    glutDisplayFunc(Draw);
    glutKeyboardFunc(my_keyboard);
    glutMainLoop();
    return 0;
}




