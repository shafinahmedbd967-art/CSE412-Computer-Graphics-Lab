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
void drawMetroRailViaductAndTrain();
void drawGround();

/* ==========================================================
   FUNCTION PROTOTYPES - SCHOOL BUILDING LAYER
   ========================================================== */
void backBoundaryWall();
void drawSchool();
void drawRoof();
void drawWindow();
void drawDoor();
void drawClock();
void drawRoofBanner();

/* ==========================================================
   FUNCTION PROTOTYPES - CAMPUS / GARDEN LAYER
   ========================================================== */
void drawShaheedMinar();
void drawFlowerTribute();
void drawGarden();
void drawFlower();
void drawBush();
void drawTree();
void drawPalmTree();
void drawMangoTree();
void drawBananaTree();
void drawRightSideForest();
void drawDecorativeTree();
void drawAssemblyGround();
void drawFlagPole();
void drawBangladeshFlag();

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
void drawSchoolBus();
void drawCNG();
void drawBRTCBus();
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
    //backBoundaryWall();
    drawMetroRailViaductAndTrain();
    drawGround();
    backBoundaryWall();
    /* ---- School Building Layer ---- */
    drawSchool();
    drawRoof();
    drawRoofBanner();
    drawWindow();
    drawDoor();
    drawClock();


    /* ---- Campus / Garden Layer ---- */
     drawRightSideForest();
    drawShaheedMinar();
    drawFlowerTribute();
    drawGarden();
    //drawFlower();
    //drawBush();
    //drawTree();
    //drawPalmTree();
    //drawMangoTree();
    //drawBananaTree();
    drawDecorativeTree();
    drawAssemblyGround();
    drawFlagPole();
    drawBangladeshFlag();
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
    drawFootpath();
    drawNoticeBoard();
    drawLampPost();
    drawBench();
    drawWaterStation();
    drawCycleParking();
    drawDustbin();

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
    drawSchoolBus();
    drawCNG();
    drawBRTCBus();
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
    int segments = 50;

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
    drawSingleCloud(150.0f + cloud1OffsetX, 110.0f, 2.70f);

    // Cloud 2 - Mid Left Sky (Fast & Tiny: 0.55x) -> NEW CLOUD 4
    drawSingleCloud(450.0f + cloud4OffsetX, 60.0f, 1.55f);

    // Cloud 3 - Center Sky (Medium Size: 0.95x)
    drawSingleCloud(750.0f + cloud2OffsetX, 95.0f, 0.95f);

    // Cloud 4 - Mid Right Sky (Higher up, Medium: 0.80x)
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
#include <GL/glut.h>
#include <math.h>

// ============================================================================
// FUNCTION: drawDistantSkyline
// Description: Renders a multi-layered distant skyline brought closer to the
//              school to eliminate awkward empty background space.
// Target Horizon Line: Y = 420 (Shifted forward for realism)
// ============================================================================
void drawDistantSkyline() {
    // ------------------------------------------------------------------------
    // 1. LAYER 1: VERY DISTANT BUILDINGS (Ultra-Soft Hazy Hues)
    // ------------------------------------------------------------------------
    glColor3f(0.72f, 0.78f, 0.84f);

    glBegin(GL_QUADS);
        // Far Building A
        glVertex2i(100, 320); glVertex2i(160, 320);
        glVertex2i(160, 420); glVertex2i(100, 420);

        // Far Building B
        glVertex2i(300, 260); glVertex2i(380, 260);
        glVertex2i(380, 420); glVertex2i(300, 420);

        // Far Building C
        glVertex2i(850, 280); glVertex2i(940, 280);
        glVertex2i(940, 420); glVertex2i(850, 420);

        // Far Building D
        glVertex2i(1420, 240); glVertex2i(1520, 240);
        glVertex2i(1520, 420); glVertex2i(1420, 420);
    glEnd();

    // ------------------------------------------------------------------------
    // 2. LAYER 2: MID-DISTANCE BUILDINGS (Sharper Silhouettes)
    // ------------------------------------------------------------------------
    glColor3f(0.58f, 0.66f, 0.74f);

    glBegin(GL_QUADS);
        // Building 1 (Left Tower)
        glVertex2i(40,  290); glVertex2i(110, 290);
        glVertex2i(110, 420); glVertex2i(40,  420);

        // Building 2 (Center-Left)
        glVertex2i(180, 270); glVertex2i(250, 270);
        glVertex2i(250, 420); glVertex2i(180, 420);

        // Building 3 (Behind School - Left)
        glVertex2i(480, 280); glVertex2i(570, 280);
        glVertex2i(570, 420); glVertex2i(480, 420);

        // Building 4 (Behind School - Right)
        glVertex2i(990, 240); glVertex2i(1070, 240);
        glVertex2i(1070, 420); glVertex2i(990, 420);

        // Building 5 (Far Right)
        glVertex2i(1350, 290); glVertex2i(1430, 290);
        glVertex2i(1430, 420); glVertex2i(1350, 420);
    glEnd();

    // Spire / Antennas
    glColor3f(0.50f, 0.58f, 0.65f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2i(1030, 240); glVertex2i(1030, 210);
        glVertex2i(215,  270); glVertex2i(215,  245);
    glEnd();

    // Reflective Windows
    glColor3f(0.85f, 0.92f, 0.98f);
    glBegin(GL_QUADS);
        for (int wy = 255; wy < 400; wy += 25) {
            glVertex2i(1010, wy); glVertex2i(1025, wy); glVertex2i(1025, wy + 12); glVertex2i(1010, wy + 12);
            glVertex2i(1035, wy); glVertex2i(1050, wy); glVertex2i(1050, wy + 12); glVertex2i(1035, wy + 12);
        }
        for (int wy = 305; wy < 400; wy += 20) {
            glVertex2i(55, wy); glVertex2i(70, wy); glVertex2i(70, wy + 10); glVertex2i(55, wy + 10);
            glVertex2i(80, wy); glVertex2i(95, wy); glVertex2i(95, wy + 10); glVertex2i(80, wy + 10);
        }
    glEnd();

    // ------------------------------------------------------------------------
    // 3. DISTANT NATURAL TREE HORIZON (Organic Foliage Brought Forward)
    // ------------------------------------------------------------------------
    // Back Tree Line
    glColor3f(0.42f, 0.58f, 0.42f);
    for (int x = -10; x <= 1610; x += 30) {
        float treeHeight = 370.0f + sin(x * 0.03f) * 12.0f;
        glBegin(GL_POLYGON);
            glVertex2i(x - 25, 420);
            glVertex2f(x - 15, treeHeight + 12.0f);
            glVertex2f(x,       treeHeight);
            glVertex2f(x + 15, treeHeight + 12.0f);
            glVertex2i(x + 25, 420);
        glEnd();
    }

    // Front Tree Line
    glColor3f(0.32f, 0.50f, 0.32f);
    for (int x = 5; x <= 1610; x += 38) {
        float treeHeight = 380.0f + cos(x * 0.025f) * 10.0f;
        glBegin(GL_POLYGON);
            glVertex2i(x - 22, 420);
            glVertex2f(x - 12, treeHeight + 10.0f);
            glVertex2f(x,       treeHeight);
            glVertex2f(x + 12, treeHeight + 10.0f);
            glVertex2i(x + 22, 420);
        glEnd();
    }
}

// ============================================================================
// FUNCTION: drawGround
// Description: Detailed realistic grass ground with organic depth & smooth shade variations
// ============================================================================
void drawGround() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 1. BASE HORIZON & FIELD GRADIENT (4-Layer Depth Blend)
    glBegin(GL_QUADS);
        // Distance Horizon (Y: 420 - 520)
        glColor3f(0.48f, 0.80f, 0.35f); // Soft Sunlight Horizon Green
        glVertex2i(0, 420);
        glVertex2i(1600, 420);
        glColor3f(0.38f, 0.72f, 0.28f);
        glVertex2i(1600, 520);
        glVertex2i(0, 520);

        // Mid-Distance Layer 1 (Y: 520 - 650)
        glColor3f(0.38f, 0.72f, 0.28f);
        glVertex2i(0, 520);
        glVertex2i(1600, 520);
        glColor3f(0.28f, 0.62f, 0.20f);
        glVertex2i(1600, 650);
        glVertex2i(0, 650);

        // Foreground Transition (Y: 650 - 780)
        glColor3f(0.28f, 0.62f, 0.20f);
        glVertex2i(0, 650);
        glVertex2i(1600, 650);
        glColor3f(0.18f, 0.50f, 0.14f);
        glVertex2i(1600, 780);
        glVertex2i(0, 780);

        // Immediate Foreground (Y: 780 - 900)
        glColor3f(0.18f, 0.50f, 0.14f);
        glVertex2i(0, 780);
        glVertex2i(1600, 780);
        glColor3f(0.10f, 0.38f, 0.08f); // Rich Deep Foreground Green
        glVertex2i(1600, 900);
        glVertex2i(0, 900);
    glEnd();

    // 2. NATURAL ORGANIC SHADE VARIATIONS (Patches of Sunlight & Density)
    // Sunlit / Lighter Grass Field Patches
    glColor4f(0.55f, 0.85f, 0.38f, 0.18f); // Soft Transparent Warm Green
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(350.0f, 550.0f);
        glVertex2f(200.0f, 500.0f);
        glVertex2f(500.0f, 480.0f);
        glVertex2f(600.0f, 580.0f);
        glVertex2f(420.0f, 620.0f);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(1200.0f, 600.0f);
        glVertex2f(1050.0f, 530.0f);
        glVertex2f(1380.0f, 520.0f);
        glVertex2f(1450.0f, 640.0f);
        glVertex2f(1300.0f, 660.0f);
    glEnd();

    // Denser / Shaded Grass Patches
    glColor4f(0.08f, 0.32f, 0.06f, 0.22f); // Deep Shadowy Green
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(800.0f, 680.0f);
        glVertex2f(600.0f, 640.0f);
        glVertex2f(750.0f, 750.0f);
        glVertex2f(1000.0f, 720.0f);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(250.0f, 760.0f);
        glVertex2f(100.0f, 700.0f);
        glVertex2f(400.0f, 720.0f);
        glVertex2f(320.0f, 820.0f);
    glEnd();

    // 3. SUBTLE DIRT/SOIL TONE BLEND (Gives realistic ground texture beneath grass)
    glColor4f(0.38f, 0.30f, 0.18f, 0.08f); // Very soft soil brown tint
    glBegin(GL_QUADS);
        glVertex2i(0, 600);
        glVertex2i(1600, 600);
        glVertex2i(1600, 900);
        glVertex2i(0, 900);
    glEnd();

    // 4. MICRO GRASS SHRED DETAILS (Tiny subtle grass tufts - minimal and non-distracting)
    glColor4f(0.22f, 0.58f, 0.18f, 0.45f);
    glLineWidth(1.2f);
    glBegin(GL_LINES);
        // Distributed tiny field micro-tufts
        for (int x = 50; x < 1550; x += 110) {
            float y = 500.0f + (x % 70);
            glVertex2f((float)x, y);
            glVertex2f((float)x - 2.0f, y - 6.0f);

            glVertex2f((float)x + 8.0f, y + 20.0f);
            glVertex2f((float)x + 11.0f, y + 12.0f);
        }
    glEnd();

    glDisable(GL_BLEND);
    glLineWidth(1.0f);
}

#include <GL/glut.h>
#include <math.h>

// ============================================================================
// FUNCTION: backBoundaryWall
// Description: Renders the classic textured concrete brick boundary wall.
// Location: Positioned behind the trees (Y = 395 to 455).
// ============================================================================
void backBoundaryWall() {
    int wallTop = 405;
    int wallBottom = 465;

    // 1. MAIN CONCRETE WALL BASE
    glBegin(GL_QUADS);
        glColor3f(0.85f, 0.84f, 0.80f); // Top highlight
        glVertex2i(0, wallTop);
        glVertex2i(1600, wallTop);

        glColor3f(0.68f, 0.67f, 0.64f); // Bottom shadow
        glVertex2i(1600, wallBottom);
        glVertex2i(0, wallBottom);
    glEnd();

    // 2. BRICK PATTERN
    glColor3f(0.60f, 0.59f, 0.56f);
    glLineWidth(1.0f);

    glBegin(GL_LINES);
    for (int y = wallTop + 12; y < wallBottom; y += 12) {
        glVertex2i(0, y);
        glVertex2i(1600, y);
    }
    glEnd();

    glBegin(GL_LINES);
    int row = 0;
    for (int y = wallTop; y < wallBottom; y += 12) {
        int xOffset = (row % 2 == 0) ? 0 : 20;
        for (int x = xOffset; x < 1600; x += 40) {
            glVertex2i(x, y);
            glVertex2i(x, y + 12);
        }
        row++;
    }
    glEnd();

    // 3. TOP COPING CAP
    glBegin(GL_QUADS);
        glColor3f(0.75f, 0.74f, 0.70f);
        glVertex2i(0, wallTop - 8);
        glVertex2i(1600, wallTop - 8);
        glVertex2i(1600, wallTop);
        glVertex2i(0, wallTop);
    glEnd();

    // 4. WALL PILLARS
    for (int x = 0; x <= 1600; x += 100) {
        glBegin(GL_QUADS);
            glColor3f(0.88f, 0.87f, 0.83f);
            glVertex2i(x - 8, wallTop - 10);
            glVertex2i(x + 2, wallTop - 10);
            glVertex2i(x + 2, wallBottom);
            glVertex2i(x - 8, wallBottom);

            glColor3f(0.72f, 0.71f, 0.67f);
            glVertex2i(x + 2, wallTop - 10);
            glVertex2i(x + 8, wallTop - 10);
            glVertex2i(x + 8, wallBottom);
            glVertex2i(x + 2, wallBottom);
        glEnd();
    }
}
#include <GL/glut.h>
#include <math.h>

// Global variable for Metro Rail Animation
float metroX = -800.0f; // Start position off-screen on the left

// ============================================================================
// FUNCTION: drawMetroRailViaductAndTrain
// Description: Renders heavy realistic flyover pillars, box girders, steel rails,
//              and an aerodynamically redesigned Dhaka Metro Rail train.
// ============================================================================
void drawMetroRailViaductAndTrain() {
    int deckTop = 330;
    int deckBottom = 352;

    // ------------------------------------------------------------------------
    // 1. HEAVY REALISTIC METRO PILLARS (Flyover Pillars)
    // ------------------------------------------------------------------------
    for (int x = 80; x <= 1600; x += 220) {
        // Main Pillar Column
        glBegin(GL_QUADS);
            // Left Highlight Side
            glColor3f(0.75f, 0.77f, 0.80f);
            glVertex2i(x - 18, deckBottom + 12);
            glVertex2i(x, deckBottom + 12);
            glVertex2i(x, 420);
            glVertex2i(x - 18, 420);

            // Right Shadow Side
            glColor3f(0.58f, 0.60f, 0.63f);
            glVertex2i(x, deckBottom + 12);
            glVertex2i(x + 18, deckBottom + 12);
            glVertex2i(x + 18, 420);
            glVertex2i(x, 420);
        glEnd();

        // Heavy T-Bar Pier Cap
        glBegin(GL_QUADS);
            glColor3f(0.82f, 0.84f, 0.88f);
            glVertex2i(x - 38, deckBottom);
            glVertex2i(x + 38, deckBottom);
            glVertex2i(x + 32, deckBottom + 12);
            glVertex2i(x - 32, deckBottom + 12);
        glEnd();

        // Pier Cap Under-Shadow
        glBegin(GL_QUADS);
            glColor3f(0.45f, 0.47f, 0.50f);
            glVertex2i(x - 32, deckBottom + 10);
            glVertex2i(x + 32, deckBottom + 10);
            glVertex2i(x + 28, deckBottom + 14);
            glVertex2i(x - 28, deckBottom + 14);
        glEnd();
    }

    // ------------------------------------------------------------------------
    // 2. CONCRETE BOX GIRDER DECK (Continuous Elevated Track Segment)
    // ------------------------------------------------------------------------
    glBegin(GL_QUADS);
        glColor3f(0.88f, 0.90f, 0.93f);
        glVertex2i(0, deckTop);
        glVertex2i(1600, deckTop);

        glColor3f(0.62f, 0.64f, 0.68f);
        glVertex2i(1600, deckBottom);
        glVertex2i(0, deckBottom);
    glEnd();

    // Side Parapet / Sound Barrier Wall
    glBegin(GL_QUADS);
        glColor3f(0.50f, 0.53f, 0.58f);
        glVertex2i(0, deckTop - 8);
        glVertex2i(1600, deckTop - 8);
        glVertex2i(1600, deckTop);
        glVertex2i(0, deckTop);
    glEnd();

    // Steel Track Railing
    glColor3f(0.20f, 0.22f, 0.25f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2i(0, deckTop - 3); glVertex2i(1600, deckTop - 3);
        glVertex2i(0, deckTop - 6); glVertex2i(1600, deckTop - 6);
    glEnd();
    glLineWidth(1.0f);

    // ------------------------------------------------------------------------
    // 3. ANIMATED DHAKA METRO RAIL TRAIN (Moving Left to Right)
    // ------------------------------------------------------------------------
    glPushMatrix();
    glTranslatef(metroX, 0.0f, 0.0f);

    int trainWidth = 850;
    int trainLeft = 0;
    int trainRight = trainLeft + trainWidth;
    int trainTop = deckTop - 44;
    int trainBottom = deckTop - 4;

    // --- Train Metallic White Main Body ---
    glBegin(GL_QUADS);
        glColor3f(0.95f, 0.96f, 0.97f);
        glVertex2i(trainLeft + 15, trainTop);
        glVertex2i(trainRight - 15, trainTop);
        glVertex2i(trainRight - 15, trainBottom);
        glVertex2i(trainLeft + 15, trainBottom);
    glEnd();

    // --- Aerodynamic Front Head (Right Engine Nose) ---
    glBegin(GL_POLYGON);
        glColor3f(0.95f, 0.96f, 0.97f);
        glVertex2i(trainRight - 15, trainTop);
        glVertex2i(trainRight + 20, trainTop + 6);
        glVertex2i(trainRight + 45, trainTop + 20);
        glVertex2i(trainRight + 38, trainBottom - 4);
        glVertex2i(trainRight - 15, trainBottom);
    glEnd();

    // --- Aerodynamic Rear Head (Left Engine Nose) ---
    glBegin(GL_POLYGON);
        glColor3f(0.95f, 0.96f, 0.97f);
        glVertex2i(trainLeft + 15, trainTop);
        glVertex2i(trainLeft - 20, trainTop + 6);
        glVertex2i(trainLeft - 45, trainTop + 20);
        glVertex2i(trainLeft - 38, trainBottom - 4);
        glVertex2i(trainLeft + 15, trainBottom);
    glEnd();

    // --- Dhaka Metro Green Band (Upper Stripe Across Whole Train) ---
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.54f, 0.32f);
        glVertex2i(trainLeft - 30, trainTop + 14);
        glVertex2i(trainLeft - 10, trainTop + 2);
        glVertex2i(trainRight + 10, trainTop + 2);
        glVertex2i(trainRight + 30, trainTop + 14);
        glVertex2i(trainRight + 20, trainTop + 22);
        glVertex2i(trainLeft - 20, trainTop + 22);
    glEnd();

    // --- Dhaka Metro Red Accent Stripe (Lower Body Line) ---
    glBegin(GL_QUADS);
        glColor3f(0.85f, 0.12f, 0.15f);
        glVertex2i(trainLeft - 10, trainBottom - 7);
        glVertex2i(trainRight + 10, trainBottom - 7);
        glVertex2i(trainRight + 5, trainBottom - 2);
        glVertex2i(trainLeft - 5, trainBottom - 2);
    glEnd();

    // --- Curved Front Windshield (Driver's Glass Cockpit - Right) ---
    glBegin(GL_POLYGON);
        glColor3f(0.08f, 0.12f, 0.18f); // Dark Tinted Glass
        glVertex2i(trainRight, trainTop + 8);
        glVertex2i(trainRight + 32, trainTop + 16);
        glVertex2i(trainRight + 28, trainTop + 26);
        glVertex2i(trainRight - 5, trainTop + 26);
    glEnd();

    // Windshield Reflection Line
    glColor3f(0.4f, 0.6f, 0.8f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2i(trainRight + 5, trainTop + 12);
        glVertex2i(trainRight + 22, trainTop + 20);
    glEnd();

    // --- Curved Rear Windshield (Driver's Glass Cockpit - Left) ---
    glBegin(GL_POLYGON);
        glColor3f(0.08f, 0.12f, 0.18f);
        glVertex2i(trainLeft, trainTop + 8);
        glVertex2i(trainLeft - 32, trainTop + 16);
        glVertex2i(trainLeft - 28, trainTop + 26);
        glVertex2i(trainLeft + 5, trainTop + 26);
    glEnd();

    // --- Red Circle National Symbol on Front Nose ---
    glColor3f(0.85f, 0.12f, 0.15f);
    glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 20) {
            float rad = i * 3.14159f / 180.0f;
            glVertex2f(trainRight + 12 + cos(rad) * 4.5f, trainTop + 32 + sin(rad) * 4.5f);
        }
    glEnd();

    // --- Inter-Coach Gangway Connectors (Bogie Separators) ---
    glColor3f(0.15f, 0.15f, 0.18f);
    for (int cx = trainLeft + 210; cx < trainRight - 50; cx += 210) {
        glBegin(GL_QUADS);
            glVertex2i(cx - 4, trainTop + 3);
            glVertex2i(cx + 4, trainTop + 3);
            glVertex2i(cx + 4, trainBottom - 1);
            glVertex2i(cx - 4, trainBottom - 1);
        glEnd();
    }

    // --- Passenger Windows with Metallic Frames ---
    for (int wx = trainLeft + 25; wx < trainRight - 40; wx += 38) {
        // Skip window rendering where doors are located
        if ((wx - trainLeft) % 210 > 70 && (wx - trainLeft) % 210 < 140) continue;

        // Window Outer Metallic Frame
        glColor3f(0.3f, 0.35f, 0.4f);
        glBegin(GL_QUADS);
            glVertex2i(wx - 1, trainTop + 13);
            glVertex2i(wx + 25, trainTop + 13);
            glVertex2i(wx + 25, trainTop + 29);
            glVertex2i(wx - 1, trainTop + 29);
        glEnd();

        // Dark Tinted Window Glass
        glColor3f(0.12f, 0.22f, 0.32f);
        glBegin(GL_QUADS);
            glVertex2i(wx, trainTop + 14);
            glVertex2i(wx + 24, trainTop + 14);
            glVertex2i(wx + 24, trainTop + 28);
            glVertex2i(wx, trainTop + 28);
        glEnd();

        // Glass Highlight/Reflection
        glColor3f(0.3f, 0.5f, 0.7f);
        glLineWidth(1.0f);
        glBegin(GL_LINES);
            glVertex2i(wx + 3, trainTop + 26);
            glVertex2i(wx + 10, trainTop + 16);
        glEnd();
    }

    // --- Automatic Passenger Sliding Doors ---
    for (int dx = trainLeft + 105; dx < trainRight - 50; dx += 210) {
        // Door Frame
        glColor3f(0.6f, 0.63f, 0.68f);
        glBegin(GL_QUADS);
            glVertex2i(dx - 1, trainTop + 11);
            glVertex2i(dx + 27, trainTop + 11);
            glVertex2i(dx + 27, trainBottom - 6);
            glVertex2i(dx - 1, trainBottom - 6);
        glEnd();

        // Door Panel
        glColor3f(0.82f, 0.85f, 0.88f);
        glBegin(GL_QUADS);
            glVertex2i(dx, trainTop + 12);
            glVertex2i(dx + 26, trainTop + 12);
            glVertex2i(dx + 26, trainBottom - 7);
            glVertex2i(dx, trainBottom - 7);
        glEnd();

        // Door Square Glass Window
        glColor3f(0.1f, 0.18f, 0.25f);
        glBegin(GL_QUADS);
            glVertex2i(dx + 4, trainTop + 15);
            glVertex2i(dx + 22, trainTop + 15);
            glVertex2i(dx + 22, trainTop + 25);
            glVertex2i(dx + 4, trainTop + 25);
        glEnd();

        // Center Seam Line (Split Doors)
        glColor3f(0.2f, 0.2f, 0.2f);
        glLineWidth(1.2f);
        glBegin(GL_LINES);
            glVertex2i(dx + 13, trainTop + 12);
            glVertex2i(dx + 13, trainBottom - 7);
        glEnd();
    }

    glPopMatrix();
}

