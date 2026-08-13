/* ==========================================================
   PROJECT
   Modern Government Primary School in Bangladesh
   Canvas: 1600 x 900
   Coordinate System: Matches Approved Master Blueprint
   Origin (0,0) = TOP-LEFT corner
   X increases to the RIGHT
   Y increases DOWNWARD
   (Achieved via gluOrtho2D(0, 1600, 900, 0))
.
   ========================================================== */

#include <GL/glut.h>
#include <cmath>

bool isPassingActive = true;
bool isGateOpen = false;
bool isLampOn = false;   // Lamp Light toggle
bool isFountainOn = true;
float fountainWaterHeight = 1.0f; // Height multiplier
bool isCngLightOn = false; // CNG Headlight State (Default: OFF)

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
















// ---------------------------------------------------------
// Helper functions for 2D/3D Mode
// ---------------------------------------------------------
// float windowWidth = 1600.0f;
// float windowHeight = 900.0f;

// 2D orthographic mode - for background
void set2DMode()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1600, 900, 0); // Your original coordinate system

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST); // Disable depth test for flat 2D
}

// 3D perspective mode - for 3D bench, gate, etc.
void set3DMode()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Use perspective projection. FAR must be large enough.
    gluPerspective(45.0, (double)windowWidth / (double)windowHeight, 1.0, 10000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Setup 3D Camera view
    gluLookAt(800.0, 450.0, 1200.0,   // Camera position (far away)
              800.0, 450.0, 0.0,      // Look-at point (center of screen)
              0.0, -1.0, 0.0);        // Up vector (Y down like blueprint)

    glEnable(GL_DEPTH_TEST); // Enable depth test for 3D depth layering
}













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
void draw3DFountain ();
void drawBench3D();
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














// Helper Function to draw a colored 3D Cuboid (box)
// (x, y, z) - starting position, (w, h, d) - width, height, depth
void drawCuboid(float x, float y, float z, float w, float h, float d, float r, float g, float b, float a = 1.0f)
{
    // Front face
    glColor4f(r, g, b, a);
    glBegin(GL_QUADS);
    glVertex3f(x, y, z);
    glVertex3f(x + w, y, z);
    glVertex3f(x + w, y + h, z);
    glVertex3f(x, y + h, z);
    glEnd();

    // Back face (Darker)
    glColor4f(r * 0.7f, g * 0.7f, b * 0.7f, a);
    glBegin(GL_QUADS);
    glVertex3f(x, y, z + d);
    glVertex3f(x + w, y, z + d);
    glVertex3f(x + w, y + h, z + d);
    glVertex3f(x, y + h, z + d);
    glEnd();

    // Top face (Lighter highlight)
    float rTop = (r * 1.1f > 1.0f) ? 1.0f : r * 1.1f;
    float gTop = (g * 1.1f > 1.0f) ? 1.0f : g * 1.1f;
    float bTop = (b * 1.1f > 1.0f) ? 1.0f : b * 1.1f;
    glColor4f(rTop, gTop, bTop, a);
    glBegin(GL_QUADS);
    glVertex3f(x, y, z);
    glVertex3f(x + w, y, z);
    glVertex3f(x + w, y, z + d);
    glVertex3f(x, y, z + d);
    glEnd();

    // Bottom face (Shaded)
    glColor4f(r * 0.5f, g * 0.5f, b * 0.5f, a);
    glBegin(GL_QUADS);
    glVertex3f(x, y + h, z);
    glVertex3f(x + w, y + h, z);
    glVertex3f(x + w, y + h, z + d);
    glVertex3f(x, y + h, z + d);
    glEnd();

    // Left face
    glColor4f(r * 0.8f, g * 0.8f, b * 0.8f, a);
    glBegin(GL_QUADS);
    glVertex3f(x, y, z);
    glVertex3f(x, y + h, z);
    glVertex3f(x, y + h, z + d);
    glVertex3f(x, y, z + d);
    glEnd();

    // Right face
    glColor4f(r * 0.9f, g * 0.9f, b * 0.9f, a);
    glBegin(GL_QUADS);
    glVertex3f(x + w, y, z);
    glVertex3f(x + w, y + h, z);
    glVertex3f(x + w, y + h, z + d);
    glVertex3f(x + w, y, z + d);
    glEnd();
}



/* ==========================================================
   INIT FUNCTION
   ========================================================== */
void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    set2DMode();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/* ==========================================================
   DISPLAY FUNCTION
   ========================================================== */
void display()
{
    // Color buffer এবং Depth buffer দুটোই ক্লিয়ার করা হলো
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // --------------------------------------------------
    // LAYER 1: EVERYTHING IN 2D
    // --------------------------------------------------
    set2DMode();

    /* ---- Sky Layer ---- */
    drawSky();
    drawSun();
    drawCloud();
    set3DMode();
    drawBird();
    set2DMode();
    drawAirplane();

    // BACKGROUND GROUND & WALL
    drawDistantSkyline();
    drawMetroRailViaductAndTrain();
    drawGround();
    backBoundaryWall();

    /* ---- School Building Layer ---- */
    drawRightSideForest();
    drawSchool();
    drawRoof();
    drawRoofBanner();
    drawWindow();
    drawDoor();
    drawClock();

    /* ---- Campus / Garden Layer ---- */
    drawShaheedMinar();
    drawFlowerTribute();
    drawGarden();
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

    /* ---- Boundary, Footpath, Road & Others (2D) ---- */

    draw3DFountain();
    drawBoundaryWall();
    drawGate();
    drawFootpath();
    drawNoticeBoard();
    drawLampPost();
    drawCycleParking();
    drawBench();
    drawNoticeBoard();
    drawCycleParking();


    /* ---- Road Layer ---- */
    drawRoad();
    drawRoadDivider();
    drawZebraCrossing();
    drawSpeedBreaker();


    set3DMode();
    drawWaterStation();
    drawTrafficSign();
    drawDustbin();


    set2DMode();
    /* ---- People ---- */
    drawAssemblyStudents();
    drawTeacher();
    drawSecurityGuard();
    drawGardener();
    drawWalkingStudents();
    drawParent();
    drawStudent();

    /* ---- Vehicles ---- */
    drawSchoolBus();
   drawCNG();
    drawBRTCBus();
  //  drawCNG();

    /* ---- Foreground fauna ---- */
    drawButterfly();

    // --------------------------------------------------
    // LAYER 2: SPECIFIC 3D OBJECTS
    // --------------------------------------------------
    set3DMode();

    drawBench3D();       // 3D Bench

    drawTrafficSign();


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













void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'f':
    case 'F':
        isFountainOn = !isFountainOn; // Toggle Fountain ON / OFF
        break;

    case 'h':
    case 'H':
        if (fountainWaterHeight < 2.0f)
            fountainWaterHeight += 0.2f; // Increase Water Jet Height
        break;

    case 'j':
    case 'J':
        if (fountainWaterHeight > 0.4f)
            fountainWaterHeight -= 0.2f; // Decrease Water Jet Height
        break;

    case 'g':
    case 'G':
        isGateOpen = !isGateOpen;
        break;

    case 'l':
    case 'L':
        isLampOn = !isLampOn;
        break;

    case 'p':
    case 'P':
        isPassingActive = !isPassingActive;
        break;

    case 'c':
    case 'C':
        isCngLightOn = !isCngLightOn; // Toggle CNG Light ON / OFF
        break;

    case 27: // ESC key
        exit(0);
        break;

    case ' ':
        isAnimating = !isAnimating;
        break;

    default:
        break;
    }
    glutPostRedisplay(); // Screen Redraw Force
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
        if (cy > 0.0f)
        {
            glColor3f(1.0f, 1.0f, 1.0f);        // Bright White Highlight
        }
        else
        {
            glColor3f(0.92f, 0.95f, 0.98f);     // Soft Subtle Base
        }
        glVertex2f(cx, cy);

        // Edge Colors (Smooth Gradient)
        for (int i = 0; i <= segments; i++)
        {
            float angle = i * 2.0f * 3.14159f / segments;
            float px = cx + (r * cos(angle));
            float py = cy + (r * sin(angle));

            if (py > cy)
            {
                glColor3f(1.0f, 1.0f, 1.0f);    // Sunlight top edge
            }
            else
            {
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
    // Real time based constant movement logic
    float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f; // Conversion to seconds

    // Calculate fixed smooth positions based on real time
    float cloud1OffsetX = fmod(currentTime * 20.0f, 1900.0f) - 300.0f;
    float cloud2OffsetX = fmod(currentTime * 35.0f, 2300.0f) - 700.0f;
    float cloud3OffsetX = fmod(currentTime * 25.0f, 2700.0f) - 1100.0f;
    float cloud4OffsetX = fmod(currentTime * 40.0f, 2100.0f) - 500.0f;
    float cloud5OffsetX = fmod(currentTime * 30.0f, 2900.0f) - 1300.0f;

    // ---------------------------------------------------------
    // Render 5 Clouds across different Y positions and scales
    // ---------------------------------------------------------

    // Cloud 1 - Far Left Sky
    drawSingleCloud(150.0f + cloud1OffsetX, 110.0f, 2.70f);

    // Cloud 2 - Mid Left Sky
    drawSingleCloud(450.0f + cloud4OffsetX, 60.0f, 1.55f);

    // Cloud 3 - Center Sky
    drawSingleCloud(750.0f + cloud2OffsetX, 95.0f, 0.95f);

    // Cloud 4 - Mid Right Sky
    drawSingleCloud(1050.0f + cloud5OffsetX, 50.0f, 0.80f);

    // Cloud 5 - Far Right Sky
    drawSingleCloud(1350.0f + cloud3OffsetX, 130.0f, 1.15f);
}


#include <windows.h>
#include <mmsystem.h>
#include <cmath>
#pragma comment(lib, "winmm.lib")

// ============================================================================
// FUNCTION: drawSingleBird3D
// Description: Renders a 3D volumetric bird model using 3D primitives and
//              geometric transformations in 3D space.
// ============================================================================
void drawSingleBird3D(float x, float y, float z, float size, float flapAngle)
{
    float wingUp = sin(flapAngle) * (size * 0.6f);
    float wingCurve = cos(flapAngle) * (size * 0.15f);

    glPushMatrix();

    // 1. Move to bird's 3D coordinates
    glTranslatef(x, y, z);

    // Slight downward pitch angle for realistic 3D flying pose
    glRotatef(-10.0f, 1.0f, 0.0f, 0.0f);

    // Bird Color (Deep Charcoal with 3D shadow support)
    glColor3f(0.15f, 0.15f, 0.18f);

    // ---------------------------------------------------------
    // 2. 3D Body Core (Volumetric Torso using 3D Ellipsoid approximation)
    // ---------------------------------------------------------
    glPushMatrix();
    glScalef(size * 0.15f, size * 0.15f, size * 0.4f);

    // Draw 3D Body Mesh
    int slices = 8, stacks = 8;
    for (int i = 0; i < stacks; i++) {
        float lat0 = 3.14159f * (-0.5f + (float)(i) / stacks);
        float z0  = sin(lat0);
        float zr0 = cos(lat0);

        float lat1 = 3.14159f * (-0.5f + (float)(i + 1) / stacks);
        float z1  = sin(lat1);
        float zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; j++) {
            float lng = 2.0f * 3.14159f * (float)(j) / slices;
            float xVal = cos(lng);
            float yVal = sin(lng);

            glNormal3f(xVal * zr0, yVal * zr0, z0);
            glVertex3f(xVal * zr0, yVal * zr0, z0);
            glNormal3f(xVal * zr1, yVal * zr1, z1);
            glVertex3f(xVal * zr1, yVal * zr1, z1);
        }
        glEnd();
    }
    glPopMatrix();

    // ---------------------------------------------------------
    // 3. Left Wing (3D Curved Polygonal Surface with Z Depth)
    // ---------------------------------------------------------
    glBegin(GL_TRIANGLE_STRIP);
        // Inner Wing Joint
        glVertex3f(0.0f, 0.0f, size * 0.1f);
        glVertex3f(0.0f, 0.0f, -size * 0.1f);

        // Mid Wing Arch
        glVertex3f(-size * 0.5f, (size * 0.35f) + (wingUp * 0.5f), size * 0.05f);
        glVertex3f(-size * 0.5f, (size * 0.25f) + (wingUp * 0.5f), -size * 0.05f);

        // Sleek Wing Tip
        glVertex3f(-size * 1.2f, (size * 0.1f) + wingUp, 0.0f);
        glVertex3f(-size * 0.6f, -(size * 0.05f) + wingCurve, 0.0f);
    glEnd();

    // ---------------------------------------------------------
    // 4. Right Wing (3D Curved Polygonal Surface with Z Depth)
    // ---------------------------------------------------------
    glBegin(GL_TRIANGLE_STRIP);
        // Inner Wing Joint
        glVertex3f(0.0f, 0.0f, size * 0.1f);
        glVertex3f(0.0f, 0.0f, -size * 0.1f);

        // Mid Wing Arch
        glVertex3f(size * 0.5f, (size * 0.35f) + (wingUp * 0.5f), size * 0.05f);
        glVertex3f(size * 0.5f, (size * 0.25f) + (wingUp * 0.5f), -size * 0.05f);

        // Sleek Wing Tip
        glVertex3f(size * 1.2f, (size * 0.1f) + wingUp, 0.0f);
        glVertex3f(size * 0.6f, -(size * 0.05f) + wingCurve, 0.0f);
    glEnd();

    // ---------------------------------------------------------
    // 5. 3D Tail Feathers (Pyramidal Wedge Shape)
    // ---------------------------------------------------------
    glBegin(GL_TRIANGLES);
        // Top Face
        glVertex3f(-size * 0.12f, 0.0f, -size * 0.2f);
        glVertex3f(size * 0.12f, 0.0f, -size * 0.2f);
        glVertex3f(0.0f, -size * 0.1f, -size * 0.55f);

        // Bottom Face
        glVertex3f(-size * 0.12f, -size * 0.05f, -size * 0.2f);
        glVertex3f(size * 0.12f, -size * 0.05f, -size * 0.2f);
        glVertex3f(0.0f, -size * 0.1f, -size * 0.55f);
    glEnd();

    glPopMatrix();
}

// ============================================================================
// FUNCTION: drawBird
// Description: Renders a flock of 3D birds navigating through 3D space.
// ============================================================================
void drawBird()
{
    float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float birdOffsetX = fmod(currentTime * 70.0f, 2000.0f);
    float time = glutGet(GLUT_ELAPSED_TIME) * 0.007f;

    // Flock rendering with varying X, Y, and Z depths
    drawSingleBird3D(1650.0f - birdOffsetX, 85.0f,  0.0f,   9.0f, time);
    drawSingleBird3D(1685.0f - birdOffsetX, 105.0f, -15.0f, 11.0f, time + 0.7f);
    drawSingleBird3D(1720.0f - birdOffsetX, 75.0f,  20.0f,  8.0f,  time + 1.4f);
    drawSingleBird3D(1755.0f - birdOffsetX, 95.0f,  -10.0f, 10.0f, time + 2.1f);
    drawSingleBird3D(1790.0f - birdOffsetX, 115.0f, 10.0f,  7.5f,  time + 2.8f);
}





