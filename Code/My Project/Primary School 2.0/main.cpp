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
#include <cmath>

/* ==========================================================
   WINDOW CONSTANTS
   ========================================================== */
const int WINDOW_WIDTH  = 1600;
const int WINDOW_HEIGHT = 900;
const char* WINDOW_TITLE = "Government Primary School in Bangladesh";

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

// Function Declarations / Prototypes
void drawDistantSkyline();
void backBoundaryWall();
void drawGround();

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
    gluOrtho2D(0, 1600, 900, 0);

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

    // 2. BACKGROUND GROUND & WALL (NEW ADDITION)
    drawDistantSkyline();
    backBoundaryWall();
    drawGround();
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
    //drawFlower();
    //drawBush();
    drawTree();
    drawPalmTree();
    drawMangoTree();
    //drawBananaTree();
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
    gluOrtho2D(0, 1600, 900, 0);

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
// ============================================================================
// FUNCTION: drawSky
// Description: Renders a bright sunny 11:00 AM morning sky with a light gradient.
// Coordinates: Covers X from 0 to 1600 and Y from 0 (top) down to 350.
// ============================================================================
void drawSky()
{
    glBegin(GL_QUADS);

    // Top-Left (Bright Sunny Azure Blue for 11 AM)
    glColor3f(0.42f, 0.72f, 0.98f);
    glVertex2f(0.0f, 0.0f);

    // Top-Right (Bright Sunny Azure Blue for 11 AM)
    glColor3f(0.42f, 0.72f, 0.98f);
    glVertex2f(1600.0f, 0.0f);

    // Bottom-Right (Soft Horizon Sunlight / Pale Sky)
    glColor3f(0.82f, 0.93f, 1.00f);
    glVertex2f(1600.0f, 350.0f);

    // Bottom-Left (Soft Horizon Sunlight / Pale Sky)
    glColor3f(0.82f, 0.93f, 1.00f);
    glVertex2f(0.0f, 350.0f);

    glEnd();
}
// ============================================================================
// FUNCTION: drawSun
// Description: Renders a realistic 11 AM sun with a bright core and soft radial glow effect.
// Position: Center at (X = 1350, Y = 130), Base Radius = 38 (Reduced size).
// ============================================================================
void drawSun()
{
    float centerX = 1350.0f;
    float centerY = 130.0f;
    float coreRadius = 38.0f;      // Slightly reduced size for realism
    float glowRadius = 55.0f;      // Soft outer glow border
    int segments = 60;

    // ---------------------------------------------------------
    // 1. Soft Outer Sunlight Glow (Gradient Triangle Fan)
    // ---------------------------------------------------------
    glBegin(GL_TRIANGLE_FAN);
    // Glow Center Color (Warm bright yellow)
    glColor4f(1.0f, 0.95f, 0.6f, 0.6f);
    glVertex2f(centerX, centerY);

    // Glow Edge Color (Fades smoothly into sky)
    glColor4f(1.0f, 0.92f, 0.5f, 0.0f);
    for (int i = 0; i <= segments; i++)
    {
        float angle = i * 2.0f * 3.14159f / segments;
        float x = centerX + (glowRadius * cos(angle));
        float y = centerY + (glowRadius * sin(angle));
        glVertex2f(x, y);
    }
    glEnd();

    // ---------------------------------------------------------
    // 2. Bright Inner Sun Core (Radiant Center)
    // ---------------------------------------------------------
    glBegin(GL_TRIANGLE_FAN);
    // Core Center Color (Very bright white-yellow for intense 11 AM sun)
    glColor3f(1.0f, 0.98f, 0.85f);
    glVertex2f(centerX, centerY);

    // Core Edge Color (Golden Sun Yellow)
    glColor3f(1.0f, 0.88f, 0.25f);
    for (int i = 0; i <= segments; i++)
    {
        float angle = i * 2.0f * 3.14159f / segments;
        float x = centerX + (coreRadius * cos(angle));
        float y = centerY + (coreRadius * sin(angle));
        glVertex2f(x, y);
    }
    glEnd();
}
// ============================================================================
// FUNCTION: drawSingleCloud
// Description: Keeps the clean original shape, but trims the lower bulge to make
//              it look light, flat-bottomed, and realistic with soft 11 AM highlights.
// ============================================================================
void drawSingleCloud(float startX, float startY, float scale)
{
    int segments = 50;

    // Original clean arrangement with trimmed lower offsets (offsetX, offsetY, radius)
    struct CloudCircle
    {
        float offsetX, offsetY, radius;
    } circles[] =
    {
        {  0.0f,   0.0f, 26.0f }, // Left Base
        { 22.0f,  12.0f, 32.0f }, // Middle-Left Main Top
        { 50.0f,  10.0f, 28.0f }, // Middle-Right Top
        { 72.0f,   2.0f, 24.0f }, // Right Base
        { 35.0f,  -2.0f, 25.0f }  // Bottom Center Flattened Base (Trimmed to avoid bulge)
    };

    glPushMatrix();
    glTranslatef(startX, startY, 0.0f);
    glScalef(scale, scale, 1.0f);

    for (int c = 0; c < 5; c++)
    {
        float cx = circles[c].offsetX;
        float cy = circles[c].offsetY;
        float r  = circles[c].radius;

        glBegin(GL_TRIANGLE_FAN);

        // Center Color: Top gets pure white sunlight, bottom gets soft depth
        if (cy > 0.0f) {
            glColor3f(1.0f, 1.0f, 1.0f);        // Bright White Highlight
        } else {
            glColor3f(0.92f, 0.95f, 0.98f);     // Soft Subtle Base
        }
        glVertex2f(cx, cy);

        // Edge Colors (Smooth Gradient)
        for (int i = 0; i <= segments; i++)
        {
            float angle = i * 2.0f * 3.14159f / segments;
            float px = cx + (r * cos(angle));
            float py = cy + (r * sin(angle));

            if (py > cy) {
                glColor3f(1.0f, 1.0f, 1.0f);    // Sunlight top edge
            } else {
                glColor3f(0.88f, 0.92f, 0.96f); // Soft lower edge
            }
            glVertex2f(px, py);
        }
        glEnd();
    }

    glPopMatrix();
}

// ============================================================================
// FUNCTION: drawCloud
// Description: Renders five realistic drifting clouds across the sky with unique speeds.
// ============================================================================

// Extra global movement offsets for the 2 new clouds (Define these globally in your code)
 float cloud4OffsetX = 0.0f;
 float cloud5OffsetX = 0.0f;

void drawCloud()
{
    // 1. Update movement offsets (5 clouds with slightly varying speeds)
    cloud1OffsetX += 0.35f; // Small cloud 1 speed
    cloud2OffsetX += 0.55f; // Medium cloud 2 speed
    cloud3OffsetX += 0.45f; // Large cloud 3 speed
    cloud4OffsetX += 0.60f; // Fast small cloud 4 speed
    cloud5OffsetX += 0.40f; // Medium-high cloud 5 speed

    // 2. Loop clouds smoothly back when they leave the right side (X = 1600)
    if (cloud1OffsetX > 1600.0f) cloud1OffsetX = -300.0f;
    if (cloud2OffsetX > 1600.0f) cloud2OffsetX = -700.0f;
    if (cloud3OffsetX > 1600.0f) cloud3OffsetX = -1100.0f;
    if (cloud4OffsetX > 1600.0f) cloud4OffsetX = -500.0f;
    if (cloud5OffsetX > 1600.0f) cloud5OffsetX = -1300.0f;

    // ---------------------------------------------------------
    // Render 5 Clouds across different Y positions and scales
    // ---------------------------------------------------------

    // Cloud 1 - Far Left Sky (Small Size: 0.70x)
    drawSingleCloud(150.0f + cloud1OffsetX, 110.0f, 0.70f);

    // Cloud 2 - Mid Left Sky (Fast & Tiny: 0.55x) -> NEW CLOUD 4
    drawSingleCloud(450.0f + cloud4OffsetX, 60.0f, 0.55f);

    // Cloud 3 - Center Sky (Medium Size: 0.95x)
    drawSingleCloud(750.0f + cloud2OffsetX, 95.0f, 0.95f);

    // Cloud 4 - Mid Right Sky (Higher up, Medium: 0.80x) -> NEW CLOUD 5
    drawSingleCloud(1050.0f + cloud5OffsetX, 50.0f, 0.80f);

    // Cloud 5 - Far Right Sky (Large Size: 1.15x)
    drawSingleCloud(1350.0f + cloud3OffsetX, 130.0f, 1.15f);
}

// ============================================================================
// FUNCTION: drawSingleBird
// Description: Renders a realistic, graceful bird silhouette (slender wings, smooth curve, no bat look).
// ============================================================================
void drawSingleBird(float x, float y, float size, float flapAngle)
{
    // Deep Charcoal Color (Natural bird shadow in bright sky)
    glColor3f(0.15f, 0.15f, 0.18f);

    // Natural smooth wing motion (up/down and slight arch)
    float wingUp = sin(flapAngle) * (size * 0.6f);
    float wingCurve = cos(flapAngle) * (size * 0.15f);

    // ---------------------------------------------------------
    // 1. Left Wing (Graceful Curved Feathered Shape)
    // ---------------------------------------------------------
    glBegin(GL_POLYGON);
    glVertex2f(x, y - (size * 0.1f));                                 // Lower Body Center
    glVertex2f(x, y + (size * 0.15f));                                // Upper Body Center
    glVertex2f(x - (size * 0.5f), y + (size * 0.35f) + (wingUp * 0.5f));// Wing Elbow/Arch
    glVertex2f(x - (size * 1.2f), y + (size * 0.1f) + wingUp);        // Sleek Wing Tip
    glVertex2f(x - (size * 0.6f), y - (size * 0.05f) + wingCurve);    // Wing Inner Arch
    glEnd();

    // ---------------------------------------------------------
    // 2. Right Wing (Graceful Curved Feathered Shape)
    // ---------------------------------------------------------
    glBegin(GL_POLYGON);
    glVertex2f(x, y - (size * 0.1f));                                 // Lower Body Center
    glVertex2f(x, y + (size * 0.15f));                                // Upper Body Center
    glVertex2f(x + (size * 0.5f), y + (size * 0.35f) + (wingUp * 0.5f));// Wing Elbow/Arch
    glVertex2f(x + (size * 1.2f), y + (size * 0.1f) + wingUp);        // Sleek Wing Tip
    glVertex2f(x + (size * 0.6f), y - (size * 0.05f) + wingCurve);    // Wing Inner Arch
    glEnd();

    // ---------------------------------------------------------
    // 3. Slender Tail Feathers
    // ---------------------------------------------------------
    glBegin(GL_TRIANGLES);
    glVertex2f(x - (size * 0.12f), y - (size * 0.1f));
    glVertex2f(x + (size * 0.12f), y - (size * 0.1f));
    glVertex2f(x, y - (size * 0.45f));                                // Pointed Tail
    glEnd();
}

