/* ==========================================================
   PHASE 1 - PROJECT FOUNDATION
   Modern Government Primary School in Bangladesh
   Canvas: 1600 x 900
   Coordinate System: Matches Approved Master Blueprint
   Origin (0,0) = TOP-LEFT corner
   X increases to the RIGHT
   Y increases DOWNWARD
   (Achieved via gluOrtho2D(0, 1600, 900, 0))

   This file contains ONLY:
   - GLUT/OpenGL initialization
   - Window + projection setup
   - Global variables / color constants / animation variables
   - Timer, Keyboard, Display, Reshape, init(), main()
   - EMPTY prototypes for every drawing function required by the blueprint

   NO objects are drawn in this phase.
   ========================================================== */

#include <GL/glut.h>

/* ==========================================================
   WINDOW CONSTANTS
   ========================================================== */
const int WINDOW_WIDTH  = 1600;
const int WINDOW_HEIGHT = 900;
const char* WINDOW_TITLE = "Modern Government Primary School in Bangladesh";

/* ==========================================================
   COLOR CONSTANTS
   (Values to be filled in during drawing phases.
    Declared here so all future functions share one palette.)
   ========================================================== */
GLfloat COLOR_SKY_BLUE[3]        = {0.53f, 0.81f, 0.92f};
GLfloat COLOR_SUN_YELLOW[3]      = {1.00f, 0.85f, 0.10f};
GLfloat COLOR_CLOUD_WHITE[3]     = {1.00f, 1.00f, 1.00f};
GLfloat COLOR_GRASS_GREEN[3]     = {0.30f, 0.65f, 0.25f};
GLfloat COLOR_GROUND_DARK[3]     = {0.20f, 0.45f, 0.20f};
GLfloat COLOR_BUILDING_CREAM[3]  = {0.94f, 0.87f, 0.70f};
GLfloat COLOR_BUILDING_RED[3]    = {0.70f, 0.20f, 0.20f};
GLfloat COLOR_ROOF_GRAY[3]       = {0.55f, 0.55f, 0.55f};
GLfloat COLOR_WINDOW_BLUE[3]     = {0.40f, 0.70f, 0.90f};
GLfloat COLOR_DOOR_BROWN[3]      = {0.40f, 0.25f, 0.10f};
GLfloat COLOR_FLAG_GREEN[3]      = {0.00f, 0.40f, 0.20f};
GLfloat COLOR_FLAG_RED[3]        = {0.85f, 0.10f, 0.10f};
GLfloat COLOR_POLE_GRAY[3]       = {0.60f, 0.60f, 0.60f};
GLfloat COLOR_TREE_TRUNK[3]      = {0.36f, 0.20f, 0.09f};
GLfloat COLOR_TREE_LEAVES[3]     = {0.13f, 0.55f, 0.13f};
GLfloat COLOR_FLOWER_PINK[3]     = {0.95f, 0.40f, 0.60f};
GLfloat COLOR_FLOWER_YELLOW[3]   = {1.00f, 0.90f, 0.20f};
GLfloat COLOR_ROAD_ASPHALT[3]    = {0.25f, 0.25f, 0.25f};
GLfloat COLOR_ROAD_DIVIDER[3]    = {1.00f, 1.00f, 1.00f};
GLfloat COLOR_FOOTPATH_GRAY[3]   = {0.75f, 0.72f, 0.68f};
GLfloat COLOR_WALL_GRAY[3]       = {0.65f, 0.60f, 0.55f};
GLfloat COLOR_GATE_BLACK[3]      = {0.15f, 0.15f, 0.15f};
GLfloat COLOR_BUS_YELLOW[3]      = {1.00f, 0.80f, 0.00f};
GLfloat COLOR_RICKSHAW_TEAL[3]   = {0.10f, 0.50f, 0.50f};
GLfloat COLOR_CAR_BLUE[3]        = {0.15f, 0.30f, 0.70f};
GLfloat COLOR_SKIN_TONE[3]       = {0.87f, 0.68f, 0.53f};
GLfloat COLOR_UNIFORM_WHITE[3]   = {1.00f, 1.00f, 1.00f};
GLfloat COLOR_UNIFORM_BLUE[3]    = {0.10f, 0.20f, 0.55f};
GLfloat COLOR_BLACK[3]           = {0.00f, 0.00f, 0.00f};
GLfloat COLOR_WHITE[3]           = {1.00f, 1.00f, 1.00f};