// ============================================================================
// TIMER / ANIMATION FUNCTION
// Description: Updates the train position smoothly and redraws the frame.
// ============================================================================
void updateMetroRail(int value) {
    metroX += 3.5f; // Train Speed

    // Reset position when train moves completely out of screen on the right
    if (metroX > 1700.0f) {
        metroX = -1000.0f;
    }

    glutPostRedisplay(); // Trigger re-render
    glutTimerFunc(16, updateMetroRail, 0); // ~60 FPS update loop
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
// Position: Centered at (X = 800.0f)
// ============================================================================
void drawFlagPole()
{
    float poleX = 800.0f; // Centered to match Assembly Ground & Entrance

    // Pedestal (Centered horizontally around X = 800)
    glColor3fv(COLOR_ROOF_GRAY);
    glBegin(GL_QUADS);
    glVertex2f(poleX - 12.0f, 480.0f); // 788.0f
    glVertex2f(poleX + 12.0f, 480.0f); // 812.0f
    glVertex2f(poleX + 12.0f, 487.0f); // 812.0f
    glVertex2f(poleX - 12.0f, 487.0f); // 788.0f
    glEnd();

    // Metallic Pole (X = 800.0f)
    glColor3fv(COLOR_POLE_GRAY);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(poleX, 484.0f);
    glVertex2f(poleX, 275.0f);
    glEnd();

    // Golden Knob (X = 800.0f)
    glColor3fv(COLOR_SUN_YELLOW);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(poleX, 273.0f);
    glEnd();
}

// ============================================================================
// FUNCTION: drawBangladeshFlag
// Position: Centered attached to Pole at X = 800.0f
// ============================================================================
void drawBangladeshFlag()
{
    float poleX = 800.0f; // Shifted from 745.0f to 800.0f
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
// Text: "GOVERNMENT PRIMARY SCHOOL"
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

    // Green Text (Vertically centered)
    glColor3fv(COLOR_FLAG_GREEN);
    glRasterPos2f(690.0f, 240.0f);
    const char* bannerText = "GOVERNMENT PRIMARY SCHOOL";
    for (const char* c = bannerText; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c);
    }
}

// ============================================================================
// FUNCTION: drawShaheedMinar
// Description: Fully transparent hollow frame Shaheed Minar with thin steel grills
//              (guitar string style) so the background and red sun show through seamlessly.
// Position: Center X = 1320.0f, Base Y = 480.0f
// ============================================================================
void drawShaheedMinar()
{
    float cx = 1320.0f;          // Center X position
    float baseY = 480.0f;        // Base platform position
    float scale = 0.65f;         // Scale factor

    #define SH_X(offset) (cx + ((offset) * scale))
    #define SH_Y(offset) (baseY - ((offset) * scale))

    // ---------------------------------------------------------
    // 1. Red Sun Disc (Directly behind the central pillar)
    // ---------------------------------------------------------
    glColor3f(0.85f, 0.12f, 0.15f); // Bangladesh Flag Red
    float sunX = SH_X(0.0f);
    float sunY = SH_Y(115.0f);
    float sunR = 48.0f * scale;
    int segments = 50;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(sunX, sunY);
        for (int i = 0; i <= segments; i++) {
            float angle = i * 2.0f * 3.14159f / segments;
            glVertex2f(sunX + (sunR * cos(angle)), sunY + (sunR * sin(angle)));
        }
    glEnd();

    // ---------------------------------------------------------
    // 2. Pillars Hollow Marble Frames (White Concrete Fill)
    // ---------------------------------------------------------
    glColor3f(0.94f, 0.95f, 0.96f);

    // --- Center Pillar (Hollow Frame) ---
    // Left Leg
    glBegin(GL_QUADS);
        glVertex2f(SH_X(-32.0f), SH_Y(10.0f));
        glVertex2f(SH_X(-22.0f), SH_Y(10.0f));
        glVertex2f(SH_X(-22.0f), SH_Y(150.0f));
        glVertex2f(SH_X(-32.0f), SH_Y(155.0f));
    glEnd();
    // Right Leg
    glBegin(GL_QUADS);
        glVertex2f(SH_X(22.0f),  SH_Y(10.0f));
        glVertex2f(SH_X(32.0f),  SH_Y(10.0f));
        glVertex2f(SH_X(32.0f),  SH_Y(155.0f));
        glVertex2f(SH_X(22.0f),  SH_Y(150.0f));
    glEnd();
    // Top Angled Header Frame (Symmetric Flare)
    glBegin(GL_QUADS);
        glVertex2f(SH_X(-42.0f), SH_Y(200.0f));
        glVertex2f(SH_X(42.0f),  SH_Y(200.0f));
        glVertex2f(SH_X(30.0f),  SH_Y(188.0f));
        glVertex2f(SH_X(-30.0f), SH_Y(188.0f));
    glEnd();
    glBegin(GL_QUADS); // Top Left Joint
        glVertex2f(SH_X(-32.0f), SH_Y(155.0f));
        glVertex2f(SH_X(-22.0f), SH_Y(150.0f));
        glVertex2f(SH_X(-30.0f), SH_Y(188.0f));
        glVertex2f(SH_X(-42.0f), SH_Y(200.0f));
    glEnd();
    glBegin(GL_QUADS); // Top Right Joint
        glVertex2f(SH_X(22.0f),  SH_Y(150.0f));
        glVertex2f(SH_X(32.0f),  SH_Y(155.0f));
        glVertex2f(SH_X(42.0f),  SH_Y(200.0f));
        glVertex2f(SH_X(30.0f),  SH_Y(188.0f));
    glEnd();

    // --- Medium Left Pillar Frame ---
    glBegin(GL_QUADS);
        glVertex2f(SH_X(-78.0f), SH_Y(10.0f)); glVertex2f(SH_X(-70.0f), SH_Y(10.0f));
        glVertex2f(SH_X(-70.0f), SH_Y(130.0f)); glVertex2f(SH_X(-78.0f), SH_Y(130.0f));
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(SH_X(-54.0f), SH_Y(10.0f)); glVertex2f(SH_X(-46.0f), SH_Y(10.0f));
        glVertex2f(SH_X(-46.0f), SH_Y(130.0f)); glVertex2f(SH_X(-54.0f), SH_Y(130.0f));
    glEnd();
    glBegin(GL_QUADS); // Top Cap
        glVertex2f(SH_X(-78.0f), SH_Y(122.0f)); glVertex2f(SH_X(-46.0f), SH_Y(122.0f));
        glVertex2f(SH_X(-46.0f), SH_Y(130.0f)); glVertex2f(SH_X(-78.0f), SH_Y(130.0f));
    glEnd();

    // --- Medium Right Pillar Frame ---
    glBegin(GL_QUADS);
        glVertex2f(SH_X(46.0f), SH_Y(10.0f)); glVertex2f(SH_X(54.0f), SH_Y(10.0f));
        glVertex2f(SH_X(54.0f), SH_Y(130.0f)); glVertex2f(SH_X(46.0f), SH_Y(130.0f));
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(SH_X(70.0f), SH_Y(10.0f)); glVertex2f(SH_X(78.0f), SH_Y(10.0f));
        glVertex2f(SH_X(78.0f), SH_Y(130.0f)); glVertex2f(SH_X(70.0f), SH_Y(130.0f));
    glEnd();
    glBegin(GL_QUADS); // Top Cap
        glVertex2f(SH_X(46.0f), SH_Y(122.0f)); glVertex2f(SH_X(78.0f), SH_Y(122.0f));
        glVertex2f(SH_X(78.0f), SH_Y(130.0f)); glVertex2f(SH_X(46.0f), SH_Y(130.0f));
    glEnd();

    // --- Far Left Small Pillar Frame ---
    glBegin(GL_QUADS);
        glVertex2f(SH_X(-120.0f), SH_Y(10.0f)); glVertex2f(SH_X(-112.0f), SH_Y(10.0f));
        glVertex2f(SH_X(-112.0f), SH_Y(95.0f)); glVertex2f(SH_X(-120.0f), SH_Y(95.0f));
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(SH_X(-100.0f), SH_Y(10.0f)); glVertex2f(SH_X(-92.0f), SH_Y(10.0f));
        glVertex2f(SH_X(-92.0f), SH_Y(95.0f)); glVertex2f(SH_X(-100.0f), SH_Y(95.0f));
    glEnd();
    glBegin(GL_QUADS); // Top Cap
        glVertex2f(SH_X(-120.0f), SH_Y(87.0f)); glVertex2f(SH_X(-92.0f), SH_Y(87.0f));
        glVertex2f(SH_X(-92.0f), SH_Y(95.0f)); glVertex2f(SH_X(-120.0f), SH_Y(95.0f));
    glEnd();

    // --- Far Right Small Pillar Frame ---
    glBegin(GL_QUADS);
        glVertex2f(SH_X(92.0f), SH_Y(10.0f)); glVertex2f(SH_X(100.0f), SH_Y(10.0f));
        glVertex2f(SH_X(100.0f), SH_Y(95.0f)); glVertex2f(SH_X(92.0f), SH_Y(95.0f));
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(SH_X(112.0f), SH_Y(10.0f)); glVertex2f(SH_X(120.0f), SH_Y(10.0f));
        glVertex2f(SH_X(120.0f), SH_Y(95.0f)); glVertex2f(SH_X(112.0f), SH_Y(95.0f));
    glEnd();
    glBegin(GL_QUADS); // Top Cap
        glVertex2f(SH_X(92.0f), SH_Y(87.0f)); glVertex2f(SH_X(120.0f), SH_Y(87.0f));
        glVertex2f(SH_X(120.0f), SH_Y(95.0f)); glVertex2f(SH_X(92.0f), SH_Y(95.0f));
    glEnd();

    // ---------------------------------------------------------
    // 3. Thin Steel Grills / Strings Inside Frames
    // ---------------------------------------------------------
    glColor3f(0.20f, 0.20f, 0.25f);
    glLineWidth(1.2f); // Thin guitar-string appearance
    glBegin(GL_LINES);
        // Center Pillar Grills
        glVertex2f(SH_X(-14.0f), SH_Y(10.0f)); glVertex2f(SH_X(-14.0f), SH_Y(150.0f));
        glVertex2f(SH_X(-14.0f), SH_Y(150.0f)); glVertex2f(SH_X(-18.0f), SH_Y(188.0f));

        glVertex2f(SH_X(-5.0f),  SH_Y(10.0f)); glVertex2f(SH_X(-5.0f),  SH_Y(150.0f));
        glVertex2f(SH_X(-5.0f),  SH_Y(150.0f)); glVertex2f(SH_X(-6.0f),  SH_Y(188.0f));

        glVertex2f(SH_X(5.0f),   SH_Y(10.0f)); glVertex2f(SH_X(5.0f),   SH_Y(150.0f));
        glVertex2f(SH_X(5.0f),   SH_Y(150.0f)); glVertex2f(SH_X(6.0f),   SH_Y(188.0f));

        glVertex2f(SH_X(14.0f),  SH_Y(10.0f)); glVertex2f(SH_X(14.0f),  SH_Y(150.0f));
        glVertex2f(SH_X(14.0f),  SH_Y(150.0f)); glVertex2f(SH_X(18.0f),  SH_Y(188.0f));

        // Medium Left Grills
        glVertex2f(SH_X(-66.0f), SH_Y(10.0f)); glVertex2f(SH_X(-66.0f), SH_Y(122.0f));
        glVertex2f(SH_X(-58.0f), SH_Y(10.0f)); glVertex2f(SH_X(-58.0f), SH_Y(122.0f));

        // Medium Right Grills
        glVertex2f(SH_X(58.0f),  SH_Y(10.0f)); glVertex2f(SH_X(58.0f),  SH_Y(122.0f));
        glVertex2f(SH_X(66.0f),  SH_Y(10.0f)); glVertex2f(SH_X(66.0f),  SH_Y(122.0f));

        // Far Left Small Grills
        glVertex2f(SH_X(-108.0f), SH_Y(10.0f)); glVertex2f(SH_X(-108.0f), SH_Y(87.0f));

        // Far Right Small Grills
        glVertex2f(SH_X(108.0f),  SH_Y(10.0f)); glVertex2f(SH_X(108.0f),  SH_Y(87.0f));
    glEnd();

    // ---------------------------------------------------------
    // 4. Black Structural Border Outlines
    // ---------------------------------------------------------
    glColor3f(0.12f, 0.12f, 0.15f);
    glLineWidth(1.8f);

    // Center Outer Outline
    glBegin(GL_LINE_LOOP);
        glVertex2f(SH_X(-32.0f), SH_Y(10.0f));
        glVertex2f(SH_X(32.0f),  SH_Y(10.0f));
        glVertex2f(SH_X(32.0f),  SH_Y(155.0f));
        glVertex2f(SH_X(42.0f),  SH_Y(200.0f));
        glVertex2f(SH_X(-42.0f), SH_Y(200.0f));
        glVertex2f(SH_X(-32.0f), SH_Y(155.0f));
    glEnd();
    // Center Inner Cutout Outline
    glBegin(GL_LINE_LOOP);
        glVertex2f(SH_X(-22.0f), SH_Y(10.0f));
        glVertex2f(SH_X(22.0f),  SH_Y(10.0f));
        glVertex2f(SH_X(22.0f),  SH_Y(150.0f));
        glVertex2f(SH_X(30.0f),  SH_Y(188.0f));
        glVertex2f(SH_X(-30.0f), SH_Y(188.0f));
        glVertex2f(SH_X(-22.0f), SH_Y(150.0f));
    glEnd();

    // Medium Left Outer & Inner Outlines
    glBegin(GL_LINE_LOOP);
        glVertex2f(SH_X(-78.0f), SH_Y(10.0f)); glVertex2f(SH_X(-46.0f), SH_Y(10.0f));
        glVertex2f(SH_X(-46.0f), SH_Y(130.0f)); glVertex2f(SH_X(-78.0f), SH_Y(130.0f));
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(SH_X(-70.0f), SH_Y(10.0f)); glVertex2f(SH_X(-54.0f), SH_Y(10.0f));
        glVertex2f(SH_X(-54.0f), SH_Y(122.0f)); glVertex2f(SH_X(-70.0f), SH_Y(122.0f));
    glEnd();

    // Medium Right Outer & Inner Outlines
    glBegin(GL_LINE_LOOP);
        glVertex2f(SH_X(46.0f),  SH_Y(10.0f)); glVertex2f(SH_X(78.0f),  SH_Y(10.0f));
        glVertex2f(SH_X(78.0f),  SH_Y(130.0f)); glVertex2f(SH_X(46.0f),  SH_Y(130.0f));
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(SH_X(54.0f),  SH_Y(10.0f)); glVertex2f(SH_X(70.0f),  SH_Y(10.0f));
        glVertex2f(SH_X(70.0f),  SH_Y(122.0f)); glVertex2f(SH_X(54.0f),  SH_Y(122.0f));
    glEnd();

    // Far Left Outer & Inner Outlines
    glBegin(GL_LINE_LOOP);
        glVertex2f(SH_X(-120.0f), SH_Y(10.0f)); glVertex2f(SH_X(-92.0f),  SH_Y(10.0f));
        glVertex2f(SH_X(-92.0f),  SH_Y(95.0f)); glVertex2f(SH_X(-120.0f), SH_Y(95.0f));
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(SH_X(-112.0f), SH_Y(10.0f)); glVertex2f(SH_X(-100.0f), SH_Y(10.0f));
        glVertex2f(SH_X(-100.0f), SH_Y(87.0f)); glVertex2f(SH_X(-112.0f), SH_Y(87.0f));
    glEnd();

    // Far Right Outer & Inner Outlines
    glBegin(GL_LINE_LOOP);
        glVertex2f(SH_X(92.0f),   SH_Y(10.0f)); glVertex2f(SH_X(120.0f),  SH_Y(10.0f));
        glVertex2f(SH_X(120.0f),  SH_Y(95.0f)); glVertex2f(SH_X(92.0f),   SH_Y(95.0f));
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(SH_X(100.0f),  SH_Y(10.0f)); glVertex2f(SH_X(112.0f),  SH_Y(10.0f));
        glVertex2f(SH_X(112.0f),  SH_Y(87.0f)); glVertex2f(SH_X(100.0f),  SH_Y(87.0f));
    glEnd();

    // ---------------------------------------------------------
    // 5. Pedestal Base Steps (Staircase Platform)
    // ---------------------------------------------------------
    float stepWidths[]  = { 135.0f, 145.0f, 155.0f };
    float stepY_Start[] = { 10.0f,   2.0f,  -6.0f  };
    float stepY_End[]   = {  2.0f,  -6.0f, -14.0f  };

    for (int i = 0; i < 3; i++)
    {
        // Step Concrete Fill
        glColor3f(0.88f - (i * 0.04f), 0.89f - (i * 0.04f), 0.91f - (i * 0.04f));
        glBegin(GL_QUADS);
            glVertex2f(SH_X(-stepWidths[i]), SH_Y(stepY_Start[i]));
            glVertex2f(SH_X(stepWidths[i]),  SH_Y(stepY_Start[i]));
            glVertex2f(SH_X(stepWidths[i]),  SH_Y(stepY_End[i]));
            glVertex2f(SH_X(-stepWidths[i]), SH_Y(stepY_End[i]));
        glEnd();

        // Step Border Outline
        glColor3f(0.12f, 0.12f, 0.15f);
        glLineWidth(1.5f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(SH_X(-stepWidths[i]), SH_Y(stepY_Start[i]));
            glVertex2f(SH_X(stepWidths[i]),  SH_Y(stepY_Start[i]));
            glVertex2f(SH_X(stepWidths[i]),  SH_Y(stepY_End[i]));
            glVertex2f(SH_X(-stepWidths[i]), SH_Y(stepY_End[i]));
        glEnd();
void drawFlowerTribute(float cx, float baseY, float scale);
    }

    #undef SH_Y
    #undef SH_X

}

// Flower
void drawFlowerTribute()
{

    float cx = 1320.0f;
    float baseY = 480.0f;
    float scale = 0.65f;

    #define SH_X(offset) (cx + ((offset) * scale))
    #define SH_Y(offset) (baseY - ((offset) * scale))


    float wreathX = SH_X(0.0f);
    float wreathY = SH_Y(12.0f);
    float wreathR = 20.0f * scale;


    glColor3f(0.12f, 0.45f, 0.15f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(wreathX, wreathY);
        for (int i = 0; i <= 20; i++) {
            float a = i * 2.0f * 3.14159f / 20;
            glVertex2f(wreathX + cos(a) * wreathR, wreathY + sin(a) * wreathR);
        }
    glEnd();


    for (int i = 0; i < 8; i++) {
        float angle = i * 2.0f * 3.14159f / 8;
        float fx = wreathX + cos(angle) * (wreathR * 0.6f);
        float fy = wreathY + sin(angle) * (wreathR * 0.6f);

        glColor3f(0.90f, 0.15f, 0.15f); // লাল ফুল
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(fx, fy);
            for (int j = 0; j <= 10; j++) {
                float a = j * 2.0f * 3.14159f / 10;
                glVertex2f(fx + cos(a) * (5.0f * scale), fy + sin(a) * (5.0f * scale));
            }
        glEnd();
    }


    float flowerPositions[5][2] = {
        {-45.0f, 18.0f},
        {-75.0f, 12.0f},
        { 45.0f, 18.0f},
        { 80.0f, 12.0f},
        {  0.0f,  5.0f}
    };

    for(int k = 0; k < 5; k++) {
        float fx = SH_X(flowerPositions[k][0]);
        float fy = SH_Y(flowerPositions[k][1]);

        if(k % 2 == 0) glColor3f(0.95f, 0.75f, 0.10f); // হলুদ
        else glColor3f(0.90f, 0.15f, 0.15f);          // লাল

        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(fx, fy);
            for (int j = 0; j <= 8; j++) {
                float a = j * 2.0f * 3.14159f / 8;
                glVertex2f(fx + cos(a) * (4.0f * scale), fy + sin(a) * (4.0f * scale));
            }
        glEnd();
    }

    #undef SH_Y
    #undef SH_X
}

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

// Helper Constant for Smooth Calculations
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ============================================================================
// HIGH-DETAIL REALISTIC TREE MODELS (Enhanced Aesthetics & Lighting)
// ============================================================================

// Helper function to draw smooth gradient filled circle/oval
void drawSmoothCircle(float cx, float cy, float rx, float ry, float r, float g, float b, float alpha = 1.0f)
{
    int segments = 32;
    glColor4f(r, g, b, alpha);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= segments; i++)
        {
            float theta = i * 2.0f * M_PI / segments;
            glVertex2f(cx + rx * cos(theta), cy + ry * sin(theta));
        }
    glEnd();
}

// Helper function to draw organic tapering trunk segments
void drawBranchSegment(float x1, float y1, float w1, float x2, float y2, float w2, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x1 - w1 / 2.0f, y1);
        glVertex2f(x1 + w1 / 2.0f, y1);
        glVertex2f(x2 + w2 / 2.0f, y2);
        glVertex2f(x2 - w2 / 2.0f, y2);
    glEnd();
}

