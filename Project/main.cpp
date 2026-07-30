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
#include <ctime>

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
/* ==========================================================
   DRAW BUTTERFLY FUNCTION
   Draws colorful butterflies hovering near vegetation/sky
   ========================================================== */
void drawButterfly()
{
    glPushMatrix();
        glTranslatef(butterflyOffsetX, butterflyOffsetY, 0.0f);

        // --- Butterfly 1 (Bright Orange/Red Winged) ---
        float bx1 = 450.0f, by1 = 210.0f;

        // Outer Left Wing
        glColor3f(0.95f, 0.40f, 0.10f);
        glBegin(GL_TRIANGLES);
            glVertex2f(bx1, by1);
            glVertex2f(bx1 - 15.0f, by1 - 12.0f);
            glVertex2f(bx1 - 12.0f, by1 + 5.0f);

            glVertex2f(bx1, by1);
            glVertex2f(bx1 - 12.0f, by1 + 6.0f);
            glVertex2f(bx1 - 8.0f, by1 + 14.0f);
        glEnd();

        // Outer Right Wing
        glBegin(GL_TRIANGLES);
            glVertex2f(bx1, by1);
            glVertex2f(bx1 + 15.0f, by1 - 12.0f);
            glVertex2f(bx1 + 12.0f, by1 + 5.0f);

            glVertex2f(bx1, by1);
            glVertex2f(bx1 + 12.0f, by1 + 6.0f);
            glVertex2f(bx1 + 8.0f, by1 + 14.0f);
        glEnd();

        // Inner Wing Patterns (Yellow accent)
        glColor3fv(COLOR_FLOWER_YELLOW);
        glBegin(GL_TRIANGLES);
            glVertex2f(bx1, by1);
            glVertex2f(bx1 - 8.0f, by1 - 6.0f);
            glVertex2f(bx1 - 6.0f, by1 + 2.0f);

            glVertex2f(bx1, by1);
            glVertex2f(bx1 + 8.0f, by1 - 6.0f);
            glVertex2f(bx1 + 6.0f, by1 + 2.0f);
        glEnd();

        // Body & Antennae
        glColor3fv(COLOR_BLACK);
        glLineWidth(1.5f);
        glBegin(GL_LINES);
            // Body
            glVertex2f(bx1, by1 - 8.0f);
            glVertex2f(bx1, by1 + 8.0f);
            // Antennae
            glVertex2f(bx1, by1 - 8.0f);
            glVertex2f(bx1 - 4.0f, by1 - 14.0f);
            glVertex2f(bx1, by1 - 8.0f);
            glVertex2f(bx1 + 4.0f, by1 - 14.0f);
        glEnd();

        // --- Butterfly 2 (Cyan/Blue Winged, slightly smaller) ---
        float bx2 = 1120.0f, by2 = 230.0f;

        glColor3f(0.10f, 0.70f, 0.90f);
        glBegin(GL_TRIANGLES);
            glVertex2f(bx2, by2);
            glVertex2f(bx2 - 12.0f, by2 - 10.0f);
            glVertex2f(bx2 - 10.0f, by2 + 4.0f);

            glVertex2f(bx2, by2);
            glVertex2f(bx2 + 12.0f, by2 - 10.0f);
            glVertex2f(bx2 + 10.0f, by2 + 4.0f);
        glEnd();

        glColor3fv(COLOR_BLACK);
        glBegin(GL_LINES);
            glVertex2f(bx2, by2 - 6.0f);
            glVertex2f(bx2, by2 + 6.0f);
        glEnd();

    glPopMatrix();
}
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
/* ==========================================================
   DRAW SCHOOL FUNCTION
   Draws the main 2-story school building structure, base walls,
   veranda pillars, and floor separator borders.
   Position: X (500 -> 1480), Y (220 -> 430)
   ========================================================== */