/* ==========================================================
   GLOBAL VARIABLES
   ========================================================== */
int windowWidth  = WINDOW_WIDTH;
int windowHeight = WINDOW_HEIGHT;

/* ==========================================================
   ANIMATION VARIABLES
   (Values to be used once animated objects are implemented)
   ========================================================== */
float flagWaveOffset      = 0.0f;   // Bangladesh Flag waving
float cloud1OffsetX       = 0.0f;   // Cloud 1 drift
float cloud2OffsetX       = 0.0f;   // Cloud 2 drift
float cloud3OffsetX       = 0.0f;   // Cloud 3 drift
float birdOffsetX         = 0.0f;   // Bird flock glide
float butterflyOffsetX    = 0.0f;   // Butterfly flutter
float butterflyOffsetY    = 0.0f;   // Butterfly flutter
float airplaneOffsetX     = 0.0f;   // Airplane traverse
float clockHandAngle      = 0.0f;   // Wall clock hands
float busPositionX        = 0.0f;   // School bus movement along road
float swingAngle          = 0.0f;   // Swing pendulum motion
float seesawAngle         = 0.0f;   // Seesaw tilt motion
float slideChildOffsetY   = 0.0f;   // Child sliding motion

bool isAnimating = true;            // Master animation toggle

/* ==========================================================
   FUNCTION PROTOTYPES - CORE
   ========================================================== */
void init();
void display();
void reshape(int w, int h);
void timer(int value);
void keyboard(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);

/* ==========================================================
   FUNCTION PROTOTYPES - SKY LAYER
   ========================================================== */
void drawSky();
void drawSun();
void drawCloud();
void drawBird();
void drawButterfly();
void drawAirplane();

/* ==========================================================
   FUNCTION PROTOTYPES - SCHOOL BUILDING LAYER
   ========================================================== */
void drawSchool();
void drawRoof();
void drawWindow();
void drawDoor();
void drawClock();
void drawFlagPole();
void drawBangladeshFlag();
void drawRoofBanner();

/* ==========================================================
   FUNCTION PROTOTYPES - CAMPUS / GARDEN LAYER
   ========================================================== */
void drawShaheedMinar();
void drawGarden();
void drawFlower();
void drawBush();
void drawTree();
void drawPalmTree();
void drawMangoTree();
void drawBananaTree();
void drawDecorativeTree();
void drawAssemblyGround();

/* ==========================================================
   FUNCTION PROTOTYPES - PLAYGROUND
   ========================================================== */
void drawPlayground();
void drawFootballField();
void drawGoalPost();
void drawBasketballHoop();
void drawCricketPitch();
void drawSwing();
void drawSlide();
void drawSeesaw();
void drawMonkeyBars();

/* ==========================================================
   FUNCTION PROTOTYPES - BOUNDARY & GATE LAYER
   ========================================================== */
void drawBoundaryWall();
void drawGate();
void drawNoticeBoard();
void drawLampPost();
void drawBench();
void drawWaterStation();
void drawCycleParking();
void drawDustbin();

/* ==========================================================
   FUNCTION PROTOTYPES - FOOTPATH LAYER
   ========================================================== */
void drawFootpath();

/* ==========================================================
   FUNCTION PROTOTYPES - ROAD LAYER
   ========================================================== */
void drawRoad();
void drawRoadDivider();
void drawZebraCrossing();
void drawSpeedBreaker();
void drawTrafficSign();

/* ==========================================================
   FUNCTION PROTOTYPES - PEOPLE
   ========================================================== */
