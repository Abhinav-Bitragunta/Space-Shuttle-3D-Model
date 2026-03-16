// main.cpp

// Iteration: 1
// Description: GLUT initialisation, window creation, and callback
//              registration. No geometry code here — delegates to
//              scene.cpp and camera.cpp.

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include "config.h"
#include "camera.h"
#include "scene.h"

#include <cstdio>
#include <cstdlib>

// ---------------------------------------------------------------------------
// FPS counter state
// ---------------------------------------------------------------------------
static int  frameCount    = 0;
static int  previousTime  = 0;

// ---------------------------------------------------------------------------
// updateTitle: updates window title with camera info and FPS.
// ---------------------------------------------------------------------------
static void updateTitle() {
    char camInfo[256];
    gCamera.getTitleInfo(camInfo, sizeof(camInfo));

    char title[512];
    snprintf(title, sizeof(title), "%s  |  FPS: counting...", camInfo);
    glutSetWindowTitle(title);
}

// ---------------------------------------------------------------------------
// updateFPS: called every frame; updates title once per second.
// ---------------------------------------------------------------------------
static void updateFPS() {
    frameCount++;
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int elapsed = currentTime - previousTime;
    if (elapsed > 100) {
        float fps = frameCount * 1000.0f / elapsed;
        char camInfo[256];
        gCamera.getTitleInfo(camInfo, sizeof(camInfo));

        char title[512];
        snprintf(title, sizeof(title), "%s  |  Highlight: %s  |  FPS: %.0f",
                 camInfo, getHighlightName(), fps);
        glutSetWindowTitle(title);

        previousTime = currentTime;
        frameCount   = 0;
    }
}

// ---------------------------------------------------------------------------
// display: main render callback.
// ---------------------------------------------------------------------------
static void display() {
    glClearColor(Cfg::COL_BACKGROUND[0], Cfg::COL_BACKGROUND[1],
                 Cfg::COL_BACKGROUND[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ---- Projection ----
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    if (h == 0) h = 1;
    float aspect = static_cast<float>(w) / static_cast<float>(h);
    gluPerspective(Cfg::FOV_Y, aspect, Cfg::NEAR_CLIP, Cfg::FAR_CLIP);

    // ---- Modelview / Camera ----
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gCamera.applyView();

    // ---- Draw scene ----
    drawScene();

    // ---- Swap and update FPS ----
    glutSwapBuffers();
    updateFPS();
}

// ---------------------------------------------------------------------------
// reshape: window resize callback.
// ---------------------------------------------------------------------------
static void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

// ---------------------------------------------------------------------------
// keyboard: normal key callback.
// ---------------------------------------------------------------------------
static void keyboard(unsigned char key, int /*x*/, int /*y*/) {
    switch (key) {
        case 27: // Esc
            exit(0);
            break;

        case 'w': case 'W':
            gScene.wireframe = !gScene.wireframe;
            break;

        case 'a': case 'A':
            gScene.showAxes = !gScene.showAxes;
            break;

        // TODO: Iter 3 — 's'/'S' toggle flat/smooth shading
        // TODO: Iter 3 — 'l'/'L' toggle lighting
        // TODO: Iter 4 — 'f'/'F' toggle exterior/interior
        // TODO: Iter 4 — 'o'/'O' open/close payload bay doors

        case 'h': case 'H':
            cycleHighlight();
            break;

        case '1': case '2': case '3': case '4': case '5': case '6':
            gCamera.setPreset(key - '0');
            break;

        default:
            break;
    }
    glutPostRedisplay();
}

// ---------------------------------------------------------------------------
// mouseButton: GLUT mouse button callback.
// ---------------------------------------------------------------------------
static void mouseButton(int button, int state, int x, int y) {
    gCamera.handleMouseButton(button, state, x, y);
}

// ---------------------------------------------------------------------------
// mouseMotion: GLUT mouse drag callback.
// ---------------------------------------------------------------------------
static void mouseMotion(int x, int y) {
    gCamera.handleMouseMotion(x, y);
}

// ---------------------------------------------------------------------------
// main: entry point.
// ---------------------------------------------------------------------------
int main(int argc, char** argv) {
    // GLUT init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(Cfg::WIN_W, Cfg::WIN_H);
    glutCreateWindow("Space Shuttle — Iteration 2");

    // OpenGL state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Initialise modules
    gCamera.init();
    initScene();

    // Register callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);

    // Initial title
    updateTitle();

    // Timer for FPS tracking
    previousTime = glutGet(GLUT_ELAPSED_TIME);

    glutMainLoop();
    return 0;
}