void drawSchool()
{
    // 1. Main Building Wall (Light Cream Base)
    glColor3fv(COLOR_BUILDING_CREAM);
    glBegin(GL_QUADS);
        glVertex2f(500.0f, 220.0f);
        glVertex2f(1480.0f, 220.0f);
        glVertex2f(1480.0f, 430.0f);
        glVertex2f(500.0f, 430.0f);
    glEnd();

    // 2. Building Plinth / Base Foundation (Dark Brick Red Bottom Border)
    glColor3fv(COLOR_BUILDING_RED);
    glBegin(GL_QUADS);
        glVertex2f(490.0f, 420.0f);
        glVertex2f(1490.0f, 420.0f);
        glVertex2f(1490.0f, 430.0f);
        glVertex2f(490.0f, 430.0f);
    glEnd();

    // 3. Middle Floor Separator / Slab (Brick Red Belt)
    glColor3fv(COLOR_BUILDING_RED);
    glBegin(GL_QUADS);
        glVertex2f(495.0f, 320.0f);
        glVertex2f(1485.0f, 320.0f);
        glVertex2f(1485.0f, 330.0f);
        glVertex2f(495.0f, 330.0f);
    glEnd();

    // 4. Veranda Structural Support Pillars (White/Cream Vertical Pillars)
    glColor3f(0.88f, 0.82f, 0.65f);
    for (float px = 550.0f; px <= 1450.0f; px += 130.0f)
    {
        // 2nd Floor Pillars
        glBegin(GL_QUADS);
            glVertex2f(px, 220.0f);
            glVertex2f(px + 12.0f, 220.0f);
            glVertex2f(px + 12.0f, 320.0f);
            glVertex2f(px, 320.0f);
        glEnd();

        // 1st Floor Pillars
        glBegin(GL_QUADS);
            glVertex2f(px, 330.0f);
            glVertex2f(px + 12.0f, 330.0f);
            glVertex2f(px + 12.0f, 420.0f);
            glVertex2f(px, 420.0f);
        glEnd();
    }

    // 5. Outer Structural Boundary Outline (Subtle contrast frame)
    glLineWidth(2.0f);
    glColor3fv(COLOR_BLACK);
    glBegin(GL_LINE_LOOP);
        glVertex2f(500.0f, 220.0f);
        glVertex2f(1480.0f, 220.0f);
        glVertex2f(1480.0f, 430.0f);
        glVertex2f(500.0f, 430.0f);
    glEnd();
}
/* ==========================================================
   DRAW ROOF FUNCTION
   Draws the top roof structure, shaded trapezoid canopy,
   and parapet boundary railing for the school building.
   Position: X (470 -> 1510), Y (150 -> 220)
   ========================================================== */
