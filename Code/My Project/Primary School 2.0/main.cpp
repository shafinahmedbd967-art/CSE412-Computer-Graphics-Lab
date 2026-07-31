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
// Description: Renders the sky background covering the upper section of the canvas.
// Coordinates: Covers X from 0 to 1600 and Y from 0 (top) down to 500.
// ============================================================================
void drawSky() {
    glColor3fv(COLOR_SKY_BLUE);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);          // Top-Left
        glVertex2f(1600.0f, 0.0f);       // Top-Right
        glVertex2f(1600.0f, 350.0f);     // Bottom-Right
        glVertex2f(0.0f, 350.0f);        // Bottom-Left
    glEnd();
}
#include <cmath> // Required for cos() and sin() trigonometric calculations


// ============================================================================
// FUNCTION: drawSun
// Description: Renders a smooth filled circle representing the sun in the upper-right sky.
// Position: Center at (X = 1350, Y = 130), Radius = 55.
// ============================================================================
// ============================================================================
// FUNCTION: drawSun
// Description: Renders a smooth filled circle representing the sun in the upper-right sky.
// Position: Center at (X = 1350, Y = 130), Radius = 55.
// ============================================================================
void drawSun() {
    glColor3fv(COLOR_SUN_YELLOW);

    float centerX = 1350.0f;
    float centerY = 130.0f;
    float radius = 55.0f;
    int segments = 60;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(centerX, centerY);
        for (int i = 0; i <= segments; i++) {
            float angle = i * 2.0f * 3.14159f / segments;
            float x = centerX + (radius * cos(angle));
            float y = centerY + (radius * sin(angle));
            glVertex2f(x, y);
        }
    glEnd();
}
// Helper function to draw a single cloud using overlapping circles
void drawSingleCloud(float startX, float startY) {
    int segments = 40;

    // Cloud components relative to base point (offset, radius)
    struct CloudCircle {
        float offsetX, offsetY, radius;
    } circles[] = {
        {0.0f,   0.0f,  30.0f},
        {25.0f, -15.0f, 38.0f},
        {55.0f, -10.0f, 32.0f},
        {80.0f,  0.0f,  28.0f},
        {40.0f,  10.0f, 30.0f}
    };

    glColor3fv(COLOR_CLOUD_WHITE);

    for (int c = 0; c < 5; c++) {
        float cx = startX + circles[c].offsetX;
        float cy = startY + circles[c].offsetY;
        float r = circles[c].radius;

        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(cx, cy);
            for (int i = 0; i <= segments; i++) {
                float angle = i * 2.0f * 3.14159f / segments;
                float x = cx + (r * cos(angle));
                float y = cy + (r * sin(angle));
                glVertex2f(x, y);
            }
        glEnd();
    }
}

// ============================================================================
// FUNCTION: drawCloud
// Description: Renders three drifting clouds across the sky layer.
// ============================================================================
void drawCloud() {
    // Cloud 1 - Left Sky
    drawSingleCloud(200.0f + cloud1OffsetX, 120.0f);

    // Cloud 2 - Center Sky
    drawSingleCloud(650.0f + cloud2OffsetX, 90.0f);

    // Cloud 3 - Right Sky
    drawSingleCloud(1050.0f + cloud3OffsetX, 140.0f);
}
// Helper function to draw a single V-shaped bird
void drawSingleBird(float x, float y, float size) {
    glColor3fv(COLOR_BLACK);
    glLineWidth(2.0f);

    glBegin(GL_LINE_STRIP);
        glVertex2f(x - size, y - (size * 0.5f)); // Left wing tip
        glVertex2f(x - (size * 0.3f), y - size); // Left wing bend
        glVertex2f(x, y);                        // Center body
        glVertex2f(x + (size * 0.3f), y - size); // Right wing bend
        glVertex2f(x + size, y - (size * 0.5f)); // Right wing tip
    glEnd();
}

