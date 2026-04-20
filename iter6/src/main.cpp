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

static int  frameCount = 0;
static int  previousTime = 0;

static void updateFPS() {
    frameCount++;
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int elapsed = currentTime - previousTime;
    if (elapsed > 100) {
        float fps = frameCount * 1000.0f / elapsed;
        char camInfo[256];
        gCamera.getTitleInfo(camInfo, sizeof(camInfo));
        const char* doorStr = (gScene.doorAngle > 1.0f) ? "OPEN" : "CLOSED";
        if (gScene.doorAnimating) doorStr = "MOVING";
        const char* hlName = getHighlightName();
        char title[512];
        snprintf(title, sizeof(title),
            "Space Shuttle  |  %s  |  HL:%s  |  Doors:%s  |  L:%s  |  S:%s  |  FPS:%.0f",
            camInfo, hlName, doorStr,
            gScene.lightingEnabled ? "ON" : "OFF",
            gScene.smoothShading ? "SM" : "FL",
            fps);
        glutSetWindowTitle(title);
        previousTime = currentTime;
        frameCount = 0;
    }
}

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

    if (gCamera.isInterior()) {
        gluPerspective(Cfg::INTERIOR_FOV, aspect, Cfg::INTERIOR_NEAR, Cfg::FAR_CLIP);
    }
    else {
        gluPerspective(Cfg::FOV_Y, aspect, Cfg::NEAR_CLIP, Cfg::FAR_CLIP);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gCamera.applyView();

    drawScene();

    glutSwapBuffers();
    updateFPS();
}

static void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

static void keyboard(unsigned char key, int /*x*/, int /*y*/) {
    bool interior = gCamera.isInterior();

    if (interior) {
        switch (key) {
        case 'w': case 'W':
            gCamera.moveForward(Cfg::INTCAM_MOVE_SPEED);
            glutPostRedisplay(); return;
        case 's': case 'S':
            gCamera.moveForward(-Cfg::INTCAM_MOVE_SPEED);
            glutPostRedisplay(); return;
        case 'a': case 'A':
            gCamera.moveRight(-Cfg::INTCAM_MOVE_SPEED);
            glutPostRedisplay(); return;
        case 'd': case 'D':
            gCamera.moveRight(Cfg::INTCAM_MOVE_SPEED);
            glutPostRedisplay(); return;
        case 'q': case 'Q':
            gCamera.moveUp(-Cfg::INTCAM_MOVE_SPEED);
            glutPostRedisplay(); return;
        case 'e': case 'E':
            gCamera.moveUp(Cfg::INTCAM_MOVE_SPEED);
            glutPostRedisplay(); return;
        default: break;
        }
    }

    // Non-interior or non-WASD keys
    switch (key) {
    case 27:
        if (interior) {
            gCamera.toggleMode();
        }
        else {
            exit(0);
        }
        break;

    case 'w': case 'W':
        gScene.wireframe = !gScene.wireframe;
        break;

    case 'a': case 'A':
        gScene.showAxes = !gScene.showAxes;
        break;

    case 's': case 'S':
        gScene.smoothShading = !gScene.smoothShading;
        break;

    case 'l': case 'L':
        gScene.lightingEnabled = !gScene.lightingEnabled;
        break;

    case 'f': case 'F':
        gCamera.toggleMode();
        break;

    case 'o': case 'O':
        toggleDoorAnimation();
        break;

    case 'h': case 'H':
        cycleHighlight();
        break;

    case 'r': case 'R':
        resetScene();
        gCamera.reset();
        break;

    case '1': case '2': case '3': case '4': case '5': case '6':
        gCamera.setPreset(key - '0');
        break;

    default:
        break;
    }
    glutPostRedisplay();
}

static void mouseButton(int button, int state, int x, int y) {
    gCamera.handleMouseButton(button, state, x, y);
}

static void mouseMotion(int x, int y) {
    gCamera.handleMouseMotion(x, y);
}

static void passiveMotion(int x, int y) {
    gCamera.handlePassiveMotion(x, y);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(Cfg::WIN_W, Cfg::WIN_H);
    glutCreateWindow("Space Shuttle — Iteration 5");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_NORMALIZE);

    setupLighting();
    gCamera.init();
    initScene();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(passiveMotion);

    previousTime = glutGet(GLUT_ELAPSED_TIME);

    glutMainLoop();
    return 0;
}