void drawRoof()
{
    // 1. Main Roof Canopy (Gray Slanted Trapezoid)
    glColor3fv(COLOR_ROOF_GRAY);
    glBegin(GL_POLYGON);
        glVertex2f(510.0f, 175.0f); // Top Left
        glVertex2f(1470.0f, 175.0f); // Top Right
        glVertex2f(1500.0f, 220.0f); // Bottom Right Eave
        glVertex2f(480.0f, 220.0f);  // Bottom Left Eave
    glEnd();

    // 2. Roof Bottom Overhang/Eave Border (Dark Red Strip)
    glColor3fv(COLOR_BUILDING_RED);
    glBegin(GL_QUADS);
        glVertex2f(475.0f, 215.0f);
        glVertex2f(1505.0f, 215.0f);
        glVertex2f(1505.0f, 222.0f);
        glVertex2f(475.0f, 222.0f);
    glEnd();

    // 3. Roof Top Parapet Crest Line (Dark Gray Accent Line)
    glColor3f(0.35f, 0.35f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(505.0f, 170.0f);
        glVertex2f(1475.0f, 170.0f);
        glVertex2f(1475.0f, 175.0f);
        glVertex2f(505.0f, 170.0f);
    glEnd();

    // 4. Black Structural Outlines for Crisp Visuals
    glLineWidth(2.0f);
    glColor3fv(COLOR_BLACK);
    glBegin(GL_LINE_LOOP);
        glVertex2f(510.0f, 175.0f);
        glVertex2f(1470.0f, 175.0f);
        glVertex2f(1500.0f, 220.0f);
        glVertex2f(480.0f, 220.0f);
    glEnd();
}
/* ==========================================================
   DRAW WINDOW FUNCTION
   Draws 2 rows of blue grid windows for both 1st and 2nd floors.
   ========================================================== */
void drawWindow()
{
    // Helper lambda/inline drawing logic for a window grid panel
    auto drawSingleWindow = [](float wx, float wy) {
        float wWidth = 45.0f;
        float wHeight = 50.0f;

        // Glass Pane (Blue Background)
        glColor3fv(COLOR_WINDOW_BLUE);
        glBegin(GL_QUADS);
            glVertex2f(wx, wy);
            glVertex2f(wx + wWidth, wy);
            glVertex2f(wx + wWidth, wy + wHeight);
            glVertex2f(wx, wy + wHeight);
        glEnd();

        // Window Frame & Grids (Dark Gray / Black)
        glColor3fv(COLOR_BLACK);
        glLineWidth(1.5f);

        // Outer Frame
        glBegin(GL_LINE_LOOP);
            glVertex2f(wx, wy);
            glVertex2f(wx + wWidth, wy);
            glVertex2f(wx + wWidth, wy + wHeight);
            glVertex2f(wx, wy + wHeight);
        glEnd();

        // Inner Vertical & Horizontal Grids
        glBegin(GL_LINES);
            // Center Vertical Bar
            glVertex2f(wx + wWidth / 2.0f, wy);
            glVertex2f(wx + wWidth / 2.0f, wy + wHeight);
            // Center Horizontal Bar
            glVertex2f(wx, wy + wHeight / 2.0f);
            glVertex2f(wx + wWidth, wy + wHeight / 2.0f);
        glEnd();
    };

    // --- 2nd Floor Windows (Top Row: Y = 245) ---
    for (float x = 580.0f; x <= 1400.0f; x += 130.0f)
    {
        drawSingleWindow(x, 245.0f);
    }

    // --- 1st Floor Windows (Bottom Row: Y = 350) ---
    // (Skip entrance door center area at x = 970)
    for (float x = 580.0f; x <= 1400.0f; x += 130.0f)
    {
        if (x > 900.0f && x < 1050.0f) continue; // Leave space for main door
        drawSingleWindow(x, 350.0f);
    }
}
/* ==========================================================
   DRAW DOOR FUNCTION
   Draws the main entrance double door on the ground floor.
   Position: X (950 -> 1030), Y (330 -> 420)
   ========================================================== */
/* ==========================================================
   DRAW DOOR FUNCTION (CENTER ALIGNED)
   Draws the main entrance double door centered with the roof banner.
   Position: X (950 -> 970), Y (330 -> 420)
   ========================================================== */
void drawDoor()
{
    float dx = 970.0f; // Shifted right by 20px for perfect middle alignment
    float dy = 330.0f;
    float dw = 80.0f;
    float dh = 90.0f;

    // 1. Outer Door Frame / Arch Trim (Dark Wood)
    glColor3fv(COLOR_DOOR_BROWN);
    glBegin(GL_QUADS);
        glVertex2f(dx - 4.0f, dy - 4.0f);
        glVertex2f(dx + dw + 4.0f, dy - 4.0f);
        glVertex2f(dx + dw + 4.0f, dy + dh);
        glVertex2f(dx - 4.0f, dy + dh);
    glEnd();

    // 2. Door Panels Background (Wooden finish)
    glColor3f(0.55f, 0.35f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(dx, dy);
        glVertex2f(dx + dw, dy);
        glVertex2f(dx + dw, dy + dh);
        glVertex2f(dx, dy + dh);
    glEnd();

    // 3. Center Split Line (Double Door Separation)
    glColor3fv(COLOR_BLACK);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(dx + dw / 2.0f, dy);
        glVertex2f(dx + dw / 2.0f, dy + dh);
    glEnd();

    // 4. Door Handles (Golden / Metallic Knobs)
    glColor3fv(COLOR_FLOWER_YELLOW);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glVertex2f(dx + dw / 2.0f - 6.0f, dy + dh / 2.0f);
        glVertex2f(dx + dw / 2.0f + 6.0f, dy + dh / 2.0f);
    glEnd();

    // 5. Door Frame Black Outline
    glBegin(GL_LINE_LOOP);
        glVertex2f(dx, dy);
        glVertex2f(dx + dw, dy);
        glVertex2f(dx + dw, dy + dh);
        glVertex2f(dx, dy + dh);
    glEnd();
}
/* ==========================================================
   DRAW CLOCK FUNCTION (Perfectly Centered on Wall)
   Position: On Wall between windows, below roof banner
   ========================================================== */
void drawClock()
{
    float cx = 990.0f; // Shifted left to center between window gap
    float cy = 282.0f; // Moved down to rest on empty wall below banner
    float radius = 12.0f;

    // Get System Time
    time_t t = time(0);
    struct tm *now = localtime(&t);
    int sec = now->tm_sec;
    int min = now->tm_min;
    int hour = now->tm_hour % 12;

    // 1. Outer Border
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float rad = i * 3.14159f / 180.0f;
        glVertex2f(cx + cos(rad) * (radius + 2.0f), cy + sin(rad) * (radius + 2.0f));
    }
    glEnd();

    // 2. White Dial Face
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float rad = i * 3.14159f / 180.0f;
        glVertex2f(cx + cos(rad) * radius, cy + sin(rad) * radius);
    }
    glEnd();

    // 3. Hour Marks
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    for (int i = 0; i < 12; i++) {
        float angle = i * 30.0f * 3.14159f / 180.0f;
        glBegin(GL_LINES);
        glVertex2f(cx + cos(angle) * (radius * 0.75f), cy + sin(angle) * (radius * 0.75f));
        glVertex2f(cx + cos(angle) * (radius * 0.90f), cy + sin(angle) * (radius * 0.90f));
        glEnd();
    }

    // Hand Angles
    float secAngle = (sec * 6.0f - 90.0f) * 3.14159f / 180.0f;
    float minAngle = (min * 6.0f + sec * 0.1f - 90.0f) * 3.14159f / 180.0f;
    float hourAngle = (hour * 30.0f + min * 0.5f - 90.0f) * 3.14159f / 180.0f;

    // Hour Hand
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.5f);
    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(cx + cos(hourAngle) * (radius * 0.5f), cy + sin(hourAngle) * (radius * 0.5f));
    glEnd();

    // Minute Hand
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(cx + cos(minAngle) * (radius * 0.75f), cy + sin(minAngle) * (radius * 0.75f));
    glEnd();

    // Second Hand
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(cx + cos(secAngle) * (radius * 0.85f), cy + sin(secAngle) * (radius * 0.85f));
    glEnd();

    // Center Pin
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 30) {
        float rad = i * 3.14159f / 180.0f;
        glVertex2f(cx + cos(rad) * 1.5f, cy + sin(rad) * 1.5f);
    }
    glEnd();
}
/* ==========================================================
   DRAW FLAG POLE FUNCTION (Reference Blueprint Aligned)
   Position: In front of the central entrance (X: 1050, Y: 430)
   ========================================================== */