// ----------------------------------------------------------------------------
// 1. IMPROVED NORMAL LEAFY TREE
// ----------------------------------------------------------------------------
void drawSingleTree(float x, float y, float scale)
{
    float trunkH = 80.0f * scale;
    float topY = y - trunkH;

    // Organic Tapered Main Trunk
    drawBranchSegment(x, y, 16.0f * scale, x, topY, 9.0f * scale, 0.30f, 0.16f, 0.08f);

    // Natural Side Branches
    drawBranchSegment(x, topY + 15.0f * scale, 6.0f * scale, x - 22.0f * scale, topY - 10.0f * scale, 3.0f * scale, 0.28f, 0.14f, 0.06f);
    drawBranchSegment(x, topY + 20.0f * scale, 6.0f * scale, x + 22.0f * scale, topY - 10.0f * scale, 3.0f * scale, 0.28f, 0.14f, 0.06f);

    // Canopy Clusters with Multi-layer Lighting Depth
    float clusters[6][3] = {
        {x - (24.0f * scale), topY - (5.0f * scale),  26.0f * scale},
        {x + (24.0f * scale), topY - (5.0f * scale),  26.0f * scale},
        {x - (15.0f * scale), topY - (25.0f * scale), 30.0f * scale},
        {x + (15.0f * scale), topY - (25.0f * scale), 30.0f * scale},
        {x,                   topY - (45.0f * scale), 35.0f * scale},
        {x,                   topY - (15.0f * scale), 28.0f * scale}
    };

    // Layer 1: Dark Base Shadows
    for (int c = 0; c < 6; c++)
        drawSmoothCircle(clusters[c][0], clusters[c][1], clusters[c][2], clusters[c][2] * 0.9f, 0.05f, 0.28f, 0.08f);

    // Layer 2: Midtone Leaves
    for (int c = 0; c < 6; c++)
        drawSmoothCircle(clusters[c][0] + 2.0f * scale, clusters[c][1] - 2.0f * scale, clusters[c][2] * 0.85f, clusters[c][2] * 0.8f, 0.15f, 0.48f, 0.12f);

    // Layer 3: Vibrant Sunlit Highlights
    for (int c = 0; c < 6; c++)
        drawSmoothCircle(clusters[c][0] - 3.0f * scale, clusters[c][1] - 5.0f * scale, clusters[c][2] * 0.65f, clusters[c][2] * 0.6f, 0.28f, 0.68f, 0.20f);
}

// ----------------------------------------------------------------------------
// 2. MANGO TREE (Dense Canopy & Ripe Yellow Mangoes)
// ----------------------------------------------------------------------------
void drawSingleMangoTree(float x, float y, float scale)
{
    float topY = y - (85.0f * scale);

    // Thick Textured Trunk with Bark Gradient Accent
    drawBranchSegment(x, y, 22.0f * scale, x, topY, 12.0f * scale, 0.26f, 0.14f, 0.06f);
    drawBranchSegment(x - 2.0f * scale, y, 4.0f * scale, x - 1.0f * scale, topY, 2.0f * scale, 0.36f, 0.22f, 0.10f); // Bark Highlight

    // Spreading Branches
    drawBranchSegment(x, topY + 25.0f * scale, 8.0f * scale, x - 28.0f * scale, topY - 5.0f * scale, 4.0f * scale, 0.24f, 0.12f, 0.05f);
    drawBranchSegment(x, topY + 20.0f * scale, 8.0f * scale, x + 28.0f * scale, topY - 5.0f * scale, 4.0f * scale, 0.24f, 0.12f, 0.05f);

    float clusters[5][3] = {
        {x - (28.0f * scale), topY - (8.0f * scale),  35.0f * scale},
        {x + (28.0f * scale), topY - (8.0f * scale),  35.0f * scale},
        {x - (14.0f * scale), topY - (38.0f * scale), 38.0f * scale},
        {x + (14.0f * scale), topY - (38.0f * scale), 38.0f * scale},
        {x,                   topY - (20.0f * scale), 42.0f * scale}
    };

    // Deep Dense Foliage Layers
    for (int c = 0; c < 5; c++)
        drawSmoothCircle(clusters[c][0], clusters[c][1], clusters[c][2], clusters[c][2] * 0.85f, 0.03f, 0.24f, 0.06f);

    for (int c = 0; c < 5; c++)
        drawSmoothCircle(clusters[c][0] + 3.0f * scale, clusters[c][1] - 3.0f * scale, clusters[c][2] * 0.82f, clusters[c][2] * 0.72f, 0.10f, 0.42f, 0.10f);

    for (int c = 0; c < 5; c++)
        drawSmoothCircle(clusters[c][0] - 3.0f * scale, clusters[c][1] - 6.0f * scale, clusters[c][2] * 0.6f, clusters[c][2] * 0.5f, 0.22f, 0.58f, 0.16f);

    // High-Detail Hanging Mangoes with Stem
    float mangoes[6][2] = {
        {x - 20.0f * scale, topY - 2.0f * scale},
        {x - 8.0f  * scale, topY - 28.0f * scale},
        {x + 18.0f * scale, topY - 12.0f * scale},
        {x + 24.0f * scale, topY + 8.0f * scale},
        {x + 4.0f  * scale, topY - 35.0f * scale},
        {x - 30.0f * scale, topY + 5.0f * scale}
    };

    for (int m = 0; m < 6; m++)
    {
        // Mango Stem
        glColor3f(0.2f, 0.15f, 0.05f);
        glLineWidth(1.5f);
        glBegin(GL_LINES);
            glVertex2f(mangoes[m][0], mangoes[m][1]);
            glVertex2f(mangoes[m][0], mangoes[m][1] - 4.0f * scale);
        glEnd();

        // Mango Body (Realistic teardrop-ish gradient)
        drawSmoothCircle(mangoes[m][0], mangoes[m][1] + 5.0f * scale, 3.8f * scale, 5.5f * scale, 0.95f, 0.75f, 0.0f);
        drawSmoothCircle(mangoes[m][0] - 0.8f * scale, mangoes[m][1] + 4.2f * scale, 2.2f * scale, 3.5f * scale, 1.00f, 0.35f, 0.05f); // Blush Accent
    }
    glLineWidth(1.0f);
}

