#include <GL/glut.h>
#include <math.h>

// Screen Dimensions according to Blueprint
const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

// Global Animation State Variables
float cloudX = 0.0f;
float planeX = -200.0f;
float busX = -300.0f;
float carX = 1700.0f;
bool isNight = false;
bool isGateOpen = false;

// Function Prototypes according to Blueprint Layers
void drawSkyLayer();
void drawBuildingAndFloraLayer();
void drawCampusAndPlaygroundLayer();
void drawBoundaryAndGateLayer();
void drawFootpathLayer();
void drawRoadLayer();

// Core Render Function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Rendering in strict Bottom-to-Top Z-Order
    drawSkyLayer();
    drawBuildingAndFloraLayer();
    drawCampusAndPlaygroundLayer();
    drawBoundaryAndGateLayer();
    drawFootpathLayer();
    drawRoadLayer();

    glutSwapBuffers();
}

// Empty Function Stubs (We will write code inside these step-by-step)
void drawSkyLayer() {
    // Sun, Clouds, Birds, Airplane will go here
}

void drawBuildingAndFloraLayer() {
    // School Building, Shaheed Minar, Back Trees will go here
}

void drawCampusAndPlaygroundLayer() {
    // Assembly lines, Playground rides, Front Gardens will go here
}

void drawBoundaryAndGateLayer() {
    // Campus Wall, Main Gate, Notice Board will go here
}

void drawFootpathLayer() {
    // Footpath, Benches, Dustbins, Pedestrians will go here
}

void drawRoadLayer() {
    // Asphalt Road, Vehicles, Speedbreakers will go here
}

// Timer for smooth animations
void update(int value) {
    // Animation Logic
    cloudX += 0.5f;
    if (cloudX > SCREEN_WIDTH + 100) cloudX = -200.0f;

    planeX += 2.0f;
    if (planeX > SCREEN_WIDTH + 200) planeX = -200.0f;

    busX += 3.0f;
    if (busX > SCREEN_WIDTH + 300) busX = -300.0f;

    carX -= 4.0f;
    if (carX < -200.0f) carX = SCREEN_WIDTH + 200.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 1600x900 Coordinate System (Top: 0, Bottom: 900)
    gluOrtho2D(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Modern Government Primary School - Master Canvas");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}