void drawFlagPole()
{
    float px = 1050.0f; // Centered in front of school entrance
    float py = 430.0f;  // Base on ground level

    // 1. Concrete Base / Pedestal
    glColor3fv(COLOR_WALL_GRAY);
    glBegin(GL_QUADS);
    glVertex2f(px - 15.0f, py);
    glVertex2f(px + 15.0f, py);
    glVertex2f(px + 12.0f, py - 10.0f);
    glVertex2f(px - 12.0f, py - 10.0f);
    glEnd();

    // 2. Metallic Silver Pole
    glColor3fv(COLOR_POLE_GRAY);
    glBegin(GL_QUADS);
    glVertex2f(px - 2.5f, py - 10.0f);
    glVertex2f(px + 2.5f, py - 10.0f);
    glVertex2f(px + 2.5f, py - 180.0f);
    glVertex2f(px - 2.5f, py - 180.0f);
    glEnd();

    // 3. Gold Finial Ball at Top
    glColor3fv(COLOR_FLOWER_YELLOW);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 20) {
        float rad = i * 3.14159f / 180.0f;
        glVertex2f(px + cos(rad) * 5.0f, (py - 182.0f) + sin(rad) * 5.0f);
    }
    glEnd();
}

/* ==========================================================
   DRAW BANGLADESH FLAG FUNCTION (Reference Blueprint Aligned)
   Position: Attached right side of center pole
   ========================================================== */