// ----------------------------------------------------------------------------
// 3. COCONUT TREE (Curved Trunk Leaning Left, Green Coconuts & Feathery Fronds)
// ----------------------------------------------------------------------------
void drawSingleCoconutTree(float startX, float startY, float height)
{
    int segments = 12;
    float currentX = startX;
    float currentY = startY;
    float segmentH = height / segments;

    // Curved Trunk with Bark Ring Textures (Leaning Left)
    for (int i = 0; i < segments; i++)
    {

        float nextX = currentX - (i * .4f);
        float nextY = currentY - segmentH;
        float w1 = 11.0f - (i * 0.5f);
        float w2 = 11.0f - ((i + 1) * 0.45f);

        drawBranchSegment(currentX, currentY, w1 * 2.0f, nextX, nextY, w2 * 2.0f, 0.38f, 0.24f, 0.12f);

        // Trunk Ring Detail Lines
        glColor3f(0.22f, 0.12f, 0.05f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
            glVertex2f(currentX - w1, currentY);
            glVertex2f(currentX + w1, currentY);
        glEnd();

        currentX = nextX;
        currentY = nextY;
    }

    float topX = currentX;
    float topY = currentY;

    // Natural Round Coconuts with Highlights
    float coconutCoords[4][2] = {
        {topX - 5.0f, topY + 2.0f},
        {topX + 5.0f, topY + 2.0f},
        {topX - 1.0f, topY + 6.0f},
        {topX + 2.0f, topY - 2.0f}
    };
    for (int c = 0; c < 4; c++)
    {
        drawSmoothCircle(coconutCoords[c][0], coconutCoords[c][1], 5.5f, 6.0f, 0.15f, 0.38f, 0.05f);
        drawSmoothCircle(coconutCoords[c][0] - 1.5f, coconutCoords[c][1] - 1.5f, 2.5f, 3.0f, 0.30f, 0.55f, 0.10f);
    }

    // Organic Curved Feathery Leaves (Fronds)
    float leafAngles[] = { -165.0f, -130.0f, -85.0f, -30.0f, 20.0f, 75.0f, 120.0f, 160.0f };

    for (int f = 0; f < 8; f++)
    {
        float rad = leafAngles[f] * M_PI / 180.0f;
        float leafLen = 65.0f;
        float endX = topX + (leafLen * cos(rad));
        float endY = topY - (leafLen * sin(rad)) + (abs((int)leafAngles[f]) * 0.18f);

        // Main Spine
        glColor3f(0.08f, 0.42f, 0.08f);
        glLineWidth(2.5f);
        glBegin(GL_LINES);
            glVertex2f(topX, topY);
            glVertex2f(endX, endY);
        glEnd();

        // Feathery Leaflets along the spine
        int leaflets = 16;
        glLineWidth(1.5f);
        glColor3f(0.12f, 0.58f, 0.12f);
        for (int j = 1; j <= leaflets; j++)
        {
            float t = (float)j / leaflets;
            float lx = topX + (endX - topX) * t;
            float ly = topY + (endY - topY) * t;

            glBegin(GL_LINES);
                glVertex2f(lx, ly);
                glVertex2f(lx - 7.0f * (1.0f - t * 0.3f), ly + 10.0f);
                glVertex2f(lx, ly);
                glVertex2f(lx + 7.0f * (1.0f - t * 0.3f), ly + 10.0f);
            glEnd();
        }
    }
    glLineWidth(1.0f);
}
// ----------------------------------------------------------------------------
// 4. PALMYRA PALM TREE (Tal Gach - Tall Straight Trunk & Fan Fronds)
// ----------------------------------------------------------------------------
void drawSinglePalmTree(float x, float y, float height)
{
    float topY = y - height;

    // Dark Straight Trunk with Slight Taper
    drawBranchSegment(x, y, 15.0f, x, topY, 9.0f, 0.18f, 0.13f, 0.08f);

    // Textured Trunk Horizontal Ridges
    glColor3f(0.08f, 0.05f, 0.03f);
    glLineWidth(2.0f);
    for (float r = y - 8.0f; r > topY; r -= 10.0f)
    {
        glBegin(GL_LINES);
            glVertex2f(x - 7.0f + ((y - r) / height * 2.5f), r);
            glVertex2f(x + 7.0f - ((y - r) / height * 2.5f), r);
        glEnd();
    }

    // Black Palm Fruits (Tal) Clustered at top
    float fruits[4][2] = {{x - 6.0f, topY + 4.0f}, {x + 6.0f, topY + 4.0f}, {x, topY + 8.0f}, {x, topY + 2.0f}};
    for (int k = 0; k < 4; k++)
    {
        drawSmoothCircle(fruits[k][0], fruits[k][1], 4.5f, 4.5f, 0.05f, 0.05f, 0.05f);
        drawSmoothCircle(fruits[k][0] - 1.0f, fruits[k][1] - 1.0f, 2.0f, 2.0f, 0.25f, 0.20f, 0.10f); // Calyx accent
    }

    // Dense Fan-shaped Leaf Crown
    int numFronds = 16;
    for (int i = 0; i < numFronds; i++)
    {
        float angle = (-175.0f + (i * 23.0f)) * M_PI / 180.0f;
        float len = 46.0f;
        float ex = x + (len * cos(angle));
        float ey = topY - (len * sin(angle));

        // Fan leaf blade
        glColor3f(0.04f, 0.38f, 0.08f);
        glBegin(GL_TRIANGLES);
            glVertex2f(x, topY);
            glVertex2f(ex - 7.0f * sin(angle), ey + 7.0f * cos(angle));
            glVertex2f(ex + 7.0f * sin(angle), ey - 7.0f * cos(angle));
        glEnd();

        // Bright Leaf Edge Highlight
        glColor3f(0.12f, 0.55f, 0.15f);
        glLineWidth(1.5f);
        glBegin(GL_LINES);
            glVertex2f(x, topY);
            glVertex2f(ex, ey);
        glEnd();
    }
    glLineWidth(1.0f);
}

// ----------------------------------------------------------------------------
// 5. BANANA TREE (Arching Drooping Leaves & Kolar Mocha)
// ----------------------------------------------------------------------------
void drawSingleBananaTree(float x, float y, float scale)
{
    float topY = y - (55.0f * scale);

    // Green Soft Layered Pseudostem
    drawBranchSegment(x, y, 12.0f * scale, x, topY, 7.0f * scale, 0.35f, 0.62f, 0.15f);
    drawBranchSegment(x - 1.0f * scale, y, 3.0f * scale, x - 0.5f * scale, topY, 2.0f * scale, 0.48f, 0.75f, 0.20f); // Soft Highlight

    float leafAngles[] = { -150.0f, -105.0f, -45.0f, 45.0f, 105.0f, 150.0f };

    // Broad Curved Arching Leaves with Natural Volume
    for (int i = 0; i < 6; i++)
    {
        float rad = leafAngles[i] * M_PI / 180.0f;
        float leafLen = 50.0f * scale;

        float endX = x + (leafLen * cos(rad));
        float endY = topY - (leafLen * sin(rad)) + (abs((int)leafAngles[i]) * 0.14f * scale);

        float midX = (x + endX) / 2.0f;
        float midY = (topY + endY) / 2.0f - (10.0f * scale);

        // Smooth Broad Leaf Body
        glColor3f(0.25f, 0.68f, 0.12f);
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(x, topY);
            glVertex2f(midX - (12.0f * scale * sin(rad)), midY + (12.0f * scale * cos(rad)));
            glVertex2f(endX, endY);
            glVertex2f(midX + (12.0f * scale * sin(rad)), midY - (12.0f * scale * cos(rad)));
        glEnd();

        // Distinct Central Leaf Midrib Line
        glColor3f(0.15f, 0.42f, 0.06f);
        glLineWidth(2.5f);
        glBegin(GL_LINES);
            glVertex2f(x, topY);
            glVertex2f(endX, endY);
        glEnd();
    }

    // Hanging Banana Comb Stalk
    glColor3f(0.65f, 0.78f, 0.08f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex2f(x, topY);
        glVertex2f(x, topY + (18.0f * scale));
    glEnd();

    // Curved Yellow Bananas
    for (int b = 0; b < 3; b++)
    {
        float by = topY + ((6.0f + b * 3.5f) * scale);
        drawSmoothCircle(x - 3.0f * scale, by, 4.0f * scale, 2.0f * scale, 0.88f, 0.82f, 0.05f);
        drawSmoothCircle(x + 3.0f * scale, by, 4.0f * scale, 2.0f * scale, 0.88f, 0.82f, 0.05f);
    }

    // Banana Flower Bud (Kolar Mocha) with Smooth Curved Tip
    drawSmoothCircle(x, topY + (22.0f * scale), 5.5f * scale, 7.5f * scale, 0.45f, 0.03f, 0.12f);

    glLineWidth(1.0f);
}

// ============================================================================
// RIGHT SIDE FOREST (Single instance of each tree within 1600f screen limit)
// ============================================================================
void drawRightSideForest()
{
    // Ground Y = 460 ~ 465
    drawSingleBananaTree(1190.0f, 480.0f, 0.85f);
    drawSingleMangoTree(1450.0f, 475.0f, 0.85f);
    drawSingleCoconutTree(1570.0f, 485.0f, 130.0f);
    drawSinglePalmTree(1250.0f, 470.0f, 125.0f);
    drawSingleTree(1350.0f, 465.0f, 0.80f);
}
//Decorative tree
void drawSingleDecorativeTree(float x, float y, float scale)
{
    // 1. Terracotta Pot Base (Sitting at Y)
    glColor3f(0.60f, 0.30f, 0.15f);
    glBegin(GL_POLYGON);
        glVertex2f(x - (12.0f * scale), y);
        glVertex2f(x + (12.0f * scale), y);
        glVertex2f(x + (9.0f * scale),  y - (15.0f * scale));
        glVertex2f(x - (9.0f * scale),  y - (15.0f * scale));
    glEnd();

    // Pot Rim
    glColor3f(0.70f, 0.35f, 0.18f);
    glBegin(GL_QUADS);
        glVertex2f(x - (13.0f * scale), y - (12.0f * scale));
        glVertex2f(x + (13.0f * scale), y - (12.0f * scale));
        glVertex2f(x + (13.0f * scale), y - (15.0f * scale));
        glVertex2f(x - (13.0f * scale), y - (15.0f * scale));
    glEnd();

    // 2. Trunk (Extending Upward)
    glColor3f(0.30f, 0.20f, 0.10f);
    glBegin(GL_QUADS);
        glVertex2f(x - (4.0f * scale), y - (15.0f * scale));
        glVertex2f(x + (4.0f * scale), y - (15.0f * scale));
        glVertex2f(x + (3.0f * scale), y - (35.0f * scale));
        glVertex2f(x - (3.0f * scale), y - (35.0f * scale));
    glEnd();

    // 3. Layered Cones (Leaves pointing UPWARDS)
    float baseY = y - (30.0f * scale);

    float layers[3][3] =
    {
        {45.0f * scale, 35.0f * scale, 0.12f}, // Base layer
        {40.0f * scale, 28.0f * scale, 0.16f}, // Middle layer
        {35.0f * scale, 20.0f * scale, 0.22f}  // Top layer
    };

    float currY = baseY;
    for (int i = 0; i < 3; i++)
    {
        float height = layers[i][0];
        float halfWidth = layers[i][1];
        float greenVal = layers[i][2];

        // Left half (Shaded)
        glColor3f(0.04f, greenVal + 0.20f, 0.08f);
        glBegin(GL_TRIANGLES);
            glVertex2f(x - halfWidth, currY);
            glVertex2f(x, currY);
            glVertex2f(x, currY - height);
        glEnd();

        // Right half (Lighted)
        glColor3f(0.08f, greenVal + 0.32f, 0.14f);
        glBegin(GL_TRIANGLES);
            glVertex2f(x, currY);
            glVertex2f(x + halfWidth, currY);
            glVertex2f(x, currY - height);
        glEnd();

        currY -= (height * 0.55f); // Move upward (negative Y direction)
    }
}

void drawDecorativeTree()
{
    // Positioned at the bottom edge of the school wall (Y = 480.0f)
    drawSingleDecorativeTree(715.0f, 480.0f, 0.55f); // Left of entrance
    drawSingleDecorativeTree(885.0f, 480.0f, 0.55f); // Right of entrance
}
// ============================================================================
// PERFECTLY ADJUSTED ASSEMBLY GROUND
// Fitted exactly to Blue Line boundary (Y = 665) & Trimmed Yellow Leader Line
// ============================================================================

void drawAssemblyGround()
{
    float topY = 480.0f;
    float bottomY = 665.0f; // Adjusted to match your exact Blue Line mark
    float height = bottomY - topY; // Height = 185.0f

    // ------------------------------------------------------------------------
    // 1. PLAZA BASE DROP SHADOW (Semi-Transparent)
    // ------------------------------------------------------------------------
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.1f, 0.2f, 0.1f, 0.30f);
    glBegin(GL_POLYGON);
        glVertex2f(745.0f, 485.0f);
        glVertex2f(855.0f, 485.0f);
        glVertex2f(1025.0f, bottomY + 6.0f);
        glVertex2f(575.0f, bottomY + 6.0f);
    glEnd();
    glDisable(GL_BLEND);

    // ------------------------------------------------------------------------
    // 2. MAIN CONCRETE ASSEMBLY PLAZA
    // Top: X(750 to 850), Bottom: X(580 to 1020)
    // ------------------------------------------------------------------------
    glColor3f(0.68f, 0.70f, 0.72f); // Concrete Grey
    glBegin(GL_POLYGON);
        glVertex2f(750.0f, topY);       // Top Left
        glVertex2f(850.0f, topY);       // Top Right
        glVertex2f(1020.0f, bottomY);   // Bottom Right
        glVertex2f(580.0f, bottomY);    // Bottom Left
    glEnd();

    // Perspective Pavement Grid Lines (Tiles Texture)
    glColor3f(0.60f, 0.62f, 0.64f);
    glLineWidth(1.2f);

    // Horizontal Tile Grid
    glBegin(GL_LINES);
    for (float y = 495.0f; y <= bottomY - 5.0f; y += 16.0f) {
        float factor = (y - topY) / height;
        float xLeft = 750.0f - (170.0f * factor);
        float xRight = 850.0f + (170.0f * factor);
        glVertex2f(xLeft, y);
        glVertex2f(xRight, y);
    }
    glEnd();

    // Vertical Pavement Grid Lines
    glBegin(GL_LINES);
    for (int i = -4; i <= 4; i++) {
        float offsetTop = i * 11.0f;
        float offsetBottom = i * 50.0f;
        glVertex2f(800.0f + offsetTop, topY);
        glVertex2f(800.0f + offsetBottom, bottomY);
    }
    glEnd();

    // ------------------------------------------------------------------------
    // 3. CENTRALLY ALIGNED FLAG BASE PLAZA (Center = X: 800)
    // ------------------------------------------------------------------------

    // Bottom Step (Red Brick)
    glColor3f(0.75f, 0.18f, 0.15f);
    glBegin(GL_POLYGON);
        glVertex2f(765.0f, 478.0f);
        glVertex2f(835.0f, 478.0f);
        glVertex2f(838.0f, 492.0f);
        glVertex2f(762.0f, 492.0f);
    glEnd();

    // Top Step Slab (White Marble)
    glColor3f(0.95f, 0.95f, 0.98f);
    glBegin(GL_POLYGON);
        glVertex2f(770.0f, 478.0f);
        glVertex2f(830.0f, 478.0f);
        glVertex2f(832.0f, 488.0f);
        glVertex2f(768.0f, 488.0f);
    glEnd();

    // Green Center Accent
    glColor3f(0.0f, 0.5f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(792.0f, 481.0f);
        glVertex2f(808.0f, 481.0f);
        glVertex2f(809.0f, 485.0f);
        glVertex2f(791.0f, 485.0f);
    glEnd();

    // TRIMMED LEADER LINE (Yellow Bar strictly within plaza boundary)
    glColor3f(0.95f, 0.80f, 0.10f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex2f(725.0f, 504.0f); // Trimmed X from 670 to 725
        glVertex2f(875.0f, 504.0f); // Trimmed X from 930 to 875
    glEnd();

    // ------------------------------------------------------------------------
    // 4. PARADE STANDING LINES (Clean Perspective Lines)
    // ------------------------------------------------------------------------
    glColor4f(1.0f, 1.0f, 1.0f, 0.95f);
    glLineWidth(2.5f);

    float columnOffsets[] = { -95.0f, -32.0f, 32.0f, 95.0f };

    for (int col = 0; col < 4; col++) {
        float cx = columnOffsets[col];
        float startX = 800.0f + (cx * 0.35f);
        float endX = 800.0f + (cx * 1.65f);

        // Continuous Column Guide Lines
        glBegin(GL_LINES);
            glVertex2f(startX, 512.0f);
            glVertex2f(endX, bottomY - 10.0f);
        glEnd();
    }

    // Small White Standing Dots / Marks
    glPointSize(4.5f);
    glBegin(GL_POINTS);
    for (int col = 0; col < 4; col++) {
        float cx = columnOffsets[col];
        for (float rowY = 525.0f; rowY <= bottomY - 15.0f; rowY += 18.0f) {
            float factor = (rowY - topY) / height;
            float px = 800.0f + (cx * (0.35f + factor * 1.30f));
            glVertex2f(px, rowY);
        }
    }
    glEnd();

    // ------------------------------------------------------------------------
    // 5. RED & WHITE 3D CURBSTONES
    // ------------------------------------------------------------------------
    int totalCurbBlocks = 16;
    for (int i = 0; i < totalCurbBlocks; i++) {
        float t1 = (float)i / totalCurbBlocks;
        float t2 = (float)(i + 1) / totalCurbBlocks;

        if (i % 2 == 0) glColor3f(0.85f, 0.15f, 0.15f); // Red
        else glColor3f(0.95f, 0.95f, 0.95f);            // White

        // Left Border
        float lx1 = 750.0f - (170.0f * t1);
        float ly1 = topY + (height * t1);
        float lx2 = 750.0f - (170.0f * t2);
        float ly2 = topY + (height * t2);

        glBegin(GL_POLYGON);
            glVertex2f(lx1, ly1);
            glVertex2f(lx2, ly2);
            glVertex2f(lx2 - 6.0f, ly2 + 3.0f);
            glVertex2f(lx1 - 6.0f, ly1 + 3.0f);
        glEnd();

        // Right Border
        float rx1 = 850.0f + (170.0f * t1);
        float ry1 = topY + (height * t1);
        float rx2 = 850.0f + (170.0f * t2);
        float ry2 = topY + (height * t2);

        glBegin(GL_POLYGON);
            glVertex2f(rx1, ry1);
            glVertex2f(rx2, ry2);
            glVertex2f(rx2 + 6.0f, ry2 + 3.0f);
            glVertex2f(rx1 + 6.0f, ry1 + 3.0f);
        glEnd();
    }

    glLineWidth(1.0f);
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
// ============================================================================
// REALISTIC FRONT BOUNDARY WALL (Color Matched with Background Wall)
// Extended Depth with Concrete Panels, Vertical Support Pillars & Top Caps
// ============================================================================

void drawBoundaryWall()
{
    float wallTopY = 635.0f;
    float wallBottomY = 715.0f;
    float leftPillarX = 720.0f;
    float rightPillarX = 880.0f;

    // ------------------------------------------------------------------------
    // 1. CONCRETE BASE PLINTH (Dark Grey Foundation matching background)
    // ------------------------------------------------------------------------
    glColor3f(0.55f, 0.55f, 0.56f); // Concrete Grey Base
    glBegin(GL_QUADS);
        // Left Base
        glVertex2f(0.0f, wallBottomY - 10.0f);
        glVertex2f(leftPillarX, wallBottomY - 10.0f);
        glVertex2f(leftPillarX, wallBottomY);
        glVertex2f(0.0f, wallBottomY);

        // Right Base
        glVertex2f(rightPillarX, wallBottomY - 10.0f);
        glVertex2f(1600.0f, wallBottomY - 10.0f);
        glVertex2f(1600.0f, wallBottomY);
        glVertex2f(rightPillarX, wallBottomY);
    glEnd();

    // Base Highlight Line
    glColor3f(0.68f, 0.68f, 0.70f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2f(0.0f, wallBottomY - 10.0f);
        glVertex2f(leftPillarX, wallBottomY - 10.0f);
        glVertex2f(rightPillarX, wallBottomY - 10.0f);
        glVertex2f(1600.0f, wallBottomY - 10.0f);
    glEnd();

    // ------------------------------------------------------------------------
    // 2. MAIN WALL BODY (Light Ash / Grey matching Background Boundary Wall)
    // ------------------------------------------------------------------------
    glColor3f(0.82f, 0.82f, 0.80f); // Matched Back-wall Light Grey Tone
    glBegin(GL_QUADS);
        // Left Section
        glVertex2f(0.0f, wallTopY);
        glVertex2f(leftPillarX, wallTopY);
        glVertex2f(leftPillarX, wallBottomY - 10.0f);
        glVertex2f(0.0f, wallBottomY - 10.0f);

        // Right Section
        glVertex2f(rightPillarX, wallTopY);
        glVertex2f(1600.0f, wallTopY);
        glVertex2f(1600.0f, wallBottomY - 10.0f);
        glVertex2f(rightPillarX, wallBottomY - 10.0f);
    glEnd();

    // ------------------------------------------------------------------------
    // 3. HORIZONTAL BRICK / PANEL GROOVE LINES
    // ------------------------------------------------------------------------
    glColor3f(0.70f, 0.70f, 0.68f); // Mortar Joint Grey
    glLineWidth(1.2f);
    glBegin(GL_LINES);
    for (float y = wallTopY + 16.0f; y < wallBottomY - 10.0f; y += 16.0f) {
        glVertex2f(0.0f, y);
        glVertex2f(leftPillarX, y);

        glVertex2f(rightPillarX, y);
        glVertex2f(1600.0f, y);
    }
    glEnd();

    // Staggered Vertical Joint Lines
    int rowCount = 0;
    glBegin(GL_LINES);
    for (float y = wallTopY; y < wallBottomY - 16.0f; y += 16.0f) {
        float xShift = (rowCount % 2 == 0) ? 0.0f : 30.0f;

        // Left Section
        for (float x = xShift; x < leftPillarX; x += 60.0f) {
            glVertex2f(x, y);
            glVertex2f(x, y + 16.0f);
        }
        // Right Section
        for (float x = rightPillarX + xShift; x < 1600.0f; x += 60.0f) {
            glVertex2f(x, y);
            glVertex2f(x, y + 16.0f);
        }
        rowCount++;
    }
    glEnd();

    // ------------------------------------------------------------------------
    // 4. EMBOSSED VERTICAL CONCRETE POSTS / PILLARS (Realism Detail)
    // ------------------------------------------------------------------------
    // Adds structural pillars every 240px along the wall just like the backwall
    glColor3f(0.76f, 0.76f, 0.74f); // Slightly darker panel grey
    for (float x = 160.0f; x < leftPillarX - 20.0f; x += 200.0f) {
        glBegin(GL_QUADS);
            glVertex2f(x, wallTopY);
            glVertex2f(x + 14.0f, wallTopY);
            glVertex2f(x + 14.0f, wallBottomY - 10.0f);
            glVertex2f(x, wallBottomY - 10.0f);
        glEnd();
    }
    for (float x = rightPillarX + 160.0f; x < 1600.0f - 20.0f; x += 200.0f) {
        glBegin(GL_QUADS);
            glVertex2f(x, wallTopY);
            glVertex2f(x + 14.0f, wallTopY);
            glVertex2f(x + 14.0f, wallBottomY - 10.0f);
            glVertex2f(x, wallBottomY - 10.0f);
        glEnd();
    }

    // ------------------------------------------------------------------------
    // 5. 3D TOP CAP RAIL (Slanted Concrete Top Cover)
    // ------------------------------------------------------------------------
    // Drop Shadow under Top Cap
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.1f, 0.1f, 0.1f, 0.22f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, wallTopY);
        glVertex2f(leftPillarX, wallTopY);
        glVertex2f(leftPillarX, wallTopY + 5.0f);
        glVertex2f(0.0f, wallTopY + 5.0f);

        glVertex2f(rightPillarX, wallTopY);
        glVertex2f(1600.0f, wallTopY);
        glVertex2f(1600.0f, wallTopY + 5.0f);
        glVertex2f(rightPillarX, wallTopY + 5.0f);
    glEnd();
    glDisable(GL_BLEND);

    // Main Concrete Top Slab
    glColor3f(0.72f, 0.72f, 0.70f); // Medium Grey Cap
    glBegin(GL_QUADS);
        glVertex2f(-2.0f, wallTopY - 8.0f);
        glVertex2f(leftPillarX + 3.0f, wallTopY - 8.0f);
        glVertex2f(leftPillarX + 3.0f, wallTopY);
        glVertex2f(-2.0f, wallTopY);

        glVertex2f(rightPillarX - 3.0f, wallTopY - 8.0f);
        glVertex2f(1602.0f, wallTopY - 8.0f);
        glVertex2f(1602.0f, wallTopY);
        glVertex2f(rightPillarX - 3.0f, wallTopY);
    glEnd();

    // Top Cap Light Highlight (Sunlight Reflection on Rim)
    glColor3f(0.92f, 0.92f, 0.90f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(-2.0f, wallTopY - 8.0f);
        glVertex2f(leftPillarX + 3.0f, wallTopY - 8.0f);

        glVertex2f(rightPillarX - 3.0f, wallTopY - 8.0f);
        glVertex2f(1602.0f, wallTopY - 8.0f);
    glEnd();

    glLineWidth(1.0f);
}
// ============================================================================
// HIGHLY DETAILED MAIN ENTRANCE GATE & PILLARS
// Perfectly Matched with Boundaries (Y: 615 to 715) with 3D Concrete & Iron Work
// ============================================================================

void drawGate()
{
    float pY1 = 615.0f; // Pillar Top (Slightly taller than wall at 635)
    float pY2 = 715.0f; // Pillar Bottom (Aligned with wall base)

    float leftPillLeft = 715.0f;
    float leftPillRight = 750.0f;
    float rightPillLeft = 850.0f;
    float rightPillRight = 885.0f;

    // ------------------------------------------------------------------------
    // 1. LEFT GATE PILLAR (Concrete Pillar with 3D Depth & Moldings)
    // ------------------------------------------------------------------------
    // Base Pillar Body
    glColor3f(0.76f, 0.76f, 0.74f); // Matched Concrete Grey
    glBegin(GL_QUADS);
        glVertex2f(leftPillLeft, pY1);
        glVertex2f(leftPillRight, pY1);
        glVertex2f(leftPillRight, pY2);
        glVertex2f(leftPillLeft, pY2);
    glEnd();

    // 3D Right Side Shadow Band
    glColor3f(0.60f, 0.60f, 0.58f);
    glBegin(GL_QUADS);
        glVertex2f(leftPillRight - 6.0f, pY1);
        glVertex2f(leftPillRight, pY1);
        glVertex2f(leftPillRight, pY2);
        glVertex2f(leftPillRight - 6.0f, pY2);
    glEnd();

    // Horizontal Pillar Decorative Grooves
    glColor3f(0.50f, 0.50f, 0.48f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2f(leftPillLeft, pY1 + 30.0f); glVertex2f(leftPillRight, pY1 + 30.0f);
        glVertex2f(leftPillLeft, pY1 + 60.0f); glVertex2f(leftPillRight, pY1 + 60.0f);
    glEnd();

    // Pyramid Pillar Top Cap (Double Layer Concrete Slab)
    glColor3f(0.85f, 0.85f, 0.83f); // Light Top Highlight
    glBegin(GL_QUADS);
        // Base Cap Layer
        glVertex2f(leftPillLeft - 4.0f, pY1 - 6.0f);
        glVertex2f(leftPillRight + 4.0f, pY1 - 6.0f);
        glVertex2f(leftPillRight + 4.0f, pY1);
        glVertex2f(leftPillLeft - 4.0f, pY1);

        // Pyramid Slanted Roof Cap
        glVertex2f(leftPillLeft - 1.0f, pY1 - 14.0f);
        glVertex2f(leftPillRight + 1.0f, pY1 - 14.0f);
        glVertex2f(leftPillRight + 4.0f, pY1 - 6.0f);
        glVertex2f(leftPillLeft - 4.0f, pY1 - 6.0f);
    glEnd();

    // ------------------------------------------------------------------------
    // 2. RIGHT GATE PILLAR (Symmetrical Concrete Pillar)
    // ------------------------------------------------------------------------
    // Base Pillar Body
    glColor3f(0.76f, 0.76f, 0.74f);
    glBegin(GL_QUADS);
        glVertex2f(rightPillLeft, pY1);
        glVertex2f(rightPillRight, pY1);
        glVertex2f(rightPillRight, pY2);
        glVertex2f(rightPillLeft, pY2);
    glEnd();

    // 3D Left Side Highlight Band
    glColor3f(0.84f, 0.84f, 0.82f);
    glBegin(GL_QUADS);
        glVertex2f(rightPillLeft, pY1);
        glVertex2f(rightPillLeft + 6.0f, pY1);
        glVertex2f(rightPillLeft + 6.0f, pY2);
        glVertex2f(rightPillLeft, pY2);
    glEnd();

    // Horizontal Pillar Decorative Grooves
    glColor3f(0.50f, 0.50f, 0.48f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2f(rightPillLeft, pY1 + 30.0f); glVertex2f(rightPillRight, pY1 + 30.0f);
        glVertex2f(rightPillLeft, pY1 + 60.0f); glVertex2f(rightPillRight, pY1 + 60.0f);
    glEnd();

    // Pyramid Pillar Top Cap
    glColor3f(0.85f, 0.85f, 0.83f);
    glBegin(GL_QUADS);
        // Base Cap Layer
        glVertex2f(rightPillLeft - 4.0f, pY1 - 6.0f);
        glVertex2f(rightPillRight + 4.0f, pY1 - 6.0f);
        glVertex2f(rightPillRight + 4.0f, pY1);
        glVertex2f(rightPillLeft - 4.0f, pY1);

        // Pyramid Slanted Roof Cap
        glVertex2f(rightPillLeft - 1.0f, pY1 - 14.0f);
        glVertex2f(rightPillRight + 1.0f, pY1 - 14.0f);
        glVertex2f(rightPillRight + 4.0f, pY1 - 6.0f);
        glVertex2f(rightPillLeft - 4.0f, pY1 - 6.0f);
    glEnd();

    // ------------------------------------------------------------------------
    // 3. PILLAR HINGES & ATTACHMENTS
    // ------------------------------------------------------------------------
    glColor3f(0.20f, 0.20f, 0.22f); // Black Metal Hinges
    glBegin(GL_QUADS);
        // Left Hinges
        glVertex2f(leftPillRight, pY1 + 25.0f); glVertex2f(leftPillRight + 4.0f, pY1 + 25.0f);
        glVertex2f(leftPillRight + 4.0f, pY1 + 33.0f); glVertex2f(leftPillRight, pY1 + 33.0f);

        glVertex2f(leftPillRight, pY2 - 25.0f); glVertex2f(leftPillRight + 4.0f, pY2 - 25.0f);
        glVertex2f(leftPillRight + 4.0f, pY2 - 17.0f); glVertex2f(leftPillRight, pY2 - 17.0f);

        // Right Hinges
        glVertex2f(rightPillLeft - 4.0f, pY1 + 25.0f); glVertex2f(rightPillLeft, pY1 + 25.0f);
        glVertex2f(rightPillLeft, pY1 + 33.0f); glVertex2f(rightPillLeft - 4.0f, pY1 + 33.0f);

        glVertex2f(rightPillLeft - 4.0f, pY2 - 25.0f); glVertex2f(rightPillLeft, pY2 - 25.0f);
        glVertex2f(rightPillLeft, pY2 - 17.0f); glVertex2f(rightPillLeft - 4.0f, pY2 - 17.0f);
    glEnd();

    // ------------------------------------------------------------------------
    // 4. OPEN STEEL GRILL GATES (Detailed Wrought Iron)
    // ------------------------------------------------------------------------
    glColor3f(0.18f, 0.22f, 0.24f); // Metallic Dark Slate/Steel
    glLineWidth(2.5f);

    // --- Left Gate Door (Swung Slightly Open) ---
    float lStart = leftPillRight;
    float lEnd = 796.0f;
    float lTopY = pY1 + 18.0f;
    float lBotY = pY2 - 5.0f;

    // Outer Heavy Frame
    glBegin(GL_LINE_LOOP);
        glVertex2f(lStart, lTopY);
        glVertex2f(lEnd, lTopY + 6.0f);
        glVertex2f(lEnd, lBotY);
        glVertex2f(lStart, lBotY);
    glEnd();

    // Inner Horizontal Support Rails
    glLineWidth(1.8f);
    glBegin(GL_LINES);
        glVertex2f(lStart, lTopY + 30.0f); glVertex2f(lEnd, lTopY + 32.0f);
        glVertex2f(lStart, lBotY - 25.0f); glVertex2f(lEnd, lBotY - 25.0f);
    glEnd();

    // Vertical Steel Bars with Decorative Spearheads
    for (float x = lStart + 6.0f; x < lEnd; x += 7.5f) {
        float currentTopY = lTopY + ((x - lStart) / (lEnd - lStart)) * 6.0f;

        glLineWidth(1.8f);
        glBegin(GL_LINES);
            glVertex2f(x, currentTopY + 4.0f);
            glVertex2f(x, lBotY);
        glEnd();

        // Decorative Arrow/Spearhead Top
        glBegin(GL_TRIANGLES);
            glVertex2f(x - 2.0f, currentTopY + 4.0f);
            glVertex2f(x + 2.0f, currentTopY + 4.0f);
            glVertex2f(x, currentTopY - 3.0f);
        glEnd();
    }

    // --- Right Gate Door (Swung Slightly Open) ---
    float rStart = rightPillLeft;
    float rEnd = 804.0f;
    float rTopY = pY1 + 18.0f;
    float rBotY = pY2 - 5.0f;

    // Outer Heavy Frame
    glLineWidth(2.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(rStart, rTopY);
        glVertex2f(rEnd, rTopY + 6.0f);
        glVertex2f(rEnd, rBotY);
        glVertex2f(rStart, rBotY);
    glEnd();

    // Inner Horizontal Support Rails
    glLineWidth(1.8f);
    glBegin(GL_LINES);
        glVertex2f(rStart, rTopY + 30.0f); glVertex2f(rEnd, rTopY + 32.0f);
        glVertex2f(rStart, rBotY - 25.0f); glVertex2f(rEnd, rBotY - 25.0f);
    glEnd();

    // Vertical Steel Bars with Decorative Spearheads
    for (float x = rStart - 6.0f; x > rEnd; x -= 7.5f) {
        float currentTopY = rTopY + ((rStart - x) / (rStart - rEnd)) * 6.0f;

        glLineWidth(1.8f);
        glBegin(GL_LINES);
            glVertex2f(x, currentTopY + 4.0f);
            glVertex2f(x, rBotY);
        glEnd();

        // Decorative Arrow/Spearhead Top
        glBegin(GL_TRIANGLES);
            glVertex2f(x - 2.0f, currentTopY + 4.0f);
            glVertex2f(x + 2.0f, currentTopY + 4.0f);
            glVertex2f(x, currentTopY - 3.0f);
        glEnd();
    }

    glLineWidth(1.0f);
}
// ============================================================================
// HIGHLY DETAILED NOTICE BOARD (Placed next to right pillar at X: 910 to 980)
// Adjusted for New Boundary Height (Y: 610 to 715) with Pins, Notices & 3D Frame
// ============================================================================

void drawNoticeBoard()
{
    float bLeft = 910.0f;
    float bRight = 980.0f;
    float bTop = 612.0f;
    float bBottom = 665.0f;
    float groundY = 715.0f;

    // ------------------------------------------------------------------------
    // 1. SUPPORT LEGS (Thick Metallic/Wooden Posts)
    // ------------------------------------------------------------------------
    glColor3f(0.35f, 0.20f, 0.08f); // Dark Walnut Wood
    glBegin(GL_QUADS);
        // Left Leg
        glVertex2f(920.0f, bBottom);
        glVertex2f(925.0f, bBottom);
        glVertex2f(925.0f, groundY);
        glVertex2f(920.0f, groundY);

        // Right Leg
        glVertex2f(965.0f, bBottom);
        glVertex2f(970.0f, bBottom);
        glVertex2f(970.0f, groundY);
        glVertex2f(965.0f, groundY);
    glEnd();

    // Leg Ground Drop Shadow
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.1f, 0.1f, 0.1f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(915.0f, groundY - 2.0f);
        glVertex2f(975.0f, groundY - 2.0f);
        glVertex2f(975.0f, groundY + 3.0f);
        glVertex2f(915.0f, groundY + 3.0f);
    glEnd();
    glDisable(GL_BLEND);

    // ------------------------------------------------------------------------
    // 2. OUTER WOODEN FRAME & BACKING (3D Depth)
    // ------------------------------------------------------------------------
    // Frame Backing Shadow
    glColor3f(0.25f, 0.12f, 0.04f);
    glBegin(GL_QUADS);
        glVertex2f(bLeft - 2.0f, bTop - 2.0f);
        glVertex2f(bRight + 2.0f, bTop - 2.0f);
        glVertex2f(bRight + 2.0f, bBottom + 2.0f);
        glVertex2f(bLeft - 2.0f, bBottom + 2.0f);
    glEnd();

    // Main Wooden Frame Border
    glColor3f(0.48f, 0.28f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2f(bLeft, bTop);
        glVertex2f(bRight, bTop);
        glVertex2f(bRight, bBottom);
        glVertex2f(bLeft, bBottom);
    glEnd();

    // ------------------------------------------------------------------------
    // 3. INNER GREEN FELT BOARD SURFACE
    // ------------------------------------------------------------------------
    glColor3f(0.12f, 0.42f, 0.22f); // Forest Green Felt
    glBegin(GL_QUADS);
        glVertex2f(bLeft + 4.0f, bTop + 4.0f);
        glVertex2f(bRight - 4.0f, bTop + 4.0f);
        glVertex2f(bRight - 4.0f, bBottom - 4.0f);
        glVertex2f(bLeft + 4.0f, bBottom - 4.0f);
    glEnd();

    // Board Inner Bevel Shadow
    glColor3f(0.08f, 0.30f, 0.15f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2f(bLeft + 4.0f, bTop + 4.0f); glVertex2f(bRight - 4.0f, bTop + 4.0f);
        glVertex2f(bLeft + 4.0f, bTop + 4.0f); glVertex2f(bLeft + 4.0f, bBottom - 4.0f);
    glEnd();

    // ------------------------------------------------------------------------
    // 4. PINNED NOTICES / PAPERS WITH SIMULATED TEXT
    // ------------------------------------------------------------------------
    // --- Notice 1 (Left White Paper) ---
    glColor3f(0.96f, 0.96f, 0.94f);
    glBegin(GL_QUADS);
        glVertex2f(918.0f, 622.0f);
        glVertex2f(936.0f, 622.0f);
        glVertex2f(936.0f, 646.0f);
        glVertex2f(918.0f, 646.0f);
    glEnd();

    // Notice 1 Simulated Text Lines
    glColor3f(0.5f, 0.5f, 0.5f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
        glVertex2f(921.0f, 627.0f); glVertex2f(933.0f, 627.0f);
        glVertex2f(921.0f, 632.0f); glVertex2f(933.0f, 632.0f);
        glVertex2f(921.0f, 637.0f); glVertex2f(930.0f, 637.0f);
    glEnd();

    // Notice 1 Red Push Pin
    glColor3f(0.85f, 0.15f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(926.0f, 620.0f); glVertex2f(928.0f, 620.0f);
        glVertex2f(928.0f, 623.0f); glVertex2f(926.0f, 623.0f);
    glEnd();

    // --- Notice 2 (Right Slightly Tilted Yellowish Paper) ---
    glColor3f(0.98f, 0.96f, 0.82f); // Light Cream/Notice Paper
    glBegin(GL_QUADS);
        glVertex2f(942.0f, 626.0f);
        glVertex2f(964.0f, 625.0f);
        glVertex2f(964.0f, 654.0f);
        glVertex2f(942.0f, 655.0f);
    glEnd();

    // Notice 2 Simulated Text Lines
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_LINES);
        glVertex2f(945.0f, 631.0f); glVertex2f(960.0f, 631.0f);
        glVertex2f(945.0f, 636.0f); glVertex2f(961.0f, 636.0f);
        glVertex2f(945.0f, 641.0f); glVertex2f(958.0f, 641.0f);
        glVertex2f(945.0f, 646.0f); glVertex2f(955.0f, 646.0f);
    glEnd();

    // Notice 2 Blue Push Pin
    glColor3f(0.15f, 0.35f, 0.85f);
    glBegin(GL_QUADS);
        glVertex2f(952.0f, 623.0f); glVertex2f(954.0f, 623.0f);
        glVertex2f(954.0f, 626.0f); glVertex2f(952.0f, 626.0f);
    glEnd();

    // ------------------------------------------------------------------------
    // 5. 3D GABLE ROOF CAP (Protection Roof)
    // ------------------------------------------------------------------------
    // Roof Dark Backing
    glColor3f(0.25f, 0.12f, 0.04f);
    glBegin(GL_TRIANGLES);
        glVertex2f(bLeft - 8.0f, bTop + 1.0f);
        glVertex2f(bRight + 8.0f, bTop + 1.0f);
        glVertex2f(945.0f, bTop - 14.0f);
    glEnd();

    // Main Wooden Roof Face
    glColor3f(0.55f, 0.32f, 0.14f);
    glBegin(GL_TRIANGLES);
        glVertex2f(bLeft - 6.0f, bTop);
        glVertex2f(bRight + 6.0f, bTop);
        glVertex2f(945.0f, bTop - 12.0f);
    glEnd();

    // Roof Top Highlight Rim
    glColor3f(0.70f, 0.45f, 0.22f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(bLeft - 6.0f, bTop); glVertex2f(945.0f, bTop - 12.0f);
        glVertex2f(945.0f, bTop - 12.0f); glVertex2f(bRight + 6.0f, bTop);
    glEnd();

    glLineWidth(1.0f);
}
// ============================================================================
// HIGHLY DETAILED VINTAGE CLASSIC LAMP POSTS
// Height Adjusted for Footpath Base Alignment (Y: 570.0f to 715.0f)
// Features Cast-Iron Pedestal, Curved Lantern Bracket & Light Glow Effect
// ============================================================================

void drawLampPost()
{
    float lampPositionsX[] = { 100.0f, 680.0f, 1010.0f, 1500.0f };

    for (int i = 0; i < 4; i++) {
        float lx = lampPositionsX[i];
        float groundY = 715.0f; // Footpath Base Line

        // --------------------------------------------------------------------
        // 1. CAST-IRON PEDESTAL BASE (3D Tiered Foundation)
        // --------------------------------------------------------------------
        // Pedestal Shadow at Footpath
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.08f, 0.08f, 0.08f, 0.4f);
        glBegin(GL_QUADS);
            glVertex2f(lx - 12.0f, groundY - 2.0f);
            glVertex2f(lx + 12.0f, groundY - 2.0f);
            glVertex2f(lx + 12.0f, groundY + 2.0f);
            glVertex2f(lx - 12.0f, groundY + 2.0f);
        glEnd();
        glDisable(GL_BLEND);

        // Tier 1 Base Plinth
        glColor3f(0.12f, 0.12f, 0.14f);
        glBegin(GL_QUADS);
            glVertex2f(lx - 10.0f, groundY - 8.0f);
            glVertex2f(lx + 10.0f, groundY - 8.0f);
            glVertex2f(lx + 10.0f, groundY);
            glVertex2f(lx - 10.0f, groundY);
        glEnd();

        // Tier 2 Beveled Mid Base
        glColor3f(0.18f, 0.18f, 0.22f);
        glBegin(GL_POLYGON);
            glVertex2f(lx - 8.0f, groundY - 18.0f);
            glVertex2f(lx + 8.0f, groundY - 18.0f);
            glVertex2f(lx + 10.0f, groundY - 8.0f);
            glVertex2f(lx - 10.0f, groundY - 8.0f);
        glEnd();

        // Base Decorative Ring Collar
        glColor3f(0.25f, 0.25f, 0.30f);
        glBegin(GL_QUADS);
            glVertex2f(lx - 6.0f, groundY - 22.0f);
            glVertex2f(lx + 6.0f, groundY - 22.0f);
            glVertex2f(lx + 6.0f, groundY - 18.0f);
            glVertex2f(lx - 6.0f, groundY - 22.0f);
        glEnd();

        // --------------------------------------------------------------------
        // 2. MAIN METALLIC TAPERED SHAFT & RING RIBS
        // --------------------------------------------------------------------
        // Main Black Iron Pole Body
        glColor3f(0.15f, 0.15f, 0.18f);
        glBegin(GL_QUADS);
            glVertex2f(lx - 3.5f, 592.0f);
            glVertex2f(lx + 3.5f, 592.0f);
            glVertex2f(lx + 5.0f, groundY - 22.0f);
            glVertex2f(lx - 5.0f, groundY - 22.0f);
        glEnd();

        // Pole Highlighting Specular Line (3D Cylindrical Reflection)
        glColor3f(0.35f, 0.35f, 0.40f);
        glLineWidth(1.2f);
        glBegin(GL_LINES);
            glVertex2f(lx - 1.5f, 592.0f);
            glVertex2f(lx - 2.0f, groundY - 22.0f);
        glEnd();

        // Decorative Middle Ring Ribs
        glColor3f(0.28f, 0.28f, 0.32f);
        glBegin(GL_QUADS);
            glVertex2f(lx - 5.5f, 645.0f);
            glVertex2f(lx + 5.5f, 645.0f);
            glVertex2f(lx + 5.5f, 649.0f);
            glVertex2f(lx - 5.5f, 649.0f);
        glEnd();

        // --------------------------------------------------------------------
        // 3. CURVED LANTERN HOLDER BRACKETS
        // --------------------------------------------------------------------
        glColor3f(0.12f, 0.12f, 0.14f);
        glLineWidth(2.5f);
        glBegin(GL_LINES);
            // Left Bracket
            glVertex2f(lx, 595.0f);
            glVertex2f(lx - 9.0f, 590.0f);

            // Right Bracket
            glVertex2f(lx, 595.0f);
            glVertex2f(lx + 9.0f, 590.0f);
        glEnd();

        // --------------------------------------------------------------------
        // 4. SOFT RADIAL LIGHT GLOW / AURA (Translucent)
        // --------------------------------------------------------------------
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1.0f, 0.88f, 0.35f, 0.15f); // Soft Warm Yellow Aura
        glBegin(GL_POLYGON);
            glVertex2f(lx - 22.0f, 565.0f);
            glVertex2f(lx + 22.0f, 565.0f);
            glVertex2f(lx + 35.0f, 615.0f);
            glVertex2f(lx - 35.0f, 615.0f);
        glEnd();
        glDisable(GL_BLEND);

        // --------------------------------------------------------------------
        // 5. GLOWING LANTERN HOUSING & GLASS PANELS
        // --------------------------------------------------------------------
        // Warm Yellow Glowing Core Bulb
        glColor3f(1.0f, 0.90f, 0.40f);
        glBegin(GL_QUADS);
            glVertex2f(lx - 6.0f, 572.0f);
            glVertex2f(lx + 6.0f, 572.0f);
            glVertex2f(lx + 4.0f, 588.0f);
            glVertex2f(lx - 4.0f, 588.0f);
        glEnd();

        // Outer Lantern Vintage Frame (Black Iron Outline)
        glColor3f(0.10f, 0.10f, 0.12f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(lx - 8.0f, 570.0f);
            glVertex2f(lx + 8.0f, 570.0f);
            glVertex2f(lx + 5.0f, 590.0f);
            glVertex2f(lx - 5.0f, 590.0f);
        glEnd();

        // Vertical Glass Pane Dividers
        glLineWidth(1.0f);
        glBegin(GL_LINES);
            glVertex2f(lx, 570.0f);
            glVertex2f(lx, 590.0f);
        glEnd();

        // --------------------------------------------------------------------
        // 6. LANTERN TOP CAP & FINIAL
        // --------------------------------------------------------------------
        // Roof Cap
        glColor3f(0.18f, 0.18f, 0.20f);
        glBegin(GL_TRIANGLES);
            glVertex2f(lx - 10.0f, 570.0f);
            glVertex2f(lx + 10.0f, 570.0f);
            glVertex2f(lx, 560.0f);
        glEnd();

        // Top Decorative Finial Tip
        glBegin(GL_TRIANGLES);
            glVertex2f(lx - 2.0f, 560.0f);
            glVertex2f(lx + 2.0f, 560.0f);
            glVertex2f(lx, 553.0f);
        glEnd();
    }
    glLineWidth(1.0f);
}
// ============================================================================
// REALISTIC PARK BENCH (Low-Height Straight Legs, Wide Seating & Armrests)
// Based on Modern Public Park Bench Reference
// Footpath Alignment: Touches Ground Line properly without high stretch
// ============================================================================

void drawBench()
{
    float bx = 210.0f;          // Bench Start X Position
    float bWidth = 130.0f;      // Bench Width
    float groundY = 715.0f;     // Footpath Surface Height
    float seatY = 675.0f;       // Seat Level (Realistic low height: 30 units legs)

    // ------------------------------------------------------------------------
    // 1. DROP SHADOW ON FOOTPATH SURFACE
    // ------------------------------------------------------------------------
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.10f, 0.10f, 0.10f, 0.30f);
    glBegin(GL_POLYGON);
        glVertex2f(bx - 10.0f, groundY + 3.0f);
        glVertex2f(bx + bWidth + 10.0f, groundY + 3.0f);
        glVertex2f(bx + bWidth + 5.0f, groundY - 1.0f);
        glVertex2f(bx - 5.0f, groundY - 1.0f);
    glEnd();
    glDisable(GL_BLEND);

    // ------------------------------------------------------------------------
    // 2. SHORT VERTICAL METAL LEGS (Front & Back Straight Frame)
    // ------------------------------------------------------------------------
    glColor3f(0.20f, 0.22f, 0.25f); // Steel / Dark Iron Metallic Tone

    // Left Front Leg
    glBegin(GL_QUADS);
        glVertex2f(bx + 10.0f, seatY + 12.0f);
        glVertex2f(bx + 16.0f, seatY + 12.0f);
        glVertex2f(bx + 16.0f, groundY);
        glVertex2f(bx + 10.0f, groundY);
    glEnd();

    // Left Rear Leg
    glBegin(GL_QUADS);
        glVertex2f(bx + 22.0f, seatY);
        glVertex2f(bx + 27.0f, seatY);
        glVertex2f(bx + 27.0f, groundY);
        glVertex2f(bx + 22.0f, groundY);
    glEnd();

    // Right Front Leg
    glBegin(GL_QUADS);
        glVertex2f(bx + bWidth - 16.0f, seatY + 12.0f);
        glVertex2f(bx + bWidth - 10.0f, seatY + 12.0f);
        glVertex2f(bx + bWidth - 10.0f, groundY);
        glVertex2f(bx + bWidth - 16.0f, groundY);
    glEnd();

    // Right Rear Leg
    glBegin(GL_QUADS);
        glVertex2f(bx + bWidth - 27.0f, seatY);
        glVertex2f(bx + bWidth - 22.0f, seatY);
        glVertex2f(bx + bWidth - 22.0f, groundY);
        glVertex2f(bx + bWidth - 27.0f, groundY);
    glEnd();

    // Vertical Backrest Frame Rods (Behind Wooden Slats)
    glLineWidth(4.0f);
    glBegin(GL_LINES);
        glVertex2f(bx + 24.0f, seatY);
        glVertex2f(bx + 24.0f, seatY - 32.0f);

        glVertex2f(bx + bWidth - 24.0f, seatY);
        glVertex2f(bx + bWidth - 24.0f, seatY - 32.0f);
    glEnd();
    // ------------------------------------------------------------------------
    // 3. BACKREST WOODEN SLATS (Top Section)
    // ------------------------------------------------------------------------
    float backOffsetY[] = { -30.0f, -22.0f, -14.0f, -6.0f };

    for (int i = 0; i < 4; i++) {
        float y = seatY + backOffsetY[i];

        // Dark Wood Edge Shadow
        glColor3f(0.28f, 0.15f, 0.08f);
        glBegin(GL_QUADS);
            glVertex2f(bx + 4.0f, y);
            glVertex2f(bx + bWidth - 4.0f, y);
            glVertex2f(bx + bWidth - 4.0f, y + 6.0f);
            glVertex2f(bx + 4.0f, y + 6.0f);
        glEnd();

        // Main Mahogany Wood Body
        glColor3f(0.58f, 0.32f, 0.16f);
        glBegin(GL_QUADS);
            glVertex2f(bx + 5.0f, y + 0.8f);
            glVertex2f(bx + bWidth - 5.0f, y + 0.8f);
            glVertex2f(bx + bWidth - 5.0f, y + 5.2f);
            glVertex2f(bx + 5.0f, y + 5.2f);
        glEnd();

        // Top Highlight Rim
        glColor3f(0.72f, 0.44f, 0.22f);
        glLineWidth(1.2f);
        glBegin(GL_LINES);
            glVertex2f(bx + 5.0f, y + 5.2f);
            glVertex2f(bx + bWidth - 5.0f, y + 5.2f);
        glEnd();
    }

    // ------------------------------------------------------------------------
    // 4. MAIN SEATING SURFACE (Thick Horizontal Slab)
    // ------------------------------------------------------------------------
    // Base Under-Shadow
    glColor3f(0.22f, 0.12f, 0.05f);
    glBegin(GL_QUADS);
        glVertex2f(bx, seatY);
        glVertex2f(bx + bWidth, seatY);
        glVertex2f(bx + bWidth, seatY + 12.0f);
        glVertex2f(bx, seatY + 12.0f);
    glEnd();

    // Front Thick Wood Face
    glColor3f(0.52f, 0.28f, 0.14f);
    glBegin(GL_QUADS);
        glVertex2f(bx + 1.0f, seatY + 1.0f);
        glVertex2f(bx + bWidth - 1.0f, seatY + 1.0f);
        glVertex2f(bx + bWidth - 1.0f, seatY + 11.0f);
        glVertex2f(bx + 1.0f, seatY + 11.0f);
    glEnd();

    // Top Surface Light Highlight
    glColor3f(0.68f, 0.38f, 0.20f);
    glBegin(GL_QUADS);
        glVertex2f(bx + 1.0f, seatY + 1.0f);
        glVertex2f(bx + bWidth - 1.0f, seatY + 1.0f);
        glVertex2f(bx + bWidth - 1.0f, seatY + 4.0f);
        glVertex2f(bx + 1.0f, seatY + 4.0f);
    glEnd();


    glLineWidth(1.0f);
}

// ============================================================================
// REFINED WALL-MOUNTED DRINKING WATER STATION (Realistic Tile & Basin Detail)
// Kept exact original structure (X: 360 to 410) with realistic textures/shading
// ============================================================================

void drawWaterStation()
{
    float wx = 360.0f;
    float wy = 665.0f;

    // ------------------------------------------------------------------------
    // 1. TILED WALL BACKING (Light Cyan Tiles with Grid Lines)
    // ------------------------------------------------------------------------
    // Main Tile Surface
    glColor3f(0.82f, 0.92f, 0.96f); // Soft Cyan Ceramic Tone
    glBegin(GL_QUADS);
        glVertex2f(wx, wy - 30.0f);
        glVertex2f(wx + 50.0f, wy - 30.0f);
        glVertex2f(wx + 50.0f, wy + 25.0f);
        glVertex2f(wx, wy + 25.0f);
    glEnd();

    // Tile Grout Grid Lines (Creates realistic ceramic tile effect)
    glColor3f(0.70f, 0.82f, 0.88f);
    glLineWidth(1.2f);
    glBegin(GL_LINES);
        // Vertical Grout Lines
        glVertex2f(wx + 16.6f, wy - 30.0f); glVertex2f(wx + 16.6f, wy + 25.0f);
        glVertex2f(wx + 33.3f, wy - 30.0f); glVertex2f(wx + 33.3f, wy + 25.0f);
        // Horizontal Grout Lines
        glVertex2f(wx, wy - 12.0f); glVertex2f(wx + 50.0f, wy - 12.0f);
        glVertex2f(wx, wy + 6.0f);  glVertex2f(wx + 50.0f, wy + 6.0f);
    glEnd();

    // Tile Wall Border Outer Line
    glColor3f(0.55f, 0.68f, 0.75f);
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(wx, wy - 30.0f);
        glVertex2f(wx + 50.0f, wy - 30.0f);
        glVertex2f(wx + 50.0f, wy + 25.0f);
        glVertex2f(wx, wy + 25.0f);
    glEnd();

    // ------------------------------------------------------------------------
    // 2. STAINLESS STEEL BASIN (With Metallic 3D Shading & Drain)
    // ------------------------------------------------------------------------
    // Basin Outer Rim Shadow
    glColor3f(0.45f, 0.48f, 0.52f);
    glBegin(GL_POLYGON);
        glVertex2f(wx + 4.0f, wy + 4.0f);
        glVertex2f(wx + 46.0f, wy + 4.0f);
        glVertex2f(wx + 41.0f, wy + 19.5f);
        glVertex2f(wx + 9.0f, wy + 19.5f);
    glEnd();

    // Main Metallic Basin Face
    glColor3f(0.75f, 0.78f, 0.82f); // Stainless Steel Silver
    glBegin(GL_POLYGON);
        glVertex2f(wx + 5.0f, wy + 5.0f);
        glVertex2f(wx + 45.0f, wy + 5.0f);
        glVertex2f(wx + 40.0f, wy + 18.0f);
        glVertex2f(wx + 10.0f, wy + 18.0f);
    glEnd();

    // Inner Basin Curved Shading (Depth Gradient)
    glColor3f(0.62f, 0.65f, 0.70f);
    glBegin(GL_POLYGON);
        glVertex2f(wx + 8.0f, wy + 7.0f);
        glVertex2f(wx + 42.0f, wy + 7.0f);
        glVertex2f(wx + 38.0f, wy + 14.0f);
        glVertex2f(wx + 12.0f, wy + 14.0f);
    glEnd();

    // Drain Holes in Basin
    glColor3f(0.20f, 0.22f, 0.25f);
    glBegin(GL_QUADS);
        glVertex2f(wx + 23.0f, wy + 9.0f);
        glVertex2f(wx + 27.0f, wy + 9.0f);
        glVertex2f(wx + 27.0f, wy + 11.0f);
        glVertex2f(wx + 23.0f, wy + 11.0f);
    glEnd();

    // ------------------------------------------------------------------------
    // 3. REALISTIC CHROME FAUCETS / TAPS & WATER DROPS
    // ------------------------------------------------------------------------
    float tapX[] = { wx + 15.0f, wx + 35.0f };

    for (int i = 0; i < 2; i++) {
        float tx = tapX[i];

        // Wall Mount Base Ring
        glColor3f(0.40f, 0.42f, 0.46f);
        glBegin(GL_QUADS);
            glVertex2f(tx - 3.0f, wy - 11.0f);
            glVertex2f(tx + 3.0f, wy - 11.0f);
            glVertex2f(tx + 3.0f, wy - 8.0f);
            glVertex2f(tx - 3.0f, wy - 8.0f);
        glEnd();

        // Curved Gooseneck Tap Pipe
        glColor3f(0.28f, 0.30f, 0.35f); // Chrome Steel Tone
        glLineWidth(3.5f);
        glBegin(GL_LINE_STRIP);
            glVertex2f(tx, wy - 10.0f);
            glVertex2f(tx, wy + 1.0f);
            glVertex2f(tx + 4.0f, wy + 3.0f);
            glVertex2f(tx + 4.0f, wy + 6.0f);
        glEnd();

        // Metallic Highlight on Pipe
        glColor3f(0.85f, 0.88f, 0.92f);
        glLineWidth(1.2f);
        glBegin(GL_LINE_STRIP);
            glVertex2f(tx - 0.8f, wy - 10.0f);
            glVertex2f(tx - 0.8f, wy + 0.5f);
            glVertex2f(tx + 3.2f, wy + 2.5f);
        glEnd();

        // Water Drop (Blue Glassy Effect)
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.20f, 0.60f, 0.95f, 0.75f);
        glBegin(GL_POLYGON);
            glVertex2f(tx + 4.0f, wy + 8.0f);
            glVertex2f(tx + 5.0f, wy + 11.0f);
            glVertex2f(tx + 3.0f, wy + 11.0f);
        glEnd();
        glDisable(GL_BLEND);
    }

    // Reset Line Width
    glLineWidth(1.0f);
}
// ============================================================================
// 7. BICYCLE PARKING STAND & CYCLES (Aligned to Notice Board & Lamp Post Base)
// ============================================================================

#include <cmath>

void drawCycleParking()
{
    float cx = 1120.0f;
    // Adjusted Y coordinate: Aligned perfectly with Notice Board & Lamp Post Base Level
    float cy = 712.0f;
    const float PI = 3.14159265f;

    // ------------------------------------------------------------------------
    // 1. GROUND DROP SHADOW (On Platform Walkway Surface)
    // ------------------------------------------------------------------------
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.08f, 0.08f, 0.08f, 0.35f);
    glBegin(GL_POLYGON);
        glVertex2f(cx - 5.0f, cy + 2.0f);
        glVertex2f(cx + 95.0f, cy + 2.0f);
        glVertex2f(cx + 98.0f, cy - 3.0f);
        glVertex2f(cx - 2.0f, cy - 3.0f);
    glEnd();
    glDisable(GL_BLEND);

    // ------------------------------------------------------------------------
    // 2. PARKING RACK (Base directly sits on the Walkway Surface)
    // ------------------------------------------------------------------------
    // Horizontal Ground Bar
    glColor3f(0.40f, 0.43f, 0.48f);
    glBegin(GL_QUADS);
        glVertex2f(cx, cy);
        glVertex2f(cx + 90.0f, cy);
        glVertex2f(cx + 90.0f, cy + 3.0f);
        glVertex2f(cx, cy + 3.0f);
    glEnd();

    // Steel Arch Slots
    for (float x = cx + 8.0f; x <= cx + 80.0f; x += 18.0f) {
        glColor3f(0.30f, 0.32f, 0.36f);
        glLineWidth(3.0f);
        glBegin(GL_LINE_STRIP);
            glVertex2f(x, cy);
            glVertex2f(x + 2.0f, cy - 22.0f);
            glVertex2f(x + 8.0f, cy - 22.0f);
            glVertex2f(x + 10.0f, cy);
        glEnd();

        glColor3f(0.70f, 0.73f, 0.78f);
        glLineWidth(1.2f);
        glBegin(GL_LINE_STRIP);
            glVertex2f(x + 0.5f, cy);
            glVertex2f(x + 2.5f, cy - 21.5f);
            glVertex2f(x + 7.5f, cy - 21.5f);
        glEnd();
    }

    // ------------------------------------------------------------------------
    // Helper Function to Draw Bicycle
    // ------------------------------------------------------------------------
    auto drawBicycle = [&](float bx, float rR, float rG, float rB) {
        float radius = 10.0f;
        float rearWheelX = bx;
        float frontWheelX = bx + 32.0f;
        float wheelY = cy - radius + 1.0f; // Wheels aligned with rack base

        // --- WHEELS & SPOKES ---
        float wheelsX[] = { rearWheelX, frontWheelX };
        for (int w = 0; w < 2; w++) {
            float wx = wheelsX[w];

            // Rubber Tire
            glColor3f(0.12f, 0.12f, 0.14f);
            glBegin(GL_POLYGON);
                for (int i = 0; i < 20; i++) {
                    float a = i * 2.0f * PI / 20.0f;
                    glVertex2f(wx + radius * cos(a), wheelY + radius * sin(a));
                }
            glEnd();

            // Inner Silver Rim
            glColor3f(0.75f, 0.78f, 0.82f);
            glBegin(GL_POLYGON);
                for (int i = 0; i < 20; i++) {
                    float a = i * 2.0f * PI / 20.0f;
                    glVertex2f(wx + (radius - 2.5f) * cos(a), wheelY + (radius - 2.5f) * sin(a));
                }
            glEnd();

            // Spokes
            glColor3f(0.35f, 0.38f, 0.42f);
            glLineWidth(1.0f);
            glBegin(GL_LINES);
                for (int i = 0; i < 8; i++) {
                    float a = i * 2.0f * PI / 8.0f;
                    glVertex2f(wx, wheelY);
                    glVertex2f(wx + (radius - 3.0f) * cos(a), wheelY + (radius - 3.0f) * sin(a));
                }
            glEnd();

            // Axle Hub
            glColor3f(0.1f, 0.1f, 0.1f);
            glBegin(GL_POLYGON);
                for (int i = 0; i < 8; i++) {
                    float a = i * 2.0f * PI / 8.0f;
                    glVertex2f(wx + 1.5f * cos(a), wheelY + 1.5f * sin(a));
                }
            glEnd();
        }

        // --- DIAMOND FRAME ---
        float bbX = bx + 12.0f, bbY = wheelY;
        float seatX = bx + 8.0f, seatY = wheelY - 16.0f;
        float headX = bx + 26.0f, headY = wheelY - 17.0f;

        glColor3f(rR, rG, rB);
        glLineWidth(2.5f);
        glBegin(GL_LINES);
            glVertex2f(rearWheelX, wheelY); glVertex2f(seatX, seatY);
            glVertex2f(rearWheelX, wheelY); glVertex2f(bbX, bbY);
            glVertex2f(seatX, seatY);       glVertex2f(bbX, bbY);
            glVertex2f(seatX, seatY);       glVertex2f(headX, headY);
            glVertex2f(bbX, bbY);           glVertex2f(headX, headY);
            glVertex2f(headX, headY);       glVertex2f(frontWheelX, wheelY);
        glEnd();

        // --- HANDLEBAR & SADDLE ---
        glColor3f(0.2f, 0.2f, 0.2f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
            glVertex2f(headX, headY);
            glVertex2f(headX + 1.0f, headY - 4.0f);
            glVertex2f(headX - 3.0f, headY - 4.0f);
            glVertex2f(headX + 4.0f, headY - 4.0f);
        glEnd();

        glColor3f(0.1f, 0.1f, 0.1f);
        glBegin(GL_POLYGON);
            glVertex2f(seatX - 4.0f, seatY - 2.5f);
            glVertex2f(seatX + 3.0f, seatY - 2.5f);
            glVertex2f(seatX + 4.0f, seatY - 1.0f);
            glVertex2f(seatX - 3.0f, seatY - 1.0f);
        glEnd();
    };

    // ------------------------------------------------------------------------
    // 3. DRAW PARKED BICYCLES
    // ------------------------------------------------------------------------
    drawBicycle(cx + 12.0f, 0.85f, 0.15f, 0.15f); // Red
    drawBicycle(cx + 48.0f, 0.15f, 0.40f, 0.88f); // Blue

    glLineWidth(1.0f);
}
// ============================================================================
// 8. REALISTIC RECYCLING DUSTBINS WITH 3D SHADING & LID (Aligned to Platform)
// ============================================================================

void drawDustbin()
{
    // X Positions: Left Green Bin & Right Blue Bin
    float binX[] = { 520.0f, 1060.0f };

    for(int i = 0; i < 2; i++) {
        float bx = binX[i];
        // Aligned with the Walkway Platform floor level (same as lamp posts / notice board)
        float by = 706.0f;

        // --------------------------------------------------------------------
        // 1. GROUND DROP SHADOW (On Platform Surface)
        // --------------------------------------------------------------------
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.08f, 0.08f, 0.08f, 0.35f);
        glBegin(GL_POLYGON);
            glVertex2f(bx - 3.0f, by + 1.0f);
            glVertex2f(bx + 21.0f, by + 1.0f);
            glVertex2f(bx + 23.0f, by - 3.0f);
            glVertex2f(bx - 1.0f, by - 3.0f);
        glEnd();
        glDisable(GL_BLEND);

        // --------------------------------------------------------------------
        // 2. MAIN BIN BODY (Tapered 3D Plastic Container)
        // --------------------------------------------------------------------
        // Base Color: Green for Bio-Waste, Blue for Recycling
        if (i == 0) glColor3f(0.12f, 0.68f, 0.28f); // Vivid Bio Green
        else        glColor3f(0.12f, 0.48f, 0.88f); // Vivid Recycle Blue

        // Main Bin Body (Wider at Top, Slightly Narrower at Base)
        glBegin(GL_POLYGON);
            glVertex2f(bx + 2.0f, by);          // Bottom Left
            glVertex2f(bx + 16.0f, by);         // Bottom Right
            glVertex2f(bx + 18.0f, by - 24.0f); // Top Right
            glVertex2f(bx, by - 24.0f);         // Top Left
        glEnd();

        // 3D Side Shadow Gradient (Gives Curved Cylinder Depth)
        glColor3f(0.05f, 0.25f, 0.10f); // Shadow Overlay Color
        if (i == 1) glColor3f(0.05f, 0.20f, 0.45f);

        glBegin(GL_POLYGON);
            glVertex2f(bx + 12.0f, by);
            glVertex2f(bx + 16.0f, by);
            glVertex2f(bx + 18.0f, by - 24.0f);
            glVertex2f(bx + 14.0f, by - 24.0f);
        glEnd();

        // Front Rim / Mold Line Shading
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(1.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(bx + 2.0f, by);
            glVertex2f(bx + 16.0f, by);
            glVertex2f(bx + 18.0f, by - 24.0f);
            glVertex2f(bx, by - 24.0f);
        glEnd();

        // --------------------------------------------------------------------
        // 3. DUSTBIN LID / CAP & HANDLE (Heavy Duty Plastic Lid)
        // --------------------------------------------------------------------
        // Lid Base Overhang Lip
        glColor3f(0.18f, 0.18f, 0.20f); // Dark Slate Gray Cap
        glBegin(GL_POLYGON);
            glVertex2f(bx - 2.0f, by - 24.0f);
            glVertex2f(bx + 20.0f, by - 24.0f);
            glVertex2f(bx + 19.0f, by - 28.0f);
            glVertex2f(bx - 1.0f, by - 28.0f);
        glEnd();

        // Lid Top Dome / Raised Center
        glColor3f(0.28f, 0.28f, 0.32f);
        glBegin(GL_POLYGON);
            glVertex2f(bx + 1.0f, by - 28.0f);
            glVertex2f(bx + 17.0f, by - 28.0f);
            glVertex2f(bx + 15.0f, by - 31.0f);
            glVertex2f(bx + 3.0f, by - 31.0f);
        glEnd();

        // Lid Top Grab Handle
        glColor3f(0.10f, 0.10f, 0.12f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_STRIP);
            glVertex2f(bx + 6.0f, by - 31.0f);
            glVertex2f(bx + 6.0f, by - 33.5f);
            glVertex2f(bx + 12.0f, by - 33.5f);
            glVertex2f(bx + 12.0f, by - 31.0f);
        glEnd();

        // --------------------------------------------------------------------
        // 4. RECYCLE / BIO ICON (Solid White Emblem)
        // --------------------------------------------------------------------
        glColor3f(0.95f, 0.98f, 1.0f); // Pure Bright White

        // Filled Recycle Triangle Emblem
        glBegin(GL_TRIANGLES);
            glVertex2f(bx + 9.0f, by - 18.0f);  // Top Peak
            glVertex2f(bx + 5.0f, by - 8.0f);   // Bottom Left
            glVertex2f(bx + 13.0f, by - 8.0f);  // Bottom Right
        glEnd();

        // Inner Cutout to form Arrow Hole Look
        if (i == 0) glColor3f(0.12f, 0.68f, 0.28f);
        else        glColor3f(0.12f, 0.48f, 0.88f);

        glBegin(GL_TRIANGLES);
            glVertex2f(bx + 9.0f, by - 15.5f);
            glVertex2f(bx + 7.0f, by - 10.0f);
            glVertex2f(bx + 11.0f, by - 10.0f);
        glEnd();
    }

    // Reset Line Width
    glLineWidth(1.0f);
}
/* ---- Footpath Layer ---- */
// ============================================================================
// HIGHLY DETAILED & REALISTIC FOOTPATH / SIDEWALK LAYER
// Extended Depth with Curbstones, Interlocking Pavement Tiles & Gate Ramp
// ============================================================================

void drawFootpath()
{
    float topY = 715.0f;       // Connects seamlessly to Boundary Wall Base
    float bottomY = 745.0f;    // Extends down to the Main Road Edge
    float curbHeight = 6.0f;   // Raised Curbstone Edge Height

    float leftPillarX = 720.0f;
    float rightPillarX = 880.0f;

    // ------------------------------------------------------------------------
    // 1. FOOTPATH BASE SLAB (Main Walkway Surface Tone)
    // ------------------------------------------------------------------------
    glColor3f(0.72f, 0.72f, 0.70f); // Light Ash Concrete Pavement Tone
    glBegin(GL_QUADS);
        // Left Walkway Surface
        glVertex2f(0.0f, topY);
        glVertex2f(leftPillarX, topY);
        glVertex2f(leftPillarX, bottomY - curbHeight);
        glVertex2f(0.0f, bottomY - curbHeight);

        // Right Walkway Surface
        glVertex2f(rightPillarX, topY);
        glVertex2f(1600.0f, topY);
        glVertex2f(1600.0f, bottomY - curbHeight);
        glVertex2f(rightPillarX, bottomY - curbHeight);

        // Gate Center Ramp / Driveway Connection Area
        glVertex2f(leftPillarX, topY);
        glVertex2f(rightPillarX, topY);
        glVertex2f(rightPillarX, bottomY);
        glVertex2f(leftPillarX, bottomY);
    glEnd();

    // ------------------------------------------------------------------------
    // 2. INTERLOCKING PAVEMENT TILE GRID (Horizontal & Vertical Joints)
    // ------------------------------------------------------------------------
    glColor3f(0.62f, 0.62f, 0.60f); // Tile Joint Groove Color
    glLineWidth(1.0f);

    // Horizontal Tile Joint Lines
    glBegin(GL_LINES);
    for (float y = topY + 6.0f; y < bottomY - curbHeight; y += 6.0f) {
        // Left Side Tiles
        glVertex2f(0.0f, y);
        glVertex2f(leftPillarX, y);

        // Right Side Tiles
        glVertex2f(rightPillarX, y);
        glVertex2f(1600.0f, y);
    }
    glEnd();

    // Staggered Vertical Tile Joint Lines
    int rowCounter = 0;
    glBegin(GL_LINES);
    for (float y = topY; y < bottomY - curbHeight; y += 6.0f) {
        float xShift = (rowCounter % 2 == 0) ? 0.0f : 10.0f;

        // Left Walkway Grid
        for (float x = xShift; x < leftPillarX; x += 20.0f) {
            glVertex2f(x, y);
            glVertex2f(x, y + 6.0f);
        }
        // Right Walkway Grid
        for (float x = rightPillarX + xShift; x < 1600.0f; x += 20.0f) {
            glVertex2f(x, y);
            glVertex2f(x, y + 6.0f);
        }
        rowCounter++;
    }
    glEnd();

    // ------------------------------------------------------------------------
    // 3. GATE ENTRANCE TILE RAMP (Tactile Pattern for Gate Opening)
    // ------------------------------------------------------------------------
    // Darker Asphalt/Paver Blend for Entrance Ramp
    glColor3f(0.65f, 0.65f, 0.63f);
    glBegin(GL_QUADS);
        glVertex2f(leftPillarX + 2.0f, topY);
        glVertex2f(rightPillarX - 2.0f, topY);
        glVertex2f(rightPillarX - 2.0f, bottomY);
        glVertex2f(leftPillarX + 2.0f, bottomY);
    glEnd();

    // Ramp Horizontal Tread Texture Lines
    glColor3f(0.55f, 0.55f, 0.53f);
    glLineWidth(1.2f);
    glBegin(GL_LINES);
    for (float y = topY + 5.0f; y < bottomY; y += 5.0f) {
        glVertex2f(leftPillarX + 2.0f, y);
        glVertex2f(rightPillarX - 2.0f, y);
    }
    glEnd();

    // ------------------------------------------------------------------------
    // 4. 3D FRONT CURBSTONES (Border Blocks along Road Edge)
    // ------------------------------------------------------------------------
    // Alternating Dual-Tone Concrete Curb Blocks
    for (float x = 0.0f; x < 1600.0f; x += 40.0f) {
        // Skip Curb for Gate Entrance Ramp Area
        if (x >= leftPillarX - 10.0f && x < rightPillarX) continue;

        // Alternate Block Color (Light Grey / Charcoal Grey Concrete)
        if (((int)(x / 40.0f)) % 2 == 0) {
            glColor3f(0.80f, 0.80f, 0.78f); // Light Concrete Block
        } else {
            glColor3f(0.45f, 0.45f, 0.45f); // Dark Charcoal Block
        }

        // Top Face of Curbstone
        glBegin(GL_QUADS);
            glVertex2f(x, bottomY - curbHeight);
            glVertex2f(x + 39.0f, bottomY - curbHeight);
            glVertex2f(x + 39.0f, bottomY - 2.0f);
            glVertex2f(x, bottomY - 2.0f);
        glEnd();

        // Front Bevel Face of Curbstone (3D Perspective Shadow)
        glColor3f(0.32f, 0.32f, 0.32f);
        glBegin(GL_QUADS);
            glVertex2f(x, bottomY - 2.0f);
            glVertex2f(x + 39.0f, bottomY - 2.0f);
            glVertex2f(x + 39.0f, bottomY);
            glVertex2f(x, bottomY);
        glEnd();
    }

    // Curbstone Vertical Separation Grooves
    glColor3f(0.20f, 0.20f, 0.20f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    for (float x = 0.0f; x <= 1600.0f; x += 40.0f) {
        if (x > leftPillarX && x < rightPillarX) continue;
        glVertex2f(x, bottomY - curbHeight);
        glVertex2f(x, bottomY);
    }
    glEnd();

    // ------------------------------------------------------------------------
    // 5. SHADOW & HIGHLIGHT LINES FOR REALISTIC DEPTH
    // ------------------------------------------------------------------------
    // Boundary Wall Base Contact Shadow (Top Edge)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.1f, 0.1f, 0.1f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, topY);
        glVertex2f(1600.0f, topY);
        glVertex2f(1600.0f, topY + 3.0f);
        glVertex2f(0.0f, topY + 3.0f);
    glEnd();
    glDisable(GL_BLEND);

    // Curb Top Edge Highlight Line
    glColor3f(0.90f, 0.90f, 0.88f);
    glLineWidth(1.2f);
    glBegin(GL_LINES);
        glVertex2f(0.0f, bottomY - curbHeight);
        glVertex2f(leftPillarX, bottomY - curbHeight);

        glVertex2f(rightPillarX, bottomY - curbHeight);
        glVertex2f(1600.0f, bottomY - curbHeight);
    glEnd();

    glLineWidth(1.0f);
}

/* ---- Road Layer ---- */
// ============================================================================
// ROAD & TRAFFIC ELEMENTS (Screen Resolution: 1600 x 900)
// Fully detailed 2D/3D OpenGL primitives with shading, highlights & curb details
// ============================================================================

#include <cmath>

// ----------------------------------------------------------------------------
// 1. MAIN ASPHALT ROAD SURFACE & CURB
// ----------------------------------------------------------------------------
void drawRoad()
{
    // Dark Charcoal Asphalt Road Surface (Y: 730 to 860)
    glColor3f(0.20f, 0.22f, 0.24f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 730.0f);
        glVertex2f(1600.0f, 730.0f);
        glVertex2f(1600.0f, 900.0f);
        glVertex2f(0.0f, 900.0f);
    glEnd();

    // Road Texture / Walkway Shadow Overlay (Under Walkway Platform Edge)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 730.0f);
        glVertex2f(1600.0f, 730.0f);
        glVertex2f(1600.0f, 738.0f);
        glVertex2f(0.0f, 738.0f);
    glEnd();
    glDisable(GL_BLEND);

    // Alternating Black and White Curb Blocks Along Walkway Platform (Y: 724 to 730)
    float blockWidth = 40.0f;
    for (float x = 0.0f; x < 1600.0f; x += blockWidth) {
        int index = (int)(x / blockWidth);
        if (index % 2 == 0) glColor3f(0.15f, 0.15f, 0.15f); // Black Curb
        else                glColor3f(0.92f, 0.92f, 0.92f); // White Curb

        glBegin(GL_QUADS);
            glVertex2f(x, 724.0f);
            glVertex2f(x + blockWidth, 724.0f);
            glVertex2f(x + blockWidth, 730.0f);
            glVertex2f(x, 730.0f);
        glEnd();
    }
}

// ----------------------------------------------------------------------------
// 1. ROAD DIVIDER & REFLECTOR STUDS (Centered at Y = 815.0f)
// ----------------------------------------------------------------------------
void drawRoadDivider()
{
    float midY = 815.0f;        // Vertical exact center of the road surface (730 to 900)
    float dashWidth = 45.0f;
    float gapWidth = 35.0f;

    // Boundaries to skip drawing divider lines (Speed Breaker & Zebra Crossing areas)
    float speedBreakerStart = 480.0f;
    float speedBreakerEnd   = 580.0f;
    float zebraStart        = 680.0f;
    float zebraEnd          = 980.0f;

    for (float x = 0.0f; x < 1600.0f; x += (dashWidth + gapWidth)) {

        // Skip divider inside Speed Breaker or Zebra Crossing zone
        if ((x + dashWidth > speedBreakerStart && x < speedBreakerEnd) ||
            (x + dashWidth > zebraStart && x < zebraEnd)) {
            continue;
        }

        // White Center Line Dash Stripe
        glColor3f(0.92f, 0.92f, 0.95f);
        glBegin(GL_QUADS);
            glVertex2f(x, midY - 2.5f);
            glVertex2f(x + dashWidth, midY - 2.5f);
            glVertex2f(x + dashWidth, midY + 2.5f);
            glVertex2f(x, midY + 2.5f);
        glEnd();

        // 3D Amber Cat's Eye Reflector Studs
        float catEyeX = x + dashWidth + (gapWidth / 2.0f) - 3.0f;

        if ((catEyeX >= speedBreakerStart - 10.0f && catEyeX <= speedBreakerEnd + 10.0f) ||
            (catEyeX >= zebraStart - 10.0f && catEyeX <= zebraEnd + 10.0f) ||
            (catEyeX + 6.0f > 1600.0f)) continue;

        glColor3f(0.98f, 0.72f, 0.08f); // High-vis Amber
        glBegin(GL_QUADS);
            glVertex2f(catEyeX, midY - 3.5f);
            glVertex2f(catEyeX + 6.0f, midY - 3.5f);
            glVertex2f(catEyeX + 6.0f, midY + 3.5f);
            glVertex2f(catEyeX, midY + 3.5f);
        glEnd();
    }
}

// ----------------------------------------------------------------------------
// 2. REALISTIC PERSPECTIVE ZEBRA CROSSING (Weathered Paint, Depth & Shadows)
// ----------------------------------------------------------------------------
void drawZebraCrossing()
{
    float topY = 730.0f;      // Top road edge (near sidewalk)
    float bottomY = 900.0f;   // Bottom road edge

    // Top X coordinates (aligned at gate entrance)
    float topStartX = 720.0f;
    float topEndX   = 880.0f;

    // Bottom X coordinates with perspective spread
    float bottomStartX = 620.0f;
    float bottomEndX   = 980.0f;

    int numStripes = 7;
    float topStripeW = (topEndX - topStartX) / (numStripes * 2 - 1);
    float bottomStripeW = (bottomEndX - bottomStartX) / (numStripes * 2 - 1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (int i = 0; i < numStripes; i++) {
        float tX1 = topStartX + i * 2 * topStripeW;
        float tX2 = tX1 + topStripeW;

        float bX1 = bottomStartX + i * 2 * bottomStripeW;
        float bX2 = bX1 + bottomStripeW;

        // 1. Soft Paint Shadow Base (Gives a slight raised/painted thickness look)
        glColor4f(0.0f, 0.0f, 0.0f, 0.25f);
        glBegin(GL_QUADS);
            glVertex2f(tX1 - 2.0f, topY);
            glVertex2f(tX2 + 2.0f, topY);
            glVertex2f(bX2 + 4.0f, bottomY);
            glVertex2f(bX1 - 4.0f, bottomY);
        glEnd();

        // 2. Main White Stripe with Perspective Vertical Gradient
        // Top is slightly darker (distance fade), Bottom is brighter & clearer
        glBegin(GL_QUADS);
            // Top Left (Distance)
            glColor4f(0.88f, 0.89f, 0.90f, 0.92f);
            glVertex2f(tX1, topY);

            // Top Right (Distance)
            glColor4f(0.88f, 0.89f, 0.90f, 0.92f);
            glVertex2f(tX2, topY);

            // Bottom Right (Foreground - Brighter)
            glColor4f(0.96f, 0.96f, 0.98f, 0.98f);
            glVertex2f(bX2, bottomY);

            // Bottom Left (Foreground)
            glColor4f(0.96f, 0.96f, 0.98f, 0.98f);
            glVertex2f(bX1, bottomY);
        glEnd();

        // 3. Inner Center Wear/Tire Line (Simulates natural road wear from tires)
        float midTX = (tX1 + tX2) * 0.5f;
        float midBX = (bX1 + bX2) * 0.5f;

        glColor4f(0.80f, 0.80f, 0.82f, 0.35f);
        glBegin(GL_QUADS);
            glVertex2f(midTX - 3.0f, topY);
            glVertex2f(midTX + 3.0f, topY);
            glVertex2f(midBX + 5.0f, bottomY);
            glVertex2f(midBX - 5.0f, bottomY);
        glEnd();

        // 4. Edge Highlight (Right Side bevel for 3D realism)
        glColor4f(1.0f, 1.0f, 1.0f, 0.40f);
        glBegin(GL_LINES);
            glVertex2f(tX2, topY);
            glVertex2f(bX2, bottomY);
        glEnd();
    }

    glDisable(GL_BLEND);
}
// ----------------------------------------------------------------------------
// 3. REALISTIC 3D SPEED BREAKER (Aligned Angle with Zebra Crossing Perspective)
// ----------------------------------------------------------------------------
void drawSpeedBreaker()
{
    // Adjusted Coordinates to match EXACT slope of the Zebra Crossing:
    // Top-to-Bottom Shift = 100px (Top Slope centered around 540f, Bottom Slope shifted left to 440f)
    float topX1 = 530.0f, topX2 = 555.0f, topY = 730.0f;
    float botX1 = 430.0f, botX2 = 455.0f, botY = 900.0f;

    // 1. Soft Outer Asphalt Shadow
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(topX1 - 8.0f, topY);
        glVertex2f(topX2 + 8.0f, topY);
        glVertex2f(botX2 + 10.0f, botY);
        glVertex2f(botX1 - 10.0f, botY);
    glEnd();
    glDisable(GL_BLEND);

    // 2. Base Dark Bump Body (Asphalt Base)
    glColor3f(0.15f, 0.15f, 0.17f);
    glBegin(GL_QUADS);
        glVertex2f(topX1 - 2.0f, topY);
        glVertex2f(topX2 + 2.0f, topY);
        glVertex2f(botX2 + 2.0f, botY);
        glVertex2f(botX1 - 2.0f, botY);
    glEnd();

    // 3. Alternating Yellow & White High-Vis Caution Segments with Slanted Slope
    int numSegments = 10;
    for (int i = 0; i < numSegments; i++) {
        float t1 = (float)i / numSegments;
        float t2 = (float)(i + 1) / numSegments;

        // Perspective Interpolation
        float pX1 = topX1 + t1 * (botX1 - topX1);
        float pX2 = topX2 + t1 * (botX2 - topX2);
        float pY1 = topY + t1 * (botY - topY);

        float nX1 = topX1 + t2 * (botX1 - topX1);
        float nX2 = topX2 + t2 * (botX2 - topX2);
        float nY2 = topY + t2 * (botY - topY);

        // Center ridge for 3D curved effect
        float midPX = (pX1 + pX2) * 0.5f;
        float midNX = (nX1 + nX2) * 0.5f;

        // Colors (Yellow & White)
        float r = (i % 2 == 0) ? 0.98f : 0.92f;
        float g = (i % 2 == 0) ? 0.78f : 0.92f;
        float b = (i % 2 == 0) ? 0.05f : 0.92f;

        // Left Slope (Ramp Up)
        glBegin(GL_QUADS);
            glColor3f(r * 0.75f, g * 0.75f, b * 0.75f);
            glVertex2f(pX1, pY1);

            glColor3f(r * 1.1f > 1.0f ? 1.0f : r * 1.1f,
                      g * 1.1f > 1.0f ? 1.0f : g * 1.1f,
                      b * 1.1f > 1.0f ? 1.0f : b * 1.1f);
            glVertex2f(midPX, pY1);
            glVertex2f(midNX, nY2);

            glColor3f(r * 0.75f, g * 0.75f, b * 0.75f);
            glVertex2f(nX1, nY2);
        glEnd();

        // Right Slope (Ramp Down)
        glBegin(GL_QUADS);
            glColor3f(r * 1.1f > 1.0f ? 1.0f : r * 1.1f,
                      g * 1.1f > 1.0f ? 1.0f : g * 1.1f,
                      b * 1.1f > 1.0f ? 1.0f : b * 1.1f);
            glVertex2f(midPX, pY1);

            glColor3f(r * 0.60f, g * 0.60f, b * 0.60f);
            glVertex2f(pX2, pY1);
            glVertex2f(nX2, nY2);

            glColor3f(r * 1.1f > 1.0f ? 1.0f : r * 1.1f,
                      g * 1.1f > 1.0f ? 1.0f : g * 1.1f,
                      b * 1.1f > 1.0f ? 1.0f : b * 1.1f);
            glVertex2f(midNX, nY2);
        glEnd();
    }

    // 4. Center Specular Light Reflection
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(2.5f);
    glBegin(GL_LINES);
        glColor4f(1.0f, 1.0f, 1.0f, 0.65f);
        glVertex2f((topX1 + topX2) * 0.5f, topY);

        glColor4f(1.0f, 1.0f, 1.0f, 0.85f);
        glVertex2f((botX1 + botX2) * 0.5f, botY);
    glEnd();
    glLineWidth(1.0f);
    glDisable(GL_BLEND);
}
// ============================================================================
// 5. TRAFFIC SIGN BOARD (Speed Hump Warning Sign - Moved Near Gate & Enhanced)
// ============================================================================

void drawTrafficSign()
{
    // Shifted position to X = 620.0f (Near the gate walkway, away from water station)
    float sx = 620.0f;
    float sy = 712.0f; // Platform ground contact point

    // 1. Ground Shadow
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.08f, 0.08f, 0.08f, 0.35f);
    glBegin(GL_POLYGON);
        glVertex2f(sx - 8.0f, sy + 2.0f);
        glVertex2f(sx + 8.0f, sy + 2.0f);
        glVertex2f(sx + 10.0f, sy - 3.0f);
        glVertex2f(sx - 6.0f, sy - 3.0f);
    glEnd();
    glDisable(GL_BLEND);

    // 2. Heavy Metal Base Support Plate with Bolts
    glColor3f(0.25f, 0.27f, 0.30f);
    glBegin(GL_QUADS);
        glVertex2f(sx - 6.0f, sy - 3.0f);
        glVertex2f(sx + 6.0f, sy - 3.0f);
        glVertex2f(sx + 6.0f, sy);
        glVertex2f(sx - 6.0f, sy);
    glEnd();

    // Base Bolts
    glColor3f(0.70f, 0.72f, 0.75f);
    glPointSize(3.0f);
    glBegin(GL_POINTS);
        glVertex2f(sx - 4.0f, sy - 1.5f);
        glVertex2f(sx + 4.0f, sy - 1.5f);
    glEnd();

    // 3. Metallic Steel Pole
    glColor3f(0.50f, 0.53f, 0.58f);
    glBegin(GL_QUADS);
        glVertex2f(sx - 2.5f, sy - 80.0f);
        glVertex2f(sx + 2.5f, sy - 80.0f);
        glVertex2f(sx + 2.5f, sy - 3.0f);
        glVertex2f(sx - 2.5f, sy - 3.0f);
    glEnd();

    // Pole Metallic Specular Highlight Line
    glColor3f(0.85f, 0.88f, 0.92f);
    glLineWidth(1.2f);
    glBegin(GL_LINES);
        glVertex2f(sx - 0.8f, sy - 80.0f);
        glVertex2f(sx - 0.8f, sy - 3.0f);
    glEnd();

    // 4. Mounting Clamps/Brackets (Attaching sign board to pole)
    float boardY = sy - 80.0f;
    glColor3f(0.20f, 0.20f, 0.22f);
    glBegin(GL_QUADS);
        glVertex2f(sx - 3.5f, boardY - 5.0f);
        glVertex2f(sx + 3.5f, boardY - 5.0f);
        glVertex2f(sx + 3.5f, boardY - 2.0f);
        glVertex2f(sx - 3.5f, boardY - 2.0f);

        glVertex2f(sx - 3.5f, boardY - 20.0f);
        glVertex2f(sx + 3.5f, boardY - 20.0f);
        glVertex2f(sx + 3.5f, boardY - 17.0f);
        glVertex2f(sx - 3.5f, boardY - 17.0f);
    glEnd();

    // 5. Red Outer Warning Triangle (Border Rim)
    glColor3f(0.85f, 0.10f, 0.10f);
    glBegin(GL_TRIANGLES);
        glVertex2f(sx, boardY - 32.0f);
        glVertex2f(sx - 22.0f, boardY + 5.0f);
        glVertex2f(sx + 22.0f, boardY + 5.0f);
    glEnd();

    // Darker Edge Outline for 3D Rim Effect
    glColor3f(0.55f, 0.05f, 0.05f);
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(sx, boardY - 32.0f);
        glVertex2f(sx - 22.0f, boardY + 5.0f);
        glVertex2f(sx + 22.0f, boardY + 5.0f);
    glEnd();

    // 6. Inner White Reflective Triangle
    glColor3f(0.96f, 0.96f, 0.98f);
    glBegin(GL_TRIANGLES);
        glVertex2f(sx, boardY - 25.0f);
        glVertex2f(sx - 16.0f, boardY + 2.0f);
        glVertex2f(sx + 16.0f, boardY + 2.0f);
    glEnd();

    // 7. Speed Bump Symbol (Detailed Black Icon Inside Triangle)
    glColor3f(0.12f, 0.12f, 0.14f);
    // Flat Base Line
    glBegin(GL_QUADS);
        glVertex2f(sx - 11.0f, boardY - 1.0f);
        glVertex2f(sx + 11.0f, boardY - 1.0f);
        glVertex2f(sx + 11.0f, boardY + 1.0f);
        glVertex2f(sx - 11.0f, boardY + 1.0f);
    glEnd();

    // Curved Hump Polygon
    glBegin(GL_POLYGON);
        glVertex2f(sx - 9.0f, boardY - 1.0f);
        glVertex2f(sx - 5.0f, boardY - 1.0f);
        glVertex2f(sx - 3.0f, boardY - 8.0f);
        glVertex2f(sx + 3.0f, boardY - 8.0f);
        glVertex2f(sx + 5.0f, boardY - 1.0f);
        glVertex2f(sx + 9.0f, boardY - 1.0f);
    glEnd();

    glLineWidth(1.0f);
}
/* ---- People ---- */
void drawStudent() { }
void drawTeacher() { }
void drawParent() { }
void drawSecurityGuard() { }
void drawGardener() { }
void drawAssemblyStudents() { }
void drawWalkingStudents() { }

/* ---- Vehicles ---- */

/////// SCHOOL BUS WITH DETAILED PASSENGERS, DRIVER & REAR-WHEEL BUMP PHYSICS
#include <GL/glut.h>
#include <math.h>

// Global Variables
float schoolBusX = -350.0f;
float schoolBusWheelAngle = 0.0f;
float schoolBusY_Base = 765.0f;
float schoolBusY_Offset = 0.0f;  // Vertical bump/bounce offset

// Pause & Physics Logic
int busPauseCounter = 0;
bool isBusPaused = false;

// Helper Circle Function
void drawBusCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Timer Function with Speed Breaker Physics & Fixed X-Axis Boundary (1600f Screen)
void schoolBusTimer(int value) {
    float currentSpeed = 1.6f; // Slow, natural school bus speed

    // Rear wheel hits speed breaker when schoolBusX reaches around 485.0f
    float rearWheelOnBreakerX = 485.0f;

    // 1. Front Wheel Bump (Light Bounce)
    if (schoolBusX >= 340.0f && schoolBusX < 380.0f) {
        float frontBump = (schoolBusX - 340.0f) / 40.0f;
        schoolBusY_Offset = -sinf(frontBump * 3.14159f) * 3.5f;
    }
    // 2. STOP EXACTLY WHEN REAR WHEEL IS ON SPEED BREAKER
    else if (schoolBusX >= rearWheelOnBreakerX - 10.0f && schoolBusX <= rearWheelOnBreakerX + 15.0f && !isBusPaused) {
        if (busPauseCounter < 25) { // Stop for ~0.4s
            currentSpeed = 0.0f;    // FULL STOP
            busPauseCounter++;
            schoolBusY_Offset = -7.0f; // Height jump on bump
        } else {
            isBusPaused = true;     // Resume driving
            currentSpeed = 1.0f;
        }
    }
    // 3. Coming Down to Straight Road (Settle Bounce)
    else if (schoolBusX > rearWheelOnBreakerX + 15.0f && schoolBusX <= rearWheelOnBreakerX + 80.0f) {
        currentSpeed = 1.2f;
        float settleProgress = (schoolBusX - (rearWheelOnBreakerX + 15.0f)) / 65.0f;

        schoolBusY_Offset = -sinf(settleProgress * 3.14159f) * 5.0f + sinf(settleProgress * 6.28318f) * 1.5f;
    }
    else {
        currentSpeed = 1.6f;
        schoolBusY_Offset = 0.0f; // Back to normal flat road
    }

    // Update position and wheel angle
    schoolBusX += currentSpeed;
    if (currentSpeed > 0.0f) {
        schoolBusWheelAngle -= currentSpeed * 4.0f;
    }

    // FIXED: Reset only AFTER the entire bus completely crosses 1600f screen width
    // Bus length is ~212 units, so 1850.0f ensures it smoothly leaves the visible area
    if (schoolBusX > 1850.0f) {
        schoolBusX = -350.0f;
        isBusPaused = false;
        busPauseCounter = 0;
        schoolBusY_Offset = 0.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, schoolBusTimer, 0);
}
// ---------------------------------------------------------
// BUS INTERIOR: STUDENTS & DRIVER (DETAILED)
// ---------------------------------------------------------
void drawBusPassengers(float baseX, float baseY) {
    // 1. Draw 5 Students Sitting by the Windows
    for (int i = 0; i < 5; i++) {
        float sx = baseX + 32.0f + (i * 30.0f);
        float sy = baseY + 24.0f;

        // Student Head / Skin
        glColor3f(0.88f, 0.68f, 0.52f);
        drawBusCircle(sx, sy + 8.0f, 4.0f, 10);

        // Hair (Black/Dark Brown)
        glColor3f(0.12f, 0.1f, 0.1f);
        drawBusCircle(sx + 0.3f, sy + 10.0f, 4.0f, 8);

        // Uniform Shirt (Alternating Blue and Red school uniform)
        if (i % 2 == 0) glColor3f(0.15f, 0.45f, 0.85f);
        else glColor3f(0.85f, 0.2f, 0.2f);

        glBegin(GL_QUADS);
            glVertex2f(sx - 4.5f, sy);
            glVertex2f(sx + 4.5f, sy);
            glVertex2f(sx + 4.0f, sy + 7.0f);
            glVertex2f(sx - 4.0f, sy + 7.0f);
        glEnd();

        // School Bag Strap Detail
        glColor3f(0.2f, 0.2f, 0.2f);
        glLineWidth(1.5f);
        glBegin(GL_LINES);
            glVertex2f(sx - 2.5f, sy + 7.0f);
            glVertex2f(sx - 1.0f, sy);
        glEnd();
    }

    // 2. Draw Driver
    float dx = baseX + 184.0f;
    float dy = baseY + 24.0f;

    // Driver Head & Cap
    glColor3f(0.78f, 0.55f, 0.4f);
    drawBusCircle(dx, dy + 8.0f, 4.2f, 10);

    // Driver Uniform (Navy Blue)
    glColor3f(0.08f, 0.15f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(dx - 5.0f, dy);
        glVertex2f(dx + 5.0f, dy);
        glVertex2f(dx + 4.0f, dy + 7.0f);
        glVertex2f(dx - 4.0f, dy + 7.0f);
    glEnd();

    // Driver Cap
    glColor3f(0.05f, 0.08f, 0.2f);
    glBegin(GL_TRIANGLES);
        glVertex2f(dx - 5.0f, dy + 11.0f);
        glVertex2f(dx + 6.0f, dy + 11.0f);
        glVertex2f(dx, dy + 15.0f);
    glEnd();

    // Steering Wheel
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(2.5f);
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 12; i++) {
            float rad = i * 2.0f * 3.14159f / 12.0f;
            glVertex2f(dx + 6.0f + cos(rad) * 4.0f, dy + 5.0f + sin(rad) * 4.0f);
        }
    glEnd();
}

// ---------------------------------------------------------
// MAIN SCHOOL BUS DRAW FUNCTION
// ---------------------------------------------------------
void drawSchoolBus() {
    glPushMatrix();

    // Position bus with dynamic bump/bounce Y-offset
    glTranslatef(schoolBusX, schoolBusY_Base + schoolBusY_Offset, 0.0f);

    // Flip Y-axis to render correctly
    glScalef(1.0f, -1.0f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 1. Road Shadow
    glColor4f(0.0f, 0.0f, 0.0f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(-15.0f, 2.0f);
        glVertex2f(220.0f, 2.0f);
        glVertex2f(210.0f, -4.0f);
        glVertex2f(-25.0f, -4.0f);
    glEnd();

    // 2. Main Yellow Body
    glColor3f(0.98f, 0.75f, 0.05f);
    glBegin(GL_POLYGON);
        glVertex2f(-10.0f, 10.0f);
        glVertex2f(202.0f, 10.0f);
        glVertex2f(210.0f, 25.0f);
        glVertex2f(210.0f, 48.0f);
        glVertex2f(195.0f, 52.0f);
        glVertex2f(-10.0f, 52.0f);
    glEnd();

    // Black Side Stripe
    glColor3f(0.12f, 0.12f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2f(-10.0f, 15.0f);
        glVertex2f(205.0f, 15.0f);
        glVertex2f(205.0f, 18.0f);
        glVertex2f(-10.0f, 18.0f);
    glEnd();

    // "SCHOOL BUS" Top Signboard Frame
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(45.0f, 52.0f);
        glVertex2f(145.0f, 52.0f);
        glVertex2f(145.0f, 60.0f);
        glVertex2f(45.0f, 60.0f);
    glEnd();

    // Yellow Sign Inside Box
    glColor3f(0.98f, 0.75f, 0.05f);
    glBegin(GL_QUADS);
        glVertex2f(47.0f, 53.5f);
        glVertex2f(143.0f, 53.5f);
        glVertex2f(143.0f, 58.5f);
        glVertex2f(47.0f, 58.5f);
    glEnd();

    // 3. DRAW INTERIOR PASSENGERS BEFORE WINDOW GLASS
    drawBusPassengers(0.0f, 0.0f);

    // 4. GLASS WINDOWS (Semi-transparent so passengers are visible)
    glColor4f(0.65f, 0.85f, 0.95f, 0.45f); // Transparent Tint
    for (int i = 0; i < 5; i++) {
        float winX = 22.0f + (i * 30.0f);
        glBegin(GL_QUADS);
            glVertex2f(winX, 22.0f);
            glVertex2f(winX + 24.0f, 22.0f);
            glVertex2f(winX + 24.0f, 44.0f);
            glVertex2f(winX, 44.0f);
        glEnd();

        // Window Frame Outlines
        glColor3f(0.2f, 0.2f, 0.2f);
        glLineWidth(1.5f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(winX, 22.0f);
            glVertex2f(winX + 24.0f, 22.0f);
            glVertex2f(winX + 24.0f, 44.0f);
            glVertex2f(winX, 44.0f);
        glEnd();
        glColor4f(0.65f, 0.85f, 0.95f, 0.45f); // Reset glass color
    }

    // Driver Windshield
    glBegin(GL_QUADS);
        glVertex2f(178.0f, 22.0f);
        glVertex2f(204.0f, 22.0f);
        glVertex2f(204.0f, 44.0f);
        glVertex2f(178.0f, 44.0f);
    glEnd();

    // 5. Headlight & Tail Lights
    glColor3f(1.0f, 0.95f, 0.6f);
    drawBusCircle(208.0f, 18.0f, 3.8f, 10); // Front Light

    glColor3f(0.85f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-12.0f, 22.0f);
        glVertex2f(-10.0f, 22.0f);
        glVertex2f(-10.0f, 32.0f);
        glVertex2f(-12.0f, 32.0f);
    glEnd();

    // Front Bumper
    glColor3f(0.12f, 0.12f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2f(202.0f, 8.0f);
        glVertex2f(212.0f, 8.0f);
        glVertex2f(212.0f, 14.0f);
        glVertex2f(202.0f, 14.0f);
    glEnd();

    // 6. WHEELS (1st Wheel at X=162, 2nd Rear Wheel at X=32)
    // Front Wheel (1st Wheel)
    glColor3f(0.12f, 0.12f, 0.12f);
    drawBusCircle(162.0f, 10.0f, 13.5f, 22);
    glColor3f(0.82f, 0.82f, 0.85f);
    drawBusCircle(162.0f, 10.0f, 7.5f, 14);

    // Rear Wheel (2nd Wheel)
    glColor3f(0.12f, 0.12f, 0.12f);
    drawBusCircle(32.0f, 10.0f, 13.5f, 22);
    glColor3f(0.82f, 0.82f, 0.85f);
    drawBusCircle(32.0f, 10.0f, 7.5f, 14);

    glDisable(GL_BLEND);
    glPopMatrix();
}

/// BRTC BUS
#include <GL/glut.h>
#include <math.h>

// Global position variables
float busX = 1200.0f;
float busWheelAngle = 0.0f;
bool isTimerStarted = false;

// CNG position set strictly behind Bus & adjusted Y position
float cngX = 1800.0f; // Bus baseline distance + 600 units gap
float cngWheelAngle = 0.0f;

// Y-Coordinates aligned to the upper two lanes of 780 to 900 road range
float busY_Base = 870.0f; // Upper Lane (Bus)
float cngY_Base = 825.0f; // Middle Lane (CNG) - Lower Lane (780-815) reserved for future use

// Helper function to draw circles
void drawCircleShape(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Unified Auto Movement Timer for both Bus and CNG
void internalTrafficTimer(int value) {
    // 1. Bus Movement Update
    float busSpeed = 2.5f;
    if (busX >= 305.0f && busX <= 460.0f) {
        busSpeed = 0.7f; // Slow down over speed breaker
    }
    busX -= busSpeed;
    busWheelAngle += busSpeed * 4.0f;

    // Reset Bus Position
    if (busX < -350.0f) {
        busX = 1700.0f;
    }

    // 2. CNG Movement Update (Synchronized with Bus speed and same relative logic)
    float cngSpeed = 2.5f;
    if (cngX >= 305.0f && cngX <= 460.0f) {
        cngSpeed = 0.7f; // Slow down over speed breaker
    }
    cngX -= cngSpeed;
    cngWheelAngle += cngSpeed * 6.0f;

    // Reset CNG Position always maintaining safe distance behind the Bus
    if (cngX < -350.0f) {
        cngX = busX + 600.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, internalTrafficTimer, 0);
}

// Draw Passengers inside Bus windows
void drawDetailedPassengers(float baseX, float baseY) {
    // Upper deck passengers
    for (int i = 0; i < 5; i++) {
        float px = baseX + 45.0f + (i * 35.0f);
        float py = baseY - 78.0f;

        glColor3f(0.25f, 0.18f, 0.12f);
        drawCircleShape(px, py + 8.0f, 4.5f, 12);

        if (i % 2 == 0) glColor3f(0.85f, 0.2f, 0.2f);
        else glColor3f(0.1f, 0.4f, 0.8f);

        glBegin(GL_QUADS);
            glVertex2f(px - 5.5f, py - 5.5f);
            glVertex2f(px + 5.5f, py - 5.5f);
            glVertex2f(px + 4.5f, py + 3.5f);
            glVertex2f(px - 4.5f, py + 3.5f);
        glEnd();
    }

    // Lower deck passengers
    for (int i = 1; i < 5; i++) {
        float px = baseX + 45.0f + (i * 35.0f);
        float py = baseY - 28.0f;

        glColor3f(0.2f, 0.2f, 0.25f);
        drawCircleShape(px, py + 8.0f, 4.5f, 12);

        if (i % 2 == 0) glColor3f(0.1f, 0.6f, 0.3f);
        else glColor3f(0.9f, 0.6f, 0.1f);

        glBegin(GL_QUADS);
            glVertex2f(px - 5.5f, py - 5.5f);
            glVertex2f(px + 5.5f, py - 5.5f);
            glVertex2f(px + 4.5f, py + 3.5f);
            glVertex2f(px - 4.5f, py + 3.5f);
        glEnd();
    }
}

// Detailed Driver Function for Bus
void drawDetailedDriver(float baseX, float baseY) {
    float dx = baseX + 2.0f;
    float dy = baseY - 28.0f;

    // Driver Cap
    glColor3f(0.1f, 0.1f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(dx - 7.0f, dy + 12.0f);
        glVertex2f(dx + 5.0f, dy + 12.0f);
        glVertex2f(dx + 5.0f, dy + 14.5f);
        glVertex2f(dx - 7.0f, dy + 14.5f);
    glEnd();

    // Driver Head
    glColor3f(0.8f, 0.55f, 0.4f);
    drawCircleShape(dx - 1.0f, dy + 8.0f, 4.5f, 12);

    // Driver Uniform / Shirt
    glColor3f(0.2f, 0.4f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(dx - 7.0f, dy - 6.0f);
        glVertex2f(dx + 5.0f, dy - 6.0f);
        glVertex2f(dx + 4.0f, dy + 3.5f);
        glVertex2f(dx - 6.0f, dy + 3.5f);
    glEnd();

    // Driver Hands holding steering wheel
    glColor3f(0.8f, 0.55f, 0.4f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(dx - 2.0f, dy);
        glVertex2f(dx - 9.0f, dy - 2.0f);
    glEnd();

    // Steering Wheel
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(2.5f);
    glBegin(GL_LINES);
        glVertex2f(dx - 9.0f, dy + 4.5f);
        glVertex2f(dx - 9.0f, dy - 6.5f);
    glEnd();
    drawCircleShape(dx - 9.0f, dy - 1.0f, 4.0f, 10);
}

// Wheel with rotating spokes for Bus
void drawDetailedWheel(float wx, float wy, float radius) {
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircleShape(wx, wy, radius, 24);

    glColor3f(0.75f, 0.75f, 0.78f);
    drawCircleShape(wx, wy, radius * 0.55f, 16);

    glColor3f(0.25f, 0.25f, 0.25f);
    drawCircleShape(wx, wy, radius * 0.25f, 12);

    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        for (int i = 0; i < 4; i++) {
            float rad = (-busWheelAngle + i * 45.0f) * 3.14159f / 180.0f;
            glVertex2f(wx + cos(rad) * (radius * 0.25f), wy + sin(rad) * (radius * 0.25f));
            glVertex2f(wx + cos(rad) * (radius * 0.55f), wy + sin(rad) * (radius * 0.55f));
        }
    glEnd();
}

// Main Function: drawBRTCBus
void drawBRTCBus() {
    if (!isTimerStarted) {
        glutTimerFunc(16, internalTrafficTimer, 0);
        isTimerStarted = true;
    }

    float currentPositionY = busY_Base;

    if (busX >= 305.0f && busX <= 460.0f) {
        float bumpPhase = (busX - 305.0f) / 155.0f * 3.14159f * 2.0f;
        currentPositionY += sinf(bumpPhase) * 5.0f;
    }

    glPushMatrix();
    glTranslatef(busX, currentPositionY, 0.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 1. Bus Shadow
    glColor4f(0.0f, 0.0f, 0.0f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(-20.0f, 6.0f);
        glVertex2f(260.0f, 6.0f);
        glVertex2f(240.0f, 17.0f);
        glVertex2f(-35.0f, 17.0f);
    glEnd();

    // 2. Main BRTC Red Body
    glColor3f(0.85f, 0.08f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(-15.0f, -108.0f);
        glVertex2f(245.0f, -108.0f);
        glVertex2f(245.0f, 0.0f);
        glVertex2f(-18.0f, 0.0f);
    glEnd();

    // 3. Roof Edge Highlight
    glColor3f(0.65f, 0.05f, 0.08f);
    glBegin(GL_QUADS);
        glVertex2f(-15.0f, -112.0f);
        glVertex2f(245.0f, -112.0f);
        glVertex2f(245.0f, -108.0f);
        glVertex2f(-15.0f, -108.0f);
    glEnd();

    // 4. BRTC Green Stripes
    glColor3f(0.0f, 0.52f, 0.24f);
    glBegin(GL_QUADS);
        glVertex2f(-15.0f, -58.0f);
        glVertex2f(245.0f, -58.0f);
        glVertex2f(245.0f, -51.0f);
        glVertex2f(-15.0f, -51.0f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(-17.0f, -9.0f);
        glVertex2f(245.0f, -9.0f);
        glVertex2f(245.0f, -2.0f);
        glVertex2f(-17.0f, -2.0f);
    glEnd();

    // 5. Passengers & Driver
    drawDetailedPassengers(0.0f, 0.0f);
    drawDetailedDriver(0.0f, 0.0f);

    // 6. Glass Windows
    glColor4f(0.65f, 0.85f, 0.95f, 0.55f);

    for (int i = 0; i < 6; i++) {
        float winX = 22.0f + (i * 35.0f);
        glBegin(GL_QUADS);
            glVertex2f(winX, -95.0f);
            glVertex2f(winX + 27.0f, -95.0f);
            glVertex2f(winX + 27.0f, -65.0f);
            glVertex2f(winX, -65.0f);
        glEnd();
    }

    for (int i = 0; i < 6; i++) {
        float winX = 22.0f + (i * 35.0f);
        glBegin(GL_QUADS);
            glVertex2f(winX, -45.0f);
            glVertex2f(winX + 27.0f, -45.0f);
            glVertex2f(winX + 27.0f, -15.0f);
            glVertex2f(winX, -15.0f);
        glEnd();
    }

    glBegin(GL_QUADS);
        glVertex2f(-12.0f, -95.0f);
        glVertex2f(13.0f, -95.0f);
        glVertex2f(13.0f, -65.0f);
        glVertex2f(-12.0f, -65.0f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(-14.0f, -45.0f);
        glVertex2f(13.0f, -45.0f);
        glVertex2f(13.0f, -15.0f);
        glVertex2f(-14.0f, -15.0f);
    glEnd();

    // 7. Metallic Window Frames
    glColor3f(0.2f, 0.2f, 0.2f);
    glLineWidth(1.5f);
    for (int i = 0; i < 6; i++) {
        float winX = 22.0f + (i * 35.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(winX, -95.0f);
            glVertex2f(winX + 27.0f, -95.0f);
            glVertex2f(winX + 27.0f, -65.0f);
            glVertex2f(winX, -65.0f);
        glEnd();
        glBegin(GL_LINE_LOOP);
            glVertex2f(winX, -45.0f);
            glVertex2f(winX + 27.0f, -45.0f);
            glVertex2f(winX + 27.0f, -15.0f);
            glVertex2f(winX, -15.0f);
        glEnd();
    }

    // 8. Side Mirror & Wiper
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_LINES);
        glVertex2f(-14.0f, -39.0f);
        glVertex2f(-25.0f, -35.0f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(-28.0f, -42.0f);
        glVertex2f(-23.0f, -42.0f);
        glVertex2f(-23.0f, -30.0f);
        glVertex2f(-28.0f, -30.0f);
    glEnd();

    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(0.0f, -15.0f);
        glVertex2f(-9.0f, -31.0f);
    glEnd();

    // 9. Front Grill & Headlights
    glColor3f(0.15f, 0.15f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(-16.0f, -9.0f);
        glVertex2f(-14.0f, -9.0f);
        glVertex2f(-14.0f, 0.0f);
        glVertex2f(-16.0f, 0.0f);
    glEnd();

    glColor3f(0.4f, 0.4f, 0.4f);
    drawCircleShape(-15.0f, -13.0f, 4.5f, 10);
    drawCircleShape(-15.0f, -22.0f, 4.5f, 10);

    // Rear Taillights
    glColor3f(0.7f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(245.0f, -20.0f);
        glVertex2f(247.0f, -20.0f);
        glVertex2f(247.0f, -11.0f);
        glVertex2f(245.0f, -11.0f);
    glEnd();

    // 10. Heavy Bumpers
    glColor3f(0.12f, 0.12f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2f(-18.0f, -3.0f);
        glVertex2f(249.0f, -3.0f);
        glVertex2f(249.0f, 3.5f);
        glVertex2f(-18.0f, 3.5f);
    glEnd();

    // 11. Wheels
    drawDetailedWheel(32.0f, 3.5f, 17.5f);
    drawDetailedWheel(190.0f, 3.5f, 17.5f);

    glDisable(GL_BLEND);
    glPopMatrix();
}

// Compact CNG Wheel
void drawCngWheel(float wx, float wy, float radius) {
    glColor3f(0.12f, 0.12f, 0.12f);
    drawCircleShape(wx, wy, radius, 20);

    glColor3f(0.75f, 0.75f, 0.78f);
    drawCircleShape(wx, wy, radius * 0.55f, 14);

    glColor3f(0.2f, 0.2f, 0.2f);
    drawCircleShape(wx, wy, radius * 0.25f, 10);

    glColor3f(0.35f, 0.35f, 0.35f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        for (int i = 0; i < 4; i++) {
            float rad = (-cngWheelAngle + i * 45.0f) * 3.14159f / 180.0f;
            glVertex2f(wx + cos(rad) * (radius * 0.25f), wy + sin(rad) * (radius * 0.25f));
            glVertex2f(wx + cos(rad) * (radius * 0.55f), wy + sin(rad) * (radius * 0.55f));
        }
    glEnd();
}

// Driver inside Boxy CNG
void drawCngDriver(float baseX, float baseY) {
    float dx = baseX + 18.0f;
    float dy = baseY - 32.0f;

    glColor3f(0.15f, 0.15f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(dx - 5.0f, dy + 11.0f);
        glVertex2f(dx + 5.0f, dy + 11.0f);
        glVertex2f(dx + 4.0f, dy + 13.5f);
        glVertex2f(dx - 5.0f, dy + 13.5f);
    glEnd();

    glColor3f(0.8f, 0.55f, 0.4f);
    drawCircleShape(dx, dy + 6.5f, 4.0f, 12);

    glColor3f(0.2f, 0.45f, 0.75f);
    glBegin(GL_QUADS);
        glVertex2f(dx - 5.0f, dy - 10.0f);
        glVertex2f(dx + 5.0f, dy - 10.0f);
        glVertex2f(dx + 4.0f, dy + 2.0f);
        glVertex2f(dx - 4.0f, dy + 2.0f);
    glEnd();

    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(dx - 10.0f, dy - 2.0f);
        glVertex2f(dx - 1.0f, dy - 4.0f);
    glEnd();
}

// Passengers in rear seat
void drawCngPassengers(float baseX, float baseY) {
    float px1 = baseX + 56.0f;
    float py1 = baseY - 30.0f;

    glColor3f(0.75f, 0.5f, 0.38f);
    drawCircleShape(px1, py1 + 6.5f, 3.8f, 12);

    glColor3f(0.85f, 0.25f, 0.25f);
    glBegin(GL_QUADS);
        glVertex2f(px1 - 4.5f, py1 - 10.0f);
        glVertex2f(px1 + 4.5f, py1 - 10.0f);
        glVertex2f(px1 + 3.8f, py1 + 2.0f);
        glVertex2f(px1 - 3.8f, py1 + 2.0f);
    glEnd();

    float px2 = baseX + 68.0f;
    float py2 = baseY - 30.0f;

    glColor3f(0.7f, 0.48f, 0.35f);
    drawCircleShape(px2, py2 + 6.5f, 3.8f, 12);

    glColor3f(0.2f, 0.65f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(px2 - 4.5f, py2 - 10.0f);
        glVertex2f(px2 + 4.5f, py2 - 10.0f);
        glVertex2f(px2 + 3.8f, py2 + 2.0f);
        glVertex2f(px2 - 3.8f, py2 + 2.0f);
    glEnd();
}

// Metal Mesh Grill
void drawCngGrillMesh(float x1, float y1, float x2, float y2) {
    glColor3f(0.25f, 0.3f, 0.25f);
    glLineWidth(1.2f);

    for (float x = x1 + 4.0f; x < x2; x += 5.0f) {
        glBegin(GL_LINES);
            glVertex2f(x, y1);
            glVertex2f(x, y2);
        glEnd();
    }

    for (float y = y1 + 4.0f; y < y2; y += 5.0f) {
        glBegin(GL_LINES);
            glVertex2f(x1, y);
            glVertex2f(x2, y);
        glEnd();
    }
}

// Main CNG Function
void drawCNG() {
    float currentPositionY = cngY_Base;

    if (cngX >= 305.0f && cngX <= 460.0f) {
        float bumpPhase = (cngX - 305.0f) / 155.0f * 3.14159f * 2.0f;
        currentPositionY += sinf(bumpPhase) * 4.0f;
    }

    glPushMatrix();
    glTranslatef(cngX, currentPositionY, 0.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 1. Ground Shadow
    glColor4f(0.0f, 0.0f, 0.0f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(-10.0f, 6.0f);
        glVertex2f(90.0f, 6.0f);
        glVertex2f(80.0f, 15.0f);
        glVertex2f(-18.0f, 15.0f);
    glEnd();

    // 3. Green Metallic Body
    glColor3f(0.08f, 0.52f, 0.28f);
    glBegin(GL_POLYGON);
        glVertex2f(-4.0f, -22.0f);
        glVertex2f(8.0f, -54.0f);
        glVertex2f(32.0f, -54.0f);
        glVertex2f(82.0f, -54.0f);
        glVertex2f(84.0f, -2.0f);
        glVertex2f(-4.0f, -2.0f);
    glEnd();

    // 4. Yellow & White Stripes
    glColor3f(0.95f, 0.8f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(4.0f, -24.0f);
        glVertex2f(82.0f, -24.0f);
        glVertex2f(82.0f, -20.0f);
        glVertex2f(4.0f, -20.0f);
    glEnd();

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(4.0f, -20.0f);
        glVertex2f(82.0f, -20.0f);
        glVertex2f(82.0f, -17.0f);
        glVertex2f(4.0f, -17.0f);
    glEnd();

    // 5. Driver & Passengers
    drawCngDriver(0.0f, 0.0f);
    drawCngPassengers(0.0f, 0.0f);

    // 6. Front Windshield Glass
    glColor4f(0.7f, 0.85f, 0.9f, 0.6f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, -26.0f);
        glVertex2f(10.0f, -50.0f);
        glVertex2f(22.0f, -50.0f);
        glVertex2f(16.0f, -26.0f);
    glEnd();

    // Windshield Frame
    glColor3f(0.15f, 0.15f, 0.15f);
    glLineWidth(1.8f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.0f, -26.0f);
        glVertex2f(10.0f, -50.0f);
        glVertex2f(22.0f, -50.0f);
        glVertex2f(16.0f, -26.0f);
    glEnd();

    // 7. Door Openings & Protective Mesh
    glColor3f(0.05f, 0.35f, 0.18f);
    glBegin(GL_QUADS);
        glVertex2f(22.0f, -48.0f);
        glVertex2f(40.0f, -48.0f);
        glVertex2f(40.0f, -26.0f);
        glVertex2f(22.0f, -26.0f);
    glEnd();
    drawCngGrillMesh(22.0f, -48.0f, 40.0f, -26.0f);

    glBegin(GL_QUADS);
        glVertex2f(44.0f, -48.0f);
        glVertex2f(78.0f, -48.0f);
        glVertex2f(78.0f, -26.0f);
        glVertex2f(44.0f, -26.0f);
    glEnd();
    drawCngGrillMesh(44.0f, -48.0f, 78.0f, -26.0f);

    // 8. Door Frame Borders
    glColor3f(0.12f, 0.12f, 0.12f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(22.0f, -48.0f);
        glVertex2f(40.0f, -48.0f);
        glVertex2f(40.0f, -26.0f);
        glVertex2f(22.0f, -26.0f);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(44.0f, -48.0f);
        glVertex2f(78.0f, -48.0f);
        glVertex2f(78.0f, -26.0f);
        glVertex2f(44.0f, -26.0f);
    glEnd();

    // 9. Side Mirror & Front Unlit Headlight
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_LINES);
        glVertex2f(-1.0f, -24.0f);
        glVertex2f(-6.0f, -22.0f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(-8.0f, -26.0f);
        glVertex2f(-5.0f, -26.0f);
        glVertex2f(-5.0f, -20.0f);
        glVertex2f(-8.0f, -20.0f);
    glEnd();

    glColor3f(0.35f, 0.35f, 0.38f);
    drawCircleShape(-3.0f, -14.0f, 3.2f, 10);
    glColor3f(0.85f, 0.45f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-2.0f, -9.0f);
        glVertex2f(2.0f, -9.0f);
        glVertex2f(2.0f, -6.0f);
        glVertex2f(-2.0f, -6.0f);
    glEnd();

    // Rear Bumper Guard
    glColor3f(0.75f, 0.75f, 0.78f);
    glLineWidth(2.5f);
    glBegin(GL_LINES);
        glVertex2f(82.0f, -12.0f);
        glVertex2f(90.0f, -12.0f);
        glVertex2f(82.0f, -6.0f);
        glVertex2f(90.0f, -6.0f);
        glVertex2f(88.0f, -14.0f);
        glVertex2f(88.0f, -4.0f);
    glEnd();

    // 10. Wheels Setup
    drawCngWheel(8.0f, 3.5f, 11.0f);   // Front Wheel
    drawCngWheel(68.0f, 3.5f, 12.0f);  // Rear Wheel

    glDisable(GL_BLEND);
    glPopMatrix();
}
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

    // Start Metro Rail Animation Loop
    glutTimerFunc(0, updateMetroRail, 0);
    //Bus Timer
    glutTimerFunc(0, schoolBusTimer, 0);
    //glutTimerFunc(0, updateTimer, 0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();

    return 0;
}