// BUTTERFLY
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
    airplaneOffsetX -= .5f;
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
void drawDistantSkyline()
{
    // ------------------------------------------------------------------------
    // 1. LAYER 1: VERY DISTANT BUILDINGS (Ultra-Soft Hazy Hues)
    // ------------------------------------------------------------------------
    glColor3f(0.72f, 0.78f, 0.84f);

    glBegin(GL_QUADS);
    // Far Building A
    glVertex2i(100, 320);
    glVertex2i(160, 320);
    glVertex2i(160, 420);
    glVertex2i(100, 420);

    // Far Building B
    glVertex2i(300, 260);
    glVertex2i(380, 260);
    glVertex2i(380, 420);
    glVertex2i(300, 420);

    // Far Building C
    glVertex2i(850, 280);
    glVertex2i(940, 280);
    glVertex2i(940, 420);
    glVertex2i(850, 420);

    // Far Building D
    glVertex2i(1420, 240);
    glVertex2i(1520, 240);
    glVertex2i(1520, 420);
    glVertex2i(1420, 420);
    glEnd();

    // ------------------------------------------------------------------------
    // 2. LAYER 2: MID-DISTANCE BUILDINGS (Sharper Silhouettes)
    // ------------------------------------------------------------------------
    glColor3f(0.58f, 0.66f, 0.74f);

    glBegin(GL_QUADS);
    // Building 1 (Left Tower)
    glVertex2i(40,  290);
    glVertex2i(110, 290);
    glVertex2i(110, 420);
    glVertex2i(40,  420);

    // Building 2 (Center-Left)
    glVertex2i(180, 270);
    glVertex2i(250, 270);
    glVertex2i(250, 420);
    glVertex2i(180, 420);

    // Building 3 (Behind School - Left)
    glVertex2i(480, 280);
    glVertex2i(570, 280);
    glVertex2i(570, 420);
    glVertex2i(480, 420);

    // Building 4 (Behind School - Right)
    glVertex2i(990, 240);
    glVertex2i(1070, 240);
    glVertex2i(1070, 420);
    glVertex2i(990, 420);

    // Building 5 (Far Right)
    glVertex2i(1350, 290);
    glVertex2i(1430, 290);
    glVertex2i(1430, 420);
    glVertex2i(1350, 420);
    glEnd();

    // Spire / Antennas
    glColor3f(0.50f, 0.58f, 0.65f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2i(1030, 240);
    glVertex2i(1030, 210);
    glVertex2i(215,  270);
    glVertex2i(215,  245);
    glEnd();

    // Reflective Windows
    glColor3f(0.85f, 0.92f, 0.98f);
    glBegin(GL_QUADS);
    for (int wy = 255; wy < 400; wy += 25)
    {
        glVertex2i(1010, wy);
        glVertex2i(1025, wy);
        glVertex2i(1025, wy + 12);
        glVertex2i(1010, wy + 12);
        glVertex2i(1035, wy);
        glVertex2i(1050, wy);
        glVertex2i(1050, wy + 12);
        glVertex2i(1035, wy + 12);
    }
    for (int wy = 305; wy < 400; wy += 20)
    {
        glVertex2i(55, wy);
        glVertex2i(70, wy);
        glVertex2i(70, wy + 10);
        glVertex2i(55, wy + 10);
        glVertex2i(80, wy);
        glVertex2i(95, wy);
        glVertex2i(95, wy + 10);
        glVertex2i(80, wy + 10);
    }
    glEnd();

    // ------------------------------------------------------------------------
    // 3. DISTANT NATURAL TREE HORIZON (Organic Foliage Brought Forward)
    // ------------------------------------------------------------------------
    // Back Tree Line
    glColor3f(0.42f, 0.58f, 0.42f);
    for (int x = -10; x <= 1610; x += 30)
    {
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
    for (int x = 5; x <= 1610; x += 38)
    {
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
void drawGround()
{
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
    for (int x = 50; x < 1550; x += 110)
    {
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
void backBoundaryWall()
{
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
    for (int y = wallTop + 12; y < wallBottom; y += 12)
    {
        glVertex2i(0, y);
        glVertex2i(1600, y);
    }
    glEnd();

    glBegin(GL_LINES);
    int row = 0;
    for (int y = wallTop; y < wallBottom; y += 12)
    {
        int xOffset = (row % 2 == 0) ? 0 : 20;
        for (int x = xOffset; x < 1600; x += 40)
        {
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
    for (int x = 0; x <= 1600; x += 100)
    {
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
void drawMetroRailViaductAndTrain()
{
    int deckTop = 330;
    int deckBottom = 352;

    // ------------------------------------------------------------------------
    // 1. HEAVY REALISTIC METRO PILLARS (Flyover Pillars)
    // ------------------------------------------------------------------------
    for (int x = 80; x <= 1600; x += 220)
    {
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
    glVertex2i(0, deckTop - 3);
    glVertex2i(1600, deckTop - 3);
    glVertex2i(0, deckTop - 6);
    glVertex2i(1600, deckTop - 6);
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
    for (int i = 0; i < 360; i += 20)
    {
        float rad = i * 3.14159f / 180.0f;
        glVertex2f(trainRight + 12 + cos(rad) * 4.5f, trainTop + 32 + sin(rad) * 4.5f);
    }
    glEnd();

    // --- Inter-Coach Gangway Connectors (Bogie Separators) ---
    glColor3f(0.15f, 0.15f, 0.18f);
    for (int cx = trainLeft + 210; cx < trainRight - 50; cx += 210)
    {
        glBegin(GL_QUADS);
        glVertex2i(cx - 4, trainTop + 3);
        glVertex2i(cx + 4, trainTop + 3);
        glVertex2i(cx + 4, trainBottom - 1);
        glVertex2i(cx - 4, trainBottom - 1);
        glEnd();
    }

    // --- Passenger Windows with Metallic Frames ---
    for (int wx = trainLeft + 25; wx < trainRight - 40; wx += 38)
    {
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
    for (int dx = trainLeft + 105; dx < trainRight - 50; dx += 210)
    {
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
void updateMetroRail(int value)
{
    metroX += 3.5f; // Train Speed

    // Reset position when train moves completely out of screen on the right
    if (metroX > 1700.0f)
    {
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
// Position: Attached to Flag Pole at X = 800.0f
// ============================================================================

void drawBangladeshFlag()
{
    float poleX = 800.0f;
    float topY = 275.0f;

    float flagW = 55.0f;
    float flagH = 33.0f;

    // ---------------------------------------------------------
    // Animation timing
    // ---------------------------------------------------------

    float time = glutGet(GLUT_ELAPSED_TIME) * 0.0045f;

    // Overall wind motion
    float wind = sin(time) * 3.0f;

    // Shearing transformation
    float shear = sin(time * 1.4f) * 0.12f;


    // ---------------------------------------------------------
    // Green Flag Body
    // ---------------------------------------------------------

    glColor3fv(COLOR_FLAG_GREEN);

    int segments = 18;

    glBegin(GL_QUADS);

    for (int i = 0; i < segments; i++)
    {
        float t1 = (float)i / segments;
        float t2 = (float)(i + 1) / segments;

        float x1 = poleX + flagW * t1;
        float x2 = poleX + flagW * t2;

        // Wave strength increases gradually away from the pole
        float wave1 =
            sin(time * 2.0f + t1 * 5.0f)
            * 2.5f * t1;

        float wave2 =
            sin(time * 2.0f + t2 * 5.0f)
            * 2.5f * t2;

        // Wind becomes stronger toward the free end
        float wind1 =
            wind * t1 * t1;

        float wind2 =
            wind * t2 * t2;

        // -----------------------------------------------------
        // Top edge
        // -----------------------------------------------------

        float topX1 =
            x1 + wave1 + wind1;

        float topX2 =
            x2 + wave2 + wind2;

        // -----------------------------------------------------
        // Bottom edge
        // Shearing creates horizontal displacement
        // based on vertical position
        // -----------------------------------------------------

        float bottomX1 =
            x1 + wave1 + wind1 + shear * flagH;

        float bottomX2 =
            x2 + wave2 + wind2 + shear * flagH;


        // Keep the pole-side edge fixed
        if (i == 0)
        {
            topX1 = poleX;
            bottomX1 = poleX;
        }

        glVertex2f(topX1, topY);
        glVertex2f(topX2, topY);

        glVertex2f(bottomX2, topY + flagH);
        glVertex2f(bottomX1, topY + flagH);
    }

    glEnd();


    // ---------------------------------------------------------
    // Red Disc
    // ---------------------------------------------------------

    glColor3fv(COLOR_FLAG_RED);

    float discPosition = 0.45f;

    float discBaseX =
        poleX + flagW * discPosition;

    float discWave =
        sin(time * 2.0f + discPosition * 5.0f)
        * 2.5f * discPosition;

    float discWind =
        wind * discPosition * discPosition;

    // Same shear displacement used by the flag
    float discShear =
        shear * (flagH * 0.5f);

    float cx =
        discBaseX +
        discWave +
        discWind +
        discShear;

    float cy =
        topY +
        flagH * 0.5f;

    float r = 10.0f;

    int circleSegments = 40;


    // ---------------------------------------------------------
    // Draw slightly sheared red disc
    // ---------------------------------------------------------

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(cx, cy);

    for (int i = 0; i <= circleSegments; i++)
    {
        float angle =
            i * 2.0f * 3.14159265f
            / circleSegments;

        float localX =
            r * cos(angle);

        float localY =
            r * sin(angle);

        // Shearing transformation
        float shearedX =
            localX + shear * localY;

        glVertex2f(
            cx + shearedX,
            cy + localY
        );
    }

    glEnd();


    // ---------------------------------------------------------
    // Small attachment strip
    // Makes the connection with the pole visually clear
    // ---------------------------------------------------------

    glColor3fv(COLOR_FLAG_GREEN);

    glBegin(GL_QUADS);

    glVertex2f(poleX - 0.8f, topY);
    glVertex2f(poleX + 1.2f, topY);

    glVertex2f(poleX + 1.2f, topY + flagH);
    glVertex2f(poleX - 0.8f, topY + flagH);

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
    for (int i = 0; i <= segments; i++)
    {
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
    glVertex2f(SH_X(-78.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-70.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-70.0f), SH_Y(130.0f));
    glVertex2f(SH_X(-78.0f), SH_Y(130.0f));
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(SH_X(-54.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-46.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-46.0f), SH_Y(130.0f));
    glVertex2f(SH_X(-54.0f), SH_Y(130.0f));
    glEnd();
    glBegin(GL_QUADS); // Top Cap
    glVertex2f(SH_X(-78.0f), SH_Y(122.0f));
    glVertex2f(SH_X(-46.0f), SH_Y(122.0f));
    glVertex2f(SH_X(-46.0f), SH_Y(130.0f));
    glVertex2f(SH_X(-78.0f), SH_Y(130.0f));
    glEnd();

    // --- Medium Right Pillar Frame ---
    glBegin(GL_QUADS);
    glVertex2f(SH_X(46.0f), SH_Y(10.0f));
    glVertex2f(SH_X(54.0f), SH_Y(10.0f));
    glVertex2f(SH_X(54.0f), SH_Y(130.0f));
    glVertex2f(SH_X(46.0f), SH_Y(130.0f));
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(SH_X(70.0f), SH_Y(10.0f));
    glVertex2f(SH_X(78.0f), SH_Y(10.0f));
    glVertex2f(SH_X(78.0f), SH_Y(130.0f));
    glVertex2f(SH_X(70.0f), SH_Y(130.0f));
    glEnd();
    glBegin(GL_QUADS); // Top Cap
    glVertex2f(SH_X(46.0f), SH_Y(122.0f));
    glVertex2f(SH_X(78.0f), SH_Y(122.0f));
    glVertex2f(SH_X(78.0f), SH_Y(130.0f));
    glVertex2f(SH_X(46.0f), SH_Y(130.0f));
    glEnd();

    // --- Far Left Small Pillar Frame ---
    glBegin(GL_QUADS);
    glVertex2f(SH_X(-120.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-112.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-112.0f), SH_Y(95.0f));
    glVertex2f(SH_X(-120.0f), SH_Y(95.0f));
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(SH_X(-100.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-92.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-92.0f), SH_Y(95.0f));
    glVertex2f(SH_X(-100.0f), SH_Y(95.0f));
    glEnd();
    glBegin(GL_QUADS); // Top Cap
    glVertex2f(SH_X(-120.0f), SH_Y(87.0f));
    glVertex2f(SH_X(-92.0f), SH_Y(87.0f));
    glVertex2f(SH_X(-92.0f), SH_Y(95.0f));
    glVertex2f(SH_X(-120.0f), SH_Y(95.0f));
    glEnd();

    // --- Far Right Small Pillar Frame ---
    glBegin(GL_QUADS);
    glVertex2f(SH_X(92.0f), SH_Y(10.0f));
    glVertex2f(SH_X(100.0f), SH_Y(10.0f));
    glVertex2f(SH_X(100.0f), SH_Y(95.0f));
    glVertex2f(SH_X(92.0f), SH_Y(95.0f));
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(SH_X(112.0f), SH_Y(10.0f));
    glVertex2f(SH_X(120.0f), SH_Y(10.0f));
    glVertex2f(SH_X(120.0f), SH_Y(95.0f));
    glVertex2f(SH_X(112.0f), SH_Y(95.0f));
    glEnd();
    glBegin(GL_QUADS); // Top Cap
    glVertex2f(SH_X(92.0f), SH_Y(87.0f));
    glVertex2f(SH_X(120.0f), SH_Y(87.0f));
    glVertex2f(SH_X(120.0f), SH_Y(95.0f));
    glVertex2f(SH_X(92.0f), SH_Y(95.0f));
    glEnd();

    // ---------------------------------------------------------
    // 3. Thin Steel Grills / Strings Inside Frames
    // ---------------------------------------------------------
    glColor3f(0.20f, 0.20f, 0.25f);
    glLineWidth(1.2f); // Thin guitar-string appearance
    glBegin(GL_LINES);
    // Center Pillar Grills
    glVertex2f(SH_X(-14.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-14.0f), SH_Y(150.0f));
    glVertex2f(SH_X(-14.0f), SH_Y(150.0f));
    glVertex2f(SH_X(-18.0f), SH_Y(188.0f));

    glVertex2f(SH_X(-5.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(-5.0f),  SH_Y(150.0f));
    glVertex2f(SH_X(-5.0f),  SH_Y(150.0f));
    glVertex2f(SH_X(-6.0f),  SH_Y(188.0f));

    glVertex2f(SH_X(5.0f),   SH_Y(10.0f));
    glVertex2f(SH_X(5.0f),   SH_Y(150.0f));
    glVertex2f(SH_X(5.0f),   SH_Y(150.0f));
    glVertex2f(SH_X(6.0f),   SH_Y(188.0f));

    glVertex2f(SH_X(14.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(14.0f),  SH_Y(150.0f));
    glVertex2f(SH_X(14.0f),  SH_Y(150.0f));
    glVertex2f(SH_X(18.0f),  SH_Y(188.0f));

    // Medium Left Grills
    glVertex2f(SH_X(-66.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-66.0f), SH_Y(122.0f));
    glVertex2f(SH_X(-58.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-58.0f), SH_Y(122.0f));

    // Medium Right Grills
    glVertex2f(SH_X(58.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(58.0f),  SH_Y(122.0f));
    glVertex2f(SH_X(66.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(66.0f),  SH_Y(122.0f));

    // Far Left Small Grills
    glVertex2f(SH_X(-108.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-108.0f), SH_Y(87.0f));

    // Far Right Small Grills
    glVertex2f(SH_X(108.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(108.0f),  SH_Y(87.0f));
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
    glVertex2f(SH_X(-78.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-46.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-46.0f), SH_Y(130.0f));
    glVertex2f(SH_X(-78.0f), SH_Y(130.0f));
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(SH_X(-70.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-54.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-54.0f), SH_Y(122.0f));
    glVertex2f(SH_X(-70.0f), SH_Y(122.0f));
    glEnd();

    // Medium Right Outer & Inner Outlines
    glBegin(GL_LINE_LOOP);
    glVertex2f(SH_X(46.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(78.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(78.0f),  SH_Y(130.0f));
    glVertex2f(SH_X(46.0f),  SH_Y(130.0f));
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(SH_X(54.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(70.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(70.0f),  SH_Y(122.0f));
    glVertex2f(SH_X(54.0f),  SH_Y(122.0f));
    glEnd();

    // Far Left Outer & Inner Outlines
    glBegin(GL_LINE_LOOP);
    glVertex2f(SH_X(-120.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-92.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(-92.0f),  SH_Y(95.0f));
    glVertex2f(SH_X(-120.0f), SH_Y(95.0f));
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(SH_X(-112.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-100.0f), SH_Y(10.0f));
    glVertex2f(SH_X(-100.0f), SH_Y(87.0f));
    glVertex2f(SH_X(-112.0f), SH_Y(87.0f));
    glEnd();

    // Far Right Outer & Inner Outlines
    glBegin(GL_LINE_LOOP);
    glVertex2f(SH_X(92.0f),   SH_Y(10.0f));
    glVertex2f(SH_X(120.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(120.0f),  SH_Y(95.0f));
    glVertex2f(SH_X(92.0f),   SH_Y(95.0f));
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(SH_X(100.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(112.0f),  SH_Y(10.0f));
    glVertex2f(SH_X(112.0f),  SH_Y(87.0f));
    glVertex2f(SH_X(100.0f),  SH_Y(87.0f));
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






















































//FLOWER TRIBUTE


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
    for (int i = 0; i <= 20; i++)
    {
        float a = i * 2.0f * 3.14159f / 20;
        glVertex2f(wreathX + cos(a) * wreathR, wreathY + sin(a) * wreathR);
    }
    glEnd();


    for (int i = 0; i < 8; i++)
    {
        float angle = i * 2.0f * 3.14159f / 8;
        float fx = wreathX + cos(angle) * (wreathR * 0.6f);
        float fy = wreathY + sin(angle) * (wreathR * 0.6f);

        glColor3f(0.90f, 0.15f, 0.15f); // লাল ফুল
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(fx, fy);
        for (int j = 0; j <= 10; j++)
        {
            float a = j * 2.0f * 3.14159f / 10;
            glVertex2f(fx + cos(a) * (5.0f * scale), fy + sin(a) * (5.0f * scale));
        }
        glEnd();
    }


    float flowerPositions[5][2] =
    {
        {-45.0f, 18.0f},
        {-75.0f, 12.0f},
        { 45.0f, 18.0f},
        { 80.0f, 12.0f},
        {  0.0f,  5.0f}
    };

    for(int k = 0; k < 5; k++)
    {
        float fx = SH_X(flowerPositions[k][0]);
        float fy = SH_Y(flowerPositions[k][1]);

        if(k % 2 == 0) glColor3f(0.95f, 0.75f, 0.10f); // হলুদ
        else glColor3f(0.90f, 0.15f, 0.15f);          // লাল

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(fx, fy);
        for (int j = 0; j <= 8; j++)
        {
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
// FUNCTION: drawBush (Realistic 3D Layered Organic Bush)
// ============================================================================
void drawBush(float x, float y, float rx, float ry)
{
    int segments = 20;

    // Helper Lambda for Semi-Circle / Ellipse Domes
    auto drawDome = [&](float cx, float cy, float radX, float radY, float r, float g, float b)
    {
        glColor3f(r, g, b);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= segments; i++)
        {
            float angle = i * 3.14159f / segments;
            // Subtracting Y-sin curves upwards in inverted Y systems
            glVertex2f(cx + (radX * cosf(angle)), cy - (radY * sinf(angle)));
        }
        glEnd();
    };

    // ------------------------------------------------------------------------
    // 1. BASE DARK DROP SHADOW (Ground Contact Layer)
    // ------------------------------------------------------------------------
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.05f, 0.15f, 0.05f, 0.40f);
    glBegin(GL_QUADS);
    glVertex2f(x - rx * 1.15f, y + 2.0f);
    glVertex2f(x + rx * 1.15f, y + 2.0f);
    glVertex2f(x + rx * 0.95f, y - 4.0f);
    glVertex2f(x - rx * 0.95f, y - 4.0f);
    glEnd();
    glDisable(GL_BLEND);

    // ------------------------------------------------------------------------
    // 2. LAYER 1: DEEP BASE SHADOW DOMES (Dark Green Silhouette)
    // ------------------------------------------------------------------------
    // Left Dome Base
    drawDome(x - rx * 0.45f, y, rx * 0.65f, ry * 0.75f, 0.08f, 0.28f, 0.08f);
    // Right Dome Base
    drawDome(x + rx * 0.45f, y, rx * 0.65f, ry * 0.70f, 0.08f, 0.28f, 0.08f);
    // Main Center Dome Base
    drawDome(x, y, rx * 0.85f, ry * 0.95f, 0.10f, 0.35f, 0.10f);

    // ------------------------------------------------------------------------
    // 3. LAYER 2: MID-TONE LEAF CLUSTERS (Rich Natural Green)
    // ------------------------------------------------------------------------
    // Left Cluster
    drawDome(x - rx * 0.42f, y - ry * 0.10f, rx * 0.58f, ry * 0.68f, 0.18f, 0.48f, 0.15f);
    // Right Cluster
    drawDome(x + rx * 0.42f, y - ry * 0.10f, rx * 0.58f, ry * 0.62f, 0.18f, 0.48f, 0.15f);
    // Center Top Main Cluster
    drawDome(x, y - ry * 0.15f, rx * 0.75f, ry * 0.88f, 0.22f, 0.55f, 0.18f);

    // ------------------------------------------------------------------------
    // 4. LAYER 3: TOP SUNLIGHT HIGHLIGHTS (Fresh Bright Green)
    // ------------------------------------------------------------------------
    // Small top-left highlight
    drawDome(x - rx * 0.35f, y - ry * 0.25f, rx * 0.42f, ry * 0.50f, 0.32f, 0.68f, 0.22f);
    // Small top-right highlight
    drawDome(x + rx * 0.35f, y - ry * 0.22f, rx * 0.40f, ry * 0.45f, 0.32f, 0.68f, 0.22f);
    // Center Top Main Specular Highlight
    drawDome(x, y - ry * 0.30f, rx * 0.55f, ry * 0.65f, 0.38f, 0.75f, 0.25f);

    // ------------------------------------------------------------------------
    // 5. ACCENT: SMALL RED BERRIES / FLOWERS (Natural Realism Details)
    // ------------------------------------------------------------------------
    struct Berry
    {
        float bx, by;
    };
    Berry berries[] =
    {
        { x - rx * 0.50f, y - ry * 0.30f },
        { x - rx * 0.20f, y - ry * 0.65f },
        { x + rx * 0.15f, y - ry * 0.50f },
        { x + rx * 0.55f, y - ry * 0.35f },
        { x - rx * 0.10f, y - ry * 0.25f },
        { x + rx * 0.35f, y - ry * 0.60f }
    };

    glColor3f(0.88f, 0.15f, 0.20f); // Bright Red Berries
    for (const auto& b : berries)
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(b.bx, b.by);
        for (int i = 0; i <= 8; i++)
        {
            float a = i * 2.0f * 3.14159f / 8;
            glVertex2f(b.bx + 2.0f * cosf(a), b.by + 2.0f * sinf(a));
        }
        glEnd();
    }
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
    float clusters[6][3] =
    {
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

    float clusters[5][3] =
    {
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
    float mangoes[6][2] =
    {
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
    // Height is increased by 1.45x for a taller realistic look
    float tallerHeight = height * 1.45f;
    int segments = 16; // Increased segments for smoother taller curve
    float currentX = startX;
    float currentY = startY;
    float segmentH = tallerHeight / segments;

    // Curved Trunk with Bark Ring Textures (Leaning Left)
    for (int i = 0; i < segments; i++)
    {
        float nextX = currentX - (i * 0.35f);
        float nextY = currentY - segmentH;
        float w1 = 12.0f - (i * 0.45f);
        float w2 = 12.0f - ((i + 1) * 0.40f);

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
    float coconutCoords[4][2] =
    {
        {topX - 6.0f, topY + 2.0f},
        {topX + 6.0f, topY + 2.0f},
        {topX - 1.0f, topY + 7.0f},
        {topX + 2.0f, topY - 2.0f}
    };
    for (int c = 0; c < 4; c++)
    {
        drawSmoothCircle(coconutCoords[c][0], coconutCoords[c][1], 6.0f, 6.5f, 0.15f, 0.38f, 0.05f);
        drawSmoothCircle(coconutCoords[c][0] - 1.5f, coconutCoords[c][1] - 1.5f, 2.8f, 3.2f, 0.30f, 0.55f, 0.10f);
    }

    // Organic Curved Feathery Leaves (Fronds)
    float leafAngles[] = { -165.0f, -130.0f, -85.0f, -30.0f, 20.0f, 75.0f, 120.0f, 160.0f };

    for (int f = 0; f < 8; f++)
    {
        float rad = leafAngles[f] * M_PI / 180.0f;
        float leafLen = 80.0f; // Increased leaf length for taller tree proportion
        float endX = topX + (leafLen * cos(rad));
        float endY = topY - (leafLen * sin(rad)) + (abs((int)leafAngles[f]) * 0.20f);

        // Main Spine
        glColor3f(0.08f, 0.42f, 0.08f);
        glLineWidth(2.5f);
        glBegin(GL_LINES);
        glVertex2f(topX, topY);
        glVertex2f(endX, endY);
        glEnd();

        // Feathery Leaflets along the spine
        int leaflets = 20; // Increased leaflets count for longer fronds
        glLineWidth(1.5f);
        glColor3f(0.12f, 0.58f, 0.12f);
        for (int j = 1; j <= leaflets; j++)
        {
            float t = (float)j / leaflets;
            float lx = topX + (endX - topX) * t;
            float ly = topY + (endY - topY) * t;

            glBegin(GL_LINES);
            glVertex2f(lx, ly);
            glVertex2f(lx - 8.0f * (1.0f - t * 0.3f), ly + 12.0f);
            glVertex2f(lx, ly);
            glVertex2f(lx + 8.0f * (1.0f - t * 0.3f), ly + 12.0f);
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
    int numFronds = 40;
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
// REWRITTEN BANANA TREE (With Smaller Bananas & Detailed Dense Bunch)
// ----------------------------------------------------------------------------
void drawSingleBananaTree(float x, float y, float scale)
{
    // Tall Trunk Height
    float height = 125.0f * scale;
    float topY = y - height;

    // 1. MAIN TALL GREEN TRUNK (Pseudostem)
    drawBranchSegment(x, y, 18.0f * scale, x, topY, 11.0f * scale, 0.42f, 0.72f, 0.18f);

    // Trunk Highlight Segment
    drawBranchSegment(x - 2.0f * scale, y, 4.0f * scale, x - 1.2f * scale, topY, 2.5f * scale, 0.58f, 0.82f, 0.28f);

    // 2. DETAILED DRY V-SHAPED BARK LAYERS (At Trunk Base)
    for (int i = 0; i < 5; i++)
    {
        float sy = y - (i * 14.0f * scale);
        float w = (18.0f - i * 1.8f) * scale;

        // Outer Dark Bark Edge
        glColor3f(0.42f, 0.36f, 0.15f);
        glBegin(GL_TRIANGLES);
        glVertex2f(x - w / 2.0f - (1.0f * scale), sy);
        glVertex2f(x + w / 2.0f + (1.0f * scale), sy);
        glVertex2f(x, sy - (13.0f * scale));
        glEnd();

        // Inner Light Brown Bark
        glColor3f(0.75f, 0.68f, 0.32f);
        glBegin(GL_TRIANGLES);
        glVertex2f(x - w / 2.0f, sy);
        glVertex2f(x + w / 2.0f, sy);
        glVertex2f(x, sy - (11.5f * scale));
        glEnd();
    }

    // 3. ARCHING BROADER LEAVES WITH DETAILED NOTCHES
    float leafAngles[] = { -160.0f, -120.0f, -75.0f, -30.0f, 30.0f, 75.0f, 120.0f, 160.0f };

    for (int i = 0; i < 8; i++)
    {
        float rad = leafAngles[i] * M_PI / 180.0f;
        float leafLen = 85.0f * scale;

        float endX = x + (leafLen * cos(rad));
        float endY = topY - (leafLen * sin(rad)) + (abs((int)leafAngles[i]) * 0.25f * scale);

        float midX = (x + endX) / 2.0f;
        float midY = (topY + endY) / 2.0f - (22.0f * scale);

        // Leaf Under Shadow Layer
        glColor3f(0.20f, 0.48f, 0.10f);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, topY);
        glVertex2f(midX - (18.0f * scale * sin(rad)), midY + (18.0f * scale * cos(rad)));
        glVertex2f(endX, endY);
        glVertex2f(midX + (18.0f * scale * sin(rad)), midY - (18.0f * scale * cos(rad)));
        glEnd();

        // Top Main Vibrant Green Leaf Body
        glColor3f(0.38f, 0.76f, 0.18f);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, topY);
        glVertex2f(midX - (15.0f * scale * sin(rad)), midY + (15.0f * scale * cos(rad)));
        glVertex2f(endX, endY);
        glVertex2f(midX + (15.0f * scale * sin(rad)), midY - (15.0f * scale * cos(rad)));
        glEnd();

        // Leaf Border Outline
        glColor3f(0.12f, 0.38f, 0.06f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_STRIP);
        glVertex2f(x, topY);
        glVertex2f(midX - (15.0f * scale * sin(rad)), midY + (15.0f * scale * cos(rad)));
        glVertex2f(endX, endY);
        glVertex2f(midX + (15.0f * scale * sin(rad)), midY - (15.0f * scale * cos(rad)));
        glVertex2f(x, topY);
        glEnd();

        // Central Midrib Stem
        glColor3f(0.20f, 0.52f, 0.10f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        glVertex2f(x, topY);
        glVertex2f(endX, endY);
        glEnd();

        // Leaf Cuts / Notches (Slits)
        glColor3f(0.15f, 0.42f, 0.08f);
        glLineWidth(1.5f);
        glBegin(GL_LINES);
        for (int k = 1; k <= 5; k++)
        {
            float t = k * 0.16f;
            float lx = x + (endX - x) * t;
            float ly = topY + (endY - topY) * t;
            glVertex2f(lx, ly);
            glVertex2f(lx - (8.0f * scale * sin(rad)), ly + (8.0f * scale * cos(rad)));
            glVertex2f(lx, ly);
            glVertex2f(lx + (8.0f * scale * sin(rad)), ly - (8.0f * scale * cos(rad)));
        }
        glEnd();
    }

    // 4. HANGING DENSE CLUSTER OF SMALLER BANANAS
    float stalkStartX = x;
    float stalkStartY = topY + (15.0f * scale);
    float bunchX = x - (20.0f * scale);
    float bunchY = topY + (38.0f * scale);

    // Green Hanging Stalk
    glColor3f(0.28f, 0.55f, 0.10f);
    glLineWidth(4.5f * scale);
    glBegin(GL_LINE_STRIP);
    glVertex2f(stalkStartX, stalkStartY);
    glVertex2f(bunchX + (4.0f * scale), topY + (22.0f * scale));
    glVertex2f(bunchX + (4.0f * scale), bunchY - (8.0f * scale));
    glEnd();

    // Much Smaller Bananas Grid Coordinates (18 bananas in compact layers)
    float bananaOffsets[][2] =
    {
        {-8.0f, -10.0f}, {-3.0f, -11.0f}, {2.0f, -11.0f}, {7.0f, -10.0f},
        {-10.0f, -4.0f}, {-5.0f, -5.0f},  {0.0f, -5.0f},  {5.0f, -5.0f},  {10.0f, -4.0f},
        {-8.0f, 2.0f},  {-3.0f, 3.0f},   {2.0f, 3.0f},   {7.0f, 2.0f},
        {-5.0f, 8.0f},  {0.0f, 9.0f},    {5.0f, 8.0f},
        {-2.0f, 14.0f}, {2.0f, 14.0f}
    };

    // Reduced Radius: Width = 2.2f * scale, Height = 3.8f * scale
    float bRadiusX = 2.2f * scale;
    float bRadiusY = 3.8f * scale;

    for (int b = 0; b < 18; b++)
    {
        float bx = bunchX + (bananaOffsets[b][0] * scale);
        float by = bunchY + (bananaOffsets[b][1] * scale);

        // Yellow Banana Body
        drawSmoothCircle(bx, by, bRadiusX, bRadiusY, 0.98f, 0.90f, 0.12f);

        // Banana Outline
        glColor3f(0.75f, 0.65f, 0.05f);
        glLineWidth(1.0f);
        glBegin(GL_LINE_LOOP);
        for (int k = 0; k < 10; k++)
        {
            float angle = k * 2.0f * M_PI / 10.0f;
            glVertex2f(bx + (bRadiusX * cosf(angle)), by + (bRadiusY * sinf(angle)));
        }
        glEnd();

        // Tiny Tip Detail
        glColor3f(0.35f, 0.25f, 0.10f);
        glBegin(GL_TRIANGLES);
        glVertex2f(bx - (0.8f * scale), by + (bRadiusY - 0.2f));
        glVertex2f(bx + (0.8f * scale), by + (bRadiusY - 0.2f));
        glVertex2f(bx, by + bRadiusY + (1.2f * scale));
        glEnd();
    }

    // 5. EXTENDED BOTANICAL FLOWER (Kolar Mocha)
    float mochaX = bunchX + (1.5f * scale);
    float mochaStartY = bunchY + (18.0f * scale);
    float mochaEndY = mochaStartY + (14.0f * scale);

    // Stem Below Banana Bunch
    glColor3f(0.28f, 0.55f, 0.10f);
    glLineWidth(2.5f * scale);
    glBegin(GL_LINES);
    glVertex2f(mochaX, mochaStartY);
    glVertex2f(mochaX, mochaEndY);
    glEnd();

    // Maroon/Pink Mocha Cone (Banana Blossom)
    glColor3f(0.88f, 0.28f, 0.38f);
    glBegin(GL_TRIANGLES);
    glVertex2f(mochaX - (4.0f * scale), mochaEndY);
    glVertex2f(mochaX + (4.0f * scale), mochaEndY);
    glVertex2f(mochaX, mochaEndY + (12.0f * scale));
    glEnd();

    // Top Crown of Mocha
    drawSmoothCircle(mochaX, mochaEndY, 4.0f * scale, 3.0f * scale, 0.70f, 0.18f, 0.28f);

    glLineWidth(1.0f);
}



















// ============================================================================
// RIGHT SIDE FOREST (Single instance of each tree within 1600f screen limit)
// ============================================================================
void drawRightSideForest()
{
    // Ground Y = 460 ~ 480 (Right Side Forest Expansion)

    // Existing Trees
    drawSingleBananaTree(1480.0f, 475.0f, 0.85f);
    drawSingleBananaTree(400.0f, 473.0f, 0.90f);
    //drawSinglePalmTree(1250.0f, 470.0f, 125.0f);
    drawSingleTree(1590.0f, 470.0f, 0.80f);
    drawSingleMangoTree(1200.0f, 475.0f, 0.85f);
    drawSingleCoconutTree(1400.0f, 470.0f, 180.0f);

    // Newly Added Trees (Filling the gaps & extending coverage)
    drawSingleMangoTree(5.0f, 470.0f, 0.82f);     // Gap between 1250 and 1350
    //drawSingleTree(400.0f, 468.0f, 0.85f);          // Gap between 1350 and 1450
    drawSinglePalmTree(270.0f, 470.0f, 170.0f);     // Gap between 1450 and 1570
    drawSingleCoconutTree(150.0f, 470.0f, 160.0f);  // Extension beyond 1570
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
    for (float y = 495.0f; y <= bottomY - 5.0f; y += 16.0f)
    {
        float factor = (y - topY) / height;
        float xLeft = 750.0f - (170.0f * factor);
        float xRight = 850.0f + (170.0f * factor);
        glVertex2f(xLeft, y);
        glVertex2f(xRight, y);
    }
    glEnd();

    // Vertical Pavement Grid Lines
    glBegin(GL_LINES);
    for (int i = -4; i <= 4; i++)
    {
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

    for (int col = 0; col < 4; col++)
    {
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
    for (int col = 0; col < 4; col++)
    {
        float cx = columnOffsets[col];
        for (float rowY = 525.0f; rowY <= bottomY - 15.0f; rowY += 18.0f)
        {
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
    for (int i = 0; i < totalCurbBlocks; i++)
    {
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
#include <GL/glut.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif
// ----------------------------------------------------------------------------
// GLOBAL ANIMATION VARIABLES (Positioned in front of Shaheed Minar Lawn)
// Coordinates: X = 1000 to 1400, Y = 510 to 600
// ----------------------------------------------------------------------------
float p1X = 1020.0f, p1Y = 520.0f; // Player 1
float p2X = 1100.0f, p2Y = 580.0f; // Player 2
float p3X = 1180.0f, p3Y = 530.0f; // Player 3
float p4X = 1260.0f, p4Y = 590.0f; // Player 4
float p5X = 1350.0f, p5Y = 540.0f; // Player 5
float p6X = 1280.0f, p6Y = 515.0f; // Player 6
float p7X = 1140.0f, p7Y = 555.0f; // Player 7

float ballX = 1020.0f;
float ballY = 520.0f;
int passState = 1; // 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 1
float ballProgress = 0.0f;
float ballRotation = 0.0f;


float speedVector[7] = { 0.005f, 0.007f, 0.006f, 0.008f, 0.006f, 0.005f, 0.007f };


void updateFootballAnimation()
{

    float speedVector[7] = { 0.005f, 0.007f, 0.006f, 0.008f, 0.006f, 0.005f, 0.007f };

    float currentSpeed = speedVector[passState - 1];
    ballProgress += currentSpeed;


    ballRotation += 4.0f;

    if (ballProgress >= 1.0f)
    {
        ballProgress = 0.0f;
        passState = (passState % 7) + 1;
    }

    float startX = p1X, startY = p1Y;
    float endX = p2X, endY = p2Y;

    if (passState == 1)
    {
        startX = p1X;
        startY = p1Y;
        endX = p2X;
        endY = p2Y;
    }
    else if (passState == 2)
    {
        startX = p2X;
        startY = p2Y;
        endX = p3X;
        endY = p3Y;
    }
    else if (passState == 3)
    {
        startX = p3X;
        startY = p3Y;
        endX = p4X;
        endY = p4Y;
    }
    else if (passState == 4)
    {
        startX = p4X;
        startY = p4Y;
        endX = p5X;
        endY = p5Y;
    }
    else if (passState == 5)
    {
        startX = p5X;
        startY = p5Y;
        endX = p6X;
        endY = p6Y;
    }
    else if (passState == 6)
    {
        startX = p6X;
        startY = p6Y;
        endX = p7X;
        endY = p7Y;
    }
    else if (passState == 7)
    {
        startX = p7X;
        startY = p7Y;
        endX = p1X;
        endY = p1Y;
    }

    // Linear interpolation
    ballX = startX + (endX - startX) * ballProgress;
    ballY = startY + (endY - startY) * ballProgress;

    // Curved pass trajectory
    float arcOffset = sinf(ballProgress * M_PI) * 8.0f;
    ballY += arcOffset;
}
// ----------------------------------------------------------------------------
// HELPER: DRAW DETAILED CASUAL PLAYER WITH KICK & IDLE ANIMATION
// ----------------------------------------------------------------------------
void drawDetailedPlayer(float px, float py, bool facingRight,
                        float shirtR, float shirtG, float shirtB,
                        float shortR, float shortG, float shortB,
                        float hairR, float hairG, float hairB,
                        float kickAngle = 0.0f, float idleOffset = 0.0f)
{
    glPushMatrix();
    glTranslatef(px, py + idleOffset, 0.0f);
    if (!facingRight) glScalef(-1.0f, 1.0f, 1.0f);

    // 1. Ground Shadow
    glColor4f(0.1f, 0.15f, 0.1f, 0.35f);
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<15; i++)
    {
        float a = i * 2.0f * M_PI / 15.0f;
        glVertex2f(cosf(a)*6.0f, sinf(a)*2.5f - idleOffset);
    }
    glEnd();

    // 2. Standing Leg (Left Leg)
    glColor3f(0.92f, 0.75f, 0.62f); // Skin
    glRectf(-2.0f, -6.0f, -0.8f, -1.2f);
    glColor3f(shirtR, shirtG, shirtB); // Sock
    glRectf(-2.1f, -3.0f, -0.7f, -1.2f);
    glColor3f(0.2f, 0.2f, 0.2f); // Shoe
    glRectf(-3.0f, -1.2f, -0.5f, 1.0f);
    glColor3f(0.9f, 0.9f, 0.9f);
    glRectf(-3.0f, -1.2f, -0.5f, -0.6f);

    // 3. Dynamic Kicking Leg (Right Leg with Rotation)
    glPushMatrix();
    glTranslatef(1.4f, -6.0f, 0.0f);
    glRotatef(kickAngle, 0.0f, 0.0f, 1.0f); // Kicking action

    // Skin & Sock
    glColor3f(0.92f, 0.75f, 0.62f);
    glRectf(-0.6f, 0.0f, 0.6f, 4.8f);
    glColor3f(shirtR, shirtG, shirtB);
    glRectf(-0.7f, 3.0f, 0.7f, 4.8f);

    // Kicking Shoe
    glColor3f(0.2f, 0.2f, 0.2f);
    glRectf(-0.9f, 4.8f, 1.6f, 7.0f);
    glColor3f(0.9f, 0.9f, 0.9f);
    glRectf(-0.9f, 4.8f, 1.6f, 5.4f);
    glPopMatrix();

    // 4. Shorts
    glColor3f(shortR, shortG, shortB);
    glRectf(-2.8f, -10.0f, 2.8f, -6.0f);

    // 5. Shirt Body & Pattern
    glColor3f(shirtR, shirtG, shirtB);
    glRectf(-3.2f, -18.0f, 3.2f, -10.0f);

    glColor3f(shortR, shortG, shortB);
    glRectf(-2.5f, -15.0f, 2.5f, -14.0f);

    // 6. Arms & Hands (Slight swing when kicking)
    float armAngle = kickAngle * 0.4f;
    glPushMatrix();
    glTranslatef(-3.8f, -14.0f, 0.0f);
    glRotatef(-armAngle, 0.0f, 0.0f, 1.0f);
    glColor3f(shirtR, shirtG, shirtB);
    glRectf(-0.7f, -2.0f, 0.6f, 2.0f);
    glColor3f(0.92f, 0.75f, 0.62f);
    glRectf(-0.5f, 2.0f, 0.5f, 5.5f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.8f, -14.0f, 0.0f);
    glRotatef(armAngle, 0.0f, 0.0f, 1.0f);
    glColor3f(shirtR, shirtG, shirtB);
    glRectf(-0.6f, -2.0f, 0.7f, 2.0f);
    glColor3f(0.92f, 0.75f, 0.62f);
    glRectf(-0.5f, 2.0f, 0.5f, 5.5f);
    glPopMatrix();

    // 7. Head & Face
    glColor3f(0.92f, 0.75f, 0.62f);
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<15; i++)
    {
        float a = i * 2.0f * M_PI / 15.0f;
        glVertex2f(cosf(a)*3.2f, -21.0f + sinf(a)*3.2f);
    }
    glEnd();

    // Eye Detail
    glColor3f(0.1f, 0.1f, 0.1f);
    glRectf(1.0f, -21.5f, 2.0f, -20.5f);

    // 8. Hair
    glColor3f(hairR, hairG, hairB);
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<12; i++)
    {
        float a = i * M_PI / 12.0f;
        glVertex2f(cosf(a)*3.5f, -21.5f - sinf(a)*3.2f);
    }
    glEnd();

    glPopMatrix();
}

void drawSmallPlayer(float px, float py, bool facingRight)
{
    drawDetailedPlayer(px, py, facingRight, 0.95f, 0.95f, 0.95f, 0.15f, 0.35f, 0.75f, 0.1f, 0.1f, 0.1f);
}
void drawGoalPost()
{
}

// ----------------------------------------------------------------------------
// MAIN DRAWING FUNCTION FOR PLAYERS & PASSING ANIMATION
// ----------------------------------------------------------------------------
void drawFootballField()
{
    float kickAngles[7] = { 0.0f };
    float idleOffsets[7] = { 0.0f };

    int passerIdx = passState - 1;
    int receiverIdx = passState % 7;

    if (isPassingActive)
    {
        if (ballProgress < 0.35f)
        {
            kickAngles[passerIdx] = sinf((ballProgress / 0.35f) * M_PI) * -35.0f;
        }
        if (ballProgress > 0.7f)
        {
            kickAngles[receiverIdx] = sinf(((ballProgress - 0.7f) / 0.3f) * M_PI) * 20.0f;
        }
        for (int i = 0; i < 7; i++)
        {
            idleOffsets[i] = sinf(ballProgress * M_PI * 2.0f + i) * 0.8f;
        }
    }

    // 1. Draw 7 Players
    drawDetailedPlayer(p1X, p1Y, true,  0.95f, 0.95f, 0.95f,  0.15f, 0.35f, 0.75f,  0.1f, 0.1f, 0.1f, kickAngles[0], idleOffsets[0]);
    drawDetailedPlayer(p2X, p2Y, true,  0.85f, 0.15f, 0.15f,  0.15f, 0.15f, 0.15f,  0.4f, 0.2f, 0.1f, kickAngles[1], idleOffsets[1]);
    drawDetailedPlayer(p3X, p3Y, true,  0.95f, 0.85f, 0.10f,  0.10f, 0.55f, 0.20f,  0.1f, 0.1f, 0.1f, kickAngles[2], idleOffsets[2]);
    drawDetailedPlayer(p4X, p4Y, true,  0.10f, 0.70f, 0.85f,  0.05f, 0.10f, 0.25f,  0.8f, 0.7f, 0.2f, kickAngles[3], idleOffsets[3]);
    drawDetailedPlayer(p5X, p5Y, false, 0.95f, 0.45f, 0.10f,  0.40f, 0.40f, 0.45f,  0.2f, 0.1f, 0.05f, kickAngles[4], idleOffsets[4]);
    drawDetailedPlayer(p6X, p6Y, false, 0.20f, 0.65f, 0.25f,  0.90f, 0.90f, 0.90f,  0.1f, 0.1f, 0.1f, kickAngles[5], idleOffsets[5]);
    drawDetailedPlayer(p7X, p7Y, true,  0.55f, 0.20f, 0.75f,  0.15f, 0.15f, 0.15f,  0.3f, 0.15f, 0.05f, kickAngles[6], idleOffsets[6]);

    // 2. Update Position Only If Active
    if (isPassingActive)
    {
        updateFootballAnimation();
    }

    // 3. Draw Football and Shadow
    glColor4f(0.1f, 0.15f, 0.1f, 0.35f);
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<12; i++)
    {
        float a = i * 2.0f * M_PI / 12.0f;
        glVertex2f(ballX + cosf(a)*3.5f, ballY + 1.0f + sinf(a)*1.4f);
    }
    glEnd();

    glPushMatrix();
    glTranslatef(ballX, ballY, 0.0f);
    glRotatef(ballRotation, 0.0f, 0.0f, 1.0f);

    glColor3f(0.98f, 0.98f, 0.98f);
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<15; i++)
    {
        float a = i * 2.0f * M_PI / 15.0f;
        glVertex2f(cosf(a)*3.0f, sinf(a)*3.0f);
    }
    glEnd();

    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(1.5f, 1.0f);
    glVertex2f(0.5f, 2.2f);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(-1.5f, -1.0f);
    glVertex2f(-0.5f, -2.2f);
    glEnd();

    glPopMatrix();
}


























// ----------------------------------------------------------------------------
// RESCALED BASKETBALL HOOP & SHOOTING ANIMATION
// Scaled down pole & player height with extra details
// ----------------------------------------------------------------------------

float bPlayerX = 1495.0f;
float bPlayerY = 485.0f;

// Ball Animation Parameters
float bBallX = 1498.0f;
float bBallY = 472.0f;
float bBallProgress = 0.0f;
float bBallRotation = 0.0f;

void updateBasketballAnimation()
{
    // Speed / Seed komano holo (0.012f -> 0.004f)
    bBallProgress += 0.004f;
    if (bBallProgress > 1.0f)
    {
        bBallProgress = 0.0f;
    }

    // Rotation speed-o Control kora holo (10.0f -> 2.5f)
    bBallRotation += 2.5f;
    if (bBallRotation >= 360.0f)
    {
        bBallRotation -= 360.0f; // Rotation angle reset
    }

    // Adjusted Arc Trajectory for smaller pole height (Rim Y = 390)
    if (bBallProgress < 0.45f)
    {
        float t = bBallProgress / 0.45f;
        float startX = 1498.0f, startY = 472.0f;
        float targetX = 1554.0f, targetY = 390.0f;

        bBallX = startX + (targetX - startX) * t;
        bBallY = startY + (targetY - startY) * t - sinf(t * M_PI) * 45.0f;
    }
    else if (bBallProgress < 0.65f)
    {
        float t = (bBallProgress - 0.45f) / 0.20f;
        float startX = 1554.0f, startY = 390.0f;
        float groundY = 510.0f;

        bBallX = startX;
        bBallY = startY + (groundY - startY) * t;
    }
    else
    {
        float t = (bBallProgress - 0.65f) / 0.35f;
        float startX = 1554.0f, startY = 510.0f;
        float endX = 1498.0f, endY = 472.0f;

        bBallX = startX + (endX - startX) * t;
        bBallY = startY + (endY - startY) * t - sinf(t * M_PI) * 15.0f;
    }
}



void drawBasketballHoop()
{
    // 1. Concrete Ground Court Patch
    glColor3f(0.70f, 0.72f, 0.74f);
    glBegin(GL_POLYGON);
    glVertex2f(1460.0f, 510.0f);
    glVertex2f(1580.0f, 510.0f);
    glVertex2f(1570.0f, 522.0f);
    glVertex2f(1450.0f, 522.0f);
    glEnd();

    // White Border Lines
    glColor3f(0.95f, 0.95f, 0.95f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(1460.0f, 510.0f);
    glVertex2f(1580.0f, 510.0f);
    glVertex2f(1570.0f, 522.0f);
    glVertex2f(1450.0f, 522.0f);
    glEnd();

    // Key Hole Arc on Court
    glLineWidth(1.2f);
    glBegin(GL_LINE_STRIP);
    for(int i=0; i<=10; i++)
    {
        float a = i * M_PI / 10.0f;
        glVertex2f(1554.0f + cosf(a)*18.0f, 510.0f + sinf(a)*5.0f);
    }
    glEnd();

    // 2. Heavy Base Stand
    glColor3f(0.20f, 0.22f, 0.24f);
    glRectf(1558.0f, 502.0f, 1576.0f, 510.0f);
    glColor3f(0.35f, 0.38f, 0.40f);
    glRectf(1560.0f, 498.0f, 1574.0f, 502.0f);

    // Reduced Height Pole (Height halved: Y = 360 to 498)
    glColor3f(0.35f, 0.37f, 0.40f);
    glRectf(1565.0f, 360.0f, 1569.0f, 498.0f);
    glColor3f(0.60f, 0.63f, 0.65f); // 3D Specular Highlight
    glRectf(1566.0f, 360.0f, 1567.0f, 498.0f);

    // Backboard Support Brackets (Behind Board)
    glColor3f(0.25f, 0.25f, 0.28f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(1565.0f, 370.0f);
    glVertex2f(1558.0f, 360.0f);
    glVertex2f(1565.0f, 390.0f);
    glVertex2f(1558.0f, 395.0f);
    glEnd();

    // 3. Backboard (Reduced Size with Glass & Rim Mount)
    // 3D Thickness Side
    glColor3f(0.50f, 0.52f, 0.55f);
    glBegin(GL_POLYGON);
    glVertex2f(1562.0f, 355.0f);
    glVertex2f(1564.0f, 357.0f);
    glVertex2f(1564.0f, 397.0f);
    glVertex2f(1562.0f, 395.0f);
    glEnd();

    // Board Main Body
    glColor3f(0.95f, 0.96f, 0.98f);
    glRectf(1546.0f, 355.0f, 1562.0f, 395.0f);

    // Black Outer Border
    glColor3f(0.12f, 0.12f, 0.15f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(1546.0f, 355.0f);
    glVertex2f(1562.0f, 355.0f);
    glVertex2f(1562.0f, 395.0f);
    glVertex2f(1546.0f, 395.0f);
    glEnd();

    // Inner Red Target Box
    glColor3f(0.85f, 0.20f, 0.10f);
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(1550.0f, 375.0f);
    glVertex2f(1558.0f, 375.0f);
    glVertex2f(1558.0f, 388.0f);
    glVertex2f(1550.0f, 388.0f);
    glEnd();

    // 4. Basketball Rim Mount & Rim Ring
    // Metal Base Connector
    glColor3f(0.80f, 0.18f, 0.05f);
    glRectf(1552.0f, 388.0f, 1556.0f, 391.0f);

    // Outer Rim Oval
    glColor3f(0.92f, 0.25f, 0.05f);
    glLineWidth(2.5f);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 20; i++)
    {
        float rad = i * 2.0f * M_PI / 20.0f;
        glVertex2f(1554.0f + cosf(rad) * 6.0f, 390.0f + sinf(rad) * 2.0f);
    }
    glEnd();

    // Net Mesh Strands
    glColor4f(0.95f, 0.95f, 0.95f, 0.85f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    for(int i = 0; i < 8; i++)
    {
        float rad = i * 2.0f * M_PI / 8.0f;
        float topX = 1554.0f + cosf(rad) * 5.5f;
        float topY = 390.0f + sinf(rad) * 1.6f;
        glVertex2f(topX, topY);
        glVertex2f(1554.0f + cosf(rad) * 2.8f, 402.0f);
    }
    glEnd();

    // 5. Scaled Down & Detailed Playing Student Body
    float armAngle = (bBallProgress < 0.3f) ? -(bBallProgress / 0.3f) * 35.0f : -10.0f;

    glPushMatrix();
    glTranslatef(bPlayerX, bPlayerY, 0.0f);

    // Player Shadow
    glColor4f(0.10f, 0.12f, 0.10f, 0.30f);
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<15; i++)
    {
        float a = i * 2.0f * M_PI / 15.0f;
        glVertex2f(cosf(a)*4.0f, 22.0f + sinf(a)*1.5f);
    }
    glEnd();

    // Shoes with Soles
    glColor3f(0.15f, 0.15f, 0.15f);
    glRectf(-1.8f, 20.5f, -0.3f, 22.0f);
    glRectf(0.3f, 20.5f, 1.8f, 22.0f);
    glColor3f(0.85f, 0.85f, 0.85f); // White sole
    glRectf(-1.8f, 21.6f, -0.3f, 22.2f);
    glRectf(0.3f, 21.6f, 1.8f, 22.2f);

    // Legs
    glColor3f(0.92f, 0.75f, 0.62f);
    glRectf(-1.4f, 15.0f, -0.5f, 20.5f);
    glRectf(0.5f, 15.0f, 1.4f, 20.5f);

    // Sports Shorts with Side Stripe
    glColor3f(0.15f, 0.35f, 0.75f);
    glRectf(-1.8f, 11.0f, 1.8f, 15.0f);
    glColor3f(0.95f, 0.95f, 0.95f); // Side Stripe
    glRectf(-1.8f, 11.0f, -1.5f, 15.0f);

    // Shirt & Collar Detail
    glColor3f(0.95f, 0.95f, 0.95f);
    glRectf(-2.0f, 2.0f, 2.0f, 11.0f);
    glColor3f(0.15f, 0.35f, 0.75f); // Blue V-Collar
    glLineWidth(1.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.8f, 2.0f);
    glVertex2f(0.8f, 2.0f);
    glVertex2f(0.0f, 4.0f);
    glEnd();

    // Head, Hair & Facial Detail
    glColor3f(0.92f, 0.75f, 0.62f); // Skin
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<15; i++)
    {
        float a = i * 2.0f * M_PI / 15.0f;
        glVertex2f(cosf(a)*2.2f, -1.8f + sinf(a)*2.2f);
    }
    glEnd();

    glColor3f(0.12f, 0.12f, 0.12f); // Hair
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<12; i++)
    {
        float a = i * M_PI / 12.0f;
        glVertex2f(cosf(a)*2.3f, -2.0f - sinf(a)*2.0f);
    }
    glEnd();

    // Eye dot
    glColor3f(0.10f, 0.10f, 0.10f);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glVertex2f(1.0f, -1.8f);
    glEnd();

    // Shooting Arms (Both Arms Visible)
    // Left Arm (Stabilizing)
    glColor3f(0.88f, 0.70f, 0.58f);
    glRectf(-0.5f, 3.0f, 2.8f, 4.5f);

    // Right Arm (Shooting Motion)
    glPushMatrix();
    glTranslatef(1.2f, 3.5f, 0.0f);
    glRotatef(armAngle, 0.0f, 0.0f, 1.0f);
    glColor3f(0.92f, 0.75f, 0.62f);
    glRectf(0.0f, -0.6f, 4.2f, 0.6f);
    glPopMatrix();

    glPopMatrix();

    // 6. Basketball with Detailed Seams
    updateBasketballAnimation();

    // Ball Ground Shadow
    glColor4f(0.10f, 0.12f, 0.10f, 0.25f);
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<12; i++)
    {
        float a = i * 2.0f * M_PI / 12.0f;
        glVertex2f(bBallX + cosf(a)*2.8f, 510.0f + sinf(a)*1.0f);
    }
    glEnd();

    // Rotating Basketball
    glPushMatrix();
    glTranslatef(bBallX, bBallY, 0.0f);
    glRotatef(bBallRotation, 0.0f, 0.0f, 1.0f);

    // Orange Base
    glColor3f(0.92f, 0.40f, 0.05f);
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<16; i++)
    {
        float a = i * 2.0f * M_PI / 16.0f;
        glVertex2f(cosf(a)*2.8f, sinf(a)*2.8f);
    }
    glEnd();

    // Black Seams/Lines
    glColor3f(0.10f, 0.10f, 0.10f);
    glLineWidth(1.2f);
    glBegin(GL_LINES);
    glVertex2f(-2.8f, 0.0f);
    glVertex2f(2.8f, 0.0f);
    glVertex2f(0.0f, -2.8f);
    glVertex2f(0.0f, 2.8f);
    glEnd();

    glLineWidth(1.0f);
    glBegin(GL_LINE_STRIP);
    for(int i=0; i<=10; i++)
    {
        float a = -M_PI/2.0f + (i * M_PI / 10.0f);
        glVertex2f(cosf(a)*1.8f - 0.8f, sinf(a)*1.8f);
    }
    glEnd();

    glPopMatrix();
}
























// ----------------------------------------------------------------------------
// HIGHLY DETAILED PERSPECTIVE CRICKET PITCH (LEFT LAWN - BRIGHT & REFINED)
// Positioned on the left field, running parallel to the central assembly path.
// Trajectory: As Y increases towards foreground (520->585), X shifts left (615->500).
// Features: Brightened turf & clay colors, ultra-thin precision white lines,
//           isometric dashed markings, and refined stump details.
// ----------------------------------------------------------------------------

void drawCricketPitch()
{
    // Primary Pitch Coordinates (Aligned with left lawn perspective)
    float x1_far = 615.0f, y1_far = 520.0f; // Far Top-Left
    float x2_far = 635.0f, y2_far = 523.0f; // Far Top-Right

    float x1_near = 495.0f, y1_near = 582.0f; // Near Bottom-Left
    float x2_near = 522.0f, y2_near = 588.0f; // Near Bottom-Right

    // 1. OUTFIELD GRASS DUST & CUT PATTERN (Brighter Grass Base Blend)
    glColor4f(0.30f, 0.62f, 0.22f, 0.70f);
    glBegin(GL_POLYGON);
    glVertex2f(x1_near - 8.0f, y1_near - 4.0f);
    glVertex2f(x2_near + 8.0f, y2_near + 4.0f);
    glVertex2f(x2_far + 6.0f,  y2_far + 3.0f);
    glVertex2f(x1_far - 6.0f,  y1_far - 3.0f);
    glEnd();

    // 2. HARD CLAY SOIL PITCH BASE (Bright Warm Khaki/Clay Tone)
    glColor3f(0.90f, 0.81f, 0.65f);
    glBegin(GL_POLYGON);
    glVertex2f(x1_near, y1_near);
    glVertex2f(x2_near, y2_near);
    glVertex2f(x2_far,  y2_far);
    glVertex2f(x1_far,  y1_far);
    glEnd();

    // 3. PITCH SURFACE TEXTURE & WEAR LINES (Lighter Dried Center Track)
    // Dry Clay Center Track
    glColor3f(0.85f, 0.75f, 0.58f);
    glBegin(GL_POLYGON);
    glVertex2f(x1_near + 5.0f, y1_near + 1.0f);
    glVertex2f(x2_near - 5.0f, y2_near - 1.0f);
    glVertex2f(x2_far - 4.0f,  y2_far - 1.0f);
    glVertex2f(x1_far + 4.0f,  y1_far + 1.0f);
    glEnd();

    // Rough Footmark Patches near Bowling Creases (Soft Lighter Dirt Marks)
    glColor3f(0.78f, 0.67f, 0.50f);
    // Near Rough
    glBegin(GL_POLYGON);
    glVertex2f(x1_near + 3.0f, y1_near - 2.0f);
    glVertex2f(x1_near + 9.0f, y1_near - 1.0f);
    glVertex2f(x1_near + 7.0f, y1_near - 12.0f);
    glVertex2f(x1_near + 1.0f, y1_near - 12.0f);
    glEnd();
    // Far Rough
    glBegin(GL_POLYGON);
    glVertex2f(x2_far - 2.0f, y2_far - 1.0f);
    glVertex2f(x2_far - 7.0f, y2_far - 1.0f);
    glVertex2f(x2_far - 5.0f, y2_far + 8.0f);
    glVertex2f(x2_far - 1.0f, y2_far + 8.0f);
    glEnd();

    // 4. ULTRA-THIN BRIGHT WHITE CREASE MARKINGS
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.0f); // Thin lines

    // Near End Creases (Batting Side)
    float nPoppingX1 = x1_near * 0.82f + x1_far * 0.18f;
    float nPoppingY1 = y1_near * 0.82f + y1_far * 0.18f;
    float nPoppingX2 = x2_near * 0.82f + x2_far * 0.18f;
    float nPoppingY2 = y2_near * 0.82f + y2_far * 0.18f;

    glBegin(GL_LINES);
    // Popping Crease Line
    glVertex2f(nPoppingX1 - 5.0f, nPoppingY1 - 1.2f);
    glVertex2f(nPoppingX2 + 5.0f, nPoppingY2 + 1.2f);

    // Bowling Crease Line
    glVertex2f(x1_near + 2.0f, y1_near + 0.5f);
    glVertex2f(x2_near - 2.0f, y2_near - 0.5f);

    // Return Creases Left & Right
    glVertex2f(x1_near + 2.0f, y1_near + 0.5f);
    glVertex2f(nPoppingX1 - 2.0f, nPoppingY1 - 0.5f);
    glVertex2f(x2_near - 2.0f, y2_near - 0.5f);
    glVertex2f(nPoppingX2 + 2.0f, nPoppingY2 + 0.5f);
    glEnd();

    // Far End Creases (Bowling Side)
    float fPoppingX1 = x1_far * 0.82f + x1_near * 0.18f;
    float fPoppingY1 = y1_far * 0.82f + y1_near * 0.18f;
    float fPoppingX2 = x2_far * 0.82f + x2_near * 0.18f;
    float fPoppingY2 = y2_far * 0.82f + y2_near * 0.18f;

    glBegin(GL_LINES);
    // Popping Crease Line
    glVertex2f(fPoppingX1 - 4.0f, fPoppingY1 - 1.0f);
    glVertex2f(fPoppingX2 + 4.0f, fPoppingY2 + 1.0f);

    // Bowling Crease Line
    glVertex2f(x1_far + 2.0f, y1_far + 0.5f);
    glVertex2f(x2_far - 2.0f, y2_far - 0.5f);

    // Return Creases Left & Right
    glVertex2f(x1_far + 2.0f, y1_far + 0.5f);
    glVertex2f(fPoppingX1 - 1.5f, fPoppingY1 - 0.5f);
    glVertex2f(x2_far - 2.0f, y2_far - 0.5f);
    glVertex2f(fPoppingX2 + 1.5f, fPoppingY2 + 0.5f);
    glEnd();

    // Fine Dashed Indicator Lines (Thin White Accent Marks)
    glLineWidth(0.8f);
    glBegin(GL_LINES);
    // Near Side Dashes
    glVertex2f(nPoppingX1 + 2.0f, nPoppingY1);
    glVertex2f(nPoppingX1 + 4.0f, nPoppingY1);
    glVertex2f(nPoppingX2 - 2.0f, nPoppingY2);
    glVertex2f(nPoppingX2 - 4.0f, nPoppingY2);
    // Far Side Dashes (Fixed Variable Name Here)
    glVertex2f(fPoppingX1 + 1.5f, fPoppingY1);
    glVertex2f(fPoppingX1 + 3.0f, fPoppingY1);
    glVertex2f(fPoppingX2 - 1.5f, fPoppingY2);
    glVertex2f(fPoppingX2 - 3.0f, fPoppingY2);
    glEnd();

    // 5. STUMPS, BAILS & GROUND CAST SHADOWS

    // --- NEAR STUMPS (Foreground - Larger Scale) ---
    float nStumpBaseX = (x1_near + x2_near) * 0.5f;
    float nStumpBaseY = (y1_near + y2_near) * 0.5f;

    // Soft Ambient Base Shadow on Pitch Surface
    glColor4f(0.12f, 0.12f, 0.12f, 0.30f);
    glBegin(GL_POLYGON);
    glVertex2f(nStumpBaseX - 5.0f, nStumpBaseY);
    glVertex2f(nStumpBaseX + 5.0f, nStumpBaseY);
    glVertex2f(nStumpBaseX + 8.0f, nStumpBaseY + 3.0f);
    glVertex2f(nStumpBaseX - 2.0f, nStumpBaseY + 3.0f);
    glEnd();

    // Wooden Stumps with Lighter Bright Highlights
    for (int i = -1; i <= 1; i++)
    {
        float sx = nStumpBaseX + (i * 3.5f);

        // Shadow Edge
        glColor3f(0.78f, 0.62f, 0.35f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glVertex2f(sx, nStumpBaseY);
        glVertex2f(sx, nStumpBaseY - 16.0f);
        glEnd();

        // Bright Wood Highlight
        glColor3f(0.98f, 0.90f, 0.68f);
        glLineWidth(1.0f);
        glBegin(GL_LINES);
        glVertex2f(sx - 0.3f, nStumpBaseY);
        glVertex2f(sx - 0.3f, nStumpBaseY - 16.0f);
        glEnd();
    }

    // Near Bails (Top Crossbars - Bright Light Yellow)
    glColor3f(1.0f, 0.95f, 0.70f);
    glLineWidth(1.2f);
    glBegin(GL_LINES);
    glVertex2f(nStumpBaseX - 4.5f, nStumpBaseY - 16.0f);
    glVertex2f(nStumpBaseX + 4.5f, nStumpBaseY - 16.0f);
    glEnd();

    // --- FAR STUMPS (Background - Scaled Down for Depth) ---
    float fStumpBaseX = (x1_far + x2_far) * 0.5f;
    float fStumpBaseY = (y1_far + y2_far) * 0.5f;

    // Soft Base Shadow
    glColor4f(0.12f, 0.12f, 0.12f, 0.25f);
    glBegin(GL_POLYGON);
    glVertex2f(fStumpBaseX - 3.5f, fStumpBaseY);
    glVertex2f(fStumpBaseX + 3.5f, fStumpBaseY);
    glVertex2f(fStumpBaseX + 6.0f, fStumpBaseY + 2.0f);
    glVertex2f(fStumpBaseX - 1.0f, fStumpBaseY + 2.0f);
    glEnd();

    // Wooden Stumps
    for (int i = -1; i <= 1; i++)
    {
        float sx = fStumpBaseX + (i * 2.4f);

        glColor3f(0.95f, 0.82f, 0.55f);
        glLineWidth(1.2f);
        glBegin(GL_LINES);
        glVertex2f(sx, fStumpBaseY);
        glVertex2f(sx, fStumpBaseY - 10.0f);
        glEnd();
    }

    // Far Bails
    glColor3f(1.0f, 0.95f, 0.70f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(fStumpBaseX - 3.2f, fStumpBaseY - 10.0f);
    glVertex2f(fStumpBaseX + 3.2f, fStumpBaseY - 10.0f);
    glEnd();
}


















































// ----------------------------------------------------------------------------
// HIGHLY DETAILED 3D-REALISTIC 2D SWING SET WITH THREE ANIMATED STUDENTS
// Scaled down to 0.60x size (60% of original scale).
// Animation FIXED to swing FORWARD/BACKWARD (depth oscillation).
// Smooth animation using static variable update and glutPostRedisplay().
// ----------------------------------------------------------------------------

void drawSwing()
{
    // Frame Timing & Animation Logic
    static float angleTime = 0.0f;
    angleTime += 0.02f; // Speed of swing oscillation

    // Updated Positioning & 0.60 Scale Parameters
    float centerX = 145.0f;     // Center X position
    float groundY = 495.0f;     // Base ground Y position

    // Scale factor applied to dimensions:
    float frameHeight = 36.0f;  // 60.0f * 0.60
    float topY = groundY - frameHeight; // Top crossbeam position
    float frameWidth = 72.0f;   // 120.0f * 0.60
    float legSpread = 8.4f;     // 14.0f * 0.60

    // ------------------------------------------------------------------------
    // 1. A-FRAME SIDE SUPPORTS & CROSSBEAM (3D Metallic/Steel Tube Effect)
    // ------------------------------------------------------------------------

    // Back Legs (Darker shade for depth perspective)
    glColor3f(0.35f, 0.38f, 0.42f); // Steel Shadow Gray
    glLineWidth(2.5f);
    glBegin(GL_LINES);
    // Left Back Leg
    glVertex2f(centerX - frameWidth / 2.0f - legSpread, groundY - 3.6f);
    glVertex2f(centerX - frameWidth / 2.0f, topY);
    // Right Back Leg
    glVertex2f(centerX + frameWidth / 2.0f - legSpread, groundY - 3.6f);
    glVertex2f(centerX + frameWidth / 2.0f, topY);
    glEnd();

    // Ground Concrete Footings (Base Pads)
    glColor3f(0.55f, 0.55f, 0.58f);
    glRectf(centerX - frameWidth / 2.0f - legSpread - 2.4f, groundY - 1.2f, centerX - frameWidth / 2.0f - legSpread + 2.4f, groundY + 1.2f);
    glRectf(centerX + frameWidth / 2.0f - legSpread - 2.4f, groundY - 1.2f, centerX + frameWidth / 2.0f - legSpread + 2.4f, groundY + 1.2f);
    glRectf(centerX - frameWidth / 2.0f + legSpread - 2.4f, groundY + 2.4f, centerX - frameWidth / 2.0f + legSpread + 2.4f, groundY + 4.8f);
    glRectf(centerX + frameWidth / 2.0f + legSpread - 2.4f, groundY + 2.4f, centerX + frameWidth / 2.0f + legSpread + 2.4f, groundY + 4.8f);

    // Front Legs (Main bright metallic frame)
    glColor3f(0.65f, 0.68f, 0.72f); // Metallic Silver Gray
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    // Left Front Leg
    glVertex2f(centerX - frameWidth / 2.0f + legSpread, groundY + 3.6f);
    glVertex2f(centerX - frameWidth / 2.0f, topY);
    // Right Front Leg
    glVertex2f(centerX + frameWidth / 2.0f + legSpread, groundY + 3.6f);
    glVertex2f(centerX + frameWidth / 2.0f, topY);
    glEnd();

    // Side A-Frame Horizontal Braces
    glColor3f(0.50f, 0.53f, 0.58f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    // Left A-Frame Brace
    glVertex2f(centerX - frameWidth / 2.0f - legSpread * 0.4f, topY + frameHeight * 0.6f);
    glVertex2f(centerX - frameWidth / 2.0f + legSpread * 0.4f, topY + frameHeight * 0.6f);
    // Right A-Frame Brace
    glVertex2f(centerX + frameWidth / 2.0f - legSpread * 0.4f, topY + frameHeight * 0.6f);
    glVertex2f(centerX + frameWidth / 2.0f + legSpread * 0.4f, topY + frameHeight * 0.6f);
    glEnd();

    // Top Main Horizontal Crossbeam
    glColor3f(0.75f, 0.78f, 0.82f); // Bright Steel Top Beam
    glLineWidth(4.2f);
    glBegin(GL_LINES);
    glVertex2f(centerX - frameWidth / 2.0f - 3.6f, topY);
    glVertex2f(centerX + frameWidth / 2.0f + 3.6f, topY);
    glEnd();

    // Corner Support Triangular Gusset Plates
    glColor3f(0.45f, 0.48f, 0.52f);
    glBegin(GL_TRIANGLES);
    glVertex2f(centerX - frameWidth / 2.0f, topY);
    glVertex2f(centerX - frameWidth / 2.0f + 6.0f, topY);
    glVertex2f(centerX - frameWidth / 2.0f, topY + 6.0f);

    glVertex2f(centerX + frameWidth / 2.0f, topY);
    glVertex2f(centerX + frameWidth / 2.0f - 6.0f, topY);
    glVertex2f(centerX + frameWidth / 2.0f, topY + 6.0f);
    glEnd();


    // ------------------------------------------------------------------------
    // 2. THREE DYNAMICALLY ANIMATED SWINGS WITH STUDENTS (Scaled 0.60x)
    // ------------------------------------------------------------------------

    // Swing Positions along crossbeam
    float swingX[3] = { centerX - 21.6f, centerX, centerX + 21.6f };
    float ropeLength = 21.6f;  // 36.0f * 0.60
    float seatWidth = 8.4f;    // 14.0f * 0.60

    for (int s = 0; s < 3; s++)
    {
        float sx = swingX[s];

        // Top Mounting Rings / Clamps
        glColor3f(0.3f, 0.3f, 0.3f);
        glRectf(sx - seatWidth / 2.0f - 0.6f, topY - 0.6f, sx - seatWidth / 2.0f + 0.6f, topY + 1.8f);
        glRectf(sx + seatWidth / 2.0f - 0.6f, topY - 0.6f, sx + seatWidth / 2.0f + 0.6f, topY + 1.8f);

        // Phase offsets for natural asynchronous motion
        float phaseOffset = (s == 1) ? 0.4f : (s == 2 ? -0.3f : 0.0f);

        // --- FORWARD/BACKWARD SWING LOGIC ---
        // We use sine to modulate the Y-offset (depth) to simulate swinging out of the 2D plane.
        // It creates a "squash and stretch" effect vertically on the ropes and student.
        float sinFactor = sinf(angleTime + phaseOffset);
        float currentRopeLength = ropeLength * (1.0f + 0.25f * sinFactor); // +/- 25% length change

        // Push matrix for local positioning around top pivot point (sx, topY)
        glPushMatrix();
        glTranslatef(sx, topY, 0.0f);

        // Chain / Suspension Ropes
        glColor3f(0.40f, 0.40f, 0.42f);
        glLineWidth(1.2f);
        glBegin(GL_LINES);
        glVertex2f(-seatWidth / 2.0f, 1.2f);
        glVertex2f(-seatWidth / 2.0f, currentRopeLength);
        glVertex2f( seatWidth / 2.0f, 1.2f);
        glVertex2f( seatWidth / 2.0f, currentRopeLength);
        glEnd();

        // Chain Links (Dotted detail)
        glColor3f(0.80f, 0.80f, 0.85f);
        glPointSize(1.5f);
        glBegin(GL_POINTS);
        for (float cy = 2.4f; cy < currentRopeLength; cy += 2.1f)
        {
            glVertex2f(-seatWidth / 2.0f, cy);
            glVertex2f( seatWidth / 2.0f, cy);
        }
        glEnd();

        // Wooden Seat Board (Perspective change with swing depth)
        glColor3f(0.70f, 0.25f, 0.15f); // Reddish Wood / Coated Seat
        // Seat board gets thinner when swinging "away"
        float seatThickness = 2.1f * (1.0f - 0.4f * fabsf(sinFactor));
        glRectf(-seatWidth / 2.0f - 1.2f, currentRopeLength, seatWidth / 2.0f + 1.2f, currentRopeLength + seatThickness);
        // Highlight Edge
        glColor3f(0.85f, 0.40f, 0.25f);
        glLineWidth(1.0f);
        glBegin(GL_LINES);
        glVertex2f(-seatWidth / 2.0f - 1.2f, currentRopeLength);
        glVertex2f( seatWidth / 2.0f + 1.2f, currentRopeLength);
        glEnd();

        // --------------------------------------------------------------------
        // STUDENT DRAWING (Scaled relative to local seat origin)
        // --------------------------------------------------------------------

        float localSeatY = currentRopeLength;
        // The student torso/head needs to scale slightly to simulate depth
        float studentScaleDepth = 1.0f + 0.15f * sinFactor; // +/- 15% vertical scale
        float baseStudentHeight = 10.8f; // 18.0f * 0.60 original
        float currentHeadY = localSeatY - baseStudentHeight * studentScaleDepth;

        // 1. Legs (Hanging down from seat)
        if (s == 1)   // Girl with Navy Blue Skirt & White Socks
        {
            glColor3f(0.12f, 0.22f, 0.50f); // Navy Skirt
            glRectf(-3.0f, localSeatY + 1.2f, 3.0f, localSeatY + 4.2f);

            // Skin Legs
            glColor3f(0.92f, 0.74f, 0.60f);
            glRectf(-2.4f, localSeatY + 4.2f, -0.9f, localSeatY + 7.8f);
            glRectf( 0.9f, localSeatY + 4.2f,  2.4f, localSeatY + 7.8f);

            // White Socks
            glColor3f(0.95f, 0.95f, 0.95f);
            glRectf(-2.4f, localSeatY + 7.8f, -0.9f, localSeatY + 9.6f);
            glRectf( 0.9f, localSeatY + 7.8f,  2.4f, localSeatY + 9.6f);

            // Black Shoes
            glColor3f(0.10f, 0.10f, 0.10f);
            glRectf(-2.7f, localSeatY + 9.6f, -0.6f, localSeatY + 10.8f);
            glRectf( 0.6f, localSeatY + 9.6f,  2.7f, localSeatY + 10.8f);
        }
        else   // Boys with Navy Blue Pants
        {
            glColor3f(0.12f, 0.22f, 0.50f); // Navy Pants
            glRectf(-2.7f, localSeatY + 1.2f, -0.6f, localSeatY + 8.4f);
            glRectf( 0.6f, localSeatY + 1.2f,  2.7f, localSeatY + 8.4f);

            // Black Shoes
            glColor3f(0.10f, 0.10f, 0.10f);
            glRectf(-3.0f, localSeatY + 8.4f, -0.3f, localSeatY + 9.9f);
            glRectf( 0.3f, localSeatY + 8.4f,  3.0f, localSeatY + 9.9f);
        }

        // 2. Torso (White School Shirt - Scaled for depth)
        glColor3f(0.96f, 0.96f, 0.98f);
        glRectf(-2.7f, currentHeadY + 3.0f * studentScaleDepth, 2.7f, localSeatY);

        // Collar & Tie detail
        glColor3f(0.12f, 0.22f, 0.50f); // Navy Collar / Tie Accent
        glBegin(GL_TRIANGLES);
        glVertex2f( 0.0f, currentHeadY + 5.4f * studentScaleDepth);
        glVertex2f(-1.2f, currentHeadY + 3.0f * studentScaleDepth);
        glVertex2f( 1.2f, currentHeadY + 3.0f * studentScaleDepth);
        glEnd();

        // 3. Arms holding chain
        glColor3f(0.96f, 0.96f, 0.98f); // Sleeves
        glRectf(-3.9f, currentHeadY + 3.3f * studentScaleDepth, -2.7f, currentHeadY + 5.4f * studentScaleDepth);
        glRectf( 2.7f, currentHeadY + 3.3f * studentScaleDepth,  3.9f, currentHeadY + 5.4f * studentScaleDepth);

        glColor3f(0.92f, 0.74f, 0.60f); // Forearms reaching to chain
        glLineWidth(1.5f);
        glBegin(GL_LINES);
        glVertex2f(-3.3f, currentHeadY + 4.8f * studentScaleDepth);
        glVertex2f(-seatWidth / 2.0f, currentHeadY + 1.2f * studentScaleDepth);
        glVertex2f( 3.3f, currentHeadY + 4.8f * studentScaleDepth);
        glVertex2f( seatWidth / 2.0f, currentHeadY + 1.2f * studentScaleDepth);
        glEnd();

        // 4. Head & Face (Scale and position changes)
        glColor3f(0.92f, 0.74f, 0.60f); // Skin tone
        glBegin(GL_POLYGON);
        float faceRadiusY = 2.4f * studentScaleDepth;
        float faceRadiusX = 2.28f * (1.0f + 0.05f * sinFactor); // Slight squash/stretch horizontally
        for (int i = 0; i < 16; i++)
        {
            float angle = i * 2.0f * 3.14159f / 16.0f;
            glVertex2f(cosf(angle) * faceRadiusX, currentHeadY + sinf(angle) * faceRadiusY);
        }
        glEnd();

        // 5. Hair & Accessories (Updates with head)
        glColor3f(0.12f, 0.08f, 0.05f); // Dark Hair
        if (s == 1)   // Girl's Long Hair with Red Ribbons
        {
            glBegin(GL_POLYGON); // Hair top
            float hairRadiusX = 2.52f * (1.0f + 0.05f * sinFactor);
            float hairRadiusY = 2.4f * studentScaleDepth;
            for (int i = 0; i < 10; i++)
            {
                float angle = 3.14159f + i * 3.14159f / 10.0f;
                glVertex2f(cosf(angle) * hairRadiusX, currentHeadY - 0.3f * studentScaleDepth + sinf(angle) * hairRadiusY);
            }
            glEnd();
            // Side Ponytails
            glRectf(-3.6f, currentHeadY - 0.6f * studentScaleDepth, -faceRadiusX, currentHeadY + 3.6f * studentScaleDepth);
            glRectf( faceRadiusX, currentHeadY - 0.6f * studentScaleDepth,  3.6f, currentHeadY + 3.6f * studentScaleDepth);

            // Red Ribbons
            glColor3f(0.85f, 0.15f, 0.15f);
            glRectf(-3.72f, currentHeadY - 0.9f * studentScaleDepth, -2.16f, currentHeadY);
            glRectf( 2.16f, currentHeadY - 0.9f * studentScaleDepth,  3.72f, currentHeadY);
        }
        else   // Boys' Neat Hair
        {
            glBegin(GL_POLYGON);
            float hairRadiusX = 2.46f * (1.0f + 0.05f * sinFactor);
            float hairRadiusY = 2.28f * studentScaleDepth;
            for (int i = 0; i < 10; i++)
            {
                float angle = 3.14159f + i * 3.14159f / 10.0f;
                glVertex2f(cosf(angle) * hairRadiusX, currentHeadY + sinf(angle) * hairRadiusY);
            }
            glEnd();
        }

        glPopMatrix(); // End depth oscillation transformation
    }

    // Force frame redraw for smooth continuous animation
    glutPostRedisplay();
}


































// ----------------------------------------------------------------------------
// HIGHLY DETAILED 3D-REALISTIC PLAYGROUND SLIDE WITH ANIMATED STUDENT
// Position: X = 345.0f, Y = 495.0f
// Note: Extra artifacts removed, sliding orientation corrected, speed halved.
// ----------------------------------------------------------------------------

void drawSlide()
{
    // Position Parameters
    float centerX = 345.0f;
    float groundY = 495.0f;

    // Slide Structural Dimensions
    float slideHeight = 45.0f;
    float topY = groundY - slideHeight;

    // Key Anchor Coordinates
    float ladderX = centerX + 22.0f;
    float topPlatformX = centerX + 18.0f;
    float slideEndX = centerX - 33.0f;

    // ------------------------------------------------------------------------
    // 1. BASE ANCHORS
    // ------------------------------------------------------------------------

    // Metallic Base Plates / Concrete Footings
    glColor3f(0.35f, 0.35f, 0.38f);
    glRectf(ladderX - 4.0f, groundY - 1.0f, ladderX + 10.0f, groundY + 2.0f);
    glRectf(slideEndX - 6.0f, groundY - 1.0f, slideEndX + 4.0f, groundY + 2.0f);

    // ------------------------------------------------------------------------
    // 2. REAR CLIMBING LADDER (3D Metallic Pipes & Bolts)
    // ------------------------------------------------------------------------

    // Back Ladder Legs
    glColor3f(0.52f, 0.54f, 0.58f);
    glLineWidth(3.5f);
    glBegin(GL_LINES);
    glVertex2f(ladderX - 4.0f, groundY);
    glVertex2f(topPlatformX - 2.0f, topY);
    glVertex2f(ladderX + 6.0f, groundY);
    glVertex2f(topPlatformX + 4.0f, topY);
    glEnd();

    // Front Ladder Legs (Bright Metallic Silver Pipe)
    glColor3f(0.75f, 0.78f, 0.82f);
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glVertex2f(ladderX - 2.0f, groundY);
    glVertex2f(topPlatformX, topY);
    glVertex2f(ladderX + 8.0f, groundY);
    glVertex2f(topPlatformX + 6.0f, topY);
    glEnd();

    // Detailed Ladder Rungs & Steel Fasteners
    for (int i = 1; i <= 6; i++)
    {
        float t = i / 7.0f;
        float rx1 = (ladderX - 2.0f) * (1.0f - t) + topPlatformX * t;
        float ry1 = groundY * (1.0f - t) + topY * t;
        float rx2 = (ladderX + 8.0f) * (1.0f - t) + (topPlatformX + 6.0f) * t;
        float ry2 = groundY * (1.0f - t) + topY * t;

        // Rung Bar
        glColor3f(0.85f, 0.88f, 0.92f);
        glLineWidth(2.5f);
        glBegin(GL_LINES);
        glVertex2f(rx1, ry1);
        glVertex2f(rx2, ry2);
        glEnd();

        // Joint Bolt Caps
        glColor3f(0.20f, 0.20f, 0.22f);
        glPointSize(3.0f);
        glBegin(GL_POINTS);
        glVertex2f(rx1, ry1);
        glVertex2f(rx2, ry2);
        glEnd();
    }

    // Curved Safety Handrails (Red Metallic Powder-Coated Finish)
    glColor3f(0.85f, 0.15f, 0.15f);
    glLineWidth(3.5f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(topPlatformX - 5.0f, topY + 2.0f);
    glVertex2f(topPlatformX - 5.0f, topY - 7.0f);
    glVertex2f(topPlatformX + 7.0f, topY - 7.0f);
    glVertex2f(topPlatformX + 7.0f, topY + 2.0f);
    glEnd();

    // Inner Railing Bar Support
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(topPlatformX + 1.0f, topY);
    glVertex2f(topPlatformX + 1.0f, topY - 7.0f);
    glEnd();

    // ------------------------------------------------------------------------
    // 3. SLIDE CHUTE & SIDE GUARDS
    // ------------------------------------------------------------------------

    // Underneath Structural Frame
    glColor3f(0.55f, 0.15f, 0.15f);
    glBegin(GL_POLYGON);
    glVertex2f(topPlatformX + 1.0f, topY - 1.0f);
    glVertex2f(slideEndX - 2.0f, groundY - 2.0f);
    glVertex2f(slideEndX - 2.0f, groundY - 4.0f);
    glVertex2f(topPlatformX + 1.0f, topY + 2.0f);
    glEnd();

    // Inner Metallic Chute Surface (Stainless Steel)
    glColor3f(0.82f, 0.85f, 0.88f);
    glBegin(GL_POLYGON);
    glVertex2f(topPlatformX, topY + 2.0f);
    glVertex2f(topPlatformX - 6.0f, topY + 2.0f);
    glVertex2f(slideEndX, groundY - 2.0f);
    glVertex2f(slideEndX + 6.0f, groundY - 2.0f);
    glEnd();

    // Metallic Reflection Highlights along Chute
    glColor3f(0.96f, 0.98f, 1.00f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(topPlatformX - 2.0f, topY + 2.0f);
    glVertex2f(slideEndX + 4.0f, groundY - 2.0f);
    glEnd();

    // Bright Red Curved Side Guard Rails
    glColor3f(0.88f, 0.18f, 0.18f);
    glLineWidth(5.5f);
    glBegin(GL_LINES);
    // Outer Top Guard Rail
    glVertex2f(topPlatformX + 1.0f, topY - 1.0f);
    glVertex2f(slideEndX - 2.0f, groundY - 4.0f);

    // Exit Flare Curved Lip
    glVertex2f(slideEndX - 2.0f, groundY - 4.0f);
    glVertex2f(slideEndX - 8.0f, groundY);

    // Inner Guard Rail
    glVertex2f(topPlatformX - 5.0f, topY + 4.0f);
    glVertex2f(slideEndX + 4.0f, groundY + 1.0f);
    glEnd();

    // Guard Rail Top Edge Bright Specular Highlight
    glColor3f(0.98f, 0.45f, 0.45f);
    glLineWidth(1.8f);
    glBegin(GL_LINES);
    glVertex2f(topPlatformX + 1.0f, topY - 2.2f);
    glVertex2f(slideEndX - 2.0f, groundY - 5.2f);
    glEnd();

    // ------------------------------------------------------------------------
    // 4. ANIMATED STUDENT (SPEED HALVED)
    // ------------------------------------------------------------------------

    // Speed halved: Divided by 2000.0f instead of 1000.0f
    float animTime = glutGet(GLUT_ELAPSED_TIME) / 2000.0f;
    animTime = fmod(animTime, 3.0f);
    if (animTime > 3.0f) animTime = 0.0f;

    float px = 0.0f, py = 0.0f;
    bool isSliding = false;

    // Phase 1: Climbing Ladder (0.0s to 1.0s in animation time)
    if (animTime <= 1.0f)
    {
        float t = animTime / 1.0f;
        px = (ladderX + 3.0f) * (1.0f - t) + (topPlatformX + 3.0f) * t;
        py = groundY * (1.0f - t) + topY * t;
    }
    // Phase 2: Sliding Down (1.0s to 2.0s in animation time)
    else if (animTime <= 2.0f)
    {
        float t = (animTime - 1.0f) / 1.0f;
        px = topPlatformX * (1.0f - t) + slideEndX * t;
        py = (topY + 1.0f) * (1.0f - t) + (groundY - 3.0f) * t;
        isSliding = true;
    }
    // Phase 3: Walking back to Ladder (2.0s to 3.0s in animation time)
    else
    {
        float t = (animTime - 2.0f) / 1.0f;
        px = slideEndX * (1.0f - t) + (ladderX + 3.0f) * t;
        py = groundY;
    }

    // --- DRAWING THE STUDENT ---
    glPushMatrix();
    glTranslatef(px, py, 0.0f);

    if (isSliding)
    {
        // Seated Sliding Motion State (Facing Left)

        // Extended Seated Legs Pointing Left
        glColor3f(0.92f, 0.74f, 0.60f);
        glRectf(-5.0f, -1.0f, 1.0f, 2.0f);

        // Socks
        glColor3f(0.95f, 0.95f, 0.95f);
        glRectf(-5.0f, -1.0f, -3.5f, 2.0f);

        // Shoes Pointing Left
        glColor3f(0.10f, 0.10f, 0.10f);
        glRectf(-7.5f, -1.5f, -5.0f, 2.0f);

        // Navy Uniform Shorts
        glColor3f(0.12f, 0.22f, 0.50f);
        glRectf(-1.0f, -3.0f, 4.0f, 3.0f);

        // White Shirt (Torso)
        glColor3f(0.96f, 0.96f, 0.98f);
        glRectf(-1.5f, -11.0f, 3.5f, -3.0f);

        // Red Tie Detail on Chest
        glColor3f(0.85f, 0.15f, 0.15f);
        glRectf(-1.2f, -10.0f, -0.2f, -5.5f);

        // Forearm holding side safety rail
        glColor3f(0.92f, 0.74f, 0.60f);
        glLineWidth(2.2f);
        glBegin(GL_LINES);
        glVertex2f(1.0f, -8.0f);
        glVertex2f(-4.0f, -5.0f);
        glEnd();

        // Detailed Head Structure
        float headY = -13.5f;
        glColor3f(0.92f, 0.74f, 0.60f);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 16; i++)
        {
            float rad = i * 2.0f * 3.14159f / 16.0f;
            glVertex2f(cosf(rad) * 2.5f, headY + sinf(rad) * 2.5f);
        }
        glEnd();

        // Facial Eye Dot (Facing Left)
        glColor3f(0.12f, 0.10f, 0.10f);
        glPointSize(2.2f);
        glBegin(GL_POINTS);
        glVertex2f(-1.5f, headY - 0.2f);
        glEnd();

        // Dark Hair Styling
        glColor3f(0.15f, 0.09f, 0.05f);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 10; i++)
        {
            float rad = 3.14159f + i * 3.14159f / 10.0f;
            glVertex2f(cosf(rad) * 2.6f, headY + sinf(rad) * 2.4f);
        }
        glEnd();
    }
    else
    {
        // Standing / Climbing Motion State

        // Adjusted leg walking animation frequency to match halved speed
        float legOffset = sinf(animTime * 12.5f) * 1.5f;

        // Navy Uniform Shorts
        glColor3f(0.12f, 0.22f, 0.50f);
        glRectf(-2.0f, -5.0f, 2.0f, 0.0f);

        // Skin Legs
        glColor3f(0.92f, 0.74f, 0.60f);
        glRectf(-1.8f + legOffset, -2.0f, -0.2f + legOffset, 3.0f);
        glRectf(0.2f - legOffset, -2.0f, 1.8f - legOffset, 3.0f);

        // Shoes
        glColor3f(0.10f, 0.10f, 0.10f);
        glRectf(-2.2f + legOffset, 3.0f, -0.1f + legOffset, 4.5f);
        glRectf(0.1f - legOffset, 3.0f, 2.2f - legOffset, 4.5f);

        // White Shirt Torso
        glColor3f(0.96f, 0.96f, 0.98f);
        glRectf(-2.5f, -12.0f, 2.5f, -5.0f);

        // Uniform Tie
        glColor3f(0.85f, 0.15f, 0.15f);
        glRectf(-0.5f, -11.0f, 0.5f, -7.0f);

        // Posed Arms
        glColor3f(0.92f, 0.74f, 0.60f);
        glLineWidth(2.2f);
        glBegin(GL_LINES);
        glVertex2f(-2.5f, -10.0f);
        glVertex2f(-4.5f - legOffset, -5.0f);
        glVertex2f(2.5f, -10.0f);
        glVertex2f(4.5f + legOffset, -5.0f);
        glEnd();

        // Head Structure
        float headY = -14.5f;
        glColor3f(0.92f, 0.74f, 0.60f);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 16; i++)
        {
            float rad = i * 2.0f * 3.14159f / 16.0f;
            glVertex2f(cosf(rad) * 2.5f, headY + sinf(rad) * 2.5f);
        }
        glEnd();

        // Dark Hair Top
        glColor3f(0.15f, 0.09f, 0.05f);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 10; i++)
        {
            float rad = 3.14159f + i * 3.14159f / 10.0f;
            glVertex2f(cosf(rad) * 2.6f, headY + sinf(rad) * 2.5f);
        }
        glEnd();
    }

    glPopMatrix();

    // Continuous frame update
    glutPostRedisplay();
}















// ----------------------------------------------------------------------------
// HIGHLY DETAILED 3D-REALISTIC SEESAW WITH TWO ANIMATED KIDS
// Positioned at X = 245.0f (Swing 145.0f + 100.0f) and Y = 505.0f (495.0f + 10.0f)
// Smooth see-saw rotation with detailed layered 3D depth and seated students.
// ----------------------------------------------------------------------------

void drawSeesaw()
{
    // Frame Timing & Animation Logic
    static float seeSawAngle = 0.0f;
    seeSawAngle += 0.012f; // Speed barano hoyeche (0.005f -> 0.012f)

    // Smooth rotation angle for see-saw plank (-12 to +12 degrees)
    float currentAngle = sinf(seeSawAngle) * 12.0f;

    // Shifted Positioning Parameters
    float centerX = 245.0f; // Shifted further along X
    float groundY = 505.0f; // Shifted down along Y

    // Base dimensions matching scale
    float baseHeight = 18.0f;
    float baseWidth = 14.0f;
    float pivotY = groundY - baseHeight;
    float plankLength = 65.0f;
    float plankThickness = 3.5f;

    // ------------------------------------------------------------------------
    // 1. 3D FULCRUM STAND (Ground Shadow Removed)
    // ------------------------------------------------------------------------

    // Concrete Footing Base Pad
    glColor3f(0.48f, 0.48f, 0.52f);
    glRectf(centerX - 11.0f, groundY - 1.5f, centerX + 11.0f, groundY + 1.5f);
    glColor3f(0.60f, 0.60f, 0.65f); // Top Highlight Edge
    glRectf(centerX - 11.0f, groundY - 1.5f, centerX + 11.0f, groundY - 0.5f);

    // Back Support Leg (3D Depth Shadow Layer)
    glColor3f(0.55f, 0.28f, 0.10f);
    glBegin(GL_POLYGON);
    glVertex2f(centerX - baseWidth / 2.0f + 2.5f, groundY - 1.5f);
    glVertex2f(centerX + baseWidth / 2.0f + 2.5f, groundY - 1.5f);
    glVertex2f(centerX + 3.5f, pivotY);
    glVertex2f(centerX - 2.5f, pivotY);
    glEnd();

    // Front Main Triangular Support Stand
    glColor3f(0.85f, 0.45f, 0.18f); // Metallic Orange/Wood Tone
    glBegin(GL_TRIANGLES);
    glVertex2f(centerX - baseWidth / 2.0f, groundY - 1.5f);
    glVertex2f(centerX + baseWidth / 2.0f, groundY - 1.5f);
    glVertex2f(centerX, pivotY);
    glEnd();

    // Stand Left Bright Edge Highlight
    glColor3f(0.96f, 0.58f, 0.25f);
    glLineWidth(2.2f);
    glBegin(GL_LINES);
    glVertex2f(centerX - baseWidth / 2.0f, groundY - 1.5f);
    glVertex2f(centerX, pivotY);
    glEnd();

    // Central Axis Pivot Bearing Assembly
    glColor3f(0.20f, 0.20f, 0.22f); // Outer Housing Ring
    glBegin(GL_POLYGON);
    for (int i = 0; i < 16; i++)
    {
        float rad = i * 2.0f * 3.14159f / 16.0f;
        glVertex2f(centerX + cosf(rad) * 3.2f, pivotY + sinf(rad) * 3.2f);
    }
    glEnd();

    glColor3f(0.75f, 0.75f, 0.80f); // Inner Metal Bolt Cap
    glBegin(GL_POLYGON);
    for (int i = 0; i < 16; i++)
    {
        float rad = i * 2.0f * 3.14159f / 16.0f;
        glVertex2f(centerX + cosf(rad) * 1.6f, pivotY + sinf(rad) * 1.6f);
    }
    glEnd();

    // ------------------------------------------------------------------------
    // 2. DYNAMIC ROTATING PLANK, HANDLES & SEATS
    // ------------------------------------------------------------------------

    glPushMatrix();
    glTranslatef(centerX, pivotY, 0.0f);
    glRotatef(currentAngle, 0.0f, 0.0f, 1.0f); // Rotate around pivot point

    // Plank 3D Bottom/Side Shadow Edge
    glColor3f(0.55f, 0.28f, 0.10f);
    glRectf(-plankLength / 2.0f, 0.0f, plankLength / 2.0f, plankThickness + 1.5f);

    // Main Upper Wooden Plank
    glColor3f(0.82f, 0.48f, 0.18f);
    glRectf(-plankLength / 2.0f, -plankThickness, plankLength / 2.0f, 0.0f);

    // Plank Top Bright Highlight Strip
    glColor3f(0.92f, 0.58f, 0.28f);
    glRectf(-plankLength / 2.0f, -plankThickness, plankLength / 2.0f, -plankThickness + 0.6f);

    // Underneath Rubber Safety Bumpers
    glColor3f(0.12f, 0.12f, 0.12f);
    glRectf(-plankLength / 2.0f + 1.0f, plankThickness + 0.5f, -plankLength / 2.0f + 5.0f, plankThickness + 2.5f);
    glRectf( plankLength / 2.0f - 5.0f, plankThickness + 0.5f,  plankLength / 2.0f - 1.0f, plankThickness + 2.5f);

    // Handle Bars (T-Shaped Metal Tubes for both ends)
    for (int side = -1; side <= 1; side += 2)
    {
        float hx = side * (plankLength / 2.0f - 8.0f);

        // Mounting Plate on Plank
        glColor3f(0.30f, 0.30f, 0.32f);
        glRectf(hx - 1.8f, -plankThickness - 0.6f, hx + 1.8f, -plankThickness);

        // Vertical Bar Pipe
        glColor3f(0.78f, 0.15f, 0.15f); // Crimson Metallic Red
        glLineWidth(2.5f);
        glBegin(GL_LINES);
        glVertex2f(hx, -plankThickness);
        glVertex2f(hx, -plankThickness - 7.5f);
        glEnd();

        // Horizontal Grip Bar
        glLineWidth(3.2f);
        glBegin(GL_LINES);
        glVertex2f(hx - 2.8f, -plankThickness - 7.5f);
        glVertex2f(hx + 2.8f, -plankThickness - 7.5f);
        glEnd();

        // Rubber End Grips
        glColor3f(0.15f, 0.15f, 0.15f);
        glPointSize(3.5f);
        glBegin(GL_POINTS);
        glVertex2f(hx - 2.8f, -plankThickness - 7.5f);
        glVertex2f(hx + 2.8f, -plankThickness - 7.5f);
        glEnd();
    }

    // ------------------------------------------------------------------------
    // 3. TWO DETAILED SEATED KIDS (LEFT & RIGHT)
    // ------------------------------------------------------------------------

    float seatX[2] = { -plankLength / 2.0f + 4.0f, plankLength / 2.0f - 4.0f };

    for (int k = 0; k < 2; k++)
    {
        float kx = seatX[k];
        float direction = (k == 0) ? 1.0f : -1.0f; // Facing inner center

        // 1. Thighs & Seated Lower Body
        glColor3f(0.12f, 0.22f, 0.50f); // Navy Blue Uniform Pants/Skirt
        glRectf(kx - 2.2f, -plankThickness - 2.2f, kx + 2.2f, -plankThickness);
        glRectf(kx + (direction * 0.8f), -plankThickness, kx + (direction * 5.2f), -plankThickness + 3.8f);

        // Skin Lower Leg (Hanging down)
        glColor3f(0.92f, 0.74f, 0.60f);
        glRectf(kx + (direction * 3.6f), -plankThickness + 3.8f, kx + (direction * 5.6f), -plankThickness + 7.8f);

        // Socks (White for both kids)
        glColor3f(0.95f, 0.95f, 0.95f);
        glRectf(kx + (direction * 3.6f), -plankThickness + 6.2f, kx + (direction * 5.6f), -plankThickness + 7.8f);

        // Black Shoes
        glColor3f(0.10f, 0.10f, 0.10f);
        glRectf(kx + (direction * 3.0f), -plankThickness + 7.8f, kx + (direction * 6.6f), -plankThickness + 9.3f);

        // 2. Torso Shirt
        if (k == 0) glColor3f(0.95f, 0.35f, 0.35f); // Red/Pink Casual Top (Girl)
        else        glColor3f(0.96f, 0.96f, 0.98f); // White School Shirt (Boy)

        glRectf(kx - 2.6f, -plankThickness - 9.8f, kx + 2.6f, -plankThickness - 2.0f);

        // Uniform Tie Detail for Boy
        if (k == 1)
        {
            glColor3f(0.12f, 0.22f, 0.50f);
            glBegin(GL_TRIANGLES);
            glVertex2f(kx, -plankThickness - 7.8f);
            glVertex2f(kx - 1.1f, -plankThickness - 9.8f);
            glVertex2f(kx + 1.1f, -plankThickness - 9.8f);
            glEnd();
        }

        // 3. Sleeves & Arms Reaching to Handle
        if (k == 0) glColor3f(0.95f, 0.35f, 0.35f);
        else        glColor3f(0.96f, 0.96f, 0.98f);
        glRectf(kx - 1.0f, -plankThickness - 8.8f, kx + 1.8f, -plankThickness - 6.6f);

        // Forearm Skin
        glColor3f(0.92f, 0.74f, 0.60f);
        glLineWidth(2.2f);
        glBegin(GL_LINES);
        glVertex2f(kx + direction * 0.5f, -plankThickness - 7.5f);
        glVertex2f(kx + direction * 4.2f, -plankThickness - 7.5f);
        glEnd();

        // 4. Head & Facial Features Structure
        float headY = -plankThickness - 12.2f;
        glColor3f(0.92f, 0.74f, 0.60f); // Skin Tone Face Polygon
        glBegin(GL_POLYGON);
        for (int i = 0; i < 16; i++)
        {
            float rad = i * 2.0f * 3.14159f / 16.0f;
            glVertex2f(kx + cosf(rad) * 2.5f, headY + sinf(rad) * 2.5f);
        }
        glEnd();

        // Eye Dots Facing Direction
        glColor3f(0.15f, 0.10f, 0.10f);
        glPointSize(2.0f);
        glBegin(GL_POINTS);
        glVertex2f(kx + direction * 1.2f, headY - 0.2f);
        glEnd();

        // 5. Hair & Accessories
        glColor3f(0.15f, 0.09f, 0.05f); // Dark Brown Hair Tone
        if (k == 0)   // Left Girl Hair Styling
        {
            glBegin(GL_POLYGON);
            for (int i = 0; i < 10; i++)
            {
                float rad = 3.14159f + i * 3.14159f / 10.0f;
                glVertex2f(kx + cosf(rad) * 2.7f, headY + sinf(rad) * 2.7f);
            }
            glEnd();
            // Side Hair Lock
            glRectf(kx - 2.9f, headY - 1.0f, kx - 1.6f, headY + 3.2f);

            // Pink Bow Clip
            glColor3f(0.95f, 0.40f, 0.65f);
            glRectf(kx - 3.0f, headY - 1.2f, kx - 1.8f, headY - 0.2f);
        }
        else   // Right Boy Neat Crop Hair
        {
            glBegin(GL_POLYGON);
            for (int i = 0; i < 10; i++)
            {
                float rad = 3.14159f + i * 3.14159f / 10.0f;
                glVertex2f(kx + cosf(rad) * 2.6f, headY + sinf(rad) * 2.5f);
            }
            glEnd();
        }
    }

    glPopMatrix(); // End plank rotation matrix

    // Force frame redraw for continuous smooth animation
    glutPostRedisplay();
}




















// ----------------------------------------------------------------------------
// 3D REALISTIC MONKEY BARS WITH STUDENTS (Shifted X +30, Y +30)
// Base Ground Level: Y = 620. Top Beam Level: Y = 538.
// Features attached ground shadows, metallic joints, and 3D depth details.
// ----------------------------------------------------------------------------

void drawStudentBodyDetailed(float x, float y, float scale, bool isSitting, bool armsUp)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // 1. Shoes with Soles
    glColor3f(0.12f, 0.12f, 0.12f);
    if (isSitting)
    {
        glRectf(-2.5f, 18.0f, -0.5f, 20.0f);
        glRectf(0.5f, 18.0f, 2.5f, 20.0f);
        glColor3f(0.85f, 0.85f, 0.85f); // Sole
        glRectf(-2.5f, 19.5f, -0.5f, 20.2f);
        glRectf(0.5f, 19.5f, 2.5f, 20.2f);

        // Socks
        glColor3f(0.92f, 0.92f, 0.92f);
        glRectf(-2.0f, 14.0f, -1.0f, 18.0f);
        glRectf(1.0f, 14.0f, 2.0f, 18.0f);
    }
    else
    {
        glRectf(-2.2f, 22.0f, -0.5f, 24.0f);
        glRectf(0.5f, 22.0f, 2.2f, 24.0f);
        glColor3f(0.85f, 0.85f, 0.85f); // Sole
        glRectf(-2.2f, 23.5f, -0.5f, 24.2f);
        glRectf(0.5f, 23.5f, 2.2f, 24.2f);

        // Socks
        glColor3f(0.92f, 0.92f, 0.92f);
        glRectf(-1.8f, 18.0f, -0.9f, 22.0f);
        glRectf(0.9f, 18.0f, 1.8f, 22.0f);
    }

    // 2. Legs (Skin Tone)
    glColor3f(0.92f, 0.75f, 0.62f);
    if (isSitting)
    {
        glRectf(-1.8f, 10.0f, -1.0f, 14.0f);
        glRectf(1.0f, 10.0f, 1.8f, 14.0f);
    }
    else
    {
        glRectf(-1.6f, 13.0f, -0.8f, 18.0f);
        glRectf(0.8f, 13.0f, 1.6f, 18.0f);
    }

    // 3. Blue Uniform Shorts
    glColor3f(0.15f, 0.35f, 0.75f);
    glRectf(-2.2f, 8.0f, 2.2f, 13.0f);
    glColor3f(0.95f, 0.95f, 0.95f); // Side Stripe Detail
    glRectf(-2.2f, 8.0f, -1.9f, 13.0f);

    // 4. White Uniform Shirt & Collar Detail
    glColor3f(0.95f, 0.95f, 0.95f);
    glRectf(-2.5f, -2.0f, 2.5f, 8.0f);

    glColor3f(0.15f, 0.35f, 0.75f); // V-Collar
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(0.0f, 3.5f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();

    // 5. Head, Hair & Face Details
    glColor3f(0.92f, 0.75f, 0.62f);
    glBegin(GL_TRIANGLE_FAN);
    for(int i = 0; i < 15; i++)
    {
        float a = i * 2.0f * M_PI / 15.0f;
        glVertex2f(cosf(a) * 2.2f, -5.0f + sinf(a) * 2.2f);
    }
    glEnd();

    // Dark Hair Layer
    glColor3f(0.12f, 0.12f, 0.12f);
    glBegin(GL_TRIANGLE_FAN);
    for(int i = 0; i < 12; i++)
    {
        float a = i * M_PI / 12.0f;
        glVertex2f(cosf(a) * 2.4f, -5.2f - sinf(a) * 2.0f);
    }
    glEnd();

    // Eye Detail
    glColor3f(0.10f, 0.10f, 0.10f);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glVertex2f(-0.8f, -5.0f);
    glVertex2f(0.8f, -5.0f);
    glEnd();

    // 6. Arms & Hands
    glColor3f(0.92f, 0.75f, 0.62f);
    if (armsUp)
    {
        glRectf(-3.5f, -8.0f, -2.2f, 0.0f);
        glRectf(2.2f, -8.0f, 3.5f, 0.0f);
    }
    else
    {
        glRectf(-3.6f, -1.0f, -2.3f, 5.0f);
        glRectf(2.3f, -1.0f, 3.6f, 5.0f);
    }

    glPopMatrix();
}

void drawMonkeyBars()
{
    // Ground Y level: 620, Base X positions shifted by +30
    float fLeftX1 = 1332.0f, fLeftX2 = 1348.0f;
    float fRightX1 = 1402.0f, fRightX2 = 1418.0f;
    float bLeftX = 1342.0f, bRightX = 1412.0f;
    float groundY = 620.0f;

    // ------------------------------------------------------------------------
    // 1. ATTACHED GROUND CAST SHADOWS (Connected directly to post bases)
    // ------------------------------------------------------------------------
    glColor4f(0.08f, 0.10f, 0.08f, 0.40f);

    // Main Wooden Frame Base Projection Shadow
    glBegin(GL_POLYGON);
    glVertex2f(fLeftX1, groundY);
    glVertex2f(fRightX2, groundY);
    glVertex2f(fRightX2 + 25.0f, groundY + 12.0f);
    glVertex2f(fLeftX1 + 25.0f, groundY + 12.0f);
    glEnd();

    // Ground Center Jumping Student Shadow
    glBegin(GL_TRIANGLE_FAN);
    for(int i = 0; i < 12; i++)
    {
        float a = i * 2.0f * M_PI / 12.0f;
        glVertex2f(1380.0f + cosf(a) * 7.0f, groundY - 2.0f + sinf(a) * 2.2f);
    }
    glEnd();

    // Concrete Footing Pads at Base of Posts
    glColor3f(0.50f, 0.52f, 0.55f);
    glRectf(fLeftX1 - 2.0f, groundY - 2.0f, fLeftX1 + 7.0f, groundY + 2.0f);
    glRectf(fLeftX2 - 2.0f, groundY - 2.0f, fLeftX2 + 7.0f, groundY + 2.0f);
    glRectf(fRightX1 - 2.0f, groundY - 2.0f, fRightX1 + 7.0f, groundY + 2.0f);
    glRectf(fRightX2 - 2.0f, groundY - 2.0f, fRightX2 + 7.0f, groundY + 2.0f);

    // ------------------------------------------------------------------------
    // 2. BACK VERTICAL FRAME (3D Depth)
    // ------------------------------------------------------------------------
    glColor3f(0.38f, 0.22f, 0.10f); // Darker Wood for Back Posts
    glRectf(bLeftX, 535.0f, bLeftX + 5.0f, groundY - 2.0f);
    glRectf(bRightX, 535.0f, bRightX + 5.0f, groundY - 2.0f);

    // Back Horizontal Bars
    for(int i = 0; i < 5; i++)
    {
        float yStep = 548.0f + (i * 13.0f);
        glRectf(bLeftX, yStep, bRightX + 5.0f, yStep + 2.5f);
    }

    // ------------------------------------------------------------------------
    // 3. FRONT MAIN WOODEN FRAME & HIGHLIGHTS
    // ------------------------------------------------------------------------
    // Front Posts
    glColor3f(0.55f, 0.35f, 0.18f); // Base Wood Tone
    glRectf(fLeftX1, 540.0f, fLeftX1 + 5.0f, groundY);
    glRectf(fLeftX2, 540.0f, fLeftX2 + 5.0f, groundY);
    glRectf(fRightX1, 540.0f, fRightX1 + 5.0f, groundY);
    glRectf(fRightX2, 540.0f, fRightX2 + 5.0f, groundY);

    // 3D Bevel Highlights
    glColor3f(0.72f, 0.48f, 0.25f);
    glRectf(fLeftX1, 540.0f, fLeftX1 + 1.5f, groundY);
    glRectf(fLeftX2, 540.0f, fLeftX2 + 1.5f, groundY);
    glRectf(fRightX1, 540.0f, fRightX1 + 1.5f, groundY);
    glRectf(fRightX2, 540.0f, fRightX2 + 1.5f, groundY);

    // Left & Right Ladder Rungs
    glColor3f(0.46f, 0.28f, 0.13f);
    for(int i = 0; i < 5; i++)
    {
        float yStep = 552.0f + (i * 13.0f);
        glRectf(fLeftX1 + 5.0f, yStep, fLeftX2, yStep + 3.0f);
        glRectf(fRightX1 + 5.0f, yStep, fRightX2, yStep + 3.0f);
    }

    // Top Main Beams
    glColor3f(0.58f, 0.38f, 0.20f);
    glRectf(fLeftX1, 538.0f, fRightX2 + 5.0f, 544.0f);
    glRectf(bLeftX, 532.0f, bRightX + 5.0f, 538.0f);

    // Metallic Joint Plates
    glColor3f(0.25f, 0.25f, 0.28f);
    glRectf(fLeftX1 - 1.0f, 537.0f, fLeftX1 + 6.0f, 545.0f);
    glRectf(fRightX2 - 1.0f, 537.0f, fRightX2 + 6.0f, 545.0f);

    // Overhead Crossing Monkey Bars (Perspective Angled)
    glColor3f(0.42f, 0.25f, 0.11f);
    for(int i = 0; i < 9; i++)
    {
        float xStep = 1340.0f + (i * 8.5f);
        glBegin(GL_POLYGON);
        glVertex2f(xStep, 544.0f);
        glVertex2f(xStep + 3.0f, 544.0f);
        glVertex2f(xStep + 8.0f, 534.0f);
        glVertex2f(xStep + 5.0f, 534.0f);
        glEnd();
    }

    // ------------------------------------------------------------------------
    // 4. STUDENTS ENJOYING (Positions shifted X +30, Y +30)
    // ------------------------------------------------------------------------
    // Student 1: Climbing Left Ladder
    drawStudentBodyDetailed(1342.0f, 570.0f, 0.85f, false, true);

    // Student 2: Sitting On Top Overhead Ladder
    drawStudentBodyDetailed(1378.0f, 528.0f, 0.85f, true, false);

    // Student 3: Cheering On Ground (Center)
    drawStudentBodyDetailed(1380.0f, 595.0f, 0.90f, false, true);

    // Student 4: Climbing Right Ladder
    drawStudentBodyDetailed(1412.0f, 575.0f, 0.85f, false, false);
}


















































/* ============================================================================
   FUNCTION: drawBench3D
   Description: Ultra-Realistic 3D Park Bench using pure glVertex3f primitives.
   Features: 3 Metal Legs, 3D Bolts, Foot Pads, Cross-Bracing Bars, 9 Slats.
   Bounding Box: X (10 to 100), Y (500 to 520), Z (0 to 15 depth)
   ============================================================================ */

void drawBench3D()
{
    float xLeft = 13.0f, xRight = 97.0f;
    float ySeatTop = 512.0f, ySeatBottom = 513.2f;

    // ========================================================================
    // 1. SEAT SLATS
    // ========================================================================
    float seatSlatsZ[] = { 1.0f, 3.5f, 6.0f, 8.5f, 11.0f }; // 5 Slats
    float slatDepth = 2.0f;

    for (int i = 0; i < 5; i++)
    {
        float zFront = seatSlatsZ[i];
        float zBack = zFront + slatDepth;

        glBegin(GL_QUADS);
        // Top Face
        glColor3f(0.88f, 0.68f, 0.48f);
        glVertex3f(xLeft,  ySeatTop, zFront);
        glColor3f(0.88f, 0.68f, 0.48f);
        glVertex3f(xRight, ySeatTop, zFront);
        glColor3f(0.78f, 0.58f, 0.38f);
        glVertex3f(xRight, ySeatTop, zBack);
        glColor3f(0.78f, 0.58f, 0.38f);
        glVertex3f(xLeft,  ySeatTop, zBack);

        // Front Face
        glColor3f(0.75f, 0.55f, 0.35f);
        glVertex3f(xLeft,  ySeatTop,    zFront);
        glColor3f(0.75f, 0.55f, 0.35f);
        glVertex3f(xRight, ySeatTop,    zFront);
        glColor3f(0.60f, 0.42f, 0.25f);
        glVertex3f(xRight, ySeatBottom, zFront);
        glColor3f(0.60f, 0.42f, 0.25f);
        glVertex3f(xLeft,  ySeatBottom, zFront);

        // Back Face
        glColor3f(0.50f, 0.35f, 0.20f);
        glVertex3f(xLeft,  ySeatTop,    zBack);
        glColor3f(0.50f, 0.35f, 0.20f);
        glVertex3f(xRight, ySeatTop,    zBack);
        glColor3f(0.40f, 0.28f, 0.15f);
        glVertex3f(xRight, ySeatBottom, zBack);
        glColor3f(0.40f, 0.28f, 0.15f);
        glVertex3f(xLeft,  ySeatBottom, zBack);

        // Bottom Face
        glColor3f(0.38f, 0.25f, 0.12f);
        glVertex3f(xLeft,  ySeatBottom, zFront);
        glVertex3f(xRight, ySeatBottom, zFront);
        glVertex3f(xRight, ySeatBottom, zBack);
        glVertex3f(xLeft,  ySeatBottom, zBack);

        // Side Edges
        glColor3f(0.65f, 0.45f, 0.28f);
        glVertex3f(xLeft, ySeatTop, zFront);
        glVertex3f(xLeft, ySeatTop, zBack);
        glVertex3f(xLeft, ySeatBottom, zBack);
        glVertex3f(xLeft, ySeatBottom, zFront);

        glVertex3f(xRight, ySeatTop, zFront);
        glVertex3f(xRight, ySeatTop, zBack);
        glVertex3f(xRight, ySeatBottom, zBack);
        glVertex3f(xRight, ySeatBottom, zFront);
        glEnd();
    }

    // ========================================================================
    // 2. BACKREST SLATS
    // ========================================================================
    float backSlatsY[] = { 501.0f, 503.8f, 506.6f, 509.4f };
    float zBackStart = 13.5f, zBackEnd = 14.8f;

    for (int i = 0; i < 4; i++)
    {
        float yTop = backSlatsY[i];
        float yBot = yTop + 2.1f;

        glBegin(GL_QUADS);
        // Top Face
        glColor3f(0.85f, 0.65f, 0.45f);
        glVertex3f(xLeft, yTop, zBackStart);
        glVertex3f(xRight, yTop, zBackStart);
        glVertex3f(xRight, yTop, zBackEnd);
        glVertex3f(xLeft, yTop, zBackEnd);

        // Front Face
        glColor3f(0.78f, 0.58f, 0.38f);
        glVertex3f(xLeft, yTop, zBackStart);
        glVertex3f(xRight, yTop, zBackStart);
        glColor3f(0.65f, 0.45f, 0.28f);
        glVertex3f(xRight, yBot, zBackStart);
        glVertex3f(xLeft, yBot, zBackStart);

        // Back Face
        glColor3f(0.48f, 0.32f, 0.18f);
        glVertex3f(xLeft, yTop, zBackEnd);
        glVertex3f(xRight, yTop, zBackEnd);
        glVertex3f(xRight, yBot, zBackEnd);
        glVertex3f(xLeft, yBot, zBackEnd);

        // Bottom Face & Sides
        glColor3f(0.38f, 0.25f, 0.12f);
        glVertex3f(xLeft, yBot, zBackStart);
        glVertex3f(xRight, yBot, zBackStart);
        glVertex3f(xRight, yBot, zBackEnd);
        glVertex3f(xLeft, yBot, zBackEnd);
        glEnd();
    }

    // ========================================================================
    // 3. CAST IRON FRAME
    // ========================================================================
    float legsX[3][2] = { {15.0f, 17.5f}, {53.75f, 56.25f}, {92.5f, 95.0f} };

    for (int k = 0; k < 3; k++)
    {
        float x1 = legsX[k][0];
        float x2 = legsX[k][1];

        // --- Foot Pads
        glBegin(GL_QUADS);
        glColor3f(0.10f, 0.10f, 0.12f);
        // Front Leg Footpad
        glVertex3f(x1 - 1.0f, 519.2f, 0.5f);
        glVertex3f(x2 + 1.0f, 519.2f, 0.5f);
        glVertex3f(x2 + 1.0f, 520.0f, 3.5f);
        glVertex3f(x1 - 1.0f, 520.0f, 3.5f);
        // Back Leg Footpad
        glVertex3f(x1 - 1.0f, 519.2f, 12.5f);
        glVertex3f(x2 + 1.0f, 519.2f, 12.5f);
        glVertex3f(x2 + 1.0f, 520.0f, 15.5f);
        glVertex3f(x1 - 1.0f, 520.0f, 15.5f);
        glEnd();

        // --- Front Leg Post ---
        glBegin(GL_QUADS);
        glColor3f(0.22f, 0.22f, 0.25f); // Front Face
        glVertex3f(x1, 513.2f, 1.0f);
        glVertex3f(x2, 513.2f, 1.0f);
        glVertex3f(x2, 519.5f, 1.0f);
        glVertex3f(x1, 519.5f, 1.0f);

        glColor3f(0.12f, 0.12f, 0.14f); // Sides & Back
        glVertex3f(x1, 513.2f, 3.0f);
        glVertex3f(x2, 513.2f, 3.0f);
        glVertex3f(x2, 519.5f, 3.0f);
        glVertex3f(x1, 519.5f, 3.0f);

        glVertex3f(x1, 513.2f, 1.0f);
        glVertex3f(x1, 513.2f, 3.0f);
        glVertex3f(x1, 519.5f, 3.0f);
        glVertex3f(x1, 519.5f, 1.0f);

        glVertex3f(x2, 513.2f, 1.0f);
        glVertex3f(x2, 513.2f, 3.0f);
        glVertex3f(x2, 519.5f, 3.0f);
        glVertex3f(x2, 519.5f, 1.0f);
        glEnd();

        // --- Back Leg & Backrest Post ---
        glBegin(GL_QUADS);
        glColor3f(0.25f, 0.25f, 0.28f);
        glVertex3f(x1, 500.0f, 13.0f);
        glVertex3f(x2, 500.0f, 13.0f);
        glVertex3f(x2, 519.5f, 13.0f);
        glVertex3f(x1, 519.5f, 13.0f);

        glColor3f(0.12f, 0.12f, 0.14f);
        glVertex3f(x1, 500.0f, 15.0f);
        glVertex3f(x2, 500.0f, 15.0f);
        glVertex3f(x2, 519.5f, 15.0f);
        glVertex3f(x1, 519.5f, 15.0f);

        glVertex3f(x1, 500.0f, 13.0f);
        glVertex3f(x1, 500.0f, 15.0f);
        glVertex3f(x1, 519.5f, 15.0f);
        glVertex3f(x1, 519.5f, 13.0f);

        glVertex3f(x2, 500.0f, 13.0f);
        glVertex3f(x2, 500.0f, 15.0f);
        glVertex3f(x2, 519.5f, 15.0f);
        glVertex3f(x2, 519.5f, 13.0f);
        glEnd();

        // --- Seat Support Bar
        glBegin(GL_QUADS);
        glColor3f(0.18f, 0.18f, 0.20f);
        glVertex3f(x1, ySeatBottom, 1.0f);
        glVertex3f(x2, ySeatBottom, 1.0f);
        glVertex3f(x2, ySeatBottom, 13.0f);
        glVertex3f(x1, ySeatBottom, 13.0f);
        glEnd();

        // --- Armrest
        if (k != 1)
        {
            glBegin(GL_QUADS);
            glColor3f(0.32f, 0.32f, 0.35f); // Top Highlight
            glVertex3f(x1 - 1.0f, 506.8f, 1.0f);
            glVertex3f(x2 + 1.0f, 506.8f, 1.0f);
            glVertex3f(x2 + 1.0f, 506.8f, 13.0f);
            glVertex3f(x1 - 1.0f, 506.8f, 13.0f);

            glColor3f(0.15f, 0.15f, 0.18f); // Side Body
            glVertex3f(x1 - 1.0f, 506.8f, 1.0f);
            glVertex3f(x2 + 1.0f, 506.8f, 1.0f);
            glVertex3f(x2 + 1.0f, 508.2f, 1.0f);
            glVertex3f(x1 - 1.0f, 508.2f, 1.0f);

            glVertex3f(x1 - 1.0f, 506.8f, 13.0f);
            glVertex3f(x2 + 1.0f, 506.8f, 13.0f);
            glVertex3f(x2 + 1.0f, 508.2f, 13.0f);
            glVertex3f(x1 - 1.0f, 508.2f, 13.0f);
            glEnd();
        }

        // ====================================================================
        // 4. METALLIC BOLTS / SCREWS
        // ====================================================================
        float boltX = (x1 + x2) / 2.0f;
        glColor3f(0.70f, 0.70f, 0.75f); // Bright Metallic Steel Color

        // Seat Bolts
        for (int b = 0; b < 5; b++)
        {
            float boltZ = seatSlatsZ[b] + 1.0f;
            glBegin(GL_QUADS);
            glVertex3f(boltX - 0.4f, ySeatTop - 0.1f, boltZ - 0.4f);
            glVertex3f(boltX + 0.4f, ySeatTop - 0.1f, boltZ - 0.4f);
            glVertex3f(boltX + 0.4f, ySeatTop - 0.1f, boltZ + 0.4f);
            glVertex3f(boltX - 0.4f, ySeatTop - 0.1f, boltZ + 0.4f);
            glEnd();
        }

        // Backrest Bolts
        for (int b = 0; b < 4; b++)
        {
            float boltY = backSlatsY[b] + 1.0f;
            glBegin(GL_QUADS);
            glVertex3f(boltX - 0.4f, boltY - 0.4f, zBackStart - 0.1f);
            glVertex3f(boltX + 0.4f, boltY - 0.4f, zBackStart - 0.1f);
            glVertex3f(boltX + 0.4f, boltY + 0.4f, zBackStart - 0.1f);
            glVertex3f(boltX - 0.4f, boltY + 0.4f, zBackStart - 0.1f);
            glEnd();
        }
    }

    // ========================================================================
    // 5. CROSS-CONNECTING BARS
    // ========================================================================
    glColor3f(0.15f, 0.15f, 0.18f);
    glBegin(GL_QUADS);
    // Long Rod under Front Legs
    glVertex3f(legsX[0][0], 517.0f, 2.0f);
    glVertex3f(legsX[2][1], 517.0f, 2.0f);
    glVertex3f(legsX[2][1], 518.0f, 2.0f);
    glVertex3f(legsX[0][0], 518.0f, 2.0f);

    // Long Rod under Back Legs
    glVertex3f(legsX[0][0], 517.0f, 14.0f);
    glVertex3f(legsX[2][1], 517.0f, 14.0f);
    glVertex3f(legsX[2][1], 518.0f, 14.0f);
    glVertex3f(legsX[0][0], 518.0f, 14.0f);
    glEnd();
}


























// ==========================================================
// REALISTIC 3D FOUNTAIN FUNCTION
// Center Position: cx = 45.0f, cy = 575.0f
// ==========================================================
void draw3DFountain()
{
    float animTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

    float cx = 45.0f;
    float cy = 575.0f;

    // Smooth, natural ambient water color shifts (Cyan -> Blue -> Aqua -> Soft Cyan)
    float cycle = sinf(animTime * 0.25f);
    float wR = 0.10f + 0.08f * cycle;
    float wG = 0.55f + 0.15f * sinf(animTime * 0.2f);
    float wB = 0.85f + 0.10f * cosf(animTime * 0.25f);

    glPushMatrix();
    glTranslatef(cx, cy, 0.0f);
    glScalef(1.0f, -1.0f, 1.0f);

    // 1. Soft Ground Contact Shadow
    glColor4f(0.0f, 0.0f, 0.0f, 0.15f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 32; i++)
    {
        float rad = i * 2.0f * 3.14159f / 32.0f;
        glVertex2f(cosf(rad) * 26.0f, -14.0f + sinf(rad) * 9.0f);
    }
    glEnd();

    // 2. Base Tier (Main Outer Basin)
    glColor3f(0.38f, 0.39f, 0.42f);
    glRectf(-23.0f, -14.0f, 23.0f, -9.0f);

    glColor3f(0.72f, 0.74f, 0.78f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 32; i++)
    {
        float rad = i * 2.0f * 3.14159f / 32.0f;
        glVertex2f(cosf(rad) * 23.0f, -9.0f + sinf(rad) * 10.0f);
    }
    glEnd();

    glColor3f(0.30f, 0.31f, 0.35f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 32; i++)
    {
        float rad = i * 2.0f * 3.14159f / 32.0f;
        glVertex2f(cosf(rad) * 23.0f, -9.0f + sinf(rad) * 10.0f);
    }
    glEnd();

    // Main Pool Water Surface
    glColor4f(wR, wG, wB, 0.88f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 32; i++)
    {
        float rad = i * 2.0f * 3.14159f / 32.0f;
        glVertex2f(cosf(rad) * 20.5f, -9.0f + sinf(rad) * 8.5f);
    }
    glEnd();

    // Water Surface Wave Rings
    if (isFountainOn)
    {
        glColor4f(wR + 0.3f, wG + 0.3f, 1.0f, 0.40f);
        glLineWidth(1.2f);
        for (int r = 1; r <= 3; r++)
        {
            float rippleScale = fmodf(animTime * 1.4f + r * 0.33f, 1.0f);
            glBegin(GL_LINE_STRIP);
            for (int i = 0; i <= 32; i++)
            {
                float rad = i * 2.0f * 3.14159f / 32.0f;
                glVertex2f(cosf(rad) * (2.0f + rippleScale * 17.5f),
                           -9.0f + sinf(rad) * (1.0f + rippleScale * 7.0f));
            }
            glEnd();
        }
    }

    // 3. Lower Column & Tier 2 Basin
    glColor3f(0.40f, 0.42f, 0.45f);
    glRectf(-4.0f, -9.0f, 4.0f, -1.0f);
    glColor3f(0.60f, 0.62f, 0.66f);
    glRectf(-1.2f, -9.0f, 1.2f, -1.0f);

    glColor3f(0.55f, 0.57f, 0.60f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 28; i++)
    {
        float rad = i * 2.0f * 3.14159f / 28.0f;
        glVertex2f(cosf(rad) * 14.5f, -1.0f + sinf(rad) * 5.0f);
    }
    glEnd();

    glColor4f(wR, wG, wB, 0.88f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 28; i++)
    {
        float rad = i * 2.0f * 3.14159f / 28.0f;
        glVertex2f(cosf(rad) * 12.5f, -1.0f + sinf(rad) * 4.0f);
    }
    glEnd();

    // 4. Middle Column & Tier 3 Basin
    glColor3f(0.38f, 0.40f, 0.43f);
    glRectf(-3.0f, -1.0f, 3.0f, 6.0f);
    glColor3f(0.58f, 0.60f, 0.64f);
    glRectf(-0.9f, -1.0f, 0.9f, 6.0f);

    glColor3f(0.60f, 0.62f, 0.66f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 24; i++)
    {
        float rad = i * 2.0f * 3.14159f / 24.0f;
        glVertex2f(cosf(rad) * 9.5f, 6.0f + sinf(rad) * 3.5f);
    }
    glEnd();

    glColor4f(wR, wG, wB, 0.88f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 24; i++)
    {
        float rad = i * 2.0f * 3.14159f / 24.0f;
        glVertex2f(cosf(rad) * 8.0f, 6.0f + sinf(rad) * 2.8f);
    }
    glEnd();

    // 5. Upper Column & Top Spout Crown (Tier 4)
    glColor3f(0.35f, 0.37f, 0.40f);
    glRectf(-2.0f, 6.0f, 2.0f, 12.0f);

    glColor3f(0.68f, 0.70f, 0.74f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 20; i++)
    {
        float rad = i * 2.0f * 3.14159f / 20.0f;
        glVertex2f(cosf(rad) * 5.0f, 12.0f + sinf(rad) * 2.2f);
    }
    glEnd();

    // 6. Dynamic Water Streams, Cascades & Particles
    if (isFountainOn)
    {
        float h = fountainWaterHeight;
        float spoutOriginY = 12.0f;

        // Central Vertical Spout Jet
        glLineWidth(3.5f);
        glBegin(GL_LINES);
        for (int i = 0; i < 10; i++)
        {
            float offset = sinf(animTime * 14.0f + i) * 0.5f;
            float jetTopY = spoutOriginY + (22.0f * h) + sinf(animTime * 8.0f) * 1.5f;

            glColor4f(wR + 0.4f, wG + 0.4f, 1.0f, 0.95f);
            glVertex2f(offset * 0.2f, spoutOriginY);
            glColor4f(wR, wG + 0.2f, 1.0f, 0.35f);
            glVertex2f(offset, jetTopY);
        }
        glEnd();

        // Top Spout Parabolic Arcs
        glLineWidth(1.8f);
        for (int side = -1; side <= 1; side += 2)
        {
            for (int arc = 1; arc <= 4; arc++)
            {
                float maxReachX = side * (2.8f + arc * 2.8f) * h;
                float arcPeakHeight = (9.0f + arc * 2.5f) * h;

                glBegin(GL_LINE_STRIP);
                for (int step = 0; step <= 16; step++)
                {
                    float t = step / 16.0f;
                    float currX = maxReachX * t;
                    float currY = spoutOriginY + (arcPeakHeight * t) - (arcPeakHeight * t * t * 1.3f);

                    glColor4f(wR + 0.3f, wG + 0.3f, 1.0f, 0.85f - (t * 0.45f));
                    glVertex2f(currX, currY);
                }
                glEnd();
            }
        }

        // Tier 4 -> Tier 3 Overflow Streams
        glLineWidth(1.6f);
        glColor4f(wR + 0.2f, wG + 0.2f, 1.0f, 0.70f);
        for (int c = -4; c <= 4; c++)
        {
            float xPos = c * 1.1f;
            glBegin(GL_LINES);
            glVertex2f(xPos, 12.0f);
            glVertex2f(xPos * 1.6f, 6.0f);
            glEnd();
        }

        // Tier 3 -> Tier 2 Overflow Streams
        glLineWidth(1.8f);
        glColor4f(wR + 0.2f, wG + 0.2f, 1.0f, 0.65f);
        for (int c = -7; c <= 7; c++)
        {
            float xPos = c * 1.1f;
            glBegin(GL_LINES);
            glVertex2f(xPos, 6.0f);
            glVertex2f(xPos * 1.5f, -1.0f);
            glEnd();
        }

        // Tier 2 -> Main Basin Overflow Streams
        glLineWidth(2.0f);
        glColor4f(wR + 0.15f, wG + 0.15f, 1.0f, 0.60f);
        for (int c = -10; c <= 10; c++)
        {
            float xPos = c * 1.2f;
            glBegin(GL_LINES);
            glVertex2f(xPos, -1.0f);
            glVertex2f(xPos * 1.6f, -9.0f);
            glEnd();
        }

        // Falling Water Droplets
        glColor4f(1.0f, 1.0f, 1.0f, 0.90f);
        glPointSize(2.8f);
        glBegin(GL_POINTS);
        for (int p = 0; p < 42; p++)
        {
            float pSeed = p * 1.45f;
            float pProgress = fmodf(animTime * 1.8f + pSeed, 1.0f);
            float px = (sinf(pSeed * 5.5f) * 18.0f) * pProgress;
            float py = spoutOriginY + (18.0f * h * pProgress) - (36.0f * h * pProgress * pProgress);
            glVertex2f(px, py);
        }
        glEnd();

        // Surface Splash Particles
        glColor4f(wR + 0.4f, wG + 0.4f, 1.0f, 0.75f);
        glPointSize(2.0f);
        glBegin(GL_POINTS);
        for (int s = 0; s < 20; s++)
        {
            float sAngle = s * 2.0f * 3.14159f / 20.0f;
            float splashR = 14.0f + sinf(animTime * 10.0f + s) * 2.5f;
            glVertex2f(cosf(sAngle) * splashR, -9.0f + sinf(sAngle) * (splashR * 0.4f));
        }
        glEnd();
    }

    glPopMatrix();
}










































/* ---- Boundary & Gate Layer ---- */

// ============================================================================
// REALISTIC 3D BOUNDARY WALL WITH HEAVY PILLARS & EMBOSSED BRICK PANELS
// Features thick 3D support columns, overhanging caps, and inset brick depth.
// ============================================================================

void drawBoundaryWall()
{
    float wallTopY = 635.0f;
    float wallBottomY = 715.0f;
    float leftPillarX = 720.0f;
    float rightPillarX = 880.0f;

    // ------------------------------------------------------------------------
    // 1. CONCRETE BASE PLINTH (Heavy Foundation Base)
    // ------------------------------------------------------------------------
    // Ground Drop Shadow under foundation
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.08f, 0.08f, 0.10f, 0.40f);
    glBegin(GL_QUADS);
    glVertex2f(-10.0f, wallBottomY + 5.0f);
    glVertex2f(leftPillarX + 8.0f, wallBottomY + 5.0f);
    glVertex2f(leftPillarX + 8.0f, wallBottomY - 2.0f);
    glVertex2f(-10.0f, wallBottomY - 2.0f);

    glVertex2f(rightPillarX - 8.0f, wallBottomY + 5.0f);
    glVertex2f(1610.0f, wallBottomY + 5.0f);
    glVertex2f(1610.0f, wallBottomY - 2.0f);
    glVertex2f(rightPillarX - 8.0f, wallBottomY - 2.0f);
    glEnd();
    glDisable(GL_BLEND);

    // Foundation Base Front Surface
    glColor3f(0.45f, 0.45f, 0.46f);
    glBegin(GL_QUADS);
    glVertex2f(-5.0f, wallBottomY - 12.0f);
    glVertex2f(leftPillarX + 5.0f, wallBottomY - 12.0f);
    glVertex2f(leftPillarX + 5.0f, wallBottomY);
    glVertex2f(-5.0f, wallBottomY);

    glVertex2f(rightPillarX - 5.0f, wallBottomY - 12.0f);
    glVertex2f(1605.0f, wallBottomY - 12.0f);
    glVertex2f(1605.0f, wallBottomY);
    glVertex2f(rightPillarX - 5.0f, wallBottomY);
    glEnd();

    // Foundation Top Bevel Highlight Edge
    glColor3f(0.68f, 0.68f, 0.70f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(-5.0f, wallBottomY - 12.0f);
    glVertex2f(leftPillarX + 5.0f, wallBottomY - 12.0f);
    glVertex2f(rightPillarX - 5.0f, wallBottomY - 12.0f);
    glVertex2f(1605.0f, wallBottomY - 12.0f);
    glEnd();

    // ------------------------------------------------------------------------
    // 2. MAIN WALL BACKGROUND (Cement Mortar Base)
    // ------------------------------------------------------------------------
    glColor3f(0.55f, 0.52f, 0.50f); // Darker cement mortar backing
    glBegin(GL_QUADS);
    glVertex2f(0.0f, wallTopY);
    glVertex2f(leftPillarX, wallTopY);
    glVertex2f(leftPillarX, wallBottomY - 12.0f);
    glVertex2f(0.0f, wallBottomY - 12.0f);

    glVertex2f(rightPillarX, wallTopY);
    glVertex2f(1600.0f, wallTopY);
    glVertex2f(1600.0f, wallBottomY - 12.0f);
    glVertex2f(rightPillarX, wallBottomY - 12.0f);
    glEnd();

    // ------------------------------------------------------------------------
    // 3. EMBOSSED 3D BRICK WORK (Layered Brick Pattern with Volume)
    // ------------------------------------------------------------------------
    float brickHeight = 11.0f;
    float brickWidth = 26.0f;
    int rowIndex = 0;

    for (float y = wallTopY + 2.0f; y < wallBottomY - 14.0f; y += brickHeight + 2.0f)
    {
        float xOffset = (rowIndex % 2 == 0) ? 0.0f : (brickWidth / 2.0f);

        // Left Section Bricks
        for (float x = xOffset; x < leftPillarX - 2.0f; x += brickWidth + 2.0f)
        {
            float drawW = (x + brickWidth > leftPillarX) ? (leftPillarX - x) : brickWidth;
            if (drawW <= 2.0f) continue;

            // Brick Shadow (Right & Bottom Depth)
            glColor3f(0.35f, 0.18f, 0.15f);
            glBegin(GL_QUADS);
            glVertex2f(x + 1.0f, y + 1.0f);
            glVertex2f(x + drawW + 1.0f, y + 1.0f);
            glVertex2f(x + drawW + 1.0f, y + brickHeight + 1.0f);
            glVertex2f(x + 1.0f, y + brickHeight + 1.0f);
            glEnd();

            // Brick Main Face (Textured Red Clay)
            glColor3f(0.72f, 0.32f, 0.24f);
            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + drawW, y);
            glColor3f(0.58f, 0.24f, 0.18f); // Gradient shadow on bottom of each brick
            glVertex2f(x + drawW, y + brickHeight);
            glVertex2f(x, y + brickHeight);
            glEnd();

            // Brick Top Light Highlight
            glColor3f(0.85f, 0.45f, 0.35f);
            glLineWidth(1.0f);
            glBegin(GL_LINES);
            glVertex2f(x, y);
            glVertex2f(x + drawW, y);
            glEnd();
        }

        // Right Section Bricks
        for (float x = rightPillarX + xOffset; x < 1600.0f - 2.0f; x += brickWidth + 2.0f)
        {
            float drawW = (x + brickWidth > 1600.0f) ? (1600.0f - x) : brickWidth;
            if (drawW <= 2.0f) continue;

            // Brick Shadow (Right & Bottom Depth)
            glColor3f(0.35f, 0.18f, 0.15f);
            glBegin(GL_QUADS);
            glVertex2f(x + 1.0f, y + 1.0f);
            glVertex2f(x + drawW + 1.0f, y + 1.0f);
            glVertex2f(x + drawW + 1.0f, y + brickHeight + 1.0f);
            glVertex2f(x + 1.0f, y + brickHeight + 1.0f);
            glEnd();

            // Brick Main Face
            glColor3f(0.72f, 0.32f, 0.24f);
            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + drawW, y);
            glColor3f(0.58f, 0.24f, 0.18f);
            glVertex2f(x + drawW, y + brickHeight);
            glVertex2f(x, y + brickHeight);
            glEnd();

            // Brick Top Light Highlight
            glColor3f(0.85f, 0.45f, 0.35f);
            glLineWidth(1.0f);
            glBegin(GL_LINES);
            glVertex2f(x, y);
            glVertex2f(x + drawW, y);
            glEnd();
        }
        rowIndex++;
    }

    // ------------------------------------------------------------------------
    // 4. EXTRA THICK 3D CONCRETE PILLARS (3-Faceted Solid Columns)
    // ------------------------------------------------------------------------
    float pillarWidth = 24.0f; // Made substantially wider/thicker

    auto drawSingleThickPillar = [&](float px)
    {
        // Pillar Cast Shadow on Wall
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.08f, 0.08f, 0.10f, 0.38f);
        glBegin(GL_QUADS);
        glVertex2f(px + pillarWidth, wallTopY - 5.0f);
        glVertex2f(px + pillarWidth + 10.0f, wallTopY - 5.0f);
        glVertex2f(px + pillarWidth + 10.0f, wallBottomY - 12.0f);
        glVertex2f(px + pillarWidth, wallBottomY - 12.0f);
        glEnd();
        glDisable(GL_BLEND);

        // 1. Pillar Left Bevel Face (Sunlit Highlight Edge)
        glColor3f(0.88f, 0.88f, 0.86f);
        glBegin(GL_QUADS);
        glVertex2f(px - 3.0f, wallTopY - 4.0f);
        glVertex2f(px, wallTopY - 4.0f);
        glVertex2f(px, wallBottomY - 12.0f);
        glVertex2f(px - 3.0f, wallBottomY - 12.0f);
        glEnd();

        // 2. Pillar Main Front Face
        glColor3f(0.76f, 0.76f, 0.74f);
        glBegin(GL_QUADS);
        glVertex2f(px, wallTopY - 4.0f);
        glVertex2f(px + pillarWidth - 4.0f, wallTopY - 4.0f);
        glVertex2f(px + pillarWidth - 4.0f, wallBottomY - 12.0f);
        glVertex2f(px, wallBottomY - 12.0f);
        glEnd();

        // 3. Pillar Right Shadow Face (Creates 3D Side Depth)
        glColor3f(0.52f, 0.52f, 0.50f);
        glBegin(GL_QUADS);
        glVertex2f(px + pillarWidth - 4.0f, wallTopY - 4.0f);
        glVertex2f(px + pillarWidth, wallTopY - 4.0f);
        glVertex2f(px + pillarWidth, wallBottomY - 12.0f);
        glVertex2f(px + pillarWidth - 4.0f, wallBottomY - 12.0f);
        glEnd();

        // Pillar Overhanging Capital Cap (Top Crown of Pillar)
        glColor3f(0.82f, 0.82f, 0.80f);
        glBegin(GL_QUADS);
        glVertex2f(px - 5.0f, wallTopY - 10.0f);
        glVertex2f(px + pillarWidth + 2.0f, wallTopY - 10.0f);
        glVertex2f(px + pillarWidth + 2.0f, wallTopY - 4.0f);
        glVertex2f(px - 5.0f, wallTopY - 4.0f);
        glEnd();

        // Cap Bottom Shadow Line
        glColor3f(0.40f, 0.40f, 0.38f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glVertex2f(px - 5.0f, wallTopY - 4.0f);
        glVertex2f(px + pillarWidth + 2.0f, wallTopY - 4.0f);
        glEnd();
    };

    // Draw Left Section Pillars
    for (float x = 140.0f; x < leftPillarX - 30.0f; x += 190.0f)
    {
        drawSingleThickPillar(x);
    }
    // Draw Right Section Pillars
    for (float x = rightPillarX + 140.0f; x < 1600.0f - 30.0f; x += 190.0f)
    {
        drawSingleThickPillar(x);
    }

    // ------------------------------------------------------------------------
    // 5. HEAVY OVERHANGING TOP COPING SLAB (Wall Top Cap with 3D Bevels)
    // ------------------------------------------------------------------------
    // Drop Shadow under Top Cap Slab
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.08f, 0.08f, 0.10f, 0.42f);
    glBegin(GL_QUADS);
    glVertex2f(-6.0f, wallTopY);
    glVertex2f(leftPillarX + 6.0f, wallTopY);
    glVertex2f(leftPillarX + 6.0f, wallTopY + 8.0f);
    glVertex2f(-6.0f, wallTopY + 8.0f);

    glVertex2f(rightPillarX - 6.0f, wallTopY);
    glVertex2f(1606.0f, wallTopY);
    glVertex2f(1606.0f, wallTopY + 8.0f);
    glVertex2f(rightPillarX - 6.0f, wallTopY + 8.0f);
    glEnd();
    glDisable(GL_BLEND);

    // Underside Shadow Edge of Cap
    glColor3f(0.42f, 0.42f, 0.40f);
    glBegin(GL_QUADS);
    glVertex2f(-6.0f, wallTopY - 3.0f);
    glVertex2f(leftPillarX + 6.0f, wallTopY - 3.0f);
    glVertex2f(leftPillarX + 6.0f, wallTopY);
    glVertex2f(-6.0f, wallTopY);

    glVertex2f(rightPillarX - 6.0f, wallTopY - 3.0f);
    glVertex2f(1606.0f, wallTopY - 3.0f);
    glVertex2f(1606.0f, wallTopY);
    glVertex2f(rightPillarX - 6.0f, wallTopY);
    glEnd();

    // Main Cap Front Facing Slab
    glColor3f(0.72f, 0.72f, 0.70f);
    glBegin(GL_QUADS);
    glVertex2f(-6.0f, wallTopY - 12.0f);
    glVertex2f(leftPillarX + 6.0f, wallTopY - 12.0f);
    glVertex2f(leftPillarX + 6.0f, wallTopY - 3.0f);
    glVertex2f(-6.0f, wallTopY - 3.0f);

    glVertex2f(rightPillarX - 6.0f, wallTopY - 12.0f);
    glVertex2f(1606.0f, wallTopY - 12.0f);
    glVertex2f(1606.0f, wallTopY - 3.0f);
    glVertex2f(rightPillarX - 6.0f, wallTopY - 3.0f);
    glEnd();

    // Angled Sunlit Slanted Roof of Cap
    glColor3f(0.88f, 0.88f, 0.86f);
    glBegin(GL_QUADS);
    glVertex2f(-3.0f, wallTopY - 16.0f);
    glVertex2f(leftPillarX + 3.0f, wallTopY - 16.0f);
    glVertex2f(leftPillarX + 6.0f, wallTopY - 12.0f);
    glVertex2f(-6.0f, wallTopY - 12.0f);

    glVertex2f(rightPillarX - 3.0f, wallTopY - 16.0f);
    glVertex2f(1603.0f, wallTopY - 16.0f);
    glVertex2f(1606.0f, wallTopY - 12.0f);
    glVertex2f(rightPillarX - 6.0f, wallTopY - 12.0f);
    glEnd();

    // Top Rim Specular Line Highlight
    glColor3f(0.98f, 0.98f, 0.96f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(-3.0f, wallTopY - 16.0f);
    glVertex2f(leftPillarX + 3.0f, wallTopY - 16.0f);
    glVertex2f(rightPillarX - 3.0f, wallTopY - 16.0f);
    glVertex2f(1603.0f, wallTopY - 16.0f);
    glEnd();

    glLineWidth(1.0f);
}



































// ----------------------------------------------------------------------------
// GLOBAL VARIABLES FOR GATE
// ----------------------------------------------------------------------------
float gateOpenFactor = 0.0f;

// ----------------------------------------------------------------------------
// UPDATE ANIMATION FUNCTION
// ----------------------------------------------------------------------------
void updateGateAnimation()
{
    float speed = 0.02f;

    if (isGateOpen && gateOpenFactor < 1.0f)
    {
        gateOpenFactor += speed;
        if (gateOpenFactor > 1.0f) gateOpenFactor = 1.0f;
    }
    else if (!isGateOpen && gateOpenFactor > 0.0f)
    {
        gateOpenFactor -= speed;
        if (gateOpenFactor < 0.0f) gateOpenFactor = 0.0f;
    }

    glutPostRedisplay();
}

// ============================================================================
// HIGHLY DETAILED MAIN ENTRANCE GATE & PILLARS
// Perfectly Matched with Boundaries (Y: 615 to 715) with 3D Concrete & Iron Work
// ============================================================================

void drawGate()
{
    updateGateAnimation();

    float pY1 = 615.0f; // Pillar Top
    float pY2 = 715.0f; // Pillar Bottom

    float leftPillLeft = 715.0f;
    float leftPillRight = 750.0f;
    float rightPillLeft = 850.0f;
    float rightPillRight = 885.0f;

    // ------------------------------------------------------------------------
    // 1. LEFT GATE PILLAR
    // ------------------------------------------------------------------------
    glColor3f(0.76f, 0.76f, 0.74f);
    glBegin(GL_QUADS);
    glVertex2f(leftPillLeft, pY1);
    glVertex2f(leftPillRight, pY1);
    glVertex2f(leftPillRight, pY2);
    glVertex2f(leftPillLeft, pY2);
    glEnd();

    glColor3f(0.60f, 0.60f, 0.58f);
    glBegin(GL_QUADS);
    glVertex2f(leftPillRight - 6.0f, pY1);
    glVertex2f(leftPillRight, pY1);
    glVertex2f(leftPillRight, pY2);
    glVertex2f(leftPillRight - 6.0f, pY2);
    glEnd();

    glColor3f(0.50f, 0.50f, 0.48f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    glVertex2f(leftPillLeft, pY1 + 30.0f);
    glVertex2f(leftPillRight, pY1 + 30.0f);
    glVertex2f(leftPillLeft, pY1 + 60.0f);
    glVertex2f(leftPillRight, pY1 + 60.0f);
    glEnd();

    glColor3f(0.85f, 0.85f, 0.83f);
    glBegin(GL_QUADS);
    glVertex2f(leftPillLeft - 4.0f, pY1 - 6.0f);
    glVertex2f(leftPillRight + 4.0f, pY1 - 6.0f);
    glVertex2f(leftPillRight + 4.0f, pY1);
    glVertex2f(leftPillLeft - 4.0f, pY1);

    glVertex2f(leftPillLeft - 1.0f, pY1 - 14.0f);
    glVertex2f(leftPillRight + 1.0f, pY1 - 14.0f);
    glVertex2f(leftPillRight + 4.0f, pY1 - 6.0f);
    glVertex2f(leftPillLeft - 4.0f, pY1 - 6.0f);
    glEnd();

    // ------------------------------------------------------------------------
    // 2. RIGHT GATE PILLAR
    // ------------------------------------------------------------------------
    glColor3f(0.76f, 0.76f, 0.74f);
    glBegin(GL_QUADS);
    glVertex2f(rightPillLeft, pY1);
    glVertex2f(rightPillRight, pY1);
    glVertex2f(rightPillRight, pY2);
    glVertex2f(rightPillLeft, pY2);
    glEnd();

    glColor3f(0.84f, 0.84f, 0.82f);
    glBegin(GL_QUADS);
    glVertex2f(rightPillLeft, pY1);
    glVertex2f(rightPillLeft + 6.0f, pY1);
    glVertex2f(rightPillLeft + 6.0f, pY2);
    glVertex2f(rightPillLeft, pY2);
    glEnd();

    glColor3f(0.50f, 0.50f, 0.48f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    glVertex2f(rightPillLeft, pY1 + 30.0f);
    glVertex2f(rightPillRight, pY1 + 30.0f);
    glVertex2f(rightPillLeft, pY1 + 60.0f);
    glVertex2f(rightPillRight, pY1 + 60.0f);
    glEnd();

    glColor3f(0.85f, 0.85f, 0.83f);
    glBegin(GL_QUADS);
    glVertex2f(rightPillLeft - 4.0f, pY1 - 6.0f);
    glVertex2f(rightPillRight + 4.0f, pY1 - 6.0f);
    glVertex2f(rightPillRight + 4.0f, pY1);
    glVertex2f(rightPillLeft - 4.0f, pY1);

    glVertex2f(rightPillLeft - 1.0f, pY1 - 14.0f);
    glVertex2f(rightPillRight + 1.0f, pY1 - 14.0f);
    glVertex2f(rightPillRight + 4.0f, pY1 - 6.0f);
    glVertex2f(rightPillLeft - 4.0f, pY1 - 6.0f);
    glEnd();

    // ------------------------------------------------------------------------
    // 3. PILLAR HINGES & ATTACHMENTS
    // ------------------------------------------------------------------------
    glColor3f(0.20f, 0.20f, 0.22f);
    glBegin(GL_QUADS);
    glVertex2f(leftPillRight, pY1 + 25.0f);
    glVertex2f(leftPillRight + 4.0f, pY1 + 25.0f);
    glVertex2f(leftPillRight + 4.0f, pY1 + 33.0f);
    glVertex2f(leftPillRight, pY1 + 33.0f);

    glVertex2f(leftPillRight, pY2 - 25.0f);
    glVertex2f(leftPillRight + 4.0f, pY2 - 25.0f);
    glVertex2f(leftPillRight + 4.0f, pY2 - 17.0f);
    glVertex2f(leftPillRight, pY2 - 17.0f);

    glVertex2f(rightPillLeft - 4.0f, pY1 + 25.0f);
    glVertex2f(rightPillLeft, pY1 + 25.0f);
    glVertex2f(rightPillLeft, pY1 + 33.0f);
    glVertex2f(rightPillLeft - 4.0f, pY1 + 33.0f);

    glVertex2f(rightPillLeft - 4.0f, pY2 - 25.0f);
    glVertex2f(rightPillLeft, pY2 - 25.0f);
    glVertex2f(rightPillLeft, pY2 - 17.0f);
    glVertex2f(rightPillLeft - 4.0f, pY2 - 17.0f);
    glEnd();

    // ------------------------------------------------------------------------
    // 4. ANIMATED STEEL GRILL GATES
    // ------------------------------------------------------------------------
    glColor3f(0.18f, 0.22f, 0.24f);

    // --- Left Gate Door ---
    float lStart = leftPillRight;
    float lClosedEnd = 798.0f;
    float lOpenEnd = leftPillRight + 2.0f;
    float lEnd = lClosedEnd + (lOpenEnd - lClosedEnd) * gateOpenFactor;

    float lTopY = pY1 + 18.0f;
    float lBotY = pY2 - 5.0f;

    glLineWidth(2.5f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(lStart, lTopY);
    glVertex2f(lEnd, lTopY + (6.0f * (1.0f - gateOpenFactor)));
    glVertex2f(lEnd, lBotY);
    glVertex2f(lStart, lBotY);
    glEnd();

    glLineWidth(1.8f);
    glBegin(GL_LINES);
    glVertex2f(lStart, lTopY + 30.0f);
    glVertex2f(lEnd, lTopY + 32.0f);
    glVertex2f(lStart, lBotY - 25.0f);
    glVertex2f(lEnd, lBotY - 25.0f);
    glEnd();

    if (fabs(lEnd - lStart) > 2.0f)
    {
        for (float x = lStart + 6.0f; x < lEnd; x += 7.5f)
        {
            float currentTopY = lTopY + ((x - lStart) / (lEnd - lStart)) * (6.0f * (1.0f - gateOpenFactor));

            glLineWidth(1.8f);
            glBegin(GL_LINES);
            glVertex2f(x, currentTopY + 4.0f);
            glVertex2f(x, lBotY);
            glEnd();

            glBegin(GL_TRIANGLES);
            glVertex2f(x - 2.0f, currentTopY + 4.0f);
            glVertex2f(x + 2.0f, currentTopY + 4.0f);
            glVertex2f(x, currentTopY - 3.0f);
            glEnd();
        }
    }

    // --- Right Gate Door ---
    float rStart = rightPillLeft;
    float rClosedEnd = 802.0f;
    float rOpenEnd = rightPillLeft - 2.0f;
    float rEnd = rClosedEnd + (rOpenEnd - rClosedEnd) * gateOpenFactor;

    float rTopY = pY1 + 18.0f;
    float rBotY = pY2 - 5.0f;

    glLineWidth(2.5f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(rStart, rTopY);
    glVertex2f(rEnd, rTopY + (6.0f * (1.0f - gateOpenFactor)));
    glVertex2f(rEnd, rBotY);
    glVertex2f(rStart, rBotY);
    glEnd();

    glLineWidth(1.8f);
    glBegin(GL_LINES);
    glVertex2f(rStart, rTopY + 30.0f);
    glVertex2f(rEnd, rTopY + 32.0f);
    glVertex2f(rStart, rBotY - 25.0f);
    glVertex2f(rEnd, rBotY - 25.0f);
    glEnd();

    if (fabs(rStart - rEnd) > 2.0f)
    {
        for (float x = rStart - 6.0f; x > rEnd; x -= 7.5f)
        {
            float currentTopY = rTopY + ((rStart - x) / (rStart - rEnd)) * (6.0f * (1.0f - gateOpenFactor));

            glLineWidth(1.8f);
            glBegin(GL_LINES);
            glVertex2f(x, currentTopY + 4.0f);
            glVertex2f(x, rBotY);
            glEnd();

            glBegin(GL_TRIANGLES);
            glVertex2f(x - 2.0f, currentTopY + 4.0f);
            glVertex2f(x + 2.0f, currentTopY + 4.0f);
            glVertex2f(x, currentTopY - 3.0f);
            glEnd();
        }
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
    glVertex2f(bLeft + 4.0f, bTop + 4.0f);
    glVertex2f(bRight - 4.0f, bTop + 4.0f);
    glVertex2f(bLeft + 4.0f, bTop + 4.0f);
    glVertex2f(bLeft + 4.0f, bBottom - 4.0f);
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
    glVertex2f(921.0f, 627.0f);
    glVertex2f(933.0f, 627.0f);
    glVertex2f(921.0f, 632.0f);
    glVertex2f(933.0f, 632.0f);
    glVertex2f(921.0f, 637.0f);
    glVertex2f(930.0f, 637.0f);
    glEnd();

    // Notice 1 Red Push Pin
    glColor3f(0.85f, 0.15f, 0.15f);
    glBegin(GL_QUADS);
    glVertex2f(926.0f, 620.0f);
    glVertex2f(928.0f, 620.0f);
    glVertex2f(928.0f, 623.0f);
    glVertex2f(926.0f, 623.0f);
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
    glVertex2f(945.0f, 631.0f);
    glVertex2f(960.0f, 631.0f);
    glVertex2f(945.0f, 636.0f);
    glVertex2f(961.0f, 636.0f);
    glVertex2f(945.0f, 641.0f);
    glVertex2f(958.0f, 641.0f);
    glVertex2f(945.0f, 646.0f);
    glVertex2f(955.0f, 646.0f);
    glEnd();

    // Notice 2 Blue Push Pin
    glColor3f(0.15f, 0.35f, 0.85f);
    glBegin(GL_QUADS);
    glVertex2f(952.0f, 623.0f);
    glVertex2f(954.0f, 623.0f);
    glVertex2f(954.0f, 626.0f);
    glVertex2f(952.0f, 626.0f);
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
    glVertex2f(bLeft - 6.0f, bTop);
    glVertex2f(945.0f, bTop - 12.0f);
    glVertex2f(945.0f, bTop - 12.0f);
    glVertex2f(bRight + 6.0f, bTop);
    glEnd();

    glLineWidth(1.0f);
}



































// ----------------------------------------------------------------------------
// GLOBAL VARIABLES FOR LAMP POST
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// KEYBOARD HANDLER FOR LAMP POST
// ----------------------------------------------------------------------------
void handleLampKeyboard(unsigned char key, int x, int y)
{
    if (key == 'l' || key == 'L')
    {
        isLampOn = !isLampOn;
        glutPostRedisplay();
    }
}

// ============================================================================
// HIGHLY DETAILED VINTAGE CLASSIC LAMP POSTS
// Height Adjusted for Footpath Base Alignment (Y: 570.0f to 715.0f)
// Features Cast-Iron Pedestal, Curved Lantern Bracket & Light Glow Effect
// ============================================================================

void drawLampPost()
{
    float lampPositionsX[] = { 100.0f, 680.0f, 1010.0f, 1500.0f };

    for (int i = 0; i < 4; i++)
    {
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
        if (isLampOn)
        {
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
        }

        // --------------------------------------------------------------------
        // 5. GLOWING LANTERN HOUSING & GLASS PANELS
        // --------------------------------------------------------------------
        // Core Bulb (Dynamic On/Off State)
        if (isLampOn)
        {
            glColor3f(1.0f, 0.90f, 0.40f); // Bright Warm Yellow (ON)
        }
        else
        {
            glColor3f(0.25f, 0.25f, 0.25f); // Dark Grey (OFF)
        }

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
// REALISTIC PARK BENCH (Light Brown / Warm Oak Wood Finish)
// Low-Height Straight Legs, Wide Seating & Armrests
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
    // 3. BACKREST WOODEN SLATS (Top Section - Light Brown Oak Wood)
    // ------------------------------------------------------------------------
    float backOffsetY[] = { -30.0f, -22.0f, -14.0f, -6.0f };

    for (int i = 0; i < 4; i++)
    {
        float y = seatY + backOffsetY[i];

        // Light Wood Base Edge Shadow
        glColor3f(0.55f, 0.38f, 0.20f);
        glBegin(GL_QUADS);
        glVertex2f(bx + 4.0f, y);
        glVertex2f(bx + bWidth - 4.0f, y);
        glVertex2f(bx + bWidth - 4.0f, y + 6.0f);
        glVertex2f(bx + 4.0f, y + 6.0f);
        glEnd();

        // Main Light Brown Wood Body
        glColor3f(0.82f, 0.60f, 0.36f);
        glBegin(GL_QUADS);
        glVertex2f(bx + 5.0f, y + 0.8f);
        glVertex2f(bx + bWidth - 5.0f, y + 0.8f);
        glVertex2f(bx + bWidth - 5.0f, y + 5.2f);
        glVertex2f(bx + 5.0f, y + 5.2f);
        glEnd();

        // Bright Wood Top Highlight Rim
        glColor3f(0.92f, 0.74f, 0.48f);
        glLineWidth(1.2f);
        glBegin(GL_LINES);
        glVertex2f(bx + 5.0f, y + 5.2f);
        glVertex2f(bx + bWidth - 5.0f, y + 5.2f);
        glEnd();
    }

    // ------------------------------------------------------------------------
    // 4. MAIN SEATING SURFACE (Light Brown Wood Slab)
    // ------------------------------------------------------------------------
    // Base Under-Shadow
    glColor3f(0.48f, 0.32f, 0.16f);
    glBegin(GL_QUADS);
    glVertex2f(bx, seatY);
    glVertex2f(bx + bWidth, seatY);
    glVertex2f(bx + bWidth, seatY + 12.0f);
    glVertex2f(bx, seatY + 12.0f);
    glEnd();

    // Front Light Brown Wood Face
    glColor3f(0.78f, 0.55f, 0.32f);
    glBegin(GL_QUADS);
    glVertex2f(bx + 1.0f, seatY + 1.0f);
    glVertex2f(bx + bWidth - 1.0f, seatY + 1.0f);
    glVertex2f(bx + bWidth - 1.0f, seatY + 11.0f);
    glVertex2f(bx + 1.0f, seatY + 11.0f);
    glEnd();

    // Top Surface Light Highlight
    glColor3f(0.90f, 0.70f, 0.45f);
    glBegin(GL_QUADS);
    glVertex2f(bx + 1.0f, seatY + 1.0f);
    glVertex2f(bx + bWidth - 1.0f, seatY + 1.0f);
    glVertex2f(bx + bWidth - 1.0f, seatY + 4.0f);
    glVertex2f(bx + 1.0f, seatY + 4.0f);
    glEnd();

    glLineWidth(1.0f);
}













































/* ============================================================================
   FUNCTION: drawWaterStation
   Description: Ultra-Realistic 3D Wall-Mounted Drinking Water Station.
   Base Position: wx = 360.0f, wy = 665.0f
   Depth Span (Z-axis): [-2.0f (Wall Backing) to 18.0f (Basin Front)]
   ============================================================================ */

#include <cmath>

void drawWaterStation()
{
    // Primary Position Controllers
    float wx = 100.0f; // Horizontal Position (X-axis)
    float wy = 690.0f; // Vertical Position (Y-axis)

    // ------------------------------------------------------------------------
    // 1. 3D CERAMIC TILED BACKING WALL PANEL
    // ------------------------------------------------------------------------
    float tileX1 = wx,         tileX2 = wx + 50.0f;
    float tileY1 = wy - 30.0f, tileY2 = wy + 25.0f;
    float tileZBack = -2.0f,   tileZFront = 0.0f;

    // Tile Panel Base
    glBegin(GL_QUADS);
    // Front Face (Ceramic Cyan Surface)
    glColor3f(0.82f, 0.92f, 0.96f);
    glVertex3f(tileX1, tileY1, tileZFront);
    glVertex3f(tileX2, tileY1, tileZFront);
    glVertex3f(tileX2, tileY2, tileZFront);
    glVertex3f(tileX1, tileY2, tileZFront);

    // Top Edge Rim
    glColor3f(0.90f, 0.96f, 0.98f);
    glVertex3f(tileX1, tileY2, tileZBack);
    glVertex3f(tileX2, tileY2, tileZBack);
    glVertex3f(tileX2, tileY2, tileZFront);
    glVertex3f(tileX1, tileY2, tileZFront);

    // Right Edge Rim
    glColor3f(0.70f, 0.82f, 0.88f);
    glVertex3f(tileX2, tileY1, tileZBack);
    glVertex3f(tileX2, tileY1, tileZFront);
    glVertex3f(tileX2, tileY2, tileZFront);
    glVertex3f(tileX2, tileY2, tileZBack);

    // Left Edge Rim
    glColor3f(0.85f, 0.94f, 0.98f);
    glVertex3f(tileX1, tileY1, tileZBack);
    glVertex3f(tileX1, tileY1, tileZFront);
    glVertex3f(tileX1, tileY2, tileZFront);
    glVertex3f(tileX1, tileY2, tileZBack);

    // Bottom Edge Rim
    glColor3f(0.60f, 0.72f, 0.78f);
    glVertex3f(tileX1, tileY1, tileZBack);
    glVertex3f(tileX2, tileY1, tileZBack);
    glVertex3f(tileX2, tileY1, tileZFront);
    glVertex3f(tileX1, tileY1, tileZFront);
    glEnd();

    // 3D Grout Grid Lines (Recessed Tile Grooves)
    glColor3f(0.68f, 0.80f, 0.86f);
    glLineWidth(1.4f);
    glBegin(GL_LINES);
    // Vertical Grout Lines
    glVertex3f(wx + 16.6f, tileY1, tileZFront + 0.05f);
    glVertex3f(wx + 16.6f, tileY2, tileZFront + 0.05f);

    glVertex3f(wx + 33.3f, tileY1, tileZFront + 0.05f);
    glVertex3f(wx + 33.3f, tileY2, tileZFront + 0.05f);

    // Horizontal Grout Lines
    glVertex3f(tileX1, wy - 12.0f, tileZFront + 0.05f);
    glVertex3f(tileX2, wy - 12.0f, tileZFront + 0.05f);

    glVertex3f(tileX1, wy + 6.0f,  tileZFront + 0.05f);
    glVertex3f(tileX2, wy + 6.0f,  tileZFront + 0.05f);
    glEnd();

    // ------------------------------------------------------------------------
    // 2. WALL MOUNT HEAVY STEEL BRACKETS (Underneath Basin Support)
    // ------------------------------------------------------------------------
    float bracketX[] = { wx + 8.0f, wx + 38.0f };
    for (int b = 0; b < 2; b++)
    {
        float bx = bracketX[b];
        glBegin(GL_QUADS);
        // Front Face of Strut
        glColor3f(0.35f, 0.38f, 0.42f);
        glVertex3f(bx, wy + 19.5f, 1.0f);
        glVertex3f(bx + 4.0f, wy + 19.5f, 1.0f);
        glVertex3f(bx + 2.0f, wy + 24.0f, 16.0f);
        glVertex3f(bx, wy + 24.0f, 16.0f);

        // Side Face
        glColor3f(0.25f, 0.28f, 0.32f);
        glVertex3f(bx + 4.0f, wy + 19.5f, 0.0f);
        glVertex3f(bx + 4.0f, wy + 19.5f, 1.0f);
        glVertex3f(bx + 2.0f, wy + 24.0f, 16.0f);
        glVertex3f(bx + 2.0f, wy + 24.0f, 0.0f);
        glEnd();
    }

    // ------------------------------------------------------------------------
    // 3. 3D STAINLESS STEEL BASIN (Extruded Basin Rim & Hollow Bowl)
    // ------------------------------------------------------------------------
    float bOuterX1 = wx + 4.0f,  bOuterX2 = wx + 46.0f;
    float bInnerX1 = wx + 8.0f,  bInnerX2 = wx + 42.0f;

    float bTopY = wy + 4.0f,     bBotY = wy + 19.5f;
    float bZBack = 1.0f,         bZFront = 17.0f;

    // A. Basin Outer Metallic Shell
    glBegin(GL_QUADS);
    // Outer Front Wall Face
    glColor3f(0.75f, 0.78f, 0.82f);
    glVertex3f(bOuterX1 + 5.0f, bBotY, bZFront);
    glVertex3f(bOuterX2 - 5.0f, bBotY, bZFront);
    glVertex3f(bOuterX2,        bTopY, bZFront);
    glVertex3f(bOuterX1,        bTopY, bZFront);

    // Outer Bottom Slope Face
    glColor3f(0.55f, 0.58f, 0.62f);
    glVertex3f(bOuterX1,        bTopY, bZBack);
    glVertex3f(bOuterX2,        bTopY, bZBack);
    glVertex3f(bOuterX2 - 5.0f, bBotY, bZFront);
    glVertex3f(bOuterX1 + 5.0f, bBotY, bZFront);

    // Outer Left Side Wall
    glColor3f(0.85f, 0.88f, 0.92f);
    glVertex3f(bOuterX1,        bTopY, bZBack);
    glVertex3f(bOuterX1,        bTopY, bZFront);
    glVertex3f(bOuterX1 + 5.0f, bBotY, bZFront);
    glVertex3f(bOuterX1 + 5.0f, bBotY, bZBack);

    // Outer Right Side Wall (Shadowed)
    glColor3f(0.48f, 0.50f, 0.54f);
    glVertex3f(bOuterX2,        bTopY, bZFront);
    glVertex3f(bOuterX2,        bTopY, bZBack);
    glVertex3f(bOuterX2 - 5.0f, bBotY, bZBack);
    glVertex3f(bOuterX2 - 5.0f, bBotY, bZFront);
    glEnd();

    // B. Basin Top Flat Rim / Lip
    glBegin(GL_QUADS);
    glColor3f(0.88f, 0.90f, 0.94f);
    // Front Lip Edge
    glVertex3f(bOuterX1, bTopY, bZFront - 1.5f);
    glVertex3f(bOuterX2, bTopY, bZFront - 1.5f);
    glVertex3f(bOuterX2, bTopY, bZFront);
    glVertex3f(bOuterX1, bTopY, bZFront);

    // Left Lip Edge
    glVertex3f(bOuterX1, bTopY, bZBack);
    glVertex3f(bInnerX1, bTopY, bZBack);
    glVertex3f(bInnerX1, bTopY, bZFront);
    glVertex3f(bOuterX1, bTopY, bZFront);

    // Right Lip Edge
    glVertex3f(bInnerX2, bTopY, bZBack);
    glVertex3f(bOuterX2, bTopY, bZBack);
    glVertex3f(bOuterX2, bTopY, bZFront);
    glVertex3f(bInnerX2, bTopY, bZFront);
    glEnd();

    // C. Inner Recessed Sink Cavity (Hollow Basin Interior)
    float sinkBottomY = wy + 14.0f;
    float sinkZCenter = 8.0f;

    glBegin(GL_QUADS);
    // Basin Interior Back Slope
    glColor3f(0.50f, 0.52f, 0.56f);
    glVertex3f(bInnerX1, bTopY, bZBack);
    glVertex3f(bInnerX2, bTopY, bZBack);
    glVertex3f(bInnerX2 - 3.0f, sinkBottomY, sinkZCenter);
    glVertex3f(bInnerX1 + 3.0f, sinkBottomY, sinkZCenter);

    // Basin Interior Front Slope
    glColor3f(0.68f, 0.70f, 0.75f);
    glVertex3f(bInnerX1 + 3.0f, sinkBottomY, sinkZCenter);
    glVertex3f(bInnerX2 - 3.0f, sinkBottomY, sinkZCenter);
    glVertex3f(bOuterX2 - 2.0f, bTopY, bZFront - 1.5f);
    glVertex3f(bOuterX1 + 2.0f, bTopY, bZFront - 1.5f);

    // Basin Interior Floor (Drain Bed)
    glColor3f(0.40f, 0.42f, 0.45f);
    glVertex3f(bInnerX1 + 3.0f, sinkBottomY, sinkZCenter - 2.0f);
    glVertex3f(bInnerX2 - 3.0f, sinkBottomY, sinkZCenter - 2.0f);
    glVertex3f(bInnerX2 - 3.0f, sinkBottomY, sinkZCenter + 2.0f);
    glVertex3f(bInnerX1 + 3.0f, sinkBottomY, sinkZCenter + 2.0f);
    glEnd();

    // D. 3D Metal Drain Plate & Grate Holes
    glColor3f(0.20f, 0.22f, 0.25f);
    glBegin(GL_QUADS);
    glVertex3f(wx + 22.0f, sinkBottomY - 0.1f, sinkZCenter - 1.2f);
    glVertex3f(wx + 28.0f, sinkBottomY - 0.1f, sinkZCenter - 1.2f);
    glVertex3f(wx + 28.0f, sinkBottomY - 0.1f, sinkZCenter + 1.2f);
    glVertex3f(wx + 22.0f, sinkBottomY - 0.1f, sinkZCenter + 1.2f);
    glEnd();

    // Metallic Drain Ring Highlight
    glColor3f(0.80f, 0.82f, 0.85f);
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(wx + 21.8f, sinkBottomY - 0.15f, sinkZCenter - 1.3f);
    glVertex3f(wx + 28.2f, sinkBottomY - 0.15f, sinkZCenter - 1.3f);
    glVertex3f(wx + 28.2f, sinkBottomY - 0.15f, sinkZCenter + 1.3f);
    glVertex3f(wx + 21.8f, sinkBottomY - 0.15f, sinkZCenter + 1.3f);
    glEnd();

    // ------------------------------------------------------------------------
    // 4. 3D CHROME GOOSENECK FAUCETS / TAPS & WATER FLOW
    // ------------------------------------------------------------------------
    float tapX[] = { wx + 15.0f, wx + 35.0f };

    for (int i = 0; i < 2; i++)
    {
        float tx = tapX[i];

        // Wall Mount Base Escutcheon Plate (3D Circular Ring)
        float baseRadius = 3.5f;
        glColor3f(0.45f, 0.48f, 0.52f);
        glBegin(GL_POLYGON);
        for (int a = 0; a < 360; a += 30)
        {
            float rad = a * 3.14159f / 180.0f;
            glVertex3f(tx + std::cos(rad) * baseRadius, (wy - 9.5f) + std::sin(rad) * baseRadius, tileZFront + 0.1f);
        }
        glEnd();

        // Chrome Ring Front Cap
        glColor3f(0.85f, 0.88f, 0.92f);
        glBegin(GL_POLYGON);
        for (int a = 0; a < 360; a += 30)
        {
            float rad = a * 3.14159f / 180.0f;
            glVertex3f(tx + std::cos(rad) * (baseRadius - 0.8f), (wy - 9.5f) + std::sin(rad) * (baseRadius - 0.8f), tileZFront + 1.2f);
        }
        glEnd();

        // Push Valve Button (Top Spindle)
        glColor3f(0.30f, 0.32f, 0.36f);
        glBegin(GL_QUADS);
        glVertex3f(tx - 1.2f, wy - 12.0f, 1.2f);
        glVertex3f(tx + 1.2f, wy - 12.0f, 1.2f);
        glVertex3f(tx + 1.2f, wy - 10.5f, 1.2f);
        glVertex3f(tx - 1.2f, wy - 10.5f, 1.2f);
        glEnd();

        // 3D Gooseneck Curved Faucet Tube (Extruded Pipe Faces)
        float pipeZ = 2.0f;

        // Pipe Base Segment
        glBegin(GL_QUADS);
        glColor3f(0.55f, 0.58f, 0.63f);
        glVertex3f(tx - 1.2f, wy - 9.5f, pipeZ);
        glVertex3f(tx + 1.2f, wy - 9.5f, pipeZ);
        glVertex3f(tx + 1.2f, wy + 1.0f, pipeZ + 2.0f);
        glVertex3f(tx - 1.2f, wy + 1.0f, pipeZ + 2.0f);

        // Specular Highlight Face
        glColor3f(0.92f, 0.95f, 0.98f);
        glVertex3f(tx - 0.4f, wy - 9.5f, pipeZ + 0.5f);
        glVertex3f(tx + 0.4f, wy - 9.5f, pipeZ + 0.5f);
        glVertex3f(tx + 0.4f, wy + 1.0f, pipeZ + 2.5f);
        glVertex3f(tx - 0.4f, wy + 1.0f, pipeZ + 2.5f);

        // Curved Neck Arch (Outward towards basin)
        glColor3f(0.60f, 0.63f, 0.68f);
        glVertex3f(tx - 1.2f, wy + 1.0f, pipeZ + 2.0f);
        glVertex3f(tx + 1.2f, wy + 1.0f, pipeZ + 2.0f);
        glVertex3f(tx + 4.8f, wy + 4.5f, pipeZ + 6.0f);
        glVertex3f(tx + 2.4f, wy + 4.5f, pipeZ + 6.0f);

        // Downward Nozzle Tip
        glColor3f(0.40f, 0.43f, 0.48f);
        glVertex3f(tx + 2.4f, wy + 4.5f, pipeZ + 6.0f);
        glVertex3f(tx + 4.8f, wy + 4.5f, pipeZ + 6.0f);
        glVertex3f(tx + 4.8f, wy + 7.0f, pipeZ + 6.0f);
        glVertex3f(tx + 2.4f, wy + 7.0f, pipeZ + 6.0f);
        glEnd();

        // --------------------------------------------------------------------
        // 5. TRANSLUCENT 3D WATER STREAM & SPLASH DROPS
        // --------------------------------------------------------------------
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Flowing Water Column
        glColor4f(0.25f, 0.65f, 0.98f, 0.70f);
        glBegin(GL_QUADS);
        glVertex3f(tx + 3.2f, wy + 7.0f, pipeZ + 6.0f);
        glVertex3f(tx + 4.0f, wy + 7.0f, pipeZ + 6.0f);
        glVertex3f(tx + 4.2f, sinkBottomY, sinkZCenter);
        glVertex3f(tx + 3.0f, sinkBottomY, sinkZCenter);
        glEnd();

        // Water Drop (Glassy Tear-drop Polygon)
        glColor4f(0.45f, 0.82f, 1.0f, 0.85f);
        glBegin(GL_POLYGON);
        glVertex3f(tx + 3.6f, wy + 8.5f, pipeZ + 6.1f);
        glVertex3f(tx + 4.4f, wy + 11.5f, pipeZ + 6.1f);
        glVertex3f(tx + 2.8f, wy + 11.5f, pipeZ + 6.1f);
        glEnd();

        glDisable(GL_BLEND);
    }

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































































/* ============================================================================
   FUNCTION: drawDustbin
   Description: Ultra-Realistic 3D Recycling Dustbins (Bio Green & Recycle Blue)
                using pure glVertex3f primitives.
   Positioning: Aligned with Walkway Platform floor level (by = 706.0f).
                Left Bin X = 520.0f, Right Bin X = 1060.0f.
   Depth Span (Z-axis): [-8.0f to 8.0f]
   ============================================================================ */

void drawDustbin()
{
    float binX[] = { 0.0f, 1590.0f };

    for (int i = 0; i < 2; i++)
    {
        float bx = binX[i];
        float by = 742.0f; // Platform floor level

        // --------------------------------------------------------------------
        // 1. 3D GROUND DROP SHADOW
        // --------------------------------------------------------------------
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.08f, 0.08f, 0.08f, 0.38f);
        glBegin(GL_POLYGON);
        glVertex3f(bx - 4.0f,  by + 0.5f, -9.0f);
        glVertex3f(bx + 22.0f, by + 0.5f, -9.0f);
        glVertex3f(bx + 25.0f, by + 0.5f,  9.0f);
        glVertex3f(bx - 1.0f,  by + 0.5f,  9.0f);
        glEnd();
        glDisable(GL_BLEND);

        // --------------------------------------------------------------------
        // 2. REAR WHEELS & AXLE (3D Structural Bin Detail)
        // --------------------------------------------------------------------
        // Metallic Axle Rod
        glColor3f(0.25f, 0.25f, 0.28f);
        glBegin(GL_QUADS);
        glVertex3f(bx + 1.0f, by - 2.0f, -6.5f);
        glVertex3f(bx + 17.0f, by - 2.0f, -6.5f);
        glVertex3f(bx + 17.0f, by - 1.0f, -6.5f);
        glVertex3f(bx + 1.0f, by - 1.0f, -6.5f);
        glEnd();

        // Left & Right Rubber Wheels
        float wheelZ[] = { -7.0f, 7.0f };
        for (int w = 0; w < 2; w++)
        {
            float wz1 = wheelZ[w] - 1.2f;
            float wz2 = wheelZ[w] + 1.2f;

            // Outer Tread Rim
            glColor3f(0.12f, 0.12f, 0.14f);
            glBegin(GL_QUADS);
            glVertex3f(bx + 12.0f, by - 4.5f, wz1);
            glVertex3f(bx + 16.5f, by - 4.5f, wz1);
            glVertex3f(bx + 16.5f, by - 4.5f, wz2);
            glVertex3f(bx + 12.0f, by - 4.5f, wz2);

            glVertex3f(bx + 16.5f, by - 4.5f, wz1);
            glVertex3f(bx + 16.5f, by, wz1);
            glVertex3f(bx + 16.5f, by, wz2);
            glVertex3f(bx + 16.5f, by - 4.5f, wz2);

            glVertex3f(bx + 12.0f, by, wz1);
            glVertex3f(bx + 16.5f, by, wz1);
            glVertex3f(bx + 16.5f, by, wz2);
            glVertex3f(bx + 12.0f, by, wz2);

            glVertex3f(bx + 12.0f, by - 4.5f, wz1);
            glVertex3f(bx + 12.0f, by, wz1);
            glVertex3f(bx + 12.0f, by, wz2);
            glVertex3f(bx + 12.0f, by - 4.5f, wz2);
            glEnd();

            // Wheel Hub Caps
            glColor3f(0.40f, 0.42f, 0.45f);
            glBegin(GL_QUADS);
            glVertex3f(bx + 13.0f, by - 3.8f, (w == 0) ? wz1 - 0.1f : wz2 + 0.1f);
            glVertex3f(bx + 15.5f, by - 3.8f, (w == 0) ? wz1 - 0.1f : wz2 + 0.1f);
            glVertex3f(bx + 15.5f, by - 0.8f, (w == 0) ? wz1 - 0.1f : wz2 + 0.1f);
            glVertex3f(bx + 13.0f, by - 0.8f, (w == 0) ? wz1 - 0.1f : wz2 + 0.1f);
            glEnd();
        }

        // --------------------------------------------------------------------
        // 3. MAIN TAPERED 3D BIN BODY
        // --------------------------------------------------------------------
        // Color Definitions (Base, Highlight, Mid-tone, Shadow)
        float rBase, gBase, bBase;
        float rHigh, gHigh, bHigh;
        float rShad, gShad, bShad;

        if (i == 0)   // Vivid Bio Green
        {
            rBase = 0.12f;
            gBase = 0.68f;
            bBase = 0.28f;
            rHigh = 0.22f;
            gHigh = 0.82f;
            bHigh = 0.38f;
            rShad = 0.06f;
            gShad = 0.42f;
            bShad = 0.16f;
        }
        else         // Vivid Recycle Blue
        {
            rBase = 0.12f;
            gBase = 0.48f;
            bBase = 0.88f;
            rHigh = 0.22f;
            gHigh = 0.62f;
            bHigh = 0.98f;
            rShad = 0.06f;
            gShad = 0.28f;
            bShad = 0.58f;
        }

        // Tapered Coordinates
        float yBot = by;
        float yTop = by - 24.0f;

        float xBotL = bx + 2.0f,  xBotR = bx + 16.0f;
        float xTopL = bx,          xTopR = bx + 18.0f;

        float zFrontNear = 5.5f,  zFrontFar = -5.5f;
        float zTopNear   = 6.5f,  zTopFar   = -6.5f;

        glBegin(GL_QUADS);
        // Front Face (Facing Camera - Main Color)
        glColor3f(rBase, gBase, bBase);
        glVertex3f(xBotL, yBot, zFrontNear);
        glVertex3f(xBotR, yBot, zFrontNear);
        glColor3f(rHigh, gHigh, bHigh);
        glVertex3f(xTopR, yTop, zTopNear);
        glVertex3f(xTopL, yTop, zTopNear);

        // Left Side Face (Highlight Angle)
        glColor3f(rHigh * 0.9f, gHigh * 0.9f, bHigh * 0.9f);
        glVertex3f(xBotL, yBot, zFrontFar);
        glVertex3f(xBotL, yBot, zFrontNear);
        glVertex3f(xTopL, yTop, zTopNear);
        glVertex3f(xTopL, yTop, zTopFar);

        // Right Side Face (Shadow Angle)
        glColor3f(rShad, gShad, bShad);
        glVertex3f(xBotR, yBot, zFrontNear);
        glVertex3f(xBotR, yBot, zFrontFar);
        glVertex3f(xTopR, yTop, zTopFar);
        glVertex3f(xTopR, yTop, zTopNear);

        // Back Face (Deep Shadow)
        glColor3f(rShad * 0.7f, gShad * 0.7f, bShad * 0.7f);
        glVertex3f(xBotR, yBot, zFrontFar);
        glVertex3f(xBotL, yBot, zFrontFar);
        glVertex3f(xTopL, yTop, zTopFar);
        glVertex3f(xTopR, yTop, zTopFar);

        // Bottom Face (Base Shadow)
        glColor3f(0.08f, 0.10f, 0.12f);
        glVertex3f(xBotL, yBot, zFrontNear);
        glVertex3f(xBotR, yBot, zFrontNear);
        glVertex3f(xBotR, yBot, zFrontFar);
        glVertex3f(xBotL, yBot, zFrontFar);
        glEnd();

        // Structural Front Rib Lines (Plastic Mold Detail)
        glColor3f(rShad, gShad, bShad);
        glLineWidth(1.2f);
        glBegin(GL_LINES);
        glVertex3f(bx + 4.0f, yBot - 2.0f, zFrontNear + 0.05f);
        glVertex3f(bx + 3.0f, yTop + 2.0f, zTopNear + 0.05f);

        glVertex3f(bx + 14.0f, yBot - 2.0f, zFrontNear + 0.05f);
        glVertex3f(bx + 15.0f, yTop + 2.0f, zTopNear + 0.05f);
        glEnd();

        // --------------------------------------------------------------------
        // 4. FRONT FOOT PEDAL (Bottom Metal Lever)
        // --------------------------------------------------------------------
        glColor3f(0.25f, 0.25f, 0.28f);
        glBegin(GL_QUADS);
        glVertex3f(bx + 7.0f, by - 0.2f, zFrontNear + 1.8f);
        glVertex3f(bx + 11.0f, by - 0.2f, zFrontNear + 1.8f);
        glVertex3f(bx + 11.0f, by - 1.2f, zFrontNear);
        glVertex3f(bx + 7.0f, by - 1.2f, zFrontNear);
        glEnd();

        // --------------------------------------------------------------------
        // 5. 3D DUSTBIN LID & OVERHANG LIP
        // --------------------------------------------------------------------
        // A. Lid Overhang Lip (Dark Slate Gray Base Rim)
        float yLipTop = by - 28.0f;
        float yLipBot = by - 24.0f;
        float zLipNear = 7.2f, zLipFar = -7.2f;
        float xLipL = bx - 2.0f, xLipR = bx + 20.0f;

        glBegin(GL_QUADS);
        // Lip Front Face
        glColor3f(0.22f, 0.22f, 0.25f);
        glVertex3f(xLipL, yLipBot, zLipNear);
        glVertex3f(xLipR, yLipBot, zLipNear);
        glVertex3f(xLipR, yLipTop, zLipNear);
        glVertex3f(xLipL, yLipTop, zLipNear);

        // Lip Left Face
        glColor3f(0.28f, 0.28f, 0.32f);
        glVertex3f(xLipL, yLipBot, zLipFar);
        glVertex3f(xLipL, yLipBot, zLipNear);
        glVertex3f(xLipL, yLipTop, zLipNear);
        glVertex3f(xLipL, yLipTop, zLipFar);

        // Lip Right Face
        glColor3f(0.16f, 0.16f, 0.18f);
        glVertex3f(xLipR, yLipBot, zLipNear);
        glVertex3f(xLipR, yLipBot, zLipFar);
        glVertex3f(xLipR, yLipTop, zLipFar);
        glVertex3f(xLipR, yLipTop, zLipNear);

        // Lip Top Face Rim
        glColor3f(0.32f, 0.32f, 0.36f);
        glVertex3f(xLipL, yLipTop, zLipFar);
        glVertex3f(xLipR, yLipTop, zLipFar);
        glVertex3f(xLipR, yLipTop, zLipNear);
        glVertex3f(xLipL, yLipTop, zLipNear);
        glEnd();

        // B. Lid Raised Top Dome
        float yDomeTop = by - 31.0f;
        float xDomeL = bx + 1.0f, xDomeR = bx + 17.0f;
        float zDomeNear = 5.5f, zDomeFar = -5.5f;

        glBegin(GL_QUADS);
        // Dome Front Slope
        glColor3f(0.35f, 0.35f, 0.40f);
        glVertex3f(xLipL + 1.5f, yLipTop, zLipNear - 0.5f);
        glVertex3f(xLipR - 1.5f, yLipTop, zLipNear - 0.5f);
        glVertex3f(xDomeR - 1.0f, yDomeTop, zDomeNear);
        glVertex3f(xDomeL + 1.0f, yDomeTop, zDomeNear);

        // Dome Top Roof
        glColor3f(0.42f, 0.42f, 0.46f);
        glVertex3f(xDomeL + 1.0f, yDomeTop, zDomeNear);
        glVertex3f(xDomeR - 1.0f, yDomeTop, zDomeNear);
        glVertex3f(xDomeR - 1.0f, yDomeTop, zDomeFar);
        glVertex3f(xDomeL + 1.0f, yDomeTop, zDomeFar);

        // Dome Left Slope
        glColor3f(0.38f, 0.38f, 0.42f);
        glVertex3f(xLipL, yLipTop, zLipFar);
        glVertex3f(xLipL, yLipTop, zLipNear);
        glVertex3f(xDomeL + 1.0f, yDomeTop, zDomeNear);
        glVertex3f(xDomeL + 1.0f, yDomeTop, zDomeFar);

        // Dome Right Slope
        glColor3f(0.20f, 0.20f, 0.24f);
        glVertex3f(xLipR, yLipTop, zLipNear);
        glVertex3f(xLipR, yLipTop, zLipFar);
        glVertex3f(xDomeR - 1.0f, yDomeTop, zDomeFar);
        glVertex3f(xDomeR - 1.0f, yDomeTop, zDomeNear);
        glEnd();

        // C. Lid Top Grab Handle (3D Bar)
        float yHandleTop = by - 33.5f;
        float xHndL = bx + 6.0f, xHndR = bx + 12.0f;
        float zHndNear = 1.2f, zHndFar = -1.2f;

        glBegin(GL_QUADS);
        // Handle Top Face
        glColor3f(0.18f, 0.18f, 0.20f);
        glVertex3f(xHndL, yHandleTop, zHndFar);
        glVertex3f(xHndR, yHandleTop, zHndFar);
        glVertex3f(xHndR, yHandleTop, zHndNear);
        glVertex3f(xHndL, yHandleTop, zHndNear);

        // Handle Front Face
        glColor3f(0.12f, 0.12f, 0.14f);
        glVertex3f(xHndL, yDomeTop, zHndNear);
        glVertex3f(xHndR, yDomeTop, zHndNear);
        glVertex3f(xHndR, yHandleTop, zHndNear);
        glVertex3f(xHndL, yHandleTop, zHndNear);

        // Handle Left Post
        glVertex3f(xHndL, yDomeTop, zHndFar);
        glVertex3f(xHndL, yDomeTop, zHndNear);
        glVertex3f(xHndL, yHandleTop, zHndNear);
        glVertex3f(xHndL, yHandleTop, zHndFar);

        // Handle Right Post
        glVertex3f(xHndR, yDomeTop, zHndNear);
        glVertex3f(xHndR, yDomeTop, zHndFar);
        glVertex3f(xHndR, yHandleTop, zHndFar);
        glVertex3f(xHndR, yHandleTop, zHndNear);
        glEnd();

        // --------------------------------------------------------------------
        // 6. 3D RECYCLE / BIO EMBLEM (Extruded Front Symbol)
        // --------------------------------------------------------------------
        float zSymbol = zFrontNear + 0.15f;

        // White Outer Triangle
        glColor3f(0.96f, 0.98f, 1.0f);
        glBegin(GL_TRIANGLES);
        glVertex3f(bx + 9.0f,  by - 18.0f, zSymbol);
        glVertex3f(bx + 4.5f,  by - 7.5f,  zSymbol);
        glVertex3f(bx + 13.5f, by - 7.5f,  zSymbol);
        glEnd();

        // Inner Cutout Triangle (Body Color Matching)
        glColor3f(rBase, gBase, bBase);
        glBegin(GL_TRIANGLES);
        glVertex3f(bx + 9.0f,  by - 15.5f, zSymbol + 0.05f);
        glVertex3f(bx + 6.5f,  by - 9.5f,  zSymbol + 0.05f);
        glVertex3f(bx + 11.5f, by - 9.5f,  zSymbol + 0.05f);
        glEnd();

        // Arrow Accents / Center Symbol Core
        glColor3f(0.96f, 0.98f, 1.0f);
        glBegin(GL_TRIANGLES);
        glVertex3f(bx + 9.0f,  by - 14.0f, zSymbol + 0.1f);
        glVertex3f(bx + 7.5f,  by - 11.0f, zSymbol + 0.1f);
        glVertex3f(bx + 10.5f, by - 11.0f, zSymbol + 0.1f);
        glEnd();
    }

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
    for (float y = topY + 6.0f; y < bottomY - curbHeight; y += 6.0f)
    {
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
    for (float y = topY; y < bottomY - curbHeight; y += 6.0f)
    {
        float xShift = (rowCounter % 2 == 0) ? 0.0f : 10.0f;

        // Left Walkway Grid
        for (float x = xShift; x < leftPillarX; x += 20.0f)
        {
            glVertex2f(x, y);
            glVertex2f(x, y + 6.0f);
        }
        // Right Walkway Grid
        for (float x = rightPillarX + xShift; x < 1600.0f; x += 20.0f)
        {
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
    for (float y = topY + 5.0f; y < bottomY; y += 5.0f)
    {
        glVertex2f(leftPillarX + 2.0f, y);
        glVertex2f(rightPillarX - 2.0f, y);
    }
    glEnd();

    // ------------------------------------------------------------------------
    // 4. 3D FRONT CURBSTONES (Border Blocks along Road Edge)
    // ------------------------------------------------------------------------
    // Alternating Dual-Tone Concrete Curb Blocks
    for (float x = 0.0f; x < 1600.0f; x += 40.0f)
    {
        // Skip Curb for Gate Entrance Ramp Area
        if (x >= leftPillarX - 10.0f && x < rightPillarX) continue;

        // Alternate Block Color (Light Grey / Charcoal Grey Concrete)
        if (((int)(x / 40.0f)) % 2 == 0)
        {
            glColor3f(0.80f, 0.80f, 0.78f); // Light Concrete Block
        }
        else
        {
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
    for (float x = 0.0f; x <= 1600.0f; x += 40.0f)
    {
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
    for (float x = 0.0f; x < 1600.0f; x += blockWidth)
    {
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

    for (float x = 0.0f; x < 1600.0f; x += (dashWidth + gapWidth))
    {

        // Skip divider inside Speed Breaker or Zebra Crossing zone
        if ((x + dashWidth > speedBreakerStart && x < speedBreakerEnd) ||
                (x + dashWidth > zebraStart && x < zebraEnd))
        {
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

    for (int i = 0; i < numStripes; i++)
    {
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
    for (int i = 0; i < numSegments; i++)
    {
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


















/* ============================================================================
   FUNCTION: drawTrafficSign
   Description: Ultra-Realistic 3D Speed Hump Warning Sign using pure glVertex3f.
   Position Preserved: Center X = 620.0f, Ground Y = 712.0f, Top Vertex Y = 600.0f.
   Depth Span (Z-axis): [-8.0f to 8.0f]
   ============================================================================ */

void drawTrafficSign()
{
    float sx = 1200.0f;
    float sy = 742.0f;
    float boardY = sy - 80.0f; // 632.0f

    // ------------------------------------------------------------------------
    // 1. 3D GROUND SHADOW
    // ------------------------------------------------------------------------
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.08f, 0.08f, 0.08f, 0.35f);
    glBegin(GL_POLYGON);
    glVertex3f(sx - 10.0f, sy + 0.5f, -8.0f);
    glVertex3f(sx + 10.0f, sy + 0.5f, -8.0f);
    glVertex3f(sx + 14.0f, sy + 0.5f,  8.0f);
    glVertex3f(sx - 6.0f,  sy + 0.5f,  8.0f);
    glEnd();
    glDisable(GL_BLEND);

    // ------------------------------------------------------------------------
    // 2. 3D HEAVY METAL BASE SUPPORT PLATE & BOLTS
    // ------------------------------------------------------------------------
    float baseWidth = 6.0f;
    float baseTopY = sy - 3.0f; // 709.0f
    float baseBotY = sy;        // 712.0f
    float baseZ1 = -5.0f, baseZ2 = 5.0f;

    // Base Plate Faces
    glBegin(GL_QUADS);
    // Top Face
    glColor3f(0.35f, 0.38f, 0.42f);
    glVertex3f(sx - baseWidth, baseTopY, baseZ1);
    glVertex3f(sx + baseWidth, baseTopY, baseZ1);
    glVertex3f(sx + baseWidth, baseTopY, baseZ2);
    glVertex3f(sx - baseWidth, baseTopY, baseZ2);

    // Front Face
    glColor3f(0.25f, 0.27f, 0.30f);
    glVertex3f(sx - baseWidth, baseTopY, baseZ2);
    glVertex3f(sx + baseWidth, baseTopY, baseZ2);
    glVertex3f(sx + baseWidth, baseBotY, baseZ2);
    glVertex3f(sx - baseWidth, baseBotY, baseZ2);

    // Back Face
    glColor3f(0.18f, 0.20f, 0.22f);
    glVertex3f(sx - baseWidth, baseTopY, baseZ1);
    glVertex3f(sx + baseWidth, baseTopY, baseZ1);
    glVertex3f(sx + baseWidth, baseBotY, baseZ1);
    glVertex3f(sx - baseWidth, baseBotY, baseZ1);

    // Left Face
    glColor3f(0.20f, 0.22f, 0.25f);
    glVertex3f(sx - baseWidth, baseTopY, baseZ1);
    glVertex3f(sx - baseWidth, baseTopY, baseZ2);
    glVertex3f(sx - baseWidth, baseBotY, baseZ2);
    glVertex3f(sx - baseWidth, baseBotY, baseZ1);

    // Right Face
    glColor3f(0.28f, 0.30f, 0.33f);
    glVertex3f(sx + baseWidth, baseTopY, baseZ1);
    glVertex3f(sx + baseWidth, baseTopY, baseZ2);
    glVertex3f(sx + baseWidth, baseBotY, baseZ2);
    glVertex3f(sx + baseWidth, baseBotY, baseZ1);
    glEnd();

    // 4 Corner 3D Hexagonal Steel Base Bolts
    float boltOffsetsX[] = { -4.2f, 4.2f, -4.2f, 4.2f };
    float boltOffsetsZ[] = { -3.2f, -3.2f, 3.2f, 3.2f };
    float boltSize = 0.8f;
    float boltHeight = 0.6f;

    for (int i = 0; i < 4; i++)
    {
        float bx = sx + boltOffsetsX[i];
        float bz = boltOffsetsZ[i];
        float by1 = baseTopY - boltHeight;

        glBegin(GL_QUADS);
        // Top Face of Bolt
        glColor3f(0.85f, 0.88f, 0.92f);
        glVertex3f(bx - boltSize, by1, bz - boltSize);
        glVertex3f(bx + boltSize, by1, bz - boltSize);
        glVertex3f(bx + boltSize, by1, bz + boltSize);
        glVertex3f(bx - boltSize, by1, bz + boltSize);

        // Front Face
        glColor3f(0.65f, 0.68f, 0.72f);
        glVertex3f(bx - boltSize, by1, bz + boltSize);
        glVertex3f(bx + boltSize, by1, bz + boltSize);
        glVertex3f(bx + boltSize, baseTopY, bz + boltSize);
        glVertex3f(bx - boltSize, baseTopY, bz + boltSize);

        // Right Face
        glColor3f(0.55f, 0.58f, 0.62f);
        glVertex3f(bx + boltSize, by1, bz - boltSize);
        glVertex3f(bx + boltSize, by1, bz + boltSize);
        glVertex3f(bx + boltSize, baseTopY, bz + boltSize);
        glVertex3f(bx + boltSize, baseTopY, bz - boltSize);
        glEnd();
    }

    // ------------------------------------------------------------------------
    // 3. 3D OCTAGONAL METALLIC STEEL POLE
    // ------------------------------------------------------------------------
    float poleTopY = sy - 80.0f; // 632.0f
    float poleBotY = sy - 3.0f;  // 709.0f

    glBegin(GL_QUADS);
    // Front Face
    glColor3f(0.70f, 0.73f, 0.78f);
    glVertex3f(sx - 1.8f, poleTopY, 2.0f);
    glVertex3f(sx + 1.8f, poleTopY, 2.0f);
    glVertex3f(sx + 1.8f, poleBotY, 2.0f);
    glVertex3f(sx - 1.8f, poleBotY, 2.0f);

    // Front-Right Specular Highlight Face
    glColor3f(0.85f, 0.88f, 0.92f);
    glVertex3f(sx + 1.8f, poleTopY, 2.0f);
    glVertex3f(sx + 2.5f, poleTopY, 0.8f);
    glVertex3f(sx + 2.5f, poleBotY, 0.8f);
    glVertex3f(sx + 1.8f, poleBotY, 2.0f);

    // Front-Left Angled Face
    glColor3f(0.55f, 0.58f, 0.63f);
    glVertex3f(sx - 2.5f, poleTopY, 0.8f);
    glVertex3f(sx - 1.8f, poleTopY, 2.0f);
    glVertex3f(sx - 1.8f, poleBotY, 2.0f);
    glVertex3f(sx - 2.5f, poleBotY, 0.8f);

    // Right Side Face
    glColor3f(0.50f, 0.53f, 0.58f);
    glVertex3f(sx + 2.5f, poleTopY, 0.8f);
    glVertex3f(sx + 2.5f, poleTopY, -0.8f);
    glVertex3f(sx + 2.5f, poleBotY, -0.8f);
    glVertex3f(sx + 2.5f, poleBotY, 0.8f);

    // Left Side Face
    glColor3f(0.40f, 0.43f, 0.48f);
    glVertex3f(sx - 2.5f, poleTopY, -0.8f);
    glVertex3f(sx - 2.5f, poleTopY, 0.8f);
    glVertex3f(sx - 2.5f, poleBotY, 0.8f);
    glVertex3f(sx - 2.5f, poleBotY, -0.8f);

    // Back Face (Dark Shadow)
    glColor3f(0.25f, 0.28f, 0.32f);
    glVertex3f(sx - 1.8f, poleTopY, -2.0f);
    glVertex3f(sx + 1.8f, poleTopY, -2.0f);
    glVertex3f(sx + 1.8f, poleBotY, -2.0f);
    glVertex3f(sx - 1.8f, poleBotY, -2.0f);
    glEnd();

    // ------------------------------------------------------------------------
    // 4. 3D MOUNTING CLAMPS / BRACKETS
    // ------------------------------------------------------------------------
    float clampYs[] = { boardY - 5.0f, boardY - 20.0f };
    float clampH = 3.0f;

    for (int i = 0; i < 2; i++)
    {
        float cy1 = clampYs[i];
        float cy2 = cy1 + clampH;

        glBegin(GL_QUADS);
        // Front Face of Clamp
        glColor3f(0.32f, 0.32f, 0.35f);
        glVertex3f(sx - 3.5f, cy1, 2.6f);
        glVertex3f(sx + 3.5f, cy1, 2.6f);
        glVertex3f(sx + 3.5f, cy2, 2.6f);
        glVertex3f(sx - 3.5f, cy2, 2.6f);

        // Left Side Clamp Loop
        glColor3f(0.18f, 0.18f, 0.20f);
        glVertex3f(sx - 3.5f, cy1, -2.6f);
        glVertex3f(sx - 3.5f, cy1, 2.6f);
        glVertex3f(sx - 3.5f, cy2, 2.6f);
        glVertex3f(sx - 3.5f, cy2, -2.6f);

        // Right Side Clamp Loop
        glVertex3f(sx + 3.5f, cy1, 2.6f);
        glVertex3f(sx + 3.5f, cy1, -2.6f);
        glVertex3f(sx + 3.5f, cy2, -2.6f);
        glVertex3f(sx + 3.5f, cy2, 2.6f);
        glEnd();
    }

    // ------------------------------------------------------------------------
    // 5. 3D RED OUTER WARNING TRIANGLE (Prism Plate with Depth)
    // ------------------------------------------------------------------------
    float tTopX = sx,          tTopY = boardY - 32.0f; // 600.0f
    float tLeftX = sx - 22.0f, tLeftY = boardY + 5.0f;  // 637.0f
    float tRightX = sx + 22.0f, tRightY = boardY + 5.0f; // 637.0f

    float zFront = 3.0f;
    float zBack = 1.0f;

    glBegin(GL_TRIANGLES);
    // Front Red Face
    glColor3f(0.85f, 0.10f, 0.10f);
    glVertex3f(tTopX, tTopY, zFront);
    glVertex3f(tLeftX, tLeftY, zFront);
    glVertex3f(tRightX, tRightY, zFront);

    // Back Red Face
    glColor3f(0.45f, 0.05f, 0.05f);
    glVertex3f(tTopX, tTopY, zBack);
    glVertex3f(tRightX, tRightY, zBack);
    glVertex3f(tLeftX, tLeftY, zBack);
    glEnd();

    // 3D Rim Thickness Edges
    glBegin(GL_QUADS);
    // Bottom Edge
    glColor3f(0.55f, 0.05f, 0.05f);
    glVertex3f(tLeftX, tLeftY, zFront);
    glVertex3f(tRightX, tRightY, zFront);
    glVertex3f(tRightX, tRightY, zBack);
    glVertex3f(tLeftX, tLeftY, zBack);

    // Left Slanted Edge (Highlight)
    glColor3f(0.95f, 0.18f, 0.18f);
    glVertex3f(tTopX, tTopY, zFront);
    glVertex3f(tLeftX, tLeftY, zFront);
    glVertex3f(tLeftX, tLeftY, zBack);
    glVertex3f(tTopX, tTopY, zBack);

    // Right Slanted Edge (Shadow)
    glColor3f(0.60f, 0.06f, 0.06f);
    glVertex3f(tTopX, tTopY, zFront);
    glVertex3f(tRightX, tRightY, zFront);
    glVertex3f(tRightX, tRightY, zBack);
    glVertex3f(tTopX, tTopY, zBack);
    glEnd();

    // ------------------------------------------------------------------------
    // 6. 3D INNER WHITE REFLECTIVE TRIANGLE
    // ------------------------------------------------------------------------
    float wTopX = sx,          wTopY = boardY - 25.0f;
    float wLeftX = sx - 16.0f, wLeftY = boardY + 2.0f;
    float wRightX = sx + 16.0f, wRightY = boardY + 2.0f;
    float zWhite = 3.1f;

    glBegin(GL_TRIANGLES);
    glColor3f(0.96f, 0.96f, 0.98f);
    glVertex3f(wTopX, wTopY, zWhite);
    glVertex3f(wLeftX, wLeftY, zWhite);
    glVertex3f(wRightX, wRightY, zWhite);
    glEnd();

    // ------------------------------------------------------------------------
    // 7. 3D SPEED HUMP SYMBOL (Extruded Geometry)
    // ------------------------------------------------------------------------
    float zIcon = 3.25f;

    glColor3f(0.12f, 0.12f, 0.14f);

    // Flat Base Bar
    glBegin(GL_QUADS);
    glVertex3f(sx - 11.0f, boardY - 1.0f, zIcon);
    glVertex3f(sx + 11.0f, boardY - 1.0f, zIcon);
    glVertex3f(sx + 11.0f, boardY + 1.0f, zIcon);
    glVertex3f(sx - 11.0f, boardY + 1.0f, zIcon);
    glEnd();

    // Curved Hump Structure
    glBegin(GL_POLYGON);
    glVertex3f(sx - 9.0f, boardY - 1.0f, zIcon);
    glVertex3f(sx - 5.0f, boardY - 1.0f, zIcon);
    glVertex3f(sx - 3.0f, boardY - 8.0f, zIcon);
    glVertex3f(sx + 3.0f, boardY - 8.0f, zIcon);
    glVertex3f(sx + 5.0f, boardY - 1.0f, zIcon);
    glVertex3f(sx + 9.0f, boardY - 1.0f, zIcon);
    glEnd();

    // 3D Bevel Edge Outline
    glColor3f(0.35f, 0.35f, 0.38f);
    glLineWidth(1.2f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(sx - 9.0f, boardY - 1.0f, zIcon + 0.05f);
    glVertex3f(sx - 5.0f, boardY - 1.0f, zIcon + 0.05f);
    glVertex3f(sx - 3.0f, boardY - 8.0f, zIcon + 0.05f);
    glVertex3f(sx + 3.0f, boardY - 8.0f, zIcon + 0.05f);
    glVertex3f(sx + 5.0f, boardY - 1.0f, zIcon + 0.05f);
    glVertex3f(sx + 9.0f, boardY - 1.0f, zIcon + 0.05f);
    glEnd();
    glLineWidth(1.0f);
}
















































/* ---- People ---- */
// ----------------------------------------------------------------------------
// EXCITED STUDENT GATHERING FOR CRICKET (X: 150 - 500, Y: 525 - 600)
// Scaled 1.25x, Spaced out (6 Students), holding Cricket Bat/Ball
// ----------------------------------------------------------------------------

void drawStudent()
{
    float animTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

    struct StudentData
    {
        float x;
        float y;
        float dir;
        int shirtType;
        int propType;     // 0: None (Cheering), 1: Cricket Bat, 2: Leather Ball
        float phaseShift;
    };

    // 6 Students spaced out within X [150, 500] and Y [525, 600]
    StudentData students[6] =
    {
        { 170.0f, 540.0f,  1.0f, 0, 1, 0.0f }, // Holding Cricket Bat
        { 230.0f, 530.0f,  1.0f, 1, 0, 0.8f }, // Cheering / Jumping
        { 290.0f, 555.0f,  1.0f, 0, 2, 1.5f }, // Holding Leather Ball
        { 350.0f, 535.0f, -1.0f, 2, 0, 2.2f }, // Raising arms
        { 410.0f, 560.0f, -1.0f, 1, 1, 0.4f }, // Resting Bat on shoulder
        { 470.0f, 545.0f, -1.0f, 0, 2, 1.9f }  // Tossing Ball
    };

    for (int s = 0; s < 6; s++)
    {
        float sx = students[s].x;
        float sy = students[s].y;
        float dir = students[s].dir;
        float t = animTime * 3.5f + students[s].phaseShift;

        // Dynamic jump & excitement motion
        float bounceY = fabsf(sinf(t)) * 3.2f;
        float waveArm = sinf(t * 2.0f) * 6.0f;
        float bodyLean = cosf(t) * 2.0f;

        glPushMatrix();
        glTranslatef(sx, sy - bounceY, 0.0f);
        glScalef(1.25f, 1.25f, 1.0f);

        // Light Ground Shadow
        glColor4f(0.0f, 0.0f, 0.0f, 0.10f);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 12; i++)
        {
            float rad = i * 2.0f * 3.14159f / 12.0f;
            glVertex2f(cosf(rad) * (3.8f + bounceY * 0.2f), 0.8f + sinf(rad) * 0.9f);
        }
        glEnd();

        glRotatef(bodyLean, 0.0f, 0.0f, 1.0f);

        // 1. Shoes / Cricket Spikes
        glColor3f(0.85f, 0.85f, 0.90f);
        glRectf(-2.4f, -1.2f, 0.2f, 0.5f);
        glRectf( 0.2f, -1.2f, 2.4f, 0.5f);

        // 2. Socks
        glColor3f(0.95f, 0.95f, 0.95f);
        glRectf(-1.8f, -2.8f, -0.2f, -1.2f);
        glRectf( 0.2f, -2.8f,  1.8f, -1.2f);

        // 3. Legs
        glColor3f(0.90f, 0.72f, 0.58f);
        glRectf(-1.6f, -6.5f, -0.3f, -2.8f);
        glRectf( 0.3f, -6.5f,  1.6f, -2.8f);

        // 4. Uniform Shorts (Navy)
        glColor3f(0.12f, 0.20f, 0.45f);
        glRectf(-2.2f, -10.0f, 2.2f, -6.5f);

        // 5. Shirt Colors
        if (students[s].shirtType == 0)      glColor3f(0.95f, 0.95f, 0.98f);
        else if (students[s].shirtType == 1) glColor3f(0.90f, 0.25f, 0.25f);
        else                                 glColor3f(0.20f, 0.65f, 0.35f);

        glRectf(-2.5f, -17.5f, 2.5f, -10.0f);

        // V-Neck Collar
        glColor3f(0.12f, 0.20f, 0.45f);
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, -14.5f);
        glVertex2f(-1.2f, -17.5f);
        glVertex2f( 1.2f, -17.5f);
        glEnd();

        // 6. Dynamic Arms & Cricket Props
        glColor3f(0.90f, 0.72f, 0.58f);
        glLineWidth(2.5f);

        if (students[s].propType == 1)   // CRICKET BAT
        {
            glBegin(GL_LINES);
            glVertex2f(dir * 2.5f, -16.0f);
            glVertex2f(dir * 5.0f, -12.0f + waveArm * 0.2f);
            glEnd();

            // Cricket Bat Wood
            glColor3f(0.82f, 0.62f, 0.35f);
            glRectf(dir * 5.0f, -20.0f + waveArm * 0.2f, dir * 6.5f, -9.0f + waveArm * 0.2f);
            // Rubber Handle Grip
            glColor3f(0.85f, 0.15f, 0.15f);
            glRectf(dir * 5.2f, -9.0f + waveArm * 0.2f, dir * 6.3f, -5.5f + waveArm * 0.2f);
        }
        else if (students[s].propType == 2)   // LEATHER BALL
        {
            float ballToss = fabsf(sinf(t * 3.0f)) * 5.0f;
            glBegin(GL_LINES);
            glVertex2f(dir * 2.5f, -16.0f);
            glVertex2f(dir * 4.5f, -18.0f - ballToss * 0.3f);
            glEnd();

            // Red Cricket Ball
            glColor3f(0.85f, 0.12f, 0.12f);
            glBegin(GL_POLYGON);
            for (int i = 0; i < 12; i++)
            {
                float rad = i * 2.0f * 3.14159f / 12.0f;
                glVertex2f(dir * 4.5f + cosf(rad) * 1.3f, -19.5f - ballToss + sinf(rad) * 1.3f);
            }
            glEnd();
        }
        else   // CHEERING HANDS UP
        {
            glBegin(GL_LINES);
            glVertex2f(-2.5f, -16.0f);
            glVertex2f(-5.0f, -22.0f - waveArm * 0.4f);
            glVertex2f( 2.5f, -16.0f);
            glVertex2f( 5.0f, -22.0f + waveArm * 0.4f);
            glEnd();
        }

        // 7. Head & Happy Expression
        float headY = -20.2f;
        glColor3f(0.90f, 0.72f, 0.58f);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 16; i++)
        {
            float rad = i * 2.0f * 3.14159f / 16.0f;
            glVertex2f(cosf(rad) * 2.4f, headY + sinf(rad) * 2.4f);
        }
        glEnd();

        // Eye Dots
        glColor3f(0.10f, 0.10f, 0.10f);
        glPointSize(2.2f);
        glBegin(GL_POINTS);
        glVertex2f(dir * 1.1f, headY - 0.2f);
        glEnd();

        // Smile
        glLineWidth(1.5f);
        glBegin(GL_LINE_STRIP);
        glVertex2f(dir * 0.2f, headY + 0.8f);
        glVertex2f(dir * 1.0f, headY + 1.2f);
        glVertex2f(dir * 1.6f, headY + 0.8f);
        glEnd();

        // Hair Cap
        glColor3f(0.15f, 0.10f, 0.05f);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 9; i++)
        {
            float rad = 3.14159f + i * 3.14159f / 9.0f;
            glVertex2f(cosf(rad) * 2.5f, headY + sinf(rad) * 2.4f);
        }
        glEnd();

        glPopMatrix();
    }

    glutPostRedisplay();
}


// ----------------------------------------------------------------------------
// INSTRUCTING CRICKET COACHES (X: 150 - 500, Y: 525 - 600)
// Scaled 1.25x, pointing towards pitch, holding tactical board
// ----------------------------------------------------------------------------

void drawTeacher()
{
    float animTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

    struct TeacherData
    {
        float x;
        float y;
        float dir;
        float phase;
        bool isHeadTeacher;
    };

    TeacherData teachers[2] =
    {
        { 380.0f, 580.0f, -1.0f, 0.0f, true },  // Head Coach
        { 220.0f, 590.0f,  1.0f, 1.8f, false }  // Assistant Coach
    };

    for (int t = 0; t < 2; t++)
    {
        float tx = teachers[t].x;
        float ty = teachers[t].y;
        float dir = teachers[t].dir;
        float phase = animTime * 2.2f + teachers[t].phase;

        float pointAngle = sinf(phase) * 5.0f;
        float bodyBreath = cosf(phase * 0.8f) * 0.7f;

        glPushMatrix();
        glTranslatef(tx, ty + bodyBreath, 0.0f);
        glScalef(1.25f, 1.25f, 1.0f);

        // Light Ground Shadow
        glColor4f(0.0f, 0.0f, 0.0f, 0.10f);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 12; i++)
        {
            float rad = i * 2.0f * 3.14159f / 12.0f;
            glVertex2f(cosf(rad) * 4.5f, 0.8f + sinf(rad) * 1.1f);
        }
        glEnd();

        // 1. Sports Shoes
        glColor3f(0.15f, 0.12f, 0.10f);
        glRectf(-2.6f, -1.5f, 0.2f, 0.5f);
        glRectf( 0.2f, -1.5f, 2.6f, 0.5f);

        // 2. Track Pants
        if (teachers[t].isHeadTeacher) glColor3f(0.18f, 0.22f, 0.28f);
        else                           glColor3f(0.15f, 0.18f, 0.35f);

        glRectf(-2.0f, -10.5f, -0.2f, -1.5f);
        glRectf( 0.2f, -10.5f,  2.0f, -1.5f);

        // 3. Track Suit Jacket
        if (teachers[t].isHeadTeacher) glColor3f(0.20f, 0.45f, 0.75f);
        else                           glColor3f(0.85f, 0.85f, 0.88f);

        glRectf(-2.8f, -21.0f, 2.8f, -11.5f);

        // Whistle Strap
        glColor3f(0.85f, 0.15f, 0.15f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glVertex2f(-1.0f, -20.5f);
        glVertex2f( 0.0f, -16.0f);
        glVertex2f( 1.0f, -20.5f);
        glVertex2f( 0.0f, -16.0f);
        glEnd();

        // Whistle
        glColor3f(0.85f, 0.85f, 0.90f);
        glPointSize(3.5f);
        glBegin(GL_POINTS);
        glVertex2f(0.0f, -16.0f);
        glEnd();

        // 4. Tactical Clipboard
        glColor3f(0.55f, 0.35f, 0.15f);
        glRectf(-dir * 4.8f - 1.6f, -17.5f, -dir * 4.8f + 1.6f, -12.0f);
        glColor3f(0.95f, 0.95f, 0.95f);
        glRectf(-dir * 4.8f - 1.3f, -17.0f, -dir * 4.8f + 1.3f, -12.5f);

        // 5. Pointing Arm
        glColor3f(0.88f, 0.70f, 0.56f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        glVertex2f(dir * 2.8f, -19.0f);
        glVertex2f(dir * (8.5f + pointAngle * 0.2f), -16.0f + pointAngle);
        glEnd();

        // 6. Head & Features
        float headY = -24.0f;
        glColor3f(0.88f, 0.70f, 0.56f);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 16; i++)
        {
            float rad = i * 2.0f * 3.14159f / 16.0f;
            glVertex2f(cosf(rad) * 2.6f, headY + sinf(rad) * 2.6f);
        }
        glEnd();

        // Sunglasses / Glasses
        glColor3f(0.10f, 0.10f, 0.12f);
        glLineWidth(1.8f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(dir * 0.5f, headY - 0.8f);
        glVertex2f(dir * 2.2f, headY - 0.8f);
        glVertex2f(dir * 2.2f, headY + 0.8f);
        glVertex2f(dir * 0.5f, headY + 0.8f);
        glEnd();

        // Sports Cap
        if (teachers[t].isHeadTeacher)
        {
            glColor3f(0.18f, 0.22f, 0.28f);
            glRectf(-2.8f, headY - 0.5f, 2.8f, headY + 2.8f);
            glLineWidth(3.2f);
            glBegin(GL_LINES);
            glVertex2f(dir * 0.0f, headY + 0.2f);
            glVertex2f(dir * 5.2f, headY + 0.2f);
            glEnd();
        }
        else
        {
            glColor3f(0.25f, 0.18f, 0.12f);
            glBegin(GL_POLYGON);
            for (int i = 0; i < 10; i++)
            {
                float rad = 3.14159f + i * 3.14159f / 10.0f;
                glVertex2f(cosf(rad) * 2.8f, headY + sinf(rad) * 2.6f);
            }
            glEnd();
        }

        glPopMatrix();
    }

    glutPostRedisplay();
}




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
void drawBusCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Timer Function with Speed Breaker Physics & Fixed X-Axis Boundary (1600f Screen)
void schoolBusTimer(int value)
{
    float currentSpeed = 1.6f; // Slow, natural school bus speed

    // Rear wheel hits speed breaker when schoolBusX reaches around 485.0f
    float rearWheelOnBreakerX = 485.0f;

    // 1. Front Wheel Bump (Light Bounce)
    if (schoolBusX >= 340.0f && schoolBusX < 380.0f)
    {
        float frontBump = (schoolBusX - 340.0f) / 40.0f;
        schoolBusY_Offset = -sinf(frontBump * 3.14159f) * 3.5f;
    }
    // 2. STOP EXACTLY WHEN REAR WHEEL IS ON SPEED BREAKER
    else if (schoolBusX >= rearWheelOnBreakerX - 10.0f && schoolBusX <= rearWheelOnBreakerX + 15.0f && !isBusPaused)
    {
        if (busPauseCounter < 25)   // Stop for ~0.4s
        {
            currentSpeed = 0.0f;    // FULL STOP
            busPauseCounter++;
            schoolBusY_Offset = -7.0f; // Height jump on bump
        }
        else
        {
            isBusPaused = true;     // Resume driving
            currentSpeed = 1.0f;
        }
    }
    // 3. Coming Down to Straight Road (Settle Bounce)
    else if (schoolBusX > rearWheelOnBreakerX + 15.0f && schoolBusX <= rearWheelOnBreakerX + 80.0f)
    {
        currentSpeed = 1.2f;
        float settleProgress = (schoolBusX - (rearWheelOnBreakerX + 15.0f)) / 65.0f;

        schoolBusY_Offset = -sinf(settleProgress * 3.14159f) * 5.0f + sinf(settleProgress * 6.28318f) * 1.5f;
    }
    else
    {
        currentSpeed = 1.6f;
        schoolBusY_Offset = 0.0f; // Back to normal flat road
    }

    // Update position and wheel angle
    schoolBusX += currentSpeed;
    if (currentSpeed > 0.0f)
    {
        schoolBusWheelAngle -= currentSpeed * 4.0f;
    }

    // FIXED: Reset only AFTER the entire bus completely crosses 1600f screen width
    // Bus length is ~212 units, so 1850.0f ensures it smoothly leaves the visible area
    if (schoolBusX > 1850.0f)
    {
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
void drawBusPassengers(float baseX, float baseY)
{
    // 1. Draw 5 Students Sitting by the Windows
    for (int i = 0; i < 5; i++)
    {
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
    for (int i = 0; i < 12; i++)
    {
        float rad = i * 2.0f * 3.14159f / 12.0f;
        glVertex2f(dx + 6.0f + cos(rad) * 4.0f, dy + 5.0f + sin(rad) * 4.0f);
    }
    glEnd();
}

// ---------------------------------------------------------
// MAIN SCHOOL BUS DRAW FUNCTION
// ---------------------------------------------------------
void drawSchoolBus()
{
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
    for (int i = 0; i < 5; i++)
    {
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
/// BRTC BUS WITH SOUND EFFECTS
#include <GL/glut.h>
#include <math.h>
#include <windows.h>   // Windows API support for sound
#include <mmsystem.h>  // Multimedia functions support

// Link Windows Multimedia Library
#pragma comment(lib, "winmm.lib")

// Global position variables
float busX = 1200.0f;
float busWheelAngle = 0.0f;
bool isTimerStarted = false;

// Sound State Control
bool isSoundPlaying = false;

// CNG position set strictly behind Bus & adjusted Y position
float cngX = 1800.0f; // Bus baseline distance + 600 units gap
float cngWheelAngle = 0.0f;

// Y-Coordinates aligned to the upper two lanes of 780 to 900 road range
float busY_Base = 870.0f; // Upper Lane (Bus)
float cngY_Base = 825.0f; // Middle Lane (CNG)

// Helper function to draw circles
void drawCircleShape(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Function to start bus engine audio in loop
void playBusSound()
{
    if (!isSoundPlaying)
    {
        // Plays sound asynchronously and continuously loops
        PlaySound(TEXT("bus_sound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        isSoundPlaying = true;
    }
}

// Function to stop bus audio
void stopBusSound()
{
    if (isSoundPlaying)
    {
        PlaySound(NULL, 0, 0); // Stops all active played sounds
        isSoundPlaying = false;
    }
}

// Unified Auto Movement Timer for both Bus and CNG
void internalTrafficTimer(int value)
{
    // Start playing bus sound when traffic timer begins
    playBusSound();

    // 1. Bus Movement Update
    float busSpeed = 2.5f;
    if (busX >= 305.0f && busX <= 460.0f)
    {
        busSpeed = 0.7f; // Slow down over speed breaker
    }
    busX -= busSpeed;
    busWheelAngle += busSpeed * 4.0f;

    // Reset Bus Position
    if (busX < -350.0f)
    {
        busX = 1700.0f;
    }

    // 2. CNG Movement Update (Synchronized with Bus speed)
    float cngSpeed = 2.5f;
    if (cngX >= 305.0f && cngX <= 460.0f)
    {
        cngSpeed = 0.7f; // Slow down over speed breaker
    }
    cngX -= cngSpeed;
    cngWheelAngle += cngSpeed * 6.0f;

    // Reset CNG Position maintaining safe distance behind the Bus
    if (cngX < -350.0f)
    {
        cngX = busX + 600.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, internalTrafficTimer, 0);
}

// Draw Passengers inside Bus windows
void drawDetailedPassengers(float baseX, float baseY)
{
    // Upper deck passengers
    for (int i = 0; i < 5; i++)
    {
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
    for (int i = 1; i < 5; i++)
    {
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
void drawDetailedDriver(float baseX, float baseY)
{
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
void drawDetailedWheel(float wx, float wy, float radius)
{
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircleShape(wx, wy, radius, 24);

    glColor3f(0.75f, 0.75f, 0.78f);
    drawCircleShape(wx, wy, radius * 0.55f, 16);

    glColor3f(0.25f, 0.25f, 0.25f);
    drawCircleShape(wx, wy, radius * 0.25f, 12);

    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 4; i++)
    {
        float rad = (-busWheelAngle + i * 45.0f) * 3.14159f / 180.0f;
        glVertex2f(wx + cos(rad) * (radius * 0.25f), wy + sin(rad) * (radius * 0.25f));
        glVertex2f(wx + cos(rad) * (radius * 0.55f), wy + sin(rad) * (radius * 0.55f));
    }
    glEnd();
}

// Main Function: drawBRTCBus
void drawBRTCBus()
{
    if (!isTimerStarted)
    {
        glutTimerFunc(16, internalTrafficTimer, 0);
        isTimerStarted = true;
    }

    float currentPositionY = busY_Base;

    if (busX >= 305.0f && busX <= 460.0f)
    {
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

    for (int i = 0; i < 6; i++)
    {
        float winX = 22.0f + (i * 35.0f);
        glBegin(GL_QUADS);
        glVertex2f(winX, -95.0f);
        glVertex2f(winX + 27.0f, -95.0f);
        glVertex2f(winX + 27.0f, -65.0f);
        glVertex2f(winX, -65.0f);
        glEnd();
    }

    for (int i = 0; i < 6; i++)
    {
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
    for (int i = 0; i < 6; i++)
    {
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
void drawCngWheel(float wx, float wy, float radius)
{
    glColor3f(0.12f, 0.12f, 0.12f);
    drawCircleShape(wx, wy, radius, 20);

    glColor3f(0.75f, 0.75f, 0.78f);
    drawCircleShape(wx, wy, radius * 0.55f, 14);

    glColor3f(0.2f, 0.2f, 0.2f);
    drawCircleShape(wx, wy, radius * 0.25f, 10);

    glColor3f(0.35f, 0.35f, 0.35f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 4; i++)
    {
        float rad = (-cngWheelAngle + i * 45.0f) * 3.14159f / 180.0f;
        glVertex2f(wx + cos(rad) * (radius * 0.25f), wy + sin(rad) * (radius * 0.25f));
        glVertex2f(wx + cos(rad) * (radius * 0.55f), wy + sin(rad) * (radius * 0.55f));
    }
    glEnd();
}

// Driver inside Boxy CNG
void drawCngDriver(float baseX, float baseY)
{
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
void drawCngPassengers(float baseX, float baseY)
{
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
void drawCngGrillMesh(float x1, float y1, float x2, float y2)
{
    glColor3f(0.25f, 0.3f, 0.25f);
    glLineWidth(1.2f);

    for (float x = x1 + 4.0f; x < x2; x += 5.0f)
    {
        glBegin(GL_LINES);
        glVertex2f(x, y1);
        glVertex2f(x, y2);
        glEnd();
    }

    for (float y = y1 + 4.0f; y < y2; y += 5.0f)
    {
        glBegin(GL_LINES);
        glVertex2f(x1, y);
        glVertex2f(x2, y);
        glEnd();
    }
}

// Main CNG Function
void drawCNG()
{
    float currentPositionY = cngY_Base;

    if (cngX >= 305.0f && cngX <= 460.0f)
    {
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

    // 9. Side Mirror & Dynamic Headlight
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

    // Headlight Bulb Base
    glColor3f(0.35f, 0.35f, 0.38f);
    drawCircleShape(-3.0f, -14.0f, 3.2f, 10);

    // Dynamic Headlight Beam & Glow
    if (isCngLightOn)
    {
        // Active Bright Bulb
        glColor3f(1.0f, 0.95f, 0.4f);
        drawCircleShape(-3.0f, -14.0f, 2.8f, 10);

        // Light Beam Cone (Glow Effect)
        glColor4f(1.0f, 0.9f, 0.3f, 0.35f); // Semi-transparent yellow beam
        glBegin(GL_TRIANGLES);
        glVertex2f(-3.0f, -14.0f);   // Bulb Center
        glVertex2f(-65.0f, -2.0f);   // Top Beam Spread
        glVertex2f(-65.0f, -28.0f);  // Bottom Beam Spread
        glEnd();
    }
    else
    {
        // Off Bulb Effect
        glColor3f(0.85f, 0.45f, 0.1f);
        glBegin(GL_QUADS);
        glVertex2f(-2.0f, -9.0f);
        glVertex2f(2.0f, -9.0f);
        glVertex2f(2.0f, -6.0f);
        glVertex2f(-2.0f, -6.0f);
        glEnd();
    }

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

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 50);
    glutCreateWindow(WINDOW_TITLE);

    init();

    // Register Callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    PlaySound(TEXT("bird_sound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    // Timers
    glutTimerFunc(0, updateMetroRail, 0);
    glutTimerFunc(0, schoolBusTimer, 0);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();

    return 0;
}