void drawBangladeshFlag()
{
    float fx = 1052.5f; // Attached to the pole (px + 2.5)
    float fy = 250.0f;   // Top-center position
    float flagWidth = 65.0f;
    float flagHeight = 39.0f;

    // 1. Green Rectangle
    glColor3fv(COLOR_FLAG_GREEN);
    glBegin(GL_QUADS);
    glVertex2f(fx, fy);
    glVertex2f(fx + flagWidth, fy);
    glVertex2f(fx + flagWidth, fy + flagHeight);
    glVertex2f(fx, fy + flagHeight);
    glEnd();

    // 2. Red Circle
    float cx = fx + (flagWidth * 0.45f);
    float cy = fy + (flagHeight * 0.5f);
    float radius = 13.0f;

    glColor3fv(COLOR_FLAG_RED);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float rad = i * 3.14159f / 180.0f;
        glVertex2f(cx + cos(rad) * radius, cy + sin(rad) * radius);
    }
    glEnd();
}
/* ==========================================================
   DRAW ROOF BANNER FUNCTION
   Draws the red banner board located on top of the school roof.
   Position: X (820 -> 1180), Y (160 -> 200)
   ========================================================== */
void drawRoofBanner()
{
    // 1. Banner Background Plate (Vibrant Red Frame)
    glColor3fv(COLOR_FLAG_RED);
    glBegin(GL_QUADS);
        glVertex2f(820.0f, 160.0f);
        glVertex2f(1180.0f, 160.0f);
        glVertex2f(1180.0f, 200.0f);
        glVertex2f(820.0f, 200.0f);
    glEnd();

    // 2. Banner Inner Border (Yellow Accent Frame)
    glLineWidth(2.5f);
    glColor3fv(COLOR_FLOWER_YELLOW);
    glBegin(GL_LINE_LOOP);
        glVertex2f(824.0f, 164.0f);
        glVertex2f(1176.0f, 164.0f);
        glVertex2f(1176.0f, 196.0f);
        glVertex2f(824.0f, 196.0f);
    glEnd();

    // 3. Banner Mounting Steel Posts (Connecting Roof to Banner)
    glColor3fv(COLOR_BLACK);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex2f(860.0f, 200.0f);
        glVertex2f(860.0f, 215.0f);

        glVertex2f(1140.0f, 200.0f);
        glVertex2f(1140.0f, 215.0f);
    glEnd();
}

/* ---- Campus / Garden Layer ---- */
/* ==========================================================
   DRAW SHAHEED MINAR FUNCTION (Campus Layer)
   Position: Left Side Campus Field (X: 180 -> 320, Y: 360 -> 430)
   ========================================================== */