// ============================================================================
// FUNCTION: drawBird
// Description: Renders a small flock of birds flying across the sky.
// ============================================================================
void drawBird() {
    // Flock of birds with slight position offsets
    drawSingleBird(350.0f + birdOffsetX, 80.0f, 12.0f);
    drawSingleBird(380.0f + birdOffsetX, 100.0f, 15.0f);
    drawSingleBird(420.0f + birdOffsetX, 75.0f, 11.0f);
    drawSingleBird(450.0f + birdOffsetX, 95.0f, 14.0f);
}
void drawButterfly() { }
// ============================================================================
// FUNCTION: drawAirplane
// Description: Renders an airplane soaring high across the sky layer.
// Position: Base at X = 800, Y = 60.
// ============================================================================
void drawAirplane() {
    glPushMatrix();
    glTranslatef(airplaneOffsetX, 0.0f, 0.0f); // Animation translation

    float baseX = 800.0f;
    float baseY = 60.0f;

    // 1. Fuselage (Body)
    glColor3f(0.90f, 0.90f, 0.95f); // Light grayish white
    glBegin(GL_POLYGON);
        glVertex2f(baseX - 40.0f, baseY);
        glVertex2f(baseX + 30.0f, baseY - 5.0f);
        glVertex2f(baseX + 45.0f, baseY);
        glVertex2f(baseX + 30.0f, baseY + 5.0f);
    glEnd();

    // Nose Cone
    glColor3f(0.80f, 0.10f, 0.10f); // Red Nose
    glBegin(GL_TRIANGLES);
        glVertex2f(baseX - 40.0f, baseY);
        glVertex2f(baseX - 50.0f, baseY);
        glVertex2f(baseX - 40.0f, baseY + 3.0f);
    glEnd();

    // 2. Wings (Main Sweep Wing)
    glColor3f(0.70f, 0.75f, 0.85f);
    glBegin(GL_TRIANGLES);
        glVertex2f(baseX - 5.0f, baseY - 2.0f);
        glVertex2f(baseX + 10.0f, baseY - 22.0f);
        glVertex2f(baseX + 15.0f, baseY - 2.0f);
    glEnd();

    // 3. Tail Fin (Vertical Stabilizer)
    glColor3f(0.80f, 0.10f, 0.10f); // Red Tail
    glBegin(GL_TRIANGLES);
        glVertex2f(baseX + 30.0f, baseY - 3.0f);
        glVertex2f(baseX + 42.0f, baseY - 18.0f);
        glVertex2f(baseX + 40.0f, baseY - 3.0f);
    glEnd();

    glPopMatrix();
}