void drawStudent();
void drawTeacher();
void drawParent();
void drawSecurityGuard();
void drawGardener();
void drawAssemblyStudents();
void drawWalkingStudents();

/* ==========================================================
   FUNCTION PROTOTYPES - VEHICLES
   ========================================================== */
void drawBus();
void drawRickshaw();
void drawBicycle();
void drawMotorbike();
void drawCar();

/* ==========================================================
   INIT FUNCTION
   ========================================================== */
void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /* Coordinate system exactly matching the approved blueprint:
       (0,0) at TOP-LEFT, X right, Y downward */
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/* ==========================================================
   DISPLAY FUNCTION
   Calls drawing functions in blueprint layer order:
   Sky -> Building -> Campus/Garden -> Boundary & Gate ->
   Footpath -> Road -> People -> Vehicles
   (All functions are currently EMPTY - no visuals yet)
   ========================================================== */
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    /* ---- Sky Layer ---- */
    drawSky();
    drawSun();
    drawCloud();
    drawBird();
    drawAirplane();

    /* ---- School Building Layer ---- */
    drawSchool();
    drawRoof();
    drawRoofBanner();
    drawWindow();
    drawDoor();
    drawClock();
    drawFlagPole();
    drawBangladeshFlag();

    /* ---- Campus / Garden Layer ---- */
    drawShaheedMinar();
    drawGarden();
    drawFlower();
    drawBush();
    drawTree();
    drawPalmTree();
    drawMangoTree();
    drawBananaTree();
    drawDecorativeTree();
    drawAssemblyGround();

    /* ---- Playground ---- */
    drawPlayground();
    drawFootballField();
    drawGoalPost();
    drawBasketballHoop();
    drawCricketPitch();
    drawSwing();
    drawSlide();
    drawSeesaw();
    drawMonkeyBars();

    /* ---- Boundary & Gate Layer ---- */
    drawBoundaryWall();
    drawGate();
    drawNoticeBoard();
    drawLampPost();
    drawBench();
    drawWaterStation();
    drawCycleParking();
    drawDustbin();

    /* ---- Footpath Layer ---- */
    drawFootpath();

    /* ---- Road Layer ---- */
    drawRoad();
    drawRoadDivider();
    drawZebraCrossing();
    drawSpeedBreaker();
    drawTrafficSign();

    /* ---- People (Campus + Footpath) ---- */
    drawAssemblyStudents();
    drawTeacher();
    drawSecurityGuard();
    drawGardener();
    drawWalkingStudents();
    drawParent();
    drawStudent();

    /* ---- Vehicles (Road Layer) ---- */
    drawBus();
    drawRickshaw();
    drawBicycle();
    drawMotorbike();
    drawCar();

    /* ---- Foreground fauna ---- */
    drawButterfly();

    glutSwapBuffers();
}

/* ==========================================================
   RESHAPE FUNCTION
   ========================================================== */