void drawShaheedMinar()
{
    // 1. Red Sun behind Central Column (Symbol of 1952)
    float sunX = 250.0f, sunY = 320.0f, sunR = 22.0f;
    glColor3f(0.85f, 0.10f, 0.10f); // Deep Blood Red
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float rad = i * 3.14159f / 180.0f;
        glVertex2f(sunX + cos(rad) * sunR, sunY + sin(rad) * sunR);
    }
    glEnd();

    // 2. Base Steps / Pedestal (3-Tiered White Marble Base)
    glColor3fv(COLOR_WHITE);
    // Tier 1 (Bottom Base)
    glBegin(GL_QUADS);
    glVertex2f(170.0f, 420.0f); glVertex2f(330.0f, 420.0f);
    glVertex2f(330.0f, 430.0f); glVertex2f(170.0f, 430.0f);
    // Tier 2 (Middle Base)
    glVertex2f(185.0f, 410.0f); glVertex2f(315.0f, 410.0f);
    glVertex2f(315.0f, 420.0f); glVertex2f(185.0f, 420.0f);
    // Tier 3 (Top Base)
    glVertex2f(200.0f, 400.0f); glVertex2f(300.0f, 400.0f);
    glVertex2f(300.0f, 410.0f); glVertex2f(200.0f, 410.0f);
    glEnd();

    // Outlines for Base Steps
    glColor3fv(COLOR_BLACK);
    glLineWidth(1.2f);
    glBegin(GL_LINE_LOOP); glVertex2f(170.0f, 420.0f); glVertex2f(330.0f, 420.0f); glVertex2f(330.0f, 430.0f); glVertex2f(170.0f, 430.0f); glEnd();
    glBegin(GL_LINE_LOOP); glVertex2f(185.0f, 410.0f); glVertex2f(315.0f, 410.0f); glVertex2f(315.0f, 420.0f); glVertex2f(185.0f, 420.0f); glEnd();
    glBegin(GL_LINE_LOOP); glVertex2f(200.0f, 400.0f); glVertex2f(300.0f, 400.0f); glVertex2f(300.0f, 410.0f); glVertex2f(200.0f, 410.0f); glEnd();

    // 3. Vertical Columns (Pillars)
    // Helper lambda for Drawing Minar Pillars with Top Slant Angle
    auto drawPillar = [](float x, float topY, float width, float slantHeight) {
        // Concrete Light Gray
        glColor3f(0.90f, 0.90f, 0.92f);
        glBegin(GL_POLYGON);
        glVertex2f(x, 400.0f);                  // Bottom Left
        glVertex2f(x + width, 400.0f);          // Bottom Right
        glVertex2f(x + width, topY);            // Top Right
        glVertex2f(x, topY + slantHeight);      // Top Left (Slanted)
        glEnd();

        // Pillar Black Outline
        glColor3fv(COLOR_BLACK);
        glLineWidth(1.5f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x, 400.0f);
        glVertex2f(x + width, 400.0f);
        glVertex2f(x + width, topY);
        glVertex2f(x, topY + slantHeight);
        glEnd();
    };

    // Outer Pair (Shortest)
    drawPillar(205.0f, 350.0f, 10.0f, 10.0f); // Outer Left
    drawPillar(285.0f, 350.0f, 10.0f, -10.0f); // Outer Right

    // Inner Pair (Medium Height)
    drawPillar(223.0f, 320.0f, 11.0f, 12.0f); // Inner Left
    drawPillar(266.0f, 320.0f, 11.0f, -12.0f); // Inner Right

    // Central Main Pillar (Tallest & Tilted Header)
    drawPillar(243.0f, 280.0f, 14.0f, 0.0f);

    // Tilted Header Roof on Central Pillar
    glColor3f(0.85f, 0.85f, 0.88f);
    glBegin(GL_POLYGON);
    glVertex2f(238.0f, 280.0f);
    glVertex2f(262.0f, 280.0f);
    glVertex2f(258.0f, 268.0f);
    glVertex2f(242.0f, 268.0f);
    glEnd();
    glColor3fv(COLOR_BLACK);
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(238.0f, 280.0f);
    glVertex2f(262.0f, 280.0f);
    glVertex2f(258.0f, 268.0f);
    glVertex2f(242.0f, 268.0f);
    glEnd();
}
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