/* ---- School Building Layer ---- */
// ============================================================================
// FUNCTION: drawSchool
// Description: Renders the primary multi-story school building structure.
// Position: Centered on canvas (X = 350 to 1250, Y = 180 to 480).
// ============================================================================
void drawSchool() {
    // 1. Main Base Building Walls (Cream Base)
    glColor3fv(COLOR_BUILDING_CREAM);
    glBegin(GL_QUADS);
        glVertex2f(350.0f, 250.0f);   // Top-Left
        glVertex2f(1250.0f, 250.0f);  // Top-Right
        glVertex2f(1250.0f, 550.0f);  // Bottom-Right
        glVertex2f(350.0f, 550.0f);   // Bottom-Left
    glEnd();

    // 2. Red Structural Accent Pillars
    glColor3fv(COLOR_BUILDING_RED);

    // Left Pillar
    glBegin(GL_QUADS);
        glVertex2f(350.0f, 250.0f);
        glVertex2f(380.0f, 250.0f);
        glVertex2f(380.0f, 550.0f);
        glVertex2f(350.0f, 550.0f);
    glEnd();

    // Center-Left Support Column
    glBegin(GL_QUADS);
        glVertex2f(630.0f, 250.0f);
        glVertex2f(650.0f, 250.0f);
        glVertex2f(650.0f, 550.0f);
        glVertex2f(630.0f, 550.0f);
    glEnd();

    // Center-Right Support Column
    glBegin(GL_QUADS);
        glVertex2f(950.0f, 250.0f);
        glVertex2f(970.0f, 250.0f);
        glVertex2f(970.0f, 550.0f);
        glVertex2f(950.0f, 550.0f);
    glEnd();

    // Right Pillar
    glBegin(GL_QUADS);
        glVertex2f(1220.0f, 250.0f);
        glVertex2f(1250.0f, 250.0f);
        glVertex2f(1250.0f, 550.0f);
        glVertex2f(1220.0f, 550.0f);
    glEnd();

    // Horizontal Floor Dividers
    glLineWidth(3.0f);
    glColor3f(0.50f, 0.10f, 0.10f);
    glBegin(GL_LINES);
        // Floor 1 & 2 Divider
        glVertex2f(350.0f, 350.0f);
        glVertex2f(1250.0f, 350.0f);

        // Floor 2 & 3 Divider
        glVertex2f(350.0f, 450.0f);
        glVertex2f(1250.0f, 450.0f);
    glEnd();
}
void drawRoof() {
    // 1. Main Horizontal Roof Slab (Sits perfectly on top of the school at Y = 235 to 250)
    glColor3fv(COLOR_ROOF_GRAY);
    glBegin(GL_QUADS);
        glVertex2f(330.0f, 235.0f);   // Top-Left
        glVertex2f(1270.0f, 235.0f);  // Top-Right
        glVertex2f(1270.0f, 250.0f);  // Bottom-Right
        glVertex2f(330.0f, 250.0f);   // Bottom-Left
    glEnd();

    // 2. Parapet Safety Wall (Red Accent above the gray roof slab)
    glColor3fv(COLOR_BUILDING_RED);
    glBegin(GL_QUADS);
        glVertex2f(350.0f, 220.0f);
        glVertex2f(1250.0f, 220.0f);
        glVertex2f(1250.0f, 235.0f);
        glVertex2f(350.0f, 235.0f);
    glEnd();

    // 3. Central Gable Roof (Triangular Peak)
    glColor3fv(COLOR_BUILDING_RED);
    glBegin(GL_TRIANGLES);
        glVertex2f(800.0f, 160.0f);
        glVertex2f(720.0f, 220.0f);
        glVertex2f(880.0f, 220.0f);
    glEnd();

    // Triangular Gable Inner Border
    glColor3fv(COLOR_BUILDING_CREAM);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(800.0f, 168.0f);
        glVertex2f(730.0f, 217.0f);
        glVertex2f(870.0f, 217.0f);
    glEnd();
}
// Helper function to draw a single double-pane window with dark border
void drawSingleWindow(float x, float y, float width, float height) {
    // 1. Dark Frame / Border
    glColor3f(0.15f, 0.15f, 0.20f); // Dark Slate Border
    glBegin(GL_QUADS);
        glVertex2f(x - 2.0f, y - 2.0f);
        glVertex2f(x + width + 2.0f, y - 2.0f);
        glVertex2f(x + width + 2.0f, y + height + 2.0f);
        glVertex2f(x - 2.0f, y + height + 2.0f);
    glEnd();

    // 2. Glass Panes (Blue Tint using exact palette variable)
    glColor3fv(COLOR_WINDOW_BLUE);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();

    // 3. Middle Window Pane Divider (Vertical Split)
    glColor3f(0.20f, 0.20f, 0.25f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(x + (width / 2.0f), y);
        glVertex2f(x + (width / 2.0f), y + height);
    glEnd();
}

// ============================================================================
// FUNCTION: drawWindow
// Description: Renders glass windows across all 3 floors of the school building.
// ============================================================================
void drawWindow() {
    float windowWidth = 35.0f;
    float windowHeight = 45.0f;

    // Floor Y-Positions for Windows
    float floor3Y = 280.0f; // Top Floor
    float floor2Y = 380.0f; // Middle Floor
    float floor1Y = 480.0f; // Ground Floor

    // Section A: Left Block
    for (float x = 405.0f; x <= 580.0f; x += 55.0f) {
        drawSingleWindow(x, floor3Y, windowWidth, windowHeight);
        drawSingleWindow(x, floor2Y, windowWidth, windowHeight);
        drawSingleWindow(x, floor1Y, windowWidth, windowHeight);
    }

    // Section B: Middle Block
    for (float x = 680.0f; x <= 900.0f; x += 55.0f) {
        drawSingleWindow(x, floor3Y, windowWidth, windowHeight);
        drawSingleWindow(x, floor2Y, windowWidth, windowHeight);

        // Remove windows completely around the center door on Ground Floor
        if (x < 720.0f || x > 870.0f) {
            drawSingleWindow(x, floor1Y, windowWidth, windowHeight);
        }
    }

    // Section C: Right Block
    for (float x = 995.0f; x <= 1170.0f; x += 55.0f) {
        drawSingleWindow(x, floor3Y, windowWidth, windowHeight);
        drawSingleWindow(x, floor2Y, windowWidth, windowHeight);
        drawSingleWindow(x, floor1Y, windowWidth, windowHeight);
    }
}
// ============================================================================
// FUNCTION: drawDoor
// Description: Renders the double-door main entrance at ground floor center.
// Position: Centered at X = 770 to 830, Y = 460 to 550.
// ============================================================================
void drawDoor() {
    // 1. Dark Wooden Door Base
    glColor3fv(COLOR_DOOR_BROWN);
    glBegin(GL_QUADS);
        glVertex2f(770.0f, 460.0f);
        glVertex2f(830.0f, 460.0f);
        glVertex2f(830.0f, 550.0f);
        glVertex2f(770.0f, 550.0f);
    glEnd();

    // 2. Door Frame Border
    glColor3f(0.20f, 0.10f, 0.05f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(770.0f, 460.0f);
        glVertex2f(830.0f, 460.0f);
        glVertex2f(830.0f, 550.0f);
        glVertex2f(770.0f, 550.0f);
    glEnd();

    // 3. Center Split Line (Double Door)
    glBegin(GL_LINES);
        glVertex2f(800.0f, 460.0f);
        glVertex2f(800.0f, 550.0f);
    glEnd();

    // 4. Metallic Door Handles
    glColor3fv(COLOR_SUN_YELLOW);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glVertex2f(793.0f, 510.0f);
        glVertex2f(807.0f, 510.0f);
    glEnd();
}
// ============================================================================
// FUNCTION: drawClock
// Description: Renders a circular wall clock inside the triangular roof gable.
// Position: Center at (X = 800, Y = 195), Radius = 18.
// ============================================================================
void drawClock() {
    float cx = 800.0f;
    float cy = 195.0f;
    float r = 18.0f;
    int segments = 40;

    // 1. White Clock Face
    glColor3fv(COLOR_WHITE);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= segments; i++) {
            float angle = i * 2.0f * 3.14159f / segments;
            glVertex2f(cx + (r * cos(angle)), cy + (r * sin(angle)));
        }
    glEnd();

    // 2. Clock Outer Rim (Dark Border)
    glColor3fv(COLOR_BLACK);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < segments; i++) {
            float angle = i * 2.0f * 3.14159f / segments;
            glVertex2f(cx + (r * cos(angle)), cy + (r * sin(angle)));
        }
    glEnd();

    // 3. Clock Hands (Hour & Minute)
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        // Hour hand (pointing to 10)
        glVertex2f(cx, cy);
        glVertex2f(cx - 8.0f, cy - 5.0f);

        // Minute hand (pointing to 2)
        glVertex2f(cx, cy);
        glVertex2f(cx + 10.0f, cy - 10.0f);
    glEnd();
}
// ============================================================================
// FUNCTION: drawFlagPole
// Description: Renders the tall metallic pole standing on the ground level.
// Position: Base on ground at (X = 300, Y = 550), height up to Y = 280.
// ============================================================================
void drawFlagPole() {
    // Concrete Base Pedestal at Ground
    glColor3fv(COLOR_ROOF_GRAY);
    glBegin(GL_QUADS);
        glVertex2f(285.0f, 540.0f);
        glVertex2f(315.0f, 540.0f);
        glVertex2f(315.0f, 550.0f);
        glVertex2f(285.0f, 550.0f);
    glEnd();

    // Metallic Flag Pole
    glColor3fv(COLOR_POLE_GRAY);
    glLineWidth(4.0f);
    glBegin(GL_LINES);
        glVertex2f(300.0f, 540.0f); // Base on ground pedestal
        glVertex2f(300.0f, 280.0f); // Top of pole
    glEnd();

    // Golden Knob at Top
    glColor3fv(COLOR_SUN_YELLOW);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
        glVertex2f(300.0f, 278.0f);
    glEnd();
}