// ============================================================================
// FUNCTION: drawBird
// Description: Renders a flock of 5 sleek birds with natural formation flying.
// ============================================================================
void drawBird()
{
    // 1. Move birds smoothly from Right to Left
    birdOffsetX -= 1.5f;

    // Loop back smoothly
    if (birdOffsetX < -600.0f)
    {
        birdOffsetX = 1200.0f;
    }

    // 2. Wing Flapping Speed
    float time = glutGet(GLUT_ELAPSED_TIME) * 0.007f;

    // Flock of birds with staggered wing flap angles and positions
    drawSingleBird(350.0f + birdOffsetX, 85.0f,  9.0f, time);
    drawSingleBird(385.0f + birdOffsetX, 105.0f, 11.0f, time + 0.7f);
    drawSingleBird(420.0f + birdOffsetX, 75.0f,  8.0f,  time + 1.4f);
    drawSingleBird(455.0f + birdOffsetX, 95.0f,  10.0f, time + 2.1f);
    drawSingleBird(490.0f + birdOffsetX, 115.0f, 7.5f,  time + 2.8f);
}
// Helper function to draw a single small butterfly
void drawSingleButterfly(float x, float y, float scale, float wingAngle, float r, float g, float b)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // 1. Butterfly Body
    glColor3f(0.1f, 0.1f, 0.1f); // Dark body
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, -6.0f);
    glVertex2f(0.0f, 6.0f);
    glEnd();

    // Head
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 6.0f);
    for (int i = 0; i <= 10; i++)
    {
        float angle = i * 2.0f * 3.14159f / 10;
        glVertex2f(0.0f + 1.2f * cos(angle), 6.0f + 1.2f * sin(angle));
    }
    glEnd();

    // Antennae
    glBegin(GL_LINES);
    glVertex2f(0.0f, 6.0f);
    glVertex2f(-2.5f, 10.0f);
    glVertex2f(0.0f, 6.0f);
    glVertex2f(2.5f, 10.0f);
    glEnd();

    // 2. Left Wings (Flapping with scale transformation)
    glPushMatrix();
    glScalef(cos(wingAngle), 1.0f, 1.0f); // Flapping effect
    glColor3f(r, g, b); // Wing color

    // Upper Left Wing
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(-8.0f, 7.0f);
    glVertex2f(-12.0f, 3.0f);
    glVertex2f(-6.0f, -2.0f);
    glEnd();

    // Lower Left Wing
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(-7.0f, -2.0f);
    glVertex2f(-9.0f, -7.0f);
    glVertex2f(-3.0f, -6.0f);
    glEnd();
    glPopMatrix();

    // 3. Right Wings (Flapping with scale transformation)
    glPushMatrix();
    glScalef(cos(wingAngle), 1.0f, 1.0f); // Flapping effect
    glColor3f(r, g, b); // Wing color

    // Upper Right Wing
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(8.0f, 7.0f);
    glVertex2f(12.0f, 3.0f);
    glVertex2f(6.0f, -2.0f);
    glEnd();

    // Lower Right Wing
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(7.0f, -2.0f);
    glVertex2f(9.0f, -7.0f);
    glVertex2f(3.0f, -6.0f);
    glEnd();
    glPopMatrix();

    glPopMatrix();
}

