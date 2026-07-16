//Shafin Ahmed 232-15-184 65-M1
//Translation

#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
float tx=0.00;
float ty=0.00;
void init(void)
{
  glClearColor(0.0,0.0,0.0,0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
}
void Draw()
{
 glClear(GL_COLOR_BUFFER_BIT);
   glPushMatrix();
   glTranslatef(tx,ty,0);

   glColor3f(1,0,0);
   glRectf(-75,-75,75,75);

   glColor3f(1,1,0);
   glRectf(-50,-50,50,50);

   glColor3f(0,0,1);
   glRectf(-25,-25,25,25);

   glPopMatrix();
glutSwapBuffers();
}
void spe_key(int key, int x, int y){
    switch(key){
        case GLUT_KEY_UP:
        ty=ty+5;
        glutPostRedisplay();
        break;
        case GLUT_KEY_DOWN:
        ty=ty-5;
        glutPostRedisplay();
        break;
        case GLUT_KEY_RIGHT:
        tx=tx+5;
        glutPostRedisplay();
        break;
        case GLUT_KEY_LEFT:
        tx=tx-5;
        glutPostRedisplay();
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
    glutSpecialFunc(spe_key);
    glutMainLoop();
    return 0;
}