// ============================================================================
// FUNCTION: drawBangladeshFlag
// Description: Renders the national flag waving on the ground pole.
// ============================================================================
void drawBangladeshFlag() {
    float poleX = 300.0f;
    float topY = 280.0f;
    float flagW = 75.0f;
    float flagH = 45.0f;

    // 1. Green Flag Body
    glColor3fv(COLOR_FLAG_GREEN);
    glBegin(GL_QUADS);
        glVertex2f(poleX, topY);
        glVertex2f(poleX + flagW + flagWaveOffset, topY);
        glVertex2f(poleX + flagW + flagWaveOffset, topY + flagH);
        glVertex2f(poleX, topY + flagH);
    glEnd();

    // 2. Red Disc
    glColor3fv(COLOR_FLAG_RED);
    float cx = poleX + (flagW * 0.45f) + (flagWaveOffset * 0.5f);
    float cy = topY + (flagH * 0.5f);
    float r = 14.0f;
    int segments = 30;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= segments; i++) {
            float angle = i * 2.0f * 3.14159f / segments;
            glVertex2f(cx + (r * cos(angle)), cy + (r * sin(angle)));
        }
    glEnd();
}
// ============================================================================
// FUNCTION: drawRoofBanner
// Description: Renders the school name sign board below the clock.
// ============================================================================
void drawRoofBanner() {
    // Banner Background Board
    glColor3fv(COLOR_WHITE);
    glBegin(GL_QUADS);
        glVertex2f(650.0f, 225.0f);
        glVertex2f(950.0f, 225.0f);
        glVertex2f(950.0f, 245.0f);
        glVertex2f(650.0f, 245.0f);
    glEnd();

    // Green Border Frame around Banner
    glColor3fv(COLOR_FLAG_GREEN);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(650.0f, 225.0f);
        glVertex2f(950.0f, 225.0f);
        glVertex2f(950.0f, 245.0f);
        glVertex2f(650.0f, 245.0f);
    glEnd();
}

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