// ============================================================================
// FUNCTION: drawButterfly
// Description: Renders 6 dynamically animated butterflies positioned higher up
//              in the sky/canopy area with slower speeds for Butterfly 1 & 2.
// Screen Resolution Target: 1600 x 900
// ============================================================================
void drawButterfly()
{
    float time = glutGet(GLUT_ELAPSED_TIME) * 0.005f; // Base Animation clock

    // Dynamic wing flap speed clock (Default speed for others)
    float wingFlap = time * 3.5f;

    // ------------------------------------------------------------------------
    // Butterfly 1: Golden-Yellow (Higher Up - Mid Sky)
    // Speed: Reduced Movement & Flapping Speed (time * 0.4f & flap * 1.5f)
    // ------------------------------------------------------------------------
    float b1Flap = time * 1.5f; // Slower wing flapping speed
    float b1X = 380.0f + sin(time * 0.4f) * 35.0f; // Slower movement
    float b1Y = 320.0f + cos(time * 0.6f) * 15.0f; // Positioned high (Y = 320)
    drawSingleButterfly(b1X, b1Y, 0.80f, b1Flap, 1.0f, 0.82f, 0.0f);

    // ------------------------------------------------------------------------
    // Butterfly 2: Crimson Red (High Sky above Left Trees)
    // Speed: Reduced Movement & Flapping Speed (time * 0.35f & flap * 1.6f)
    // ------------------------------------------------------------------------
    float b2Flap = time * 1.6f; // Slower wing flapping speed
    float b2X = 220.0f + cos(time * 0.35f) * 45.0f; // Slower movement
    float b2Y = 250.0f + sin(time * 0.5f) * 20.0f;  // Positioned very high (Y = 250)
    drawSingleButterfly(b2X, b2Y, 0.60f, b2Flap + 1.2f, 0.95f, 0.15f, 0.25f);

    // ------------------------------------------------------------------------
    // Butterfly 3: Electric Cyan/Blue (Above Center Field / Mid-Sky)
    // Position: Shifted higher (Y = 410)
    // ------------------------------------------------------------------------
    float b3X = 720.0f + sin(time * 1.2f) * 70.0f;
    float b3Y = 410.0f + cos(time * 1.5f) * 15.0f;
    drawSingleButterfly(b3X, b3Y, 0.85f, wingFlap + 2.1f, 0.1f, 0.78f, 1.0f);

    // ------------------------------------------------------------------------
    // Butterfly 4: Bright Orange (Upper Right Tree Canopy / Sky)
    // Position: Shifted higher (Y = 350)
    // ------------------------------------------------------------------------
    float b4X = 1040.0f + cos(time * 1.0f) * 30.0f;
    float b4Y = 350.0f + sin(time * 1.4f) * 20.0f;
    drawSingleButterfly(b4X, b4Y, 0.70f, wingFlap + 0.8f, 1.0f, 0.48f, 0.0f);

    // ---------------------------------------------------------
    // Butterfly 5: Royal Magenta/Purple (High Sky near Shahid Minar Top)
    // Position: Positioned very high (Y = 220)
    // ---------------------------------------------------------
    float b5X = 1280.0f + sin(time * 0.6f) * 45.0f;
    float b5Y = 220.0f + cos(time * 0.8f) * 30.0f;
    drawSingleButterfly(b5X, b5Y, 0.50f, wingFlap + 3.0f, 0.75f, 0.2f, 0.9f);

    // ---------------------------------------------------------
    // Butterfly 6: Soft Lime Green (Upper Center Sky)
    // Position: Shifted higher (Y = 300)
    // ---------------------------------------------------------
    float b6X = 580.0f + sin(time * 1.0f) * 50.0f;
    float b6Y = 300.0f + sin(time * 1.8f) * 20.0f;
    drawSingleButterfly(b6X, b6Y, 0.65f, wingFlap + 1.7f, 0.45f, 0.95f, 0.2f);
}
// ============================================================================
// FUNCTION: drawAirplane
// Description: Renders a highly realistic, shaded commercial airliner
//              flying right-to-left with dual wings, jet engines,
//              passenger windows, and atmospheric contrail (smoke trail).
// Position: Base at X = 800, Y = 60.
// ============================================================================
void drawAirplane()
{
    // Movement animation logic
    airplaneOffsetX -= 1.5f;
    if (airplaneOffsetX < -900.0f)
    {
        airplaneOffsetX = 900.0f;
    }

    glPushMatrix();
    glTranslatef(airplaneOffsetX, 0.0f, 0.0f);

    float baseX = 800.0f;
    float baseY = 60.0f;

    // ------------------------------------------------------------------------
    // 1. CONDENSATION TRAIL / CONTRAIL (Soft Translucent Smoke Trail)
    // ------------------------------------------------------------------------
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS);
        // Engine Trail 1
        glColor4f(1.0f, 1.0f, 1.0f, 0.0f);   // Fades out far back
        glVertex2f(baseX + 250.0f, baseY + 2.0f);
        glVertex2f(baseX + 250.0f, baseY + 8.0f);
        glColor4f(1.0f, 1.0f, 1.0f, 0.45f);  // Dense near tail
        glVertex2f(baseX + 45.0f, baseY + 5.0f);
        glVertex2f(baseX + 45.0f, baseY + 3.0f);
    glEnd();

    glDisable(GL_BLEND);

    // ------------------------------------------------------------------------
    // 2. FAR WING (Distant wing rendered behind the fuselage for depth)
    // ------------------------------------------------------------------------
    glColor3f(0.55f, 0.60f, 0.68f); // Darker shadow tone
    glBegin(GL_POLYGON);
        glVertex2f(baseX - 8.0f,  baseY - 2.0f);
        glVertex2f(baseX + 10.0f, baseY - 2.0f);
        glVertex2f(baseX + 32.0f, baseY - 22.0f); // Swept tip
        glVertex2f(baseX + 22.0f, baseY - 22.0f);
    glEnd();

    // ------------------------------------------------------------------------
    // 3. MAIN FUSELAGE (Curved, Aerodynamic Body with Top-to-Bottom Lighting)
    // ------------------------------------------------------------------------
    // Main Body Nose & Mid-section
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 1.0f, 1.0f);        // Highlight Top
        glVertex2f(baseX - 55.0f, baseY);          // Nose Tip
        glVertex2f(baseX - 35.0f, baseY - 7.0f);   // Top Front Curve
        glVertex2f(baseX + 35.0f, baseY - 6.0f);   // Top Rear Fuselage

        glColor3f(0.78f, 0.82f, 0.88f);     // Shadow Bottom
        glVertex2f(baseX + 48.0f, baseY + 1.0f);   // Tail Cone Base
        glVertex2f(baseX + 35.0f, baseY + 7.0f);   // Bottom Rear
        glVertex2f(baseX - 35.0f, baseY + 7.0f);   // Bottom Front Curve
    glEnd();

    // Nose Cone Soft Curve Shading
    glBegin(GL_TRIANGLES);
        glColor3f(0.85f, 0.88f, 0.92f);
        glVertex2f(baseX - 55.0f, baseY);
        glColor3f(0.95f, 0.95f, 0.98f);
        glVertex2f(baseX - 35.0f, baseY - 7.0f);
        glColor3f(0.75f, 0.78f, 0.84f);
        glVertex2f(baseX - 35.0f, baseY + 7.0f);
    glEnd();

    // Decorative Airline Livery Stripe along Fuselage
    glColor3f(0.85f, 0.15f, 0.20f); // Vivid Red Stripe
    glBegin(GL_QUADS);
        glVertex2f(baseX - 48.0f, baseY + 1.0f);
        glVertex2f(baseX + 42.0f, baseY + 1.0f);
        glVertex2f(baseX + 42.0f, baseY + 3.0f);
        glVertex2f(baseX - 42.0f, baseY + 3.0f);
    glEnd();

    // ------------------------------------------------------------------------
    // 4. COCKPIT WINDOW & PASSENGER WINDOWS
    // ------------------------------------------------------------------------
    // Cockpit Windshield (Glossy Glass Gradient)
    glBegin(GL_QUADS);
        glColor3f(0.15f, 0.35f, 0.55f);
        glVertex2f(baseX - 46.0f, baseY - 1.0f);
        glVertex2f(baseX - 36.0f, baseY - 5.0f);
        glColor3f(0.65f, 0.85f, 1.0f); // Reflection highlight
        glVertex2f(baseX - 32.0f, baseY - 5.0f);
        glVertex2f(baseX - 40.0f, baseY - 1.0f);
    glEnd();

    // Row of Passenger Windows
    glColor3f(0.20f, 0.25f, 0.35f);
    for (float wx = baseX - 25.0f; wx <= baseX + 28.0f; wx += 6.5f)
    {
        glBegin(GL_QUADS);
            glVertex2f(wx,        baseY - 2.5f);
            glVertex2f(wx + 3.5f, baseY - 2.5f);
            glVertex2f(wx + 3.5f, baseY - 0.5f);
            glVertex2f(wx,        baseY - 0.5f);
        glEnd();
    }

    // ------------------------------------------------------------------------
    // 5. TAIL FIN & STABILIZERS (Vertical & Horizontal Tail)
    // ------------------------------------------------------------------------
    // Vertical Tail Fin
    glBegin(GL_POLYGON);
        glColor3f(0.85f, 0.15f, 0.20f); // Red Airline Livery Tail
        glVertex2f(baseX + 28.0f, baseY - 5.0f);
        glVertex2f(baseX + 42.0f, baseY - 24.0f);
        glVertex2f(baseX + 48.0f, baseY - 24.0f);
        glColor3f(0.65f, 0.10f, 0.12f);
        glVertex2f(baseX + 44.0f, baseY - 2.0f);
    glEnd();

    // Horizontal Rear Stabilizer
    glColor3f(0.72f, 0.78f, 0.85f);
    glBegin(GL_TRIANGLES);
        glVertex2f(baseX + 36.0f, baseY + 1.0f);
        glVertex2f(baseX + 48.0f, baseY + 12.0f);
        glVertex2f(baseX + 47.0f, baseY + 1.0f);
    glEnd();

    // ------------------------------------------------------------------------
    // 6. NEAR MAIN WING & JET ENGINE (Rendered in Front)
    // ------------------------------------------------------------------------
    // Jet Engine Pod under main wing
    glColor3f(0.35f, 0.38f, 0.42f); // Dark Engine Metallic Gray
    glBegin(GL_QUADS);
        glVertex2f(baseX - 8.0f, baseY + 12.0f);
        glVertex2f(baseX + 12.0f, baseY + 12.0f);
        glVertex2f(baseX + 12.0f, baseY + 17.0f);
        glVertex2f(baseX - 8.0f, baseY + 17.0f);
    glEnd();
    // Engine Intake Glow/Front
    glColor3f(0.15f, 0.15f, 0.18f);
    glBegin(GL_QUADS);
        glVertex2f(baseX - 10.0f, baseY + 12.0f);
        glVertex2f(baseX - 8.0f,  baseY + 12.0f);
        glVertex2f(baseX - 8.0f,  baseY + 17.0f);
        glVertex2f(baseX - 10.0f, baseY + 17.0f);
    glEnd();

    // Swept Main Wing (In front of body)
    glBegin(GL_POLYGON);
        glColor3f(0.88f, 0.92f, 0.96f); // Light edge
        glVertex2f(baseX - 12.0f, baseY + 2.0f);
        glVertex2f(baseX + 8.0f,  baseY + 2.0f);
        glColor3f(0.68f, 0.72f, 0.80f); // Wingtip shadow
        glVertex2f(baseX + 28.0f, baseY + 26.0f);
        glVertex2f(baseX + 15.0f, baseY + 26.0f);
    glEnd();

    glPopMatrix();
}
// ============================================================================
// FUNCTION: drawDistantSkyline
// Description: Renders a multi-layered, realistic daytime distant skyline
//              with atmospheric haze, architectural details, and natural foliage.
// Screen Resolution Target: 1600 x 900
// ============================================================================
void drawDistantSkyline() {
    // ------------------------------------------------------------------------
    // 1. LAYER 1: VERY DISTANT BUILDINGS (Ultra-Soft Hazy Hues)
    // ------------------------------------------------------------------------
    // Soft atmospheric haze tone for far distance
    glColor3f(0.72f, 0.78f, 0.84f);

    glBegin(GL_QUADS);
        // Far Building A (Stepped Roof Line)
        glVertex2i(100, 260); glVertex2i(160, 260);
        glVertex2i(160, 330); glVertex2i(100, 330);

        // Far Building B (Tall Wide Block)
        glVertex2i(300, 190); glVertex2i(380, 190);
        glVertex2i(380, 330); glVertex2i(300, 330);

        // Far Building C (Mid-Right Skyline)
        glVertex2i(850, 210); glVertex2i(940, 210);
        glVertex2i(940, 330); glVertex2i(850, 330);

        // Far Building D (Far Right Edge)
        glVertex2i(1420, 180); glVertex2i(1520, 180);
        glVertex2i(1520, 330); glVertex2i(1420, 330);
    glEnd();

    // ------------------------------------------------------------------------
    // 2. LAYER 2: MID-DISTANCE BUILDINGS (Sharper Silhouettes)
    // ------------------------------------------------------------------------
    glColor3f(0.58f, 0.66f, 0.74f); // Slightly darker/closer tone

    glBegin(GL_QUADS);
        // Building 1 (Left Tower)
        glVertex2i(40,  220); glVertex2i(110, 220);
        glVertex2i(110, 330); glVertex2i(40,  330);

        // Building 2 (Slanted Roof Center-Left)
        glVertex2i(180, 200); glVertex2i(250, 200);
        glVertex2i(250, 330); glVertex2i(180, 330);

        // Building 3 (Behind School - Left)
        glVertex2i(480, 210); glVertex2i(570, 210);
        glVertex2i(570, 330); glVertex2i(480, 330);

        // Building 4 (Behind School - Right, High-rise)
        glVertex2i(990, 170); glVertex2i(1070, 170);
        glVertex2i(1070, 330); glVertex2i(990, 330);

        // Building 5 (Far Right Mid-layer)
        glVertex2i(1350, 220); glVertex2i(1430, 220);
        glVertex2i(1430, 330); glVertex2i(1350, 330);
    glEnd();

    // Architectural Roof Details (Spire / Antennas / Stepped Tops)
    glColor3f(0.50f, 0.58f, 0.65f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        // Antenna on Tall Building 4
        glVertex2i(1030, 170); glVertex2i(1030, 140);
        // Spire on Building 2
        glVertex2i(215, 200);  glVertex2i(215, 175);
    glEnd();

    // Distant Reflective Windows (Soft Sunlight Reflection)
    glColor3f(0.85f, 0.92f, 0.98f);
    glBegin(GL_QUADS);
        // Vertical window strips on High-rise (Building 4)
        for (int wy = 185; wy < 310; wy += 25) {
            glVertex2i(1010, wy); glVertex2i(1025, wy); glVertex2i(1025, wy + 12); glVertex2i(1010, wy + 12);
            glVertex2i(1035, wy); glVertex2i(1050, wy); glVertex2i(1050, wy + 12); glVertex2i(1035, wy + 12);
        }
        // Grid windows on Left Tower (Building 1)
        for (int wy = 235; wy < 310; wy += 20) {
            glVertex2i(55, wy); glVertex2i(70, wy); glVertex2i(70, wy + 10); glVertex2i(55, wy + 10);
            glVertex2i(80, wy); glVertex2i(95, wy); glVertex2i(95, wy + 10); glVertex2i(80, wy + 10);
        }
    glEnd();

    // ------------------------------------------------------------------------
    // 3. DISTANT NATURAL TREE HORIZON (Layered Organic Foliage)
    // ------------------------------------------------------------------------

    // Back Tree Line (Slightly lighter, hazy green)
    glColor3f(0.42f, 0.58f, 0.42f);
    for (int x = -10; x <= 1610; x += 30) {
        float treeHeight = 280.0f + sin(x * 0.03f) * 12.0f; // Organic height variation
        glBegin(GL_POLYGON);
            glVertex2i(x - 25, 330);
            glVertex2f(x - 15, treeHeight + 12.0f);
            glVertex2f(x,       treeHeight);
            glVertex2f(x + 15, treeHeight + 12.0f);
            glVertex2i(x + 25, 330);
        glEnd();
    }

    // Front Tree Line (Slightly darker, overlapping for depth)
    glColor3f(0.32f, 0.50f, 0.32f);
    for (int x = 5; x <= 1610; x += 38) {
        float treeHeight = 290.0f + cos(x * 0.025f) * 10.0f;
        glBegin(GL_POLYGON);
            glVertex2i(x - 22, 330);
            glVertex2f(x - 12, treeHeight + 10.0f);
            glVertex2f(x,       treeHeight);
            glVertex2f(x + 12, treeHeight + 10.0f);
            glVertex2i(x + 22, 330);
        glEnd();
    }
}
// ============================================================================
// FUNCTION: drawGround
// Description: Renders a realistic multi-shaded grass lawn with natural depth
//              gradient and organic grass blade texture details.
// Screen Resolution Target: 1600 x 900
// ============================================================================
void drawGround() {
    // 1. MAIN GRASS GRADIENT (3-Layer Depth Gradient)

    // Horizon to Mid-ground Layer
    glBegin(GL_QUADS);
        glColor3f(0.42f, 0.78f, 0.30f); // Light Horizon Green
        glVertex2i(0, 330);
        glVertex2i(1600, 330);

        glColor3f(0.28f, 0.62f, 0.20f); // Mid-Field Green
        glVertex2i(1600, 600);
        glVertex2i(0, 600);
    glEnd();

    // Mid-ground to Deep Foreground Layer
    glBegin(GL_QUADS);
        glColor3f(0.28f, 0.62f, 0.20f); // Mid-Field Green
        glVertex2i(0, 600);
        glVertex2i(1600, 600);

        glColor3f(0.12f, 0.42f, 0.10f); // Rich Deep Foreground Green
        glVertex2i(1600, 900);
        glVertex2i(0, 900);
    glEnd();

    // 2. REALISTIC GRASS BLADE TEXTURES (Scattered Organic Strands)
    // Denser and larger strands near foreground, subtle near horizon

    // Foreground Detailed Grass Blades (Y = 600 to 900)
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    for (int x = 5; x < 1600; x += 15) {
        for (int y = 620; y < 890; y += 45) {
            float xOffset = (x % 3 == 0) ? 4.0f : -3.0f; // Random tilt

            // Alternating bright/dark grass blades for realism
            if ((x + y) % 2 == 0) {
                glColor3f(0.35f, 0.70f, 0.25f); // Bright blade tip
            } else {
                glColor3f(0.18f, 0.48f, 0.12f); // Shadowed blade
            }

            glVertex2i(x, y);
            glVertex2f(x + xOffset, y - 10.0f); // Slight upward angle
        }
    }
    glEnd();
    glLineWidth(1.0f); // Reset line width

    // Subtle Horizon Mist Blend (Smooth Sky-Ground Boundary)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUADS);
        glColor4f(0.70f, 0.85f, 0.95f, 0.25f); // Hazy Horizon Fog
        glVertex2i(0, 325);
        glVertex2i(1600, 325);

        glColor4f(0.42f, 0.78f, 0.30f, 0.0f);  // Fades out into grass
        glVertex2i(1600, 350);
        glVertex2i(0, 350);
    glEnd();
    glDisable(GL_BLEND);
}

// ============================================================================
// FUNCTION: backBoundaryWall
// Description: Renders a textured concrete brick boundary wall with 3D
//              pillars, cap shadows, and realistic mortar lines.
// Screen Resolution Target: 1600 x 900
// ============================================================================
void backBoundaryWall() {
    int wallTop = 320;
    int wallBottom = 380;

    // 1. MAIN CONCRETE WALL BASE (Subtle Vertical Lighting Gradient)
    glBegin(GL_QUADS);
        glColor3f(0.85f, 0.84f, 0.80f); // Highlighted Top Wall
        glVertex2i(0, wallTop);
        glVertex2i(1600, wallTop);

        glColor3f(0.68f, 0.67f, 0.64f); // Slightly Shadowed Bottom Wall
        glVertex2i(1600, wallBottom);
        glVertex2i(0, wallBottom);
    glEnd();

    // 2. REALISTIC BRICK TEXTURE (Mortar Lines & Staggered Bricks)
    glColor3f(0.60f, 0.59f, 0.56f); // Darker Mortar/Grout Line Color
    glLineWidth(1.0f);

    // Horizontal Mortar Lines
    glBegin(GL_LINES);
    for (int y = wallTop + 12; y < wallBottom; y += 12) {
        glVertex2i(0, y);
        glVertex2i(1600, y);
    }
    glEnd();

    // Vertical Brick Joints (Staggered Pattern)
    glBegin(GL_LINES);
    int row = 0;
    for (int y = wallTop; y < wallBottom; y += 12) {
        int xOffset = (row % 2 == 0) ? 0 : 20; // Stagger every alternate row
        for (int x = xOffset; x < 1600; x += 40) {
            glVertex2i(x, y);
            glVertex2i(x, y + 12);
        }
        row++;
    }
    glEnd();

    // 3. TOP COPING CAP WITH 3D SHADOW
    // Top Cap Base
    glBegin(GL_QUADS);
        glColor3f(0.75f, 0.74f, 0.70f); // Light Cap Surface
        glVertex2i(0, wallTop - 8);
        glVertex2i(1600, wallTop - 8);

        glColor3f(0.62f, 0.61f, 0.58f); // Shadowed Bottom Edge
        glVertex2i(1600, wallTop);
        glVertex2i(0, wallTop);
    glEnd();

    // Cast Shadow under Cap Line
    glBegin(GL_QUADS);
        glColor3f(0.45f, 0.44f, 0.42f); // Dark Ambient Shadow
        glVertex2i(0, wallTop);
        glVertex2i(1600, wallTop);

        glColor3f(0.75f, 0.74f, 0.70f); // Fades into wall
        glVertex2i(1600, wallTop + 4);
        glVertex2i(0, wallTop + 4);
    glEnd();

    // 4. 3D PILLARS / SUPPORT COLUMNS (Spaced every 100 pixels)
    for (int x = 0; x <= 1600; x += 100) {
        // Pillar Main Face
        glBegin(GL_QUADS);
            glColor3f(0.88f, 0.87f, 0.83f); // Highlight Side
            glVertex2i(x - 8, wallTop - 10);
            glVertex2i(x + 2, wallTop - 10);
            glVertex2i(x + 2, wallBottom);
            glVertex2i(x - 8, wallBottom);

            glColor3f(0.72f, 0.71f, 0.67f); // Shadowed Side
            glVertex2i(x + 2, wallTop - 10);
            glVertex2i(x + 8, wallTop - 10);
            glVertex2i(x + 8, wallBottom);
            glVertex2i(x + 2, wallBottom);
        glEnd();

        // Pillar Top Cap
        glBegin(GL_QUADS);
            glColor3f(0.92f, 0.91f, 0.88f);
            glVertex2i(x - 10, wallTop - 14);
            glVertex2i(x + 10, wallTop - 14);
            glVertex2i(x + 10, wallTop - 10);
            glVertex2i(x - 10, wallTop - 10);
        glEnd();
    }
}
/* ---- School Building Layer ---- */

#include <GL/glut.h>
#include <cmath>
#include <ctime>


// ============================================================================
// FUNCTION: drawSchool
// Description: Moved UP & Resized School (Y = 250 to 480).
// Opens up a large assembly & road area in front.
// ============================================================================
void drawSchool()
{
    // 1. Main Base Building Walls (Cream Base)
    glColor3fv(COLOR_BUILDING_CREAM);
    glBegin(GL_QUADS);
    glVertex2f(450.0f, 250.0f);   // Top-Left
    glVertex2f(1150.0f, 250.0f);  // Top-Right
    glVertex2f(1150.0f, 480.0f);  // Bottom-Right
    glVertex2f(450.0f, 480.0f);   // Bottom-Left
    glEnd();

    // 2. Red Structural Accent Pillars
    glColor3fv(COLOR_BUILDING_RED);

    // Left Pillar
    glBegin(GL_QUADS);
    glVertex2f(450.0f, 250.0f);
    glVertex2f(475.0f, 250.0f);
    glVertex2f(475.0f, 480.0f);
    glVertex2f(450.0f, 480.0f);
    glEnd();

    // Center-Left Support Column
    glBegin(GL_QUADS);
    glVertex2f(665.0f, 250.0f);
    glVertex2f(682.0f, 250.0f);
    glVertex2f(682.0f, 480.0f);
    glVertex2f(665.0f, 480.0f);
    glEnd();

    // Center-Right Support Column
    glBegin(GL_QUADS);
    glVertex2f(918.0f, 250.0f);
    glVertex2f(935.0f, 250.0f);
    glVertex2f(935.0f, 480.0f);
    glVertex2f(918.0f, 480.0f);
    glEnd();

    // Right Pillar
    glBegin(GL_QUADS);
    glVertex2f(1125.0f, 250.0f);
    glVertex2f(1150.0f, 250.0f);
    glVertex2f(1150.0f, 480.0f);
    glVertex2f(1125.0f, 480.0f);
    glEnd();

    // Horizontal Floor Dividers
    glLineWidth(2.5f);
    glColor3f(0.50f, 0.10f, 0.10f);
    glBegin(GL_LINES);
    // Floor 1 & 2 Divider
    glVertex2f(450.0f, 326.0f);
    glVertex2f(1150.0f, 326.0f);

    // Floor 2 & 3 Divider
    glVertex2f(450.0f, 403.0f);
    glVertex2f(1150.0f, 403.0f);
    glEnd();
}

// ============================================================================
// FUNCTION: drawRoof
// ============================================================================
void drawRoof()
{
    // 1. Main Horizontal Roof Slab (Y = 237 to 250)
    glColor3fv(COLOR_ROOF_GRAY);
    glBegin(GL_QUADS);
    glVertex2f(435.0f, 237.0f);   // Top-Left
    glVertex2f(1165.0f, 237.0f);  // Top-Right
    glVertex2f(1165.0f, 250.0f);  // Bottom-Right
    glVertex2f(435.0f, 250.0f);   // Bottom-Left
    glEnd();

    // 2. Parapet Safety Wall
    glColor3fv(COLOR_BUILDING_RED);
    glBegin(GL_QUADS);
    glVertex2f(450.0f, 224.0f);
    glVertex2f(1150.0f, 224.0f);
    glVertex2f(1150.0f, 237.0f);
    glVertex2f(450.0f, 237.0f);
    glEnd();

    // 3. Central Gable Roof (Triangular Peak)
    glColor3fv(COLOR_BUILDING_RED);
    glBegin(GL_TRIANGLES);
    glVertex2f(800.0f, 172.0f);
    glVertex2f(735.0f, 224.0f);
    glVertex2f(865.0f, 224.0f);
    glEnd();

    // Triangular Gable Inner Border
    glColor3fv(COLOR_BUILDING_CREAM);
    glLineWidth(2.5f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(800.0f, 178.0f);
    glVertex2f(743.0f, 221.0f);
    glVertex2f(857.0f, 221.0f);
    glEnd();
}

// Helper function to draw a single double-pane window
void drawSingleWindow(float x, float y, float width, float height)
{
    // 1. Dark Frame
    glColor3f(0.15f, 0.15f, 0.20f);
    glBegin(GL_QUADS);
    glVertex2f(x - 1.5f, y - 1.5f);
    glVertex2f(x + width + 1.5f, y - 1.5f);
    glVertex2f(x + width + 1.5f, y + height + 1.5f);
    glVertex2f(x - 1.5f, y + height + 1.5f);
    glEnd();

    // 2. Glass Panes
    glColor3fv(COLOR_WINDOW_BLUE);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // 3. Middle Window Divider
    glColor3f(0.20f, 0.20f, 0.25f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    glVertex2f(x + (width / 2.0f), y);
    glVertex2f(x + (width / 2.0f), y + height);
    glEnd();
}

// Helper function to draw realistic balcony with 3D floor projection
void drawRealisticBalcony(float startX, float endX, float balconyY)
{
    // 1. Under-Balcony Shadow
    glColor3f(0.35f, 0.35f, 0.30f);
    glBegin(GL_QUADS);
    glVertex2f(startX - 1.5f, balconyY + 5.0f);
    glVertex2f(endX + 1.5f, balconyY + 5.0f);
    glVertex2f(endX + 1.5f, balconyY + 9.0f);
    glVertex2f(startX - 1.5f, balconyY + 9.0f);
    glEnd();

    // 2. Main Concrete Balcony Base Extension
    glColor3f(0.78f, 0.78f, 0.80f);
    glBegin(GL_QUADS);
    glVertex2f(startX - 5.0f, balconyY);
    glVertex2f(endX + 5.0f, balconyY);
    glVertex2f(endX + 5.0f, balconyY + 5.0f);
    glVertex2f(startX - 5.0f, balconyY + 5.0f);
    glEnd();

    // 3. Concrete Slab Edge Highlight
    glColor3f(0.55f, 0.55f, 0.58f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    glVertex2f(startX - 5.0f, balconyY + 5.0f);
    glVertex2f(endX + 5.0f, balconyY + 5.0f);
    glEnd();

    // 4. Balcony Railings - Vertical Steel Grill Bars
    glColor3f(0.20f, 0.20f, 0.25f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    for (float x = startX - 2.0f; x <= endX + 2.0f; x += 8.0f)
    {
        glVertex2f(x, balconyY - 15.0f);
        glVertex2f(x, balconyY);
    }
    glEnd();

    // 5. Top Handrail
    glColor3f(0.10f, 0.10f, 0.15f);
    glLineWidth(2.5f);
    glBegin(GL_LINES);
    glVertex2f(startX - 5.0f, balconyY - 15.0f);
    glVertex2f(endX + 5.0f, balconyY - 15.0f);
    glEnd();
}

// Helper function to draw classroom entry doors for balconies
void drawBalconyDoor(float x, float y, float width, float height)
{
    // Door frame
    glColor3f(0.18f, 0.10f, 0.05f);
    glBegin(GL_QUADS);
    glVertex2f(x - 1.0f, y - 1.0f);
    glVertex2f(x + width + 1.0f, y - 1.0f);
    glVertex2f(x + width + 1.0f, y + height + 1.0f);
    glVertex2f(x - 1.0f, y + height + 1.0f);
    glEnd();

    // Wooden Panel Body
    glColor3fv(COLOR_DOOR_BROWN);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // Top Glass Vision Panel on door
    glColor3fv(COLOR_WINDOW_BLUE);
    glBegin(GL_QUADS);
    glVertex2f(x + 3.0f, y + 5.0f);
    glVertex2f(x + width - 3.0f, y + 5.0f);
    glVertex2f(x + width - 3.0f, y + 18.0f);
    glVertex2f(x + 3.0f, y + 18.0f);
    glEnd();

    // Door Handle
    glColor3fv(COLOR_SUN_YELLOW);
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    glVertex2f(x + width - 4.0f, y + 25.0f);
    glEnd();
}

// ============================================================================
// FUNCTION: drawWindow
// Description: Lifted ground floor windows MUCH HIGHER (Y value decreased in OpenGL)
// ============================================================================
void drawWindow()
{
    float itemWidth = 24.0f;
    float windowHeight = 22.0f;
    float doorHeight = 40.0f;

    // Floor Y-Positions
    float floor3Y = 265.0f;
    float floor2Y = 342.0f;
    float floor1Y = 428.0f;

    // Window Y Offset for upper balcony floors
    float windowYOffset = 6.0f;

    // Ground floor window Y position: Significantly decreased (moved UP towards roof)
    // Door is at Y = 415 to 480. We put windows at Y = 425 to 447.
    float groundWinY = 425.0f;

    // --- 1ST FLOOR (Ground Floor: Lifted UP properly away from ground) ---
    // Left Block
    for (float x = 490.0f; x <= 630.0f; x += 44.0f)
        drawSingleWindow(x, groundWinY, itemWidth, windowHeight);

    // Middle Block (Flanking the Main Entrance Door)
    drawSingleWindow(730.0f, groundWinY, itemWidth, windowHeight);
    drawSingleWindow(842.0f, groundWinY, itemWidth, windowHeight);

    // Right Block
    for (float x = 955.0f; x <= 1090.0f; x += 44.0f)
        drawSingleWindow(x, groundWinY, itemWidth, windowHeight);


    // --- 2ND & 3RD FLOORS (Balcony Floors: Door - Window - Door - Window) ---
    float upperFloorsY[] = {floor2Y, floor3Y};

    for (int f = 0; f < 2; f++)
    {
        float currentY = upperFloorsY[f];
        float winY = currentY + windowYOffset;

        // Left Section
        drawBalconyDoor(490.0f, currentY, itemWidth, doorHeight);
        drawSingleWindow(534.0f, winY, itemWidth, windowHeight);
        drawBalconyDoor(578.0f, currentY, itemWidth, doorHeight);
        drawSingleWindow(622.0f, winY, itemWidth, windowHeight);

        // Middle Section
        drawBalconyDoor(725.0f, currentY, itemWidth, doorHeight);
        drawSingleWindow(786.0f, winY, itemWidth, windowHeight);
        drawBalconyDoor(847.0f, currentY, itemWidth, doorHeight);

        // Right Section
        drawBalconyDoor(955.0f, currentY, itemWidth, doorHeight);
        drawSingleWindow(999.0f, winY, itemWidth, windowHeight);
        drawBalconyDoor(1043.0f, currentY, itemWidth, doorHeight);
        drawSingleWindow(1087.0f, winY, itemWidth, windowHeight);
    }

    // --- BALCONIES ---
    float balconyY_Floor3 = floor3Y + doorHeight; // Y = 305.0
    float balconyY_Floor2 = floor2Y + doorHeight; // Y = 382.0

    // Drawing continuous balconies in front of upper doors & windows
    drawRealisticBalcony(480.0f, 655.0f, balconyY_Floor3);
    drawRealisticBalcony(480.0f, 655.0f, balconyY_Floor2);

    drawRealisticBalcony(715.0f, 885.0f, balconyY_Floor3);
    drawRealisticBalcony(715.0f, 885.0f, balconyY_Floor2);

    drawRealisticBalcony(945.0f, 1120.0f, balconyY_Floor3);
    drawRealisticBalcony(945.0f, 1120.0f, balconyY_Floor2);
}
// ============================================================================
// FUNCTION: drawDoor
// Position: Centered at X = 775 to 825, Y = 415 to 480.
// ============================================================================
void drawDoor()
{
    // 1. Dark Wooden Door Base
    glColor3fv(COLOR_DOOR_BROWN);
    glBegin(GL_QUADS);
    glVertex2f(775.0f, 415.0f);
    glVertex2f(825.0f, 415.0f);
    glVertex2f(825.0f, 480.0f);
    glVertex2f(775.0f, 480.0f);
    glEnd();

    // 2. Door Frame Border
    glColor3f(0.20f, 0.10f, 0.05f);
    glLineWidth(2.5f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(775.0f, 415.0f);
    glVertex2f(825.0f, 415.0f);
    glVertex2f(825.0f, 480.0f);
    glVertex2f(775.0f, 480.0f);
    glEnd();

    // 3. Center Split Line
    glBegin(GL_LINES);
    glVertex2f(800.0f, 415.0f);
    glVertex2f(800.0f, 480.0f);
    glEnd();

    // 4. Handles
    glColor3fv(COLOR_SUN_YELLOW);
    glPointSize(4.0f);
    glBegin(GL_POINTS);
    glVertex2f(794.0f, 450.0f);
    glVertex2f(806.0f, 450.0f);
    glEnd();
}

// ============================================================================
// FUNCTION: drawClock
// Position: Center at (X = 800, Y = 200), Radius = 13.
// ============================================================================
void drawClock()
{
    float cx = 800.0f;
    float cy = 200.0f;
    float r = 13.0f;
    int segments = 40;

    // 1. Clock Face
    glColor3fv(COLOR_WHITE);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++)
    {
        float angle = i * 2.0f * 3.14159f / segments;
        glVertex2f(cx + (r * cos(angle)), cy + (r * sin(angle)));
    }
    glEnd();

    // 2. Outer Rim
    glColor3fv(COLOR_BLACK);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++)
    {
        float angle = i * 2.0f * 3.14159f / segments;
        glVertex2f(cx + (r * cos(angle)), cy + (r * sin(angle)));
    }
    glEnd();

    // 3. Time calculation
    time_t rawTime = time(NULL);
    struct tm* timeInfo = localtime(&rawTime);

    int hours = timeInfo->tm_hour % 12;
    int minutes = timeInfo->tm_min;
    int seconds = timeInfo->tm_sec;

    float minuteAngle = (minutes + seconds / 60.0f) * (2.0f * 3.14159f / 60.0f);
    float hourAngle = (hours + minutes / 60.0f) * (2.0f * 3.14159f / 12.0f);

    float hourHandLen = 6.0f;
    float minuteHandLen = 9.0f;

    float hourX = cx + hourHandLen * sin(hourAngle);
    float hourY = cy - hourHandLen * cos(hourAngle);

    float minX = cx + minuteHandLen * sin(minuteAngle);
    float minY = cy - minuteHandLen * cos(minuteAngle);

    // 4. Render Hands
    glColor3fv(COLOR_BLACK);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(hourX, hourY);

    glVertex2f(cx, cy);
    glVertex2f(minX, minY);
    glEnd();
}

// ============================================================================
// FUNCTION: drawFlagPole
// Position: Base at (X = 745, Y = 480), Top at (X = 745, Y = 275).
// ============================================================================
void drawFlagPole()
{
    // Pedestal
    glColor3fv(COLOR_ROOF_GRAY);
    glBegin(GL_QUADS);
    glVertex2f(733.0f, 472.0f);
    glVertex2f(757.0f, 472.0f);
    glVertex2f(757.0f, 480.0f);
    glVertex2f(733.0f, 480.0f);
    glEnd();

    // Metallic Pole
    glColor3fv(COLOR_POLE_GRAY);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(745.0f, 472.0f);
    glVertex2f(745.0f, 275.0f);
    glEnd();

    // Golden Knob
    glColor3fv(COLOR_SUN_YELLOW);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(745.0f, 273.0f);
    glEnd();
}

// ============================================================================
// FUNCTION: drawBangladeshFlag
// ============================================================================
void drawBangladeshFlag()
{
    float poleX = 745.0f;
    float topY = 275.0f;
    float flagW = 55.0f;
    float flagH = 33.0f;

    float time = glutGet(GLUT_ELAPSED_TIME) * 0.005f;
    flagWaveOffset = sin(time) * 4.5f;

    // Green Flag Body
    glColor3fv(COLOR_FLAG_GREEN);
    glBegin(GL_QUADS);
    glVertex2f(poleX, topY);
    glVertex2f(poleX + flagW + flagWaveOffset, topY);
    glVertex2f(poleX + flagW + flagWaveOffset, topY + flagH);
    glVertex2f(poleX, topY + flagH);
    glEnd();

    // Red Disc
    glColor3fv(COLOR_FLAG_RED);
    float cx = poleX + (flagW * 0.45f) + (flagWaveOffset * 0.5f);
    float cy = topY + (flagH * 0.5f);
    float r = 10.0f;
    int segments = 30;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++)
    {
        float angle = i * 2.0f * 3.14159f / segments;
        glVertex2f(cx + (r * cos(angle)), cy + (r * sin(angle)));
    }
    glEnd();
}

// ============================================================================
// FUNCTION: drawRoofBanner
// Position: Centered below clock (X = 680 to 920, Y = 228 to 244).
// ============================================================================
void drawRoofBanner()
{
    // Banner Background Board
    glColor3fv(COLOR_WHITE);
    glBegin(GL_QUADS);
    glVertex2f(680.0f, 228.0f);
    glVertex2f(920.0f, 228.0f);
    glVertex2f(920.0f, 244.0f);
    glVertex2f(680.0f, 244.0f);
    glEnd();

    // Green Border
    glColor3fv(COLOR_FLAG_GREEN);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(680.0f, 228.0f);
    glVertex2f(920.0f, 228.0f);
    glVertex2f(920.0f, 244.0f);
    glVertex2f(680.0f, 244.0f);
    glEnd();
}

/* ---- Campus / Garden Layer ---- */
// ============================================================================
// FUNCTION: drawShaheedMinar
// Description: Scaled up for better visibility and shifted right to create a
//              natural gap between the school building and the monument.
// Position: Center X = 1320.0f, Base Y = 480.0f
// ============================================================================
void drawShaheedMinar()
{
    float cx = 1320.0f;          // Shifted right to create gap from school
    float baseY = 480.0f;       // Same Y-axis line as school base
    float scale = 0.58f;        // Increased size for better visual presence

    #define SH_Y(offset) (baseY - ((offset) * scale))
    #define SH_X(offset) (cx + ((offset) * scale))

    // ---------------------------------------------------------
    // 1. Red Sun Disc (Behind Center Columns)
    // ---------------------------------------------------------
    glColor3fv(COLOR_FLAG_RED);
    float sunX = SH_X(0.0f);
    float sunY = SH_Y(110.0f);
    float sunR = 40.0f * scale;
    int segments = 40;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(sunX, sunY);
    for (int i = 0; i <= segments; i++)
    {
        float angle = i * 2.0f * 3.14159f / segments;
        glVertex2f(sunX + (sunR * cos(angle)), sunY + (sunR * sin(angle)));
    }
    glEnd();

    // ---------------------------------------------------------
    // 2. Pillars Structure (Light Gray Fill)
    // ---------------------------------------------------------
    glColor3f(0.88f, 0.88f, 0.90f);

    // --- A. Center Angled Column ---
    glBegin(GL_QUADS);
    glVertex2f(SH_X(-26.0f), SH_Y(10.0f));
    glVertex2f(SH_X(26.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(22.0f),  SH_Y(110.0f));
    glVertex2f(SH_X(-22.0f), SH_Y(110.0f));
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(SH_X(-22.0f), SH_Y(110.0f));
    glVertex2f(SH_X(22.0f),  SH_Y(110.0f));
    glVertex2f(SH_X(58.0f),  SH_Y(190.0f));
    glVertex2f(SH_X(18.0f),  SH_Y(190.0f));
    glEnd();

    // --- B. Medium Side Columns ---
    glBegin(GL_QUADS);
    glVertex2f(SH_X(-62.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-34.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-34.0f), SH_Y(115.0f));
    glVertex2f(SH_X(-62.0f), SH_Y(115.0f));
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(SH_X(34.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(62.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(62.0f),  SH_Y(115.0f));
    glVertex2f(SH_X(34.0f),  SH_Y(115.0f));
    glEnd();

    // --- C. Small Side Columns ---
    glBegin(GL_QUADS);
    glVertex2f(SH_X(-94.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-70.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-70.0f), SH_Y(85.0f));
    glVertex2f(SH_X(-94.0f), SH_Y(85.0f));
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(SH_X(70.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(94.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(94.0f),  SH_Y(85.0f));
    glVertex2f(SH_X(70.0f),  SH_Y(85.0f));
    glEnd();

    // ---------------------------------------------------------
    // 3. Black Outlines & Grill Lines
    // ---------------------------------------------------------
    glColor3f(0.15f, 0.15f, 0.20f);
    glLineWidth(1.8f);

    // Center Outer & Inner Frames
    glBegin(GL_LINE_LOOP);
    glVertex2f(SH_X(-26.0f), SH_Y(10.0f));
    glVertex2f(SH_X(26.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(22.0f),  SH_Y(110.0f));
    glVertex2f(SH_X(58.0f),  SH_Y(190.0f));
    glVertex2f(SH_X(18.0f),  SH_Y(190.0f));
    glVertex2f(SH_X(-22.0f), SH_Y(110.0f));
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(SH_X(-18.0f), SH_Y(18.0f));
    glVertex2f(SH_X(18.0f),  SH_Y(18.0f));
    glVertex2f(SH_X(15.0f),  SH_Y(105.0f));
    glVertex2f(SH_X(48.0f),  SH_Y(180.0f));
    glVertex2f(SH_X(24.0f),  SH_Y(180.0f));
    glVertex2f(SH_X(-15.0f), SH_Y(105.0f));
    glEnd();

    // Medium Outer & Inner Frames
    glBegin(GL_LINE_LOOP);
    glVertex2f(SH_X(-62.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-34.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-34.0f), SH_Y(115.0f));
    glVertex2f(SH_X(-62.0f), SH_Y(115.0f));
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(SH_X(-56.0f), SH_Y(18.0f));
    glVertex2f(SH_X(-40.0f), SH_Y(18.0f));
    glVertex2f(SH_X(-40.0f), SH_Y(107.0f));
    glVertex2f(SH_X(-56.0f), SH_Y(107.0f));
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(SH_X(34.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(62.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(62.0f),  SH_Y(115.0f));
    glVertex2f(SH_X(34.0f),  SH_Y(115.0f));
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(SH_X(40.0f),  SH_Y(18.0f));
    glVertex2f(SH_X(56.0f),  SH_Y(18.0f));
    glVertex2f(SH_X(56.0f),  SH_Y(107.0f));
    glVertex2f(SH_X(40.0f),  SH_Y(107.0f));
    glEnd();

    // Small Outer & Inner Frames
    glBegin(GL_LINE_LOOP);
    glVertex2f(SH_X(-94.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-70.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-70.0f), SH_Y(85.0f));
    glVertex2f(SH_X(-94.0f), SH_Y(85.0f));
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(SH_X(-88.0f), SH_Y(18.0f));
    glVertex2f(SH_X(-76.0f), SH_Y(18.0f));
    glVertex2f(SH_X(-76.0f), SH_Y(77.0f));
    glVertex2f(SH_X(-88.0f), SH_Y(77.0f));
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(SH_X(70.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(94.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(94.0f),  SH_Y(85.0f));
    glVertex2f(SH_X(70.0f),  SH_Y(85.0f));
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(SH_X(76.0f),  SH_Y(18.0f));
    glVertex2f(SH_X(88.0f),  SH_Y(18.0f));
    glVertex2f(SH_X(88.0f),  SH_Y(77.0f));
    glVertex2f(SH_X(76.0f),  SH_Y(77.0f));
    glEnd();

    // Vertical Steel Grills
    glLineWidth(1.2f);
    glBegin(GL_LINES);
    glVertex2f(SH_X(-6.0f), SH_Y(18.0f));  glVertex2f(SH_X(-5.0f), SH_Y(105.0f));
    glVertex2f(SH_X(6.0f),  SH_Y(18.0f));  glVertex2f(SH_X(5.0f),  SH_Y(105.0f));
    glVertex2f(SH_X(-5.0f), SH_Y(105.0f)); glVertex2f(SH_X(30.0f), SH_Y(180.0f));
    glVertex2f(SH_X(5.0f),  SH_Y(105.0f)); glVertex2f(SH_X(40.0f), SH_Y(180.0f));

    glVertex2f(SH_X(-48.0f), SH_Y(18.0f)); glVertex2f(SH_X(-48.0f), SH_Y(107.0f));
    glVertex2f(SH_X(48.0f),  SH_Y(18.0f)); glVertex2f(SH_X(48.0f),  SH_Y(107.0f));

    glVertex2f(SH_X(-82.0f), SH_Y(18.0f)); glVertex2f(SH_X(-82.0f), SH_Y(77.0f));
    glVertex2f(SH_X(82.0f),  SH_Y(18.0f)); glVertex2f(SH_X(82.0f),  SH_Y(77.0f));
    glEnd();

    // ---------------------------------------------------------
    // 4. Pedestal Base Steps
    // ---------------------------------------------------------
    float stepWidths[] = { 108.0f, 118.0f, 128.0f, 138.0f };
    float stepY_Start[] = { 30.0f, 20.0f, 10.0f, 0.0f };
    float stepY_End[]   = { 20.0f, 10.0f, 0.0f, -10.0f };

    for (int i = 0; i < 4; i++)
    {
        // Step Fill
        glColor3f(0.92f - (i * 0.02f), 0.92f - (i * 0.02f), 0.94f - (i * 0.02f));
        glBegin(GL_QUADS);
        glVertex2f(SH_X(-stepWidths[i]), SH_Y(stepY_Start[i]));
        glVertex2f(SH_X(stepWidths[i]),  SH_Y(stepY_Start[i]));
        glVertex2f(SH_X(stepWidths[i]),  SH_Y(stepY_End[i]));
        glVertex2f(SH_X(-stepWidths[i]), SH_Y(stepY_End[i]));
        glEnd();

        // Step Outline
        glColor3f(0.15f, 0.15f, 0.20f);
        glLineWidth(1.5f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(SH_X(-stepWidths[i]), SH_Y(stepY_Start[i]));
        glVertex2f(SH_X(stepWidths[i]),  SH_Y(stepY_Start[i]));
        glVertex2f(SH_X(stepWidths[i]),  SH_Y(stepY_End[i]));
        glVertex2f(SH_X(-stepWidths[i]), SH_Y(stepY_End[i]));
        glEnd();
    }

    #undef SH_Y
    #undef SH_X
}
/*
// ============================================================================
// FUNCTION: drawShaheedMinar
// Description: Renders an accurate, iconic Shaheed Minar structure on campus.
// Position: Grounded on campus right wing (X = 1400 center, Y = 380 to 550).
// ============================================================================
void drawShaheedMinar() {
    float cx = 1400.0f; // Center X of Shaheed Minar

    // ---------------------------------------------------------
    // 1. Red Sun Disc (Behind Central Column)
    // ---------------------------------------------------------
    glColor3fv(COLOR_FLAG_RED);
    float sunX = cx;
    float sunY = 430.0f;
    float sunR = 32.0f;
    int segments = 40;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(sunX, sunY);
        for (int i = 0; i <= segments; i++) {
            float angle = i * 2.0f * 3.14159f / segments;
            glVertex2f(sunX + (sunR * cos(angle)), sunY + (sunR * sin(angle)));
        }
    glEnd();

    // ---------------------------------------------------------
    // 2. Concrete Base Pedestal (3 Steps)
    // ---------------------------------------------------------
    glColor3f(0.80f, 0.80f, 0.82f); // Light Marble White/Gray

    // Bottom Step
    glBegin(GL_QUADS);
        glVertex2f(cx - 90.0f, 535.0f);
        glVertex2f(cx + 90.0f, 535.0f);
        glVertex2f(cx + 90.0f, 550.0f);
        glVertex2f(cx - 90.0f, 550.0f);
    glEnd();

    // Middle Step
    glBegin(GL_QUADS);
        glVertex2f(cx - 75.0f, 520.0f);
        glVertex2f(cx + 75.0f, 520.0f);
        glVertex2f(cx + 75.0f, 535.0f);
        glVertex2f(cx - 75.0f, 535.0f);
    glEnd();

    // Top Step
    glBegin(GL_QUADS);
        glVertex2f(cx - 60.0f, 510.0f);
        glVertex2f(cx + 60.0f, 510.0f);
        glVertex2f(cx + 60.0f, 520.0f);
        glVertex2f(cx - 60.0f, 520.0f);
    glEnd();

    // Step Lines / Borders
    glColor3f(0.50f, 0.50f, 0.55f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2f(cx - 90.0f, 535.0f); glVertex2f(cx + 90.0f, 535.0f);
        glVertex2f(cx - 75.0f, 520.0f); glVertex2f(cx + 75.0f, 520.0f);
    glEnd();

    // ---------------------------------------------------------
    // 3. Vertical Columns (Marble White Pillars)
    // ---------------------------------------------------------
    glColor3f(0.92f, 0.92f, 0.95f); // Pure White Marble

    // --- A. Central Tall Column (With Backward Tilt Top) ---
    glBegin(GL_QUADS);
        glVertex2f(cx - 15.0f, 380.0f);
        glVertex2f(cx + 15.0f, 380.0f);
        glVertex2f(cx + 15.0f, 510.0f);
        glVertex2f(cx - 15.0f, 510.0f);
    glEnd();

    // Central Top Backward Slant Frame
    glColor3f(0.85f, 0.85f, 0.88f);
    glBegin(GL_QUADS);
        glVertex2f(cx - 20.0f, 365.0f);
        glVertex2f(cx + 20.0f, 365.0f);
        glVertex2f(cx + 15.0f, 380.0f);
        glVertex2f(cx - 15.0f, 380.0f);
    glEnd();

    // --- B. Inner Side Columns (Medium Height) ---
    glColor3f(0.90f, 0.90f, 0.93f);
    // Left-Inner
    glBegin(GL_QUADS);
        glVertex2f(cx - 38.0f, 420.0f);
        glVertex2f(cx - 22.0f, 420.0f);
        glVertex2f(cx - 22.0f, 510.0f);
        glVertex2f(cx - 38.0f, 510.0f);
    glEnd();
    // Right-Inner
    glBegin(GL_QUADS);
        glVertex2f(cx + 22.0f, 420.0f);
        glVertex2f(cx + 38.0f, 420.0f);
        glVertex2f(cx + 38.0f, 510.0f);
        glVertex2f(cx + 22.0f, 510.0f);
    glEnd();

    // --- C. Outer Side Columns (Short Height) ---
    glColor3f(0.88f, 0.88f, 0.91f);
    // Left-Outer
    glBegin(GL_QUADS);
        glVertex2f(cx - 58.0f, 450.0f);
        glVertex2f(cx - 44.0f, 450.0f);
        glVertex2f(cx - 44.0f, 510.0f);
        glVertex2f(cx - 58.0f, 510.0f);
    glEnd();
    // Right-Outer
    glBegin(GL_QUADS);
        glVertex2f(cx + 44.0f, 450.0f);
        glVertex2f(cx + 58.0f, 450.0f);
        glVertex2f(cx + 58.0f, 510.0f);
        glVertex2f(cx + 44.0f, 510.0f);
    glEnd();

    // ---------------------------------------------------------
    // 4. Pillar Black Outline / Grid Lines (For Sharpness)
    // ---------------------------------------------------------
    glColor3f(0.30f, 0.30f, 0.35f);
    glLineWidth(1.5f);

    // Central Pillar Lines
    glBegin(GL_LINE_LOOP);
        glVertex2f(cx - 15.0f, 380.0f);
        glVertex2f(cx + 15.0f, 380.0f);
        glVertex2f(cx + 15.0f, 510.0f);
        glVertex2f(cx - 15.0f, 510.0f);
    glEnd();

    // Inner Pillars Lines
    glBegin(GL_LINE_LOOP);
        glVertex2f(cx - 38.0f, 420.0f); glVertex2f(cx - 22.0f, 420.0f);
        glVertex2f(cx - 22.0f, 510.0f); glVertex2f(cx - 38.0f, 510.0f);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(cx + 22.0f, 420.0f); glVertex2f(cx + 38.0f, 420.0f);
        glVertex2f(cx + 38.0f, 510.0f); glVertex2f(cx + 22.0f, 510.0f);
    glEnd();

    // Outer Pillars Lines
    glBegin(GL_LINE_LOOP);
        glVertex2f(cx - 58.0f, 450.0f); glVertex2f(cx - 44.0f, 450.0f);
        glVertex2f(cx - 44.0f, 510.0f); glVertex2f(cx - 58.0f, 510.0f);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(cx + 44.0f, 450.0f); glVertex2f(cx + 58.0f, 450.0f);
        glVertex2f(cx + 58.0f, 510.0f); glVertex2f(cx + 44.0f, 510.0f);
    glEnd();
}
*/
// ============================================================================
// FUNCTION: drawFlower
// Scaled flower anchored inside bed
// ============================================================================
void drawFlower(float x, float y, float r, const float petalColor[3])
{
    float stemHeight = 6.0f;
    float flowerY = y + stemHeight;
    int segments = 10;

    // Stem
    glColor3f(0.15f, 0.45f, 0.15f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x, flowerY);
    glEnd();
    glLineWidth(1.0f);

    // Petals
    glColor3fv(petalColor);
    for (int i = 0; i < 5; i++)
    {
        float angle = i * 2.0f * 3.14159f / 5.0f;
        float px = x + cos(angle) * r;
        float py = flowerY + sin(angle) * r;

        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(px, py);
            for (int j = 0; j <= segments; j++)
            {
                float a = j * 2.0f * 3.14159f / segments;
                glVertex2f(px + (r * 0.6f * cos(a)), py + (r * 0.6f * sin(a)));
            }
        glEnd();
    }

    // Center
    glColor3f(1.0f, 0.9f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, flowerY);
        for (int i = 0; i <= segments; i++)
        {
            float angle = i * 2.0f * 3.14159f / segments;
            glVertex2f(x + (r * 0.4f * cos(angle)), flowerY + (r * 0.4f * sin(angle)));
        }
    glEnd();
}

// ============================================================================
// FUNCTION: drawBush
// Rounded green bush cap standing UPWARDS on top of garden bed
// ============================================================================
void drawBush(float x, float y, float rx, float ry)
{
    int segments = 20;

    // Outer Dark Green Layer (Curves UPWARDS: y - sin)
    glColor3f(0.10f, 0.38f, 0.10f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= segments; i++)
        {
            float angle = i * 3.14159f / segments;
            glVertex2f(x + (rx * cos(angle)), y - (ry * sin(angle)));
        }
    glEnd();

    // Inner Highlight Light Green Layer
    glColor3f(0.25f, 0.60f, 0.20f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= segments; i++)
        {
            float angle = i * 3.14159f / segments;
            glVertex2f(x + ((rx - 2.0f) * cos(angle)), y - ((ry - 2.0f) * sin(angle)));
        }
    glEnd();
}

// ============================================================================
// FUNCTION: drawGarden
// Aligned strictly between School's Red Accent Pillars
// ============================================================================
void drawGarden()
{
    float schoolBottomY = 480.0f; // Bottom foundation level of school
    float bedThickness = 10.0f;
    float bedBottomY = schoolBottomY + bedThickness;

    // ---------------------------------------------------------
    // 1. Soil Beds (Red Pillar to Red Pillar)
    // ---------------------------------------------------------
    glColor3f(0.35f, 0.22f, 0.12f); // Dark Brown Soil

    // Left Bed: From 1st Pillar (450.0f) to 2nd Pillar (682.0f)
    glBegin(GL_QUADS);
        glVertex2f(450.0f, schoolBottomY);
        glVertex2f(682.0f, schoolBottomY);
        glVertex2f(682.0f, bedBottomY);
        glVertex2f(450.0f, bedBottomY);
    glEnd();

    // Right Bed: From 3rd Pillar (918.0f) to 4th Pillar (1150.0f)
    glBegin(GL_QUADS);
        glVertex2f(918.0f,  schoolBottomY);
        glVertex2f(1150.0f, schoolBottomY);
        glVertex2f(1150.0f, bedBottomY);
        glVertex2f(918.0f,  bedBottomY);
    glEnd();

    // ---------------------------------------------------------
    // 2. Concrete Border Frames
    // ---------------------------------------------------------
    glColor3f(0.80f, 0.80f, 0.82f);
    glLineWidth(2.0f);

    // Left Frame
    glBegin(GL_LINE_LOOP);
        glVertex2f(450.0f, schoolBottomY);
        glVertex2f(682.0f, schoolBottomY);
        glVertex2f(682.0f, bedBottomY);
        glVertex2f(450.0f, bedBottomY);
    glEnd();

    // Right Frame
    glBegin(GL_LINE_LOOP);
        glVertex2f(918.0f,  schoolBottomY);
        glVertex2f(1150.0f, schoolBottomY);
        glVertex2f(1150.0f, bedBottomY);
        glVertex2f(918.0f,  bedBottomY);
    glEnd();
    glLineWidth(1.0f);

    // ---------------------------------------------------------
    // 3. Side Bushes at Bed Ends (Fitted inside pillar boundaries)
    // ---------------------------------------------------------
    drawBush(450.0f,  schoolBottomY, 10.0f, 8.0f);
    drawBush(682.0f,  schoolBottomY, 10.0f, 8.0f);
    drawBush(918.0f,  schoolBottomY, 10.0f, 8.0f);
    drawBush(1150.0f, schoolBottomY, 10.0f, 8.0f);

    // ---------------------------------------------------------
    // 4. Flowers Distribution
    // ---------------------------------------------------------
    static const float RED_PETAL[3]    = {0.95f, 0.15f, 0.20f};
    static const float YELLOW_PETAL[3] = {0.98f, 0.85f, 0.10f};
    static const float PINK_PETAL[3]   = {0.95f, 0.40f, 0.70f};
    static const float ORANGE_PETAL[3] = {0.98f, 0.50f, 0.10f};

    float plantY = schoolBottomY + 1.0f;

    // Left Bed Flowers (Span 450 to 682)
    for (int i = 0; i < 7; i++)
    {
        float fx = 470.0f + (i * 32.0f);
        const float* col = (i % 4 == 0) ? RED_PETAL : (i % 4 == 1) ? YELLOW_PETAL : (i % 4 == 2) ? PINK_PETAL : ORANGE_PETAL;
        drawFlower(fx, plantY, 3.5f, col);
    }

    // Right Bed Flowers (Span 918 to 1150)
    for (int i = 0; i < 7; i++)
    {
        float fx = 938.0f + (i * 32.0f);
        const float* col = (i % 4 == 0) ? ORANGE_PETAL : (i % 4 == 1) ? PINK_PETAL : (i % 4 == 2) ? YELLOW_PETAL : RED_PETAL;
        drawFlower(fx, plantY, 3.5f, col);
    }
}
#include <GL/glut.h>
#include <cmath>

// ============================================================================
// BACKGROUND TREES (MOVED FAR BACK & DEEP COLOR TONE)
// ============================================================================

// ----------------------------------------------------------------------------
// 1. IMPROVED NORMAL LEAFY TREE
// ----------------------------------------------------------------------------
void drawSingleTree(float x, float y, float scale)
{
    float trunkHeight = 85.0f * scale;
    float topY = y - trunkHeight;

    // Dark Bark Trunk
    glColor3f(0.25f, 0.14f, 0.06f);
    glBegin(GL_POLYGON);
        glVertex2f(x - (9.0f * scale), y);
        glVertex2f(x + (9.0f * scale), y);
        glVertex2f(x + (6.0f * scale), topY);
        glVertex2f(x - (6.0f * scale), topY);
    glEnd();

    // Trunk Bark Lines
    glColor3f(0.15f, 0.08f, 0.03f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2f(x - (3.0f * scale), y - (10.0f * scale));
        glVertex2f(x - (2.0f * scale), y - (50.0f * scale));
        glVertex2f(x + (3.0f * scale), y - (20.0f * scale));
        glVertex2f(x + (2.0f * scale), y - (60.0f * scale));
    glEnd();
    glLineWidth(1.0f);

    // Multilayered Leaf Clusters for Better Visual Depth
    int segments = 25;
    float clusters[6][3] =
    {
        {x - (24.0f * scale), topY - (8.0f * scale),  26.0f * scale},
        {x + (24.0f * scale), topY - (8.0f * scale),  26.0f * scale},
        {x - (16.0f * scale), topY - (28.0f * scale), 30.0f * scale},
        {x + (16.0f * scale), topY - (28.0f * scale), 30.0f * scale},
        {x,                   topY - (48.0f * scale), 36.0f * scale},
        {x,                   topY - (20.0f * scale), 32.0f * scale}
    };

    // Layer 1: Deep Shadow Base
    glColor3f(0.03f, 0.22f, 0.06f);
    for (int c = 0; c < 6; c++)
    {
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(clusters[c][0], clusters[c][1]);
            for (int i = 0; i <= segments; i++)
            {
                float angle = i * 2.0f * 3.14159f / segments;
                glVertex2f(clusters[c][0] + (clusters[c][2] * cos(angle)),
                           clusters[c][1] + (clusters[c][2] * sin(angle)));
            }
        glEnd();
    }

    // Layer 2: Deeper Forest Green Highlight
    glColor3f(0.07f, 0.35f, 0.10f);
    for (int c = 0; c < 6; c++)
    {
        float cx = clusters[c][0];
        float cy = clusters[c][1] + (2.0f * scale);
        float r  = clusters[c][2] - (3.0f * scale);

        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(cx, cy);
            for (int i = 0; i <= segments; i++)
            {
                float angle = i * 2.0f * 3.14159f / segments;
                glVertex2f(cx + (r * cos(angle)), cy + (r * sin(angle)));
            }
        glEnd();
    }
}

void drawTree()
{
    // Placed far back behind the wall/fence level
    drawSingleTree(1220.0f, 405.0f, 0.85f);
    drawSingleTree(1650.0f, 410.0f, 0.90f);
}

// ----------------------------------------------------------------------------
// 2. PALM TREE
// ----------------------------------------------------------------------------
void drawSinglePalmTree(float startX, float startY, float height)
{
    glColor3f(0.35f, 0.22f, 0.12f);
    int segments = 8;
    float currentX = startX;
    float currentY = startY;
    float segmentH = height / segments;

    for (int i = 0; i < segments; i++)
    {
        float nextX = currentX + (i * 0.8f);
        float nextY = currentY - segmentH;
        float w1 = 11.0f - (i * 0.5f);
        float w2 = 11.0f - ((i + 1) * 0.5f);

        glBegin(GL_QUADS);
            glVertex2f(currentX - w1, currentY);
            glVertex2f(currentX + w1, currentY);
            glVertex2f(nextX + w2, nextY);
            glVertex2f(nextX - w2, nextY);
        glEnd();

        glColor3f(0.22f, 0.12f, 0.06f);
        glLineWidth(1.5f);
        glBegin(GL_LINES);
            glVertex2f(currentX - w1, currentY);
            glVertex2f(currentX + w1, currentY);
        glEnd();

        glColor3f(0.35f, 0.22f, 0.12f);
        currentX = nextX;
        currentY = nextY;
    }

    float topX = currentX;
    float topY = currentY;

    // Dark Coconuts
    glColor3f(0.12f, 0.30f, 0.05f);
    int circleSegs = 15;
    float coconutCoords[3][2] = {
        {topX - 5.0f, topY + 4.0f},
        {topX + 5.0f, topY + 4.0f},
        {topX,        topY + 8.0f}
    };
    for (int c = 0; c < 3; c++)
    {
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(coconutCoords[c][0], coconutCoords[c][1]);
            for (int i = 0; i <= circleSegs; i++)
            {
                float angle = i * 2.0f * 3.14159f / circleSegs;
                glVertex2f(coconutCoords[c][0] + (5.5f * cos(angle)),
                           coconutCoords[c][1] + (5.5f * sin(angle)));
            }
        glEnd();
    }

    // Palm Leaves (Darker Green Tone)
    glColor3f(0.06f, 0.38f, 0.10f);
    glLineWidth(2.5f);
    float leafAngles[] = { -160.0f, -120.0f, -70.0f, -20.0f, 20.0f, 70.0f, 120.0f, 160.0f };

    for (int f = 0; f < 8; f++)
    {
        float rad = leafAngles[f] * 3.14159f / 180.0f;
        float leafLen = 65.0f;
        float endX = topX + (leafLen * cos(rad));
        float endY = topY - (leafLen * sin(rad)) + (abs((int)leafAngles[f]) * 0.15f);

        glBegin(GL_LINES);
            glVertex2f(topX, topY);
            glVertex2f(endX, endY);
        glEnd();

        int leaflets = 10;
        for (int j = 1; j <= leaflets; j++)
        {
            float t = (float)j / leaflets;
            float lx = topX + (endX - topX) * t;
            float ly = topY + (endY - topY) * t;

            glBegin(GL_LINES);
                glVertex2f(lx, ly);
                glVertex2f(lx - 7.0f, ly + 10.0f);
                glVertex2f(lx, ly);
                glVertex2f(lx + 7.0f, ly + 10.0f);
            glEnd();
        }
    }
    glLineWidth(1.0f);
}

void drawPalmTree()
{
    // Placed at the far right corner gap
    drawSinglePalmTree(1730.0f, 410.0f, 145.0f);
}

// ----------------------------------------------------------------------------
// 3. MANGO TREE
// ----------------------------------------------------------------------------
void drawSingleMangoTree(float x, float y, float scale)
{
    // Trunk
    glColor3f(0.28f, 0.16f, 0.08f);
    glBegin(GL_POLYGON);
        glVertex2f(x - (10.0f * scale), y);
        glVertex2f(x + (10.0f * scale), y);
        glVertex2f(x + (7.0f * scale), y - (95.0f * scale));
        glVertex2f(x - (7.0f * scale), y - (95.0f * scale));
    glEnd();

    float topY = y - (95.0f * scale);
    int segments = 25;

    float clusters[4][3] = {
        {x - (24.0f * scale), topY - (10.0f * scale), 34.0f * scale},
        {x + (24.0f * scale), topY - (10.0f * scale), 34.0f * scale},
        {x,                   topY - (38.0f * scale), 40.0f * scale},
        {x,                   topY - (15.0f * scale), 36.0f * scale}
    };

    // Dark Canopy
    glColor3f(0.02f, 0.20f, 0.05f);
    for (int c = 0; c < 4; c++)
    {
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(clusters[c][0], clusters[c][1]);
            for (int i = 0; i <= segments; i++)
            {
                float angle = i * 2.0f * 3.14159f / segments;
                glVertex2f(clusters[c][0] + (clusters[c][2] * cos(angle)),
                           clusters[c][1] + (clusters[c][2] * sin(angle)));
            }
        glEnd();
    }

    // Deeper Highlight
    glColor3f(0.06f, 0.32f, 0.09f);
    for (int c = 0; c < 4; c++)
    {
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(clusters[c][0], clusters[c][1] - (3.0f * scale));
            for (int i = 0; i <= segments; i++)
            {
                float angle = i * 2.0f * 3.14159f / segments;
                glVertex2f(clusters[c][0] + ((clusters[c][2] - 4.0f) * cos(angle)),
                           clusters[c][1] - (3.0f * scale) + ((clusters[c][2] - 4.0f) * sin(angle)));
            }
        glEnd();
    }

    // Mangoes
    float mangoes[5][2] = {
        {x - 18.0f * scale, topY - 5.0f * scale},
        {x - 8.0f  * scale, topY - 28.0f * scale},
        {x + 15.0f * scale, topY - 12.0f * scale},
        {x + 22.0f * scale, topY + 5.0f * scale},
        {x + 4.0f  * scale, topY - 38.0f * scale}
    };

    for (int m = 0; m < 5; m++)
    {
        glColor3f(0.78f, 0.62f, 0.08f);
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(mangoes[m][0], mangoes[m][1]);
            for (int i = 0; i <= segments; i++)
            {
                float angle = i * 2.0f * 3.14159f / segments;
                glVertex2f(mangoes[m][0] + (3.5f * scale * cos(angle)),
                           mangoes[m][1] + (5.0f * scale * sin(angle)));
            }
        glEnd();
    }
}

void drawMangoTree()
{
    // Placed in the background gap between school and Minar
    drawSingleMangoTree(1320.0f, 405.0f, 0.90f);
}
// Helper for Cypress / Cone Shaped Ornamental Tree
void drawSingleDecorativeTree(float x, float y, float scale)
{
    // Small Pot / Stand Base
    glColor3f(0.60f, 0.30f, 0.15f); // Terracotta Red/Brown
    glBegin(GL_POLYGON);
    glVertex2f(x - (12.0f * scale), y);
    glVertex2f(x + (12.0f * scale), y);
    glVertex2f(x + (9.0f * scale),  y - (15.0f * scale));
    glVertex2f(x - (9.0f * scale),  y - (15.0f * scale));
    glEnd();

    // Trunk
    glColor3f(0.30f, 0.20f, 0.10f);
    glBegin(GL_QUADS);
    glVertex2f(x - (4.0f * scale), y - (15.0f * scale));
    glVertex2f(x + (4.0f * scale), y - (15.0f * scale));
    glVertex2f(x + (3.0f * scale), y - (35.0f * scale));
    glVertex2f(x - (3.0f * scale), y - (35.0f * scale));
    glEnd();

    float baseY = y - (35.0f * scale);

    // Layered Cones (Pine/Cypress Look)
    float layers[3][3] =
    {
        {45.0f * scale, 35.0f * scale, 0.12f}, // {Height, Half-Width, Color-Green-Tone}
        {40.0f * scale, 28.0f * scale, 0.16f},
        {35.0f * scale, 20.0f * scale, 0.22f}
    };

    float currY = baseY;
    for (int i = 0; i < 3; i++)
    {
        glColor3f(0.05f, layers[i][2] + 0.25f, 0.10f);
        glBegin(GL_TRIANGLES);
        glVertex2f(x - layers[i][1], currY);
        glVertex2f(x + layers[i][1], currY);
        glVertex2f(x, currY - layers[i][0]);
        glEnd();
        currY -= (layers[i][0] * 0.60f); // Overlap layers
    }
}

void drawDecorativeTree()
{
    // School-er Mukhopath / Main Entrance-er Dui Pashe
    drawSingleDecorativeTree(680.0f, 550.0f, 0.85f); // Entrance Left
    drawSingleDecorativeTree(920.0f, 550.0f, 0.85f); // Entrance Right
}
// ============================================================================
// FUNCTION: drawAssemblyGround
// Description: Fills the lower half with green grass, parade grounds, and pathways.
// ============================================================================
void drawAssemblyGround()
{
    /*
    // ---------------------------------------------------------
    // 1. Main Green Campus Field (Y: 550 to 900)
    // ---------------------------------------------------------
    glColor3f(0.25f, 0.68f, 0.25f); // Natural Grass Green
    glBegin(GL_QUADS);
        glVertex2f(0.0f,    550.0f);
        glVertex2f(1800.0f, 550.0f);
        glVertex2f(1800.0f, 900.0f);
        glVertex2f(0.0f,    900.0f);
    glEnd();

    // Field Top Border Line (Boundary between building base & grass)
    glColor3f(0.18f, 0.50f, 0.18f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex2f(0.0f,    550.0f);
        glVertex2f(1800.0f, 550.0f);
    glEnd();

    // ---------------------------------------------------------
    // 2. Central Pathway / Walkway (Paved Road in front of Main Door)
    // ---------------------------------------------------------
    glColor3f(0.82f, 0.78f, 0.72f); // Light Tan/Concrete Brick Color
    glBegin(GL_QUADS);
        glVertex2f(760.0f, 550.0f);
        glVertex2f(840.0f, 550.0f);
        glVertex2f(870.0f, 900.0f);
        glVertex2f(730.0f, 900.0f);
    glEnd();

    // Pathway Side Borders
    glColor3f(0.55f, 0.50f, 0.45f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(760.0f, 550.0f); glVertex2f(730.0f, 900.0f);
        glVertex2f(840.0f, 550.0f); glVertex2f(870.0f, 900.0f);
    glEnd();

    // Pathway Horizontal Brick Lines Texture
    glColor3f(0.72f, 0.68f, 0.62f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
        for (float py = 580.0f; py < 900.0f; py += 30.0f) {
            float ratio = (py - 550.0f) / 350.0f;
            float leftX  = 760.0f - (30.0f * ratio);
            float rightX = 840.0f + (30.0f * ratio);
            glVertex2f(leftX, py);
            glVertex2f(rightX, py);
        }
    glEnd();

    // ---------------------------------------------------------
    // 3. Assembly Ground Parade Standing Lines (White Chalk Lines)
    // ---------------------------------------------------------
    glColor3f(0.95f, 0.95f, 0.95f); // White Paint
    glLineWidth(2.0f);

    // Assembly Square Outer Margin
    glBegin(GL_LINE_LOOP);
        glVertex2f(450.0f, 620.0f);
        glVertex2f(1150.0f, 620.0f);
        glVertex2f(1150.0f, 820.0f);
        glVertex2f(450.0f, 820.0f);
    glEnd();

    // Standing Squad Lines for Students
    glBegin(GL_LINES);
        for (float lx = 520.0f; lx <= 1080.0f; lx += 70.0f) {
            // Skip the central walkway area
            if (lx > 720.0f && lx < 880.0f) continue;

            glVertex2f(lx, 640.0f);
            glVertex2f(lx, 800.0f);
        }
    glEnd();

    // ---------------------------------------------------------
    // 4. Shaheed Minar Connecting Pathway
    // ---------------------------------------------------------
    glColor3f(0.82f, 0.78f, 0.72f);
    glBegin(GL_QUADS);
        glVertex2f(1300.0f, 550.0f);
        glVertex2f(1500.0f, 550.0f);
        glVertex2f(1520.0f, 650.0f);
        glVertex2f(1280.0f, 650.0f);
    glEnd();

    glColor3f(0.55f, 0.50f, 0.45f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(1300.0f, 550.0f);
        glVertex2f(1500.0f, 550.0f);
        glVertex2f(1520.0f, 650.0f);
        glVertex2f(1280.0f, 650.0f);
    glEnd();
    */
}

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
