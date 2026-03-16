// main.cpp

// Iteration: 1 (Iter 2: H key, Iter 3: S/L keys, lighting setup)
// Description: GLUT initialisation, window creation, and callback
//              registration. No geometry code here.

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
#include "lighting.h"

#include <cstdio>
#include <cstdlib>

// ---------------------------------------------------------------------------
// FPS counter
// ---------------------------------------------------------------------------
static int  frameCount   = 0;
static int  previousTime = 0;

static void updateTitle() {
    char camInfo[256];
    gCamera.getTitleInfo(camInfo, sizeof(camInfo));
    char title[512];
    snprintf(title, sizeof(title), "%s  |  FPS: ...", camInfo);
    glutSetWindowTitle(title);
}

static void updateFPS() {
    frameCount++;
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int elapsed = currentTime - previousTime;
    if (elapsed > 100) {
        float fps = frameCount * 1000.0f / elapsed;
        char camInfo[256];
        gCamera.getTitleInfo(camInfo, sizeof(camInfo));
        char title[512];
        snprintf(title, sizeof(title),
                 "%s  |  Highlight: %s  |  Light: %s  |  Shading: %s  |  FPS: %.0f",
                 camInfo, getHighlightName(),
                 gScene.lightingEnabled ? "ON" : "OFF",
                 gScene.smoothShading   ? "SMOOTH" : "FLAT",
                 fps);
        glutSetWindowTitle(title);
        previousTime = currentTime;
        frameCount   = 0;
    }
}

// ---------------------------------------------------------------------------
// display
// ---------------------------------------------------------------------------
static void display() {
    glClearColor(Cfg::COL_BACKGROUND[0], Cfg::COL_BACKGROUND[1],
                 Cfg::COL_BACKGROUND[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    if (h == 0) h = 1;
    float aspect = static_cast<float>(w) / static_cast<float>(h);
    gluPerspective(Cfg::FOV_Y, aspect, Cfg::NEAR_CLIP, Cfg::FAR_CLIP);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gCamera.applyView();

    drawScene();

    glutSwapBuffers();
    updateFPS();
}

// ---------------------------------------------------------------------------
static void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

// ---------------------------------------------------------------------------
static void keyboard(unsigned char key, int /*x*/, int /*y*/) {
    switch (key) {
        case 27:
            exit(0);
            break;

        case 'w': case 'W':
            gScene.wireframe = !gScene.wireframe;
            break;

        case 'a': case 'A':
            gScene.showAxes = !gScene.showAxes;
            break;

        case 's': case 'S':  // Iter 3: flat/smooth shading toggle
            gScene.smoothShading = !gScene.smoothShading;
            break;

        case 'l': case 'L':  // Iter 3: lighting on/off toggle
            gScene.lightingEnabled = !gScene.lightingEnabled;
            break;

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
static void mouseButton(int button, int state, int x, int y) {
    gCamera.handleMouseButton(button, state, x, y);
}

static void mouseMotion(int x, int y) {
    gCamera.handleMouseMotion(x, y);
}

// ---------------------------------------------------------------------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(Cfg::WIN_W, Cfg::WIN_H);
    glutCreateWindow("Space Shuttle — Iteration 3");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_NORMALIZE);  // Iter 3: auto-normalize normals after scaling

    // Iter 3: configure light parameters once
    setupLighting();

    gCamera.init();
    initScene();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);

    updateTitle();
    previousTime = glutGet(GLUT_ELAPSED_TIME);

    glutMainLoop();
    return 0;
}
