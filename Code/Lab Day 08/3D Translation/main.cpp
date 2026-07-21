#include <GL/glut.h>
#include <iostream>
using namespace std;
 
float X1, Y1, Z1;
float X2, Y2, Z2;
 
float Tx, Ty, Tz;
 
float moveX = 0, moveY = 0, moveZ = 0;
 
void drawCubeFromPoints(float x1, float y1, float z1, float x2, float y2, float z2)
{
	glBegin(GL_QUADS);
 
	// Front face
	glColor3f(1, 0, 0);
	glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);
 
	// Back face
	glColor3f(0, 1, 0);
	glVertex3f(x1, y1, z2);
	glVertex3f(x1, y2, z2);
    glVertex3f(x2, y2, z2);
	glVertex3f(x2, y1, z2);
 
	// Left face
	glColor3f(0, 0, 1);
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y1, z2);
	glVertex3f(x1, y2, z2);
	glVertex3f(x1, y2, z1);
 
	// Right face
	glColor3f(1, 1, 0);
	glVertex3f(x2, y1, z1);
	glVertex3f(x2, y1, z2);
    glVertex3f(x2, y2, z2);
	glVertex3f(x2, y2, z1);
 
	// Top face
	glColor3f(0, 1, 1);
	glVertex3f(x1, y2, z1);
	glVertex3f(x1, y2, z2);
	glVertex3f(x2, y2, z2);
	glVertex3f(x2, y2, z1);
 
	// Bottom face
	glColor3f(1, 0, 1);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
	glVertex3f(x1, y1, z2);
 
	glEnd();
}
 
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(15, 15, 25, 0, 0, 0, 0, 1, 0);
	glTranslatef(moveX, moveY, moveZ);
	drawCubeFromPoints(X1, Y1, Z1, X2, Y2, Z2);
	glutSwapBuffers();
}
 
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
    	case 'X': moveX += Tx; break;   // move +X
    	case 'x': moveX -= Tx; break;   // move -X
 
    	case 'Y': moveY += Ty; break;   // move +Y
    	case 'y': moveY -= Ty; break;   // move -Y
 
    	case 'Z': moveZ += Tz; break;   // move +Z
    	case 'z': moveZ -= Tz; break;   // move -Z
	}
 
	glutPostRedisplay();
}
 
 
void init()
{
	glEnable(GL_DEPTH_TEST);
 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 1.0, 100.0);
 
	glMatrixMode(GL_MODELVIEW);
}
 
int main(int argc, char** argv)
{
	cout << "Enter first point (x1 y1 z1): ";
	cin >> X1 >> Y1 >> Z1;
 
	cout << "Enter second point (x2 y2 z2): ";
	cin >> X2 >> Y2 >> Z2;
 
	cout << "Enter translation unit (Tx Ty Tz): ";
	cin >> Tx >> Ty >> Tz;
 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("3D Translation");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