void reshape(int w, int h)
{
    if (h == 0) h = 1;

    windowWidth  = w;
    windowHeight = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /* Maintain blueprint coordinate system regardless of window resize */
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* ==========================================================
   TIMER FUNCTION
   (Drives future animations: flag, clouds, birds, bus, swing,
   seesaw, slide, clock, butterfly, airplane)
   ========================================================== */
void timer(int value)
{
    if (isAnimating)
    {
        /* Animation variable updates will be implemented
           in later phases once objects exist. */
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // ~60 FPS
}

/* ==========================================================
   KEYBOARD FUNCTION
   ========================================================== */
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27: // ESC key
            exit(0);
            break;
        case ' ': // Spacebar toggles animation
            isAnimating = !isAnimating;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

/* ==========================================================
   SPECIAL KEYS FUNCTION (arrow keys, reserved for future use)
   ========================================================== */
void specialKeys(int key, int x, int y)
{
    switch (key)
    {
        default:
            break;
    }
    glutPostRedisplay();
}

/* ==========================================================
   EMPTY DRAWING FUNCTION DEFINITIONS
   (To be implemented in later phases - blueprint locked)
   ========================================================== */

/* ---- Sky Layer ---- */
/* ==========================================================
   DRAW SKY FUNCTION
   Fills the background sky layer with a smooth light cyan/sky gradient
   Area: X (0 -> 1600), Y (0 -> 260)
   ========================================================== */
void drawSky()
{
    glBegin(GL_QUADS);
        // Top edge: Slightly deeper sky blue
        glColor3f(0.40f, 0.70f, 0.95f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(1600.0f, 0.0f);

        // Horizon transition edge: Very light soft cyan
        glColor3f(0.75f, 0.90f, 0.98f);
        glVertex2f(1600.0f, 260.0f);
        glVertex2f(0.0f, 260.0f);
    glEnd();
}
#include <cmath> // Math library top-e na thakle math.h use kora jabe, simple circle math er jonno

/* ==========================================================
   DRAW SUN FUNCTION
   Draws a bright yellow sun with a subtle outer glow layer
   Position: Center (110, 110), Core Radius: 55px, Glow Radius: 70px
   ========================================================== */
void drawSun()
{
    float cx = 110.0f;
    float cy = 110.0f;
    float rOuter = 70.0f;
    float rInner = 55.0f;
    int numSegments = 50;

    // 1. Outer Sun Glow (Soft Yellow Radial Blend)
    glBegin(GL_TRIANGLE_FAN);
        glColor4f(1.00f, 0.95f, 0.40f, 0.50f); // Soft semi-transparent yellow center
        glVertex2f(cx, cy);
        glColor4f(1.00f, 0.95f, 0.40f, 0.00f); // Fades out to transparent
        for (int i = 0; i <= numSegments; i++)
        {
            float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
            float x = rOuter * cosf(theta);
            float y = rOuter * sinf(theta);
            glVertex2f(cx + x, cy + y);
        }
    glEnd();

    // 2. Inner Solid Sun Core (Bright Vibrant Yellow)
    glBegin(GL_TRIANGLE_FAN);
        glColor3fv(COLOR_SUN_YELLOW);
        glVertex2f(cx, cy);
        for (int i = 0; i <= numSegments; i++)
        {
            float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
            float x = rInner * cosf(theta);
            float y = rInner * sinf(theta);
            glVertex2f(cx + x, cy + y);
        }
    glEnd();
}
/* ==========================================================
   HELPER FUNCTION FOR CLOUD PUFFS
   ========================================================== */
void drawCircleShape(float cx, float cy, float radius)
{
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= 30; i++)
        {
            float theta = 2.0f * 3.1415926f * float(i) / 30.0f;
            float x = radius * cosf(theta);
            float y = radius * sinf(theta);
            glVertex2f(cx + x, cy + y);
        }
    glEnd();
}

/* ==========================================================
   DRAW CLOUD FUNCTION
   Draws 3 fluffy white clouds across the sky
   ========================================================== */
void drawCloud()
{
    glColor3fv(COLOR_CLOUD_WHITE);

    // --- Cloud 1 (Left Side, Large) ---
    glPushMatrix();
        glTranslatef(cloud1OffsetX, 0.0f, 0.0f);
        drawCircleShape(400.0f, 100.0f, 35.0f);
        drawCircleShape(430.0f, 85.0f,  45.0f);
        drawCircleShape(470.0f, 90.0f,  40.0f);
        drawCircleShape(500.0f, 105.0f, 30.0f);
        // Base fill
        glBegin(GL_QUADS);
            glVertex2f(385.0f, 120.0f);
            glVertex2f(515.0f, 120.0f);
            glVertex2f(515.0f, 95.0f);
            glVertex2f(385.0f, 95.0f);
        glEnd();
    glPopMatrix();

    // --- Cloud 2 (Center-Right, Medium) ---
    glPushMatrix();
        glTranslatef(cloud2OffsetX, 0.0f, 0.0f);
        drawCircleShape(850.0f, 75.0f,  28.0f);
        drawCircleShape(875.0f, 60.0f,  38.0f);
        drawCircleShape(910.0f, 65.0f,  32.0f);
        drawCircleShape(935.0f, 80.0f,  22.0f);
        // Base fill
        glBegin(GL_QUADS);
            glVertex2f(835.0f, 92.0f);
            glVertex2f(945.0f, 92.0f);
            glVertex2f(945.0f, 72.0f);
            glVertex2f(835.0f, 72.0f);
        glEnd();
    glPopMatrix();

    // --- Cloud 3 (Far Right, Fluffy Small-Medium) ---
    glPushMatrix();
        glTranslatef(cloud3OffsetX, 0.0f, 0.0f);
        drawCircleShape(1420.0f, 110.0f, 25.0f);
        drawCircleShape(1445.0f, 95.0f,  35.0f);
        drawCircleShape(1480.0f, 100.0f, 30.0f);
        drawCircleShape(1505.0f, 115.0f, 20.0f);
        // Base fill
        glBegin(GL_QUADS);
            glVertex2f(1405.0f, 125.0f);
            glVertex2f(1515.0f, 125.0f);
            glVertex2f(1515.0f, 105.0f);
            glVertex2f(1405.0f, 105.0f);
        glEnd();
    glPopMatrix();
}
/* ==========================================================
   HELPER FUNCTION TO DRAW A SINGLE BIRD (V-SHAPE / WINGS)
   ========================================================== */
void drawSingleBird(float x, float y, float size)
{
    glLineWidth(2.0f);
    glColor3fv(COLOR_BLACK);
    glBegin(GL_LINE_STRIP);
        glVertex2f(x - size, y - size * 0.4f);  // Left wing tip
        glVertex2f(x - size * 0.3f, y);         // Left arch
        glVertex2f(x, y + size * 0.5f);         // Center body junction
        glVertex2f(x + size * 0.3f, y);         // Right arch
        glVertex2f(x + size, y - size * 0.4f);  // Right wing tip
    glEnd();
}

/* ==========================================================
   DRAW BIRD FLOCK FUNCTION
   Draws a flock of birds flying across the sky in formation
   ========================================================== */
void drawBird()
{
    glPushMatrix();
        glTranslatef(birdOffsetX, 0.0f, 0.0f);

        // Flock of birds flying in V-formation
        drawSingleBird(280.0f, 150.0f, 14.0f); // Leader bird
        drawSingleBird(250.0f, 170.0f, 11.0f); // Wingman 1 (Left)
        drawSingleBird(220.0f, 185.0f, 9.0f);  // Wingman 2 (Left back)
        drawSingleBird(315.0f, 168.0f, 11.0f); // Wingman 3 (Right)
        drawSingleBird(345.0f, 182.0f, 9.0f);  // Wingman 4 (Right back)
        drawSingleBird(290.0f, 195.0f, 8.0f);  // Trailing bird
    glPopMatrix();
}
void drawButterfly() { }
/* ==========================================================
   DRAW AIRPLANE FUNCTION
   Draws a sleek passenger airplane flying near the top right sky
   ========================================================== */
void drawAirplane()
{
    glPushMatrix();
        glTranslatef(airplaneOffsetX, 0.0f, 0.0f);

        // 1. Airplane Main Body (Fuselage) - Light Gray / Blue Tint
        glColor3f(0.88f, 0.92f, 0.96f);
        glBegin(GL_POLYGON);
            glVertex2f(1180.0f, 75.0f); // Nose cone tip
            glVertex2f(1200.0f, 68.0f); // Top windshield curve
            glVertex2f(1290.0f, 68.0f); // Top body line
            glVertex2f(1310.0f, 55.0f); // Tail fin top rear
            glVertex2f(1315.0f, 55.0f);
            glVertex2f(1300.0f, 78.0f); // Rear fuselage bottom
            glVertex2f(1200.0f, 78.0f); // Bottom body line
        glEnd();

        // 2. Main Wings (Sweep-back design)
        glColor3f(0.20f, 0.40f, 0.70f); // Royal Blue Wings
        glBegin(GL_TRIANGLES);
            // Main Wing
            glVertex2f(1235.0f, 73.0f);
            glVertex2f(1220.0f, 95.0f);
            glVertex2f(1255.0f, 73.0f);

            // Tail Fin Accent Wing
            glVertex2f(1285.0f, 70.0f);
            glVertex2f(1310.0f, 50.0f);
            glVertex2f(1298.0f, 70.0f);
        glEnd();

        // 3. Cockpit Glass & Windows
        glColor3f(0.15f, 0.25f, 0.45f); // Dark Window Blue
        // Cockpit Windshield
        glBegin(GL_TRIANGLES);
            glVertex2f(1185.0f, 74.0f);
            glVertex2f(1198.0f, 70.0f);
            glVertex2f(1198.0f, 74.0f);
        glEnd();

        // Passenger Windows (Small Dots/Dots row)
        for (float wx = 1210.0f; wx <= 1275.0f; wx += 10.0f)
        {
            glBegin(GL_QUADS);
                glVertex2f(wx, 71.0f);
                glVertex2f(wx + 4.0f, 71.0f);
                glVertex2f(wx + 4.0f, 74.0f);
                glVertex2f(wx, 74.0f);
            glEnd();
        }

        // 4. Red Stripe Along Body (Airlines Decor)
        glColor3f(0.85f, 0.15f, 0.15f);
        glBegin(GL_QUADS);
            glVertex2f(1190.0f, 75.0f);
            glVertex2f(1295.0f, 75.0f);
            glVertex2f(1295.0f, 76.5f);
            glVertex2f(1190.0f, 76.5f);
        glEnd();

    glPopMatrix();
}

/* ---- School Building Layer ---- */
void drawSchool() { }
void drawRoof() { }
void drawWindow() { }
void drawDoor() { }
void drawClock() { }
void drawFlagPole() { }
void drawBangladeshFlag() { }
void drawRoofBanner() { }

/* ---- Campus / Garden Layer ---- */
void drawShaheedMinar() { }
void drawGarden() { }
void drawFlower() { }
void drawBush() { }
void drawTree() { }
void drawPalmTree() { }
void drawMangoTree() { }
void drawBananaTree() { }
void drawDecorativeTree() { }
void drawAssemblyGround() { }

/* ---- Playground ---- */
void drawPlayground() { }
void drawFootballField() { }
void drawGoalPost() { }
void drawBasketballHoop() { }
void drawCricketPitch() { }
void drawSwing() { }
void drawSlide() { }
void drawSeesaw() { }
void drawMonkeyBars() { }

/* ---- Boundary & Gate Layer ---- */
void drawBoundaryWall() { }
void drawGate() { }
void drawNoticeBoard() { }
void drawLampPost() { }
void drawBench() { }
void drawWaterStation() { }
void drawCycleParking() { }
void drawDustbin() { }

/* ---- Footpath Layer ---- */
void drawFootpath() { }

/* ---- Road Layer ---- */
void drawRoad() { }
void drawRoadDivider() { }
void drawZebraCrossing() { }
void drawSpeedBreaker() { }
void drawTrafficSign() { }

/* ---- People ---- */
void drawStudent() { }
void drawTeacher() { }
void drawParent() { }
void drawSecurityGuard() { }
void drawGardener() { }
void drawAssemblyStudents() { }
void drawWalkingStudents() { }

/* ---- Vehicles ---- */
void drawBus() { }
void drawRickshaw() { }
void drawBicycle() { }
void drawMotorbike() { }
void drawCar() { }

/* ==========================================================
   MAIN FUNCTION
   ========================================================== */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 50);
    glutCreateWindow(WINDOW_TITLE);

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();

    return 0;
}
