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
    //drawFlower();
    //drawBush();
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
// Description: Renders the flag pole standing on the ground, right next to the main entrance.
// Position: Base at (X = 730, Y = 550), Top at (X = 730, Y = 280).
// ============================================================================
void drawFlagPole() {
    // Concrete Base Pedestal at Ground near Main Door
    glColor3fv(COLOR_ROOF_GRAY);
    glBegin(GL_QUADS);
        glVertex2f(715.0f, 540.0f);
        glVertex2f(745.0f, 540.0f);
        glVertex2f(745.0f, 550.0f);
        glVertex2f(715.0f, 550.0f);
    glEnd();

    // Metallic Flag Pole
    glColor3fv(COLOR_POLE_GRAY);
    glLineWidth(4.0f);
    glBegin(GL_LINES);
        glVertex2f(730.0f, 540.0f); // Base on ground
        glVertex2f(730.0f, 280.0f); // Top of pole
    glEnd();

    // Golden Knob at Top
    glColor3fv(COLOR_SUN_YELLOW);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
        glVertex2f(730.0f, 278.0f);
    glEnd();
}

// ============================================================================
// FUNCTION: drawBangladeshFlag
// Description: Renders the national flag waving near the main door center.
// ============================================================================
void drawBangladeshFlag() {
    float poleX = 730.0f;
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
// ============================================================================
// FUNCTION: drawShaheedMinar
// Description: Accurate 2D representation matching standard Shaheed Minar art.
// Position: Centered at X = 1400, Base at Y = 550.
// ============================================================================
void drawShaheedMinar() {
    float cx = 1400.0f; // Center position

    // ---------------------------------------------------------
    // 1. Red Sun Disc (Behind Center Column)
    // ---------------------------------------------------------
    glColor3fv(COLOR_FLAG_RED);
    float sunX = cx;
    float sunY = 445.0f;
    float sunR = 38.0f;
    int segments = 40;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(sunX, sunY);
        for (int i = 0; i <= segments; i++) {
            float angle = i * 2.0f * 3.14159f / segments;
            glVertex2f(sunX + (sunR * cos(angle)), sunY + (sunR * sin(angle)));
        }
    glEnd();

    // Helper lambda-like vertical grill bar renderer
    // (Pillars Fill: White, Outline & Grill Bars: Black/Dark Gray)

    // ---------------------------------------------------------
    // 2. Pillars Structure
    // ---------------------------------------------------------

    // --- A. Center Double Column (Trapezoid flared top) ---
    // Left Inner Pillar of Center Block
    glColor3f(0.95f, 0.95f, 0.98f);
    glBegin(GL_POLYGON);
        glVertex2f(cx - 32.0f, 360.0f); // Flared top-left
        glVertex2f(cx - 3.0f,  360.0f); // Top-right near center
        glVertex2f(cx - 3.0f,  510.0f); // Bottom-right
        glVertex2f(cx - 22.0f, 510.0f); // Bottom-left
    glEnd();

    // Right Inner Pillar of Center Block
    glBegin(GL_POLYGON);
        glVertex2f(cx + 3.0f,  360.0f); // Top-left near center
        glVertex2f(cx + 32.0f, 360.0f); // Flared top-right
        glVertex2f(cx + 22.0f, 510.0f); // Bottom-right
        glVertex2f(cx + 3.0f,  510.0f); // Bottom-left
    glEnd();

    // Top Connecting Roof Slab for Center Column
    glBegin(GL_POLYGON);
        glVertex2f(cx - 36.0f, 348.0f);
        glVertex2f(cx + 36.0f, 348.0f);
        glVertex2f(cx + 32.0f, 360.0f);
        glVertex2f(cx - 32.0f, 360.0f);
    glEnd();

    // --- B. Medium Side Columns (Inner Pair) ---
    // Left Medium
    glBegin(GL_QUADS);
        glVertex2f(cx - 52.0f, 410.0f);
        glVertex2f(cx - 30.0f, 410.0f);
        glVertex2f(cx - 30.0f, 510.0f);
        glVertex2f(cx - 52.0f, 510.0f);
    glEnd();
    // Right Medium
    glBegin(GL_QUADS);
        glVertex2f(cx + 30.0f, 410.0f);
        glVertex2f(cx + 52.0f, 410.0f);
        glVertex2f(cx + 52.0f, 510.0f);
        glVertex2f(cx + 30.0f, 510.0f);
    glEnd();

    // --- C. Small Side Columns (Outer Pair) ---
    // Left Small
    glBegin(GL_QUADS);
        glVertex2f(cx - 74.0f, 450.0f);
        glVertex2f(cx - 58.0f, 450.0f);
        glVertex2f(cx - 58.0f, 510.0f);
        glVertex2f(cx - 74.0f, 510.0f);
    glEnd();
    // Right Small
    glBegin(GL_QUADS);
        glVertex2f(cx + 58.0f, 450.0f);
        glVertex2f(cx + 74.0f, 450.0f);
        glVertex2f(cx + 74.0f, 510.0f);
        glVertex2f(cx + 58.0f, 510.0f);
    glEnd();

    // ---------------------------------------------------------
    // 3. Black Outlines & Vertical Steel Grill Bars
    // ---------------------------------------------------------
    glColor3f(0.10f, 0.10f, 0.15f);
    glLineWidth(2.0f);

    // Center Left Pillar Frame & Grills
    glBegin(GL_LINE_LOOP);
        glVertex2f(cx - 32.0f, 360.0f);
        glVertex2f(cx - 3.0f,  360.0f);
        glVertex2f(cx - 3.0f,  510.0f);
        glVertex2f(cx - 22.0f, 510.0f);
    glEnd();
    // Center Right Pillar Frame & Grills
    glBegin(GL_LINE_LOOP);
        glVertex2f(cx + 3.0f,  360.0f);
        glVertex2f(cx + 32.0f, 360.0f);
        glVertex2f(cx + 22.0f, 510.0f);
        glVertex2f(cx + 3.0f,  510.0f);
    glEnd();
    // Center Top Frame Outline
    glBegin(GL_LINE_LOOP);
        glVertex2f(cx - 36.0f, 348.0f);
        glVertex2f(cx + 36.0f, 348.0f);
        glVertex2f(cx + 32.0f, 360.0f);
        glVertex2f(cx - 32.0f, 360.0f);
    glEnd();

    // Medium Pillars Outlines
    glBegin(GL_LINE_LOOP);
        glVertex2f(cx - 52.0f, 410.0f); glVertex2f(cx - 30.0f, 410.0f);
        glVertex2f(cx - 30.0f, 510.0f); glVertex2f(cx - 52.0f, 510.0f);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(cx + 30.0f, 410.0f); glVertex2f(cx + 52.0f, 410.0f);
        glVertex2f(cx + 52.0f, 510.0f); glVertex2f(cx + 30.0f, 510.0f);
    glEnd();

    // Small Pillars Outlines
    glBegin(GL_LINE_LOOP);
        glVertex2f(cx - 74.0f, 450.0f); glVertex2f(cx - 58.0f, 450.0f);
        glVertex2f(cx - 58.0f, 510.0f); glVertex2f(cx - 74.0f, 510.0f);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(cx + 58.0f, 450.0f); glVertex2f(cx + 74.0f, 450.0f);
        glVertex2f(cx + 74.0f, 510.0f); glVertex2f(cx + 58.0f, 510.0f);
    glEnd();

    // Inner Grill Lines (Vertical Bars inside each pillar)
    glLineWidth(1.0f);
    glBegin(GL_LINES);
        // Center-Left Grills
        glVertex2f(cx - 22.0f, 360.0f); glVertex2f(cx - 16.0f, 510.0f);
        glVertex2f(cx - 12.0f, 360.0f); glVertex2f(cx - 9.0f,  510.0f);

        // Center-Right Grills
        glVertex2f(cx + 12.0f, 360.0f); glVertex2f(cx + 9.0f,  510.0f);
        glVertex2f(cx + 22.0f, 360.0f); glVertex2f(cx + 16.0f, 510.0f);

        // Medium Left Grills
        glVertex2f(cx - 45.0f, 410.0f); glVertex2f(cx - 45.0f, 510.0f);
        glVertex2f(cx - 37.0f, 410.0f); glVertex2f(cx - 37.0f, 510.0f);

        // Medium Right Grills
        glVertex2f(cx + 37.0f, 410.0f); glVertex2f(cx + 37.0f, 510.0f);
        glVertex2f(cx + 45.0f, 410.0f); glVertex2f(cx + 45.0f, 510.0f);

        // Small Left Grill
        glVertex2f(cx - 66.0f, 450.0f); glVertex2f(cx - 66.0f, 510.0f);

        // Small Right Grill
        glVertex2f(cx + 66.0f, 450.0f); glVertex2f(cx + 66.0f, 510.0f);
    glEnd();

    // ---------------------------------------------------------
    // 4. Concrete Base Pedestal (3 Steps with Black Outlines)
    // ---------------------------------------------------------
    glColor3f(0.88f, 0.88f, 0.90f);

    // Step 3 (Top)
    glBegin(GL_QUADS);
        glVertex2f(cx - 82.0f, 510.0f); glVertex2f(cx + 82.0f, 510.0f);
        glVertex2f(cx + 82.0f, 522.0f); glVertex2f(cx - 82.0f, 522.0f);
    glEnd();
    // Step 2 (Middle)
    glBegin(GL_QUADS);
        glVertex2f(cx - 92.0f, 522.0f); glVertex2f(cx + 92.0f, 522.0f);
        glVertex2f(cx + 92.0f, 536.0f); glVertex2f(cx - 92.0f, 536.0f);
    glEnd();
    // Step 1 (Bottom)
    glBegin(GL_QUADS);
        glVertex2f(cx - 102.0f, 536.0f); glVertex2f(cx + 102.0f, 536.0f);
        glVertex2f(cx + 102.0f, 550.0f); glVertex2f(cx - 102.0f, 550.0f);
    glEnd();

    // Step Outlines
    glColor3f(0.10f, 0.10f, 0.15f);
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(cx - 82.0f, 510.0f); glVertex2f(cx + 82.0f, 510.0f);
        glVertex2f(cx + 82.0f, 522.0f); glVertex2f(cx - 82.0f, 522.0f);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(cx - 92.0f, 522.0f); glVertex2f(cx + 92.0f, 522.0f);
        glVertex2f(cx + 92.0f, 536.0f); glVertex2f(cx - 92.0f, 536.0f);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(cx - 102.0f, 536.0f); glVertex2f(cx + 102.0f, 536.0f);
        glVertex2f(cx + 102.0f, 550.0f); glVertex2f(cx - 102.0f, 550.0f);
    glEnd();
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
// Helper function to draw a single flower with stem and leaves
void drawFlower(float x, float y, float r, const float petalColor[3]) {
    // 1. Stem
    glColor3f(0.15f, 0.45f, 0.15f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x, y + 15.0f);
    glEnd();

    // 2. Petals (5-petal fan)
    glColor3fv(petalColor);
    float flowerY = y + 15.0f;
    int segments = 12;

    for (int i = 0; i < 5; i++) {
        float angle = i * 2.0f * 3.14159f / 5.0f;
        float px = x + cos(angle) * r;
        float py = flowerY + sin(angle) * r;

        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(px, py);
            for (int j = 0; j <= segments; j++) {
                float a = j * 2.0f * 3.14159f / segments;
                glVertex2f(px + (r * 0.7f * cos(a)), py + (r * 0.7f * sin(a)));
            }
        glEnd();
    }

    // 3. Flower Center Disc
    glColor3fv(COLOR_SUN_YELLOW);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, flowerY);
        for (int i = 0; i <= segments; i++) {
            float angle = i * 2.0f * 3.14159f / segments;
            glVertex2f(x + (r * 0.5f * cos(angle)), flowerY + (r * 0.5f * sin(angle)));
        }
    glEnd();
}

// Helper function to draw a bushy plant clump
void drawBush(float x, float y, float rx, float ry) {
    // Outer dark green base
    glColor3f(0.1f, 0.4f, 0.1f);
    int segments = 30;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= segments; i++) {
            float angle = i * 3.14159f / segments; // Semi-circle bush
            glVertex2f(x + (rx * cos(angle)), y - (ry * sin(angle)));
        }
    glEnd();

    // Inner bright green highlights
    glColor3fv(COLOR_TREE_LEAVES); // Fixed: Changed from COLOR_TREE_LEAF to COLOR_TREE_LEAVES
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y - 3.0f);
        for (int i = 0; i <= segments; i++) {
            float angle = i * 3.14159f / segments;
            glVertex2f(x + ((rx - 4.0f) * cos(angle)), y - 3.0f - ((ry - 4.0f) * sin(angle)));
        }
    glEnd();
}
// ============================================================================
// FUNCTION: drawGarden
// Description: Renders flower beds, lawn patches, bushes, and decorative plants.
// ============================================================================
void drawGarden() {
    // ---------------------------------------------------------
    // 1. Garden Beds / Soil Patches (Left & Right Front Sections)
    // ---------------------------------------------------------
    // Left Flower Bed
    glColor3f(0.35f, 0.22f, 0.12f); // Soil Brown
    glBegin(GL_QUADS);
        glVertex2f(380.0f, 545.0f);
        glVertex2f(670.0f, 545.0f);
        glVertex2f(670.0f, 565.0f);
        glVertex2f(380.0f, 565.0f);
    glEnd();

    // Right Flower Bed
    glBegin(GL_QUADS);
        glVertex2f(930.0f, 545.0f);
        glVertex2f(1220.0f, 545.0f);
        glVertex2f(1220.0f, 565.0f);
        glVertex2f(930.0f, 565.0f);
    glEnd();

    // Bed Concrete Borders
    glColor3f(0.75f, 0.75f, 0.78f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(380.0f, 545.0f); glVertex2f(670.0f, 545.0f);
        glVertex2f(670.0f, 565.0f); glVertex2f(380.0f, 565.0f);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(930.0f, 545.0f); glVertex2f(1220.0f, 545.0f);
        glVertex2f(1220.0f, 565.0f); glVertex2f(930.0f, 565.0f);
    glEnd();

    // ---------------------------------------------------------
    // 2. Decorative Bushes on Garden Edges
    // ---------------------------------------------------------
    drawBush(390.0f, 545.0f, 20.0f, 18.0f);
    drawBush(660.0f, 545.0f, 20.0f, 18.0f);
    drawBush(940.0f, 545.0f, 20.0f, 18.0f);
    drawBush(1210.0f, 545.0f, 20.0f, 18.0f);

    // ---------------------------------------------------------
    // 3. Colorful Flowers Array
    // ---------------------------------------------------------
    static const float RED_PETAL[3]    = {0.95f, 0.15f, 0.20f};
    static const float YELLOW_PETAL[3] = {0.98f, 0.85f, 0.10f};
    static const float PINK_PETAL[3]   = {0.95f, 0.40f, 0.70f};
    static const float ORANGE_PETAL[3] = {0.98f, 0.50f, 0.10f};

    // Left Garden Flowers
    drawFlower(420.0f, 540.0f, 5.0f, RED_PETAL);
    drawFlower(450.0f, 542.0f, 5.0f, YELLOW_PETAL);
    drawFlower(480.0f, 539.0f, 5.0f, PINK_PETAL);
    drawFlower(510.0f, 541.0f, 5.0f, ORANGE_PETAL);
    drawFlower(540.0f, 540.0f, 5.0f, RED_PETAL);
    drawFlower(570.0f, 543.0f, 5.0f, YELLOW_PETAL);
    drawFlower(600.0f, 539.0f, 5.0f, PINK_PETAL);
    drawFlower(630.0f, 541.0f, 5.0f, ORANGE_PETAL);

    // Right Garden Flowers
    drawFlower(970.0f,  540.0f, 5.0f, ORANGE_PETAL);
    drawFlower(1000.0f, 542.0f, 5.0f, PINK_PETAL);
    drawFlower(1030.0f, 539.0f, 5.0f, YELLOW_PETAL);
    drawFlower(1060.0f, 541.0f, 5.0f, RED_PETAL);
    drawFlower(1090.0f, 540.0f, 5.0f, ORANGE_PETAL);
    drawFlower(1120.0f, 543.0f, 5.0f, PINK_PETAL);
    drawFlower(1150.0f, 539.0f, 5.0f, YELLOW_PETAL);
    drawFlower(1180.0f, 541.0f, 5.0f, RED_PETAL);
}
// Helper function to render an individual leafy tree
void drawSingleTree(float x, float y, float scale) {
    // ---------------------------------------------------------
    // 1. Tree Trunk (Wood Bark)
    // ---------------------------------------------------------
    glColor3fv(COLOR_TREE_TRUNK);
    glBegin(GL_POLYGON);
        glVertex2f(x - (14.0f * scale), y);
        glVertex2f(x + (14.0f * scale), y);
        glVertex2f(x + (9.0f * scale),  y - (130.0f * scale));
        glVertex2f(x - (9.0f * scale),  y - (130.0f * scale));
    glEnd();

    // Trunk Bark Lines / Texture
    glColor3f(0.22f, 0.12f, 0.05f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(x - (4.0f * scale), y - (20.0f * scale));
        glVertex2f(x - (3.0f * scale), y - (85.0f * scale));
        glVertex2f(x + (4.0f * scale), y - (30.0f * scale));
        glVertex2f(x + (3.0f * scale), y - (95.0f * scale));
    glEnd();

    // ---------------------------------------------------------
    // 2. Leafy Canopy (Layered Clusters)
    // ---------------------------------------------------------
    float topY = y - (130.0f * scale);
    int segments = 30;

    // Cluster positions relative to trunk top
    float clusters[5][3] = {
        {x - (32.0f * scale), topY + (10.0f * scale), 36.0f * scale},
        {x + (32.0f * scale), topY + (10.0f * scale), 36.0f * scale},
        {x - (22.0f * scale), topY - (25.0f * scale), 42.0f * scale},
        {x + (22.0f * scale), topY - (25.0f * scale), 42.0f * scale},
        {x,                  topY - (50.0f * scale), 48.0f * scale}
    };

    // A. Dark Green Base Layer (Shadow)
    glColor3f(0.10f, 0.38f, 0.12f);
    for (int c = 0; c < 5; c++) {
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(clusters[c][0], clusters[c][1]);
            for (int i = 0; i <= segments; i++) {
                float angle = i * 2.0f * 3.14159f / segments;
                glVertex2f(clusters[c][0] + (clusters[c][2] * cos(angle)),
                           clusters[c][1] + (clusters[c][2] * sin(angle)));
            }
        glEnd();
    }

    // B. Bright Green Top Layer (Highlights)
    glColor3fv(COLOR_TREE_LEAVES);
    for (int c = 0; c < 5; c++) {
        float cx = clusters[c][0];
        float cy = clusters[c][1] - (3.0f * scale);
        float r  = clusters[c][2] - (4.0f * scale);

        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(cx, cy);
            for (int i = 0; i <= segments; i++) {
                float angle = i * 2.0f * 3.14159f / segments;
                glVertex2f(cx + (r * cos(angle)), cy + (r * sin(angle)));
            }
        glEnd();
    }
}

// ============================================================================
// FUNCTION: drawTree
// Description: Places trees seamlessly on both sides of the campus field.
// ============================================================================
void drawTree() {
    // Left Boundary Trees
    //drawSingleTree(180.0f, 550.0f, 1.10f);
    //drawSingleTree(290.0f, 550.0f, 0.90f);

    // Right Boundary Tree (Behind Shaheed Minar Area)
    drawSingleTree(1580.0f, 550.0f, 1.15f);
}
// Helper function to draw an individual Palm / Coconut Tree
void drawSinglePalmTree(float startX, float startY, float height) {
    // ---------------------------------------------------------
    // 1. Curved Trunk (Slanted Quads)
    // ---------------------------------------------------------
    glColor3f(0.45f, 0.30f, 0.18f); // Trunk Brown
    int segments = 8;
    float currentX = startX;
    float currentY = startY;
    float segmentH = height / segments;
    float curveOffset = 2.5f; // Curve strength

    for (int i = 0; i < segments; i++) {
        float nextX = currentX + (i * 0.8f); // Gentle curve to right
        float nextY = currentY - segmentH;
        float w1 = 12.0f - (i * 0.6f); // Tapering width
        float w2 = 12.0f - ((i + 1) * 0.6f);

        // Segment Quad
        glBegin(GL_QUADS);
            glVertex2f(currentX - w1, currentY);
            glVertex2f(currentX + w1, currentY);
            glVertex2f(nextX + w2, nextY);
            glVertex2f(nextX - w2, nextY);
        glEnd();

        // Ring texture line
        glColor3f(0.30f, 0.20f, 0.10f);
        glLineWidth(1.5f);
        glBegin(GL_LINES);
            glVertex2f(currentX - w1, currentY);
            glVertex2f(currentX + w1, currentY);
        glEnd();

        glColor3f(0.45f, 0.30f, 0.18f); // Reset trunk color
        currentX = nextX;
        currentY = nextY;
    }

    // Top Crown Center Position
    float topX = currentX;
    float topY = currentY;

    // ---------------------------------------------------------
    // 2. Coconuts Group at Top
    // ---------------------------------------------------------
    glColor3f(0.20f, 0.40f, 0.05f); // Green Coconuts
    int circleSegs = 15;
    float coconutCoords[3][2] = {
        {topX - 5.0f, topY + 4.0f},
        {topX + 5.0f, topY + 4.0f},
        {topX,        topY + 8.0f}
    };
    for (int c = 0; c < 3; c++) {
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(coconutCoords[c][0], coconutCoords[c][1]);
            for (int i = 0; i <= circleSegs; i++) {
                float angle = i * 2.0f * 3.14159f / circleSegs;
                glVertex2f(coconutCoords[c][0] + (6.0f * cos(angle)),
                           coconutCoords[c][1] + (6.0f * sin(angle)));
            }
        glEnd();
    }

    // ---------------------------------------------------------
    // 3. Palm Fronds (Drooping Leaves)
    // ---------------------------------------------------------
    glColor3f(0.12f, 0.55f, 0.15f); // Palm Green
    glLineWidth(2.5f);

    float leafAngles[] = { -160.0f, -120.0f, -70.0f, -20.0f, 20.0f, 70.0f, 120.0f, 160.0f };
    int totalFronds = 8;

    for (int f = 0; f < totalFronds; f++) {
        float rad = leafAngles[f] * 3.14159f / 180.0f;
        float leafLen = 65.0f;
        float endX = topX + (leafLen * cos(rad));
        float endY = topY - (leafLen * sin(rad)) + (abs((int)leafAngles[f]) * 0.15f); // Droop effect

        // Main Leaf Spine
        glBegin(GL_LINES);
            glVertex2f(topX, topY);
            glVertex2f(endX, endY);
        glEnd();

        // Sub-leaflets (Leaf blades along the spine)
        int leaflets = 10;
        for (int j = 1; j <= leaflets; j++) {
            float t = (float)j / leaflets;
            float lx = topX + (endX - topX) * t;
            float ly = topY + (endY - topY) * t;

            glBegin(GL_LINES);
                glVertex2f(lx, ly);
                glVertex2f(lx - 8.0f, ly + 12.0f);
                glVertex2f(lx, ly);
                glVertex2f(lx + 8.0f, ly + 12.0f);
            glEnd();
        }
    }
}

// ============================================================================
// FUNCTION: drawPalmTree
// Description: Renders coconut/palm trees at selected spots.
// ============================================================================
void drawPalmTree() {
    // Left boundary palm tree
    drawSinglePalmTree(100.0f, 550.0f, 160.0f);

    // Far-right boundary palm tree
    //drawSinglePalmTree(1580.0f, 550.0f, 170.0f);
}
// Helper for Mango Tree
void drawSingleMangoTree(float x, float y, float scale) {
    // Trunk
    glColor3f(0.38f, 0.24f, 0.12f);
    glBegin(GL_POLYGON);
        glVertex2f(x - (12.0f * scale), y);
        glVertex2f(x + (12.0f * scale), y);
        glVertex2f(x + (8.0f * scale), y - (110.0f * scale));
        glVertex2f(x - (8.0f * scale), y - (110.0f * scale));
    glEnd();

    // Dense Canopy Base
    float topY = y - (110.0f * scale);
    int segments = 25;

    // Foliage Clusters
    float clusters[4][3] = {
        {x - (25.0f * scale), topY - (10.0f * scale), 35.0f * scale},
        {x + (25.0f * scale), topY - (10.0f * scale), 35.0f * scale},
        {x,                   topY - (40.0f * scale), 42.0f * scale},
        {x,                   topY - (15.0f * scale), 38.0f * scale}
    };

    // Dark Green Background
    glColor3f(0.08f, 0.35f, 0.10f);
    for (int c = 0; c < 4; c++) {
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(clusters[c][0], clusters[c][1]);
            for (int i = 0; i <= segments; i++) {
                float angle = i * 2.0f * 3.14159f / segments;
                glVertex2f(clusters[c][0] + (clusters[c][2] * cos(angle)),
                           clusters[c][1] + (clusters[c][2] * sin(angle)));
            }
        glEnd();
    }

    // Bright Green Highlights
    glColor3f(0.18f, 0.55f, 0.18f);
    for (int c = 0; c < 4; c++) {
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(clusters[c][0], clusters[c][1] - (3.0f * scale));
            for (int i = 0; i <= segments; i++) {
                float angle = i * 2.0f * 3.14159f / segments;
                glVertex2f(clusters[c][0] + ((clusters[c][2] - 4.0f) * cos(angle)),
                           clusters[c][1] - (3.0f * scale) + ((clusters[c][2] - 4.0f) * sin(angle)));
            }
        glEnd();
    }

    // Hanging Mangoes (Yellow-Green Ovals)
    float mangoes[6][2] = {
        {x - 20.0f * scale, topY - 5.0f * scale},
        {x - 10.0f * scale, topY - 30.0f * scale},
        {x + 15.0f * scale, topY - 15.0f * scale},
        {x + 25.0f * scale, topY + 5.0f * scale},
        {x - 30.0f * scale, topY + 10.0f * scale},
        {x + 5.0f  * scale, topY - 45.0f * scale}
    };

    for (int m = 0; m < 6; m++) {
        glColor3f(0.85f, 0.75f, 0.10f); // Mango yellow/green
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(mangoes[m][0], mangoes[m][1]);
            for (int i = 0; i <= segments; i++) {
                float angle = i * 2.0f * 3.14159f / segments;
                glVertex2f(mangoes[m][0] + (4.0f * scale * cos(angle)),
                           mangoes[m][1] + (6.0f * scale * sin(angle)));
            }
        glEnd();
    }
}

void drawMangoTree() {
    // School Math-er Bam pashe Rakha holo (Adjust X as needed)
    drawSingleMangoTree(260.0f, 550.0f, 1.0f);
}
// Helper for Banana Tree
void drawSingleBananaTree(float x, float y, float scale) {
    // Soft Green Stem (Pseudostem)
    glColor3f(0.40f, 0.65f, 0.20f);
    glBegin(GL_POLYGON);
        glVertex2f(x - (8.0f * scale), y);
        glVertex2f(x + (8.0f * scale), y);
        glVertex2f(x + (5.0f * scale), y - (80.0f * scale));
        glVertex2f(x - (5.0f * scale), y - (80.0f * scale));
    glEnd();

    float topY = y - (80.0f * scale);

    // Large Wide Leaves (6 Arching Leaves)
    glColor3f(0.20f, 0.70f, 0.15f);
    float angles[] = { -140.0f, -100.0f, -40.0f, 40.0f, 100.0f, 140.0f };

    for (int i = 0; i < 6; i++) {
        float rad = angles[i] * 3.14159f / 180.0f;
        float endX = x + (55.0f * scale * cos(rad));
        float endY = topY - (35.0f * scale * sin(rad));

        // Wide Oval-like Leaf
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f((x + endX) / 2.0f, (topY + endY) / 2.0f + (10.0f * scale));
            glVertex2f(x, topY);
            glVertex2f(endX - (10.0f * scale), endY + (5.0f * scale));
            glVertex2f(endX, endY);
            glVertex2f(endX + (10.0f * scale), endY - (5.0f * scale));
        glEnd();

        // Leaf Center Rib Line
        glColor3f(0.12f, 0.45f, 0.10f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
            glVertex2f(x, topY);
            glVertex2f(endX, endY);
        glEnd();
        glColor3f(0.20f, 0.70f, 0.15f); // Reset Leaf Color
    }

    // Banana Blossom / Bunch (Redish-Purple Heart at Center)
    glColor3f(0.50f, 0.10f, 0.20f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - (6.0f * scale), topY + (10.0f * scale));
        glVertex2f(x + (6.0f * scale), topY + (10.0f * scale));
        glVertex2f(x, topY + (25.0f * scale));
    glEnd();
}

void drawBananaTree() {
    // School-er Bam side e
    drawSingleBananaTree(360.0f, 550.0f, 0.95f);
}
// Helper for Cypress / Cone Shaped Ornamental Tree
void drawSingleDecorativeTree(float x, float y, float scale) {
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
    float layers[3][3] = {
        {45.0f * scale, 35.0f * scale, 0.12f}, // {Height, Half-Width, Color-Green-Tone}
        {40.0f * scale, 28.0f * scale, 0.16f},
        {35.0f * scale, 20.0f * scale, 0.22f}
    };

    float currY = baseY;
    for (int i = 0; i < 3; i++) {
        glColor3f(0.05f, layers[i][2] + 0.25f, 0.10f);
        glBegin(GL_TRIANGLES);
            glVertex2f(x - layers[i][1], currY);
            glVertex2f(x + layers[i][1], currY);
            glVertex2f(x, currY - layers[i][0]);
        glEnd();
        currY -= (layers[i][0] * 0.60f); // Overlap layers
    }
}

void drawDecorativeTree() {
    // School-er Mukhopath / Main Entrance-er Dui Pashe
    drawSingleDecorativeTree(680.0f, 550.0f, 0.85f); // Entrance Left
    drawSingleDecorativeTree(920.0f, 550.0f, 0.85f); // Entrance Right
}
// ============================================================================
// FUNCTION: drawAssemblyGround
// Description: Fills the lower half with green grass, parade grounds, and pathways.
// ============================================================================
void drawAssemblyGround() {
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
