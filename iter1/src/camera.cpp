// camera.cpp

// Iteration: 1
// Description: Orbit camera implementation with mouse-driven rotation,
//              zoom, pan, scroll-wheel zoom, and numbered preset viewpoints.

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include "camera.h"
#include "config.h"
#include <cmath>
#include <cstdio>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Camera gCamera;

void Camera::init() {
    mode       = Mode::ORBIT;
    azimuth    = Cfg::CAM_DEFAULT_AZIMUTH;
    elevation  = Cfg::CAM_DEFAULT_ELEVATION;
    distance   = Cfg::CAM_DEFAULT_DISTANCE;
    panX       = 0.0f;
    panY       = 0.0f;
    posX = posY = posZ = 0.0f;
    yaw = pitch = 0.0f;
    lastMouseX = lastMouseY = 0;
    activeButton = -1;
}

void Camera::applyView() const {
    if (mode == Mode::ORBIT) {
        float azRad  = static_cast<float>(azimuth  * M_PI / 180.0);
        float elRad  = static_cast<float>(elevation * M_PI / 180.0);

        float eyeX = distance * cosf(elRad) * sinf(azRad);
        float eyeY = distance * sinf(elRad);
        float eyeZ = distance * cosf(elRad) * cosf(azRad);

        gluLookAt(eyeX + panX, eyeY + panY, eyeZ,
                  panX, panY, 0.0,
                  0.0, 1.0, 0.0);
    }
    // TODO: Iter 4 — interior first-person view
    // TODO: Iter 5 — cinematic camera with interpolation
}

void Camera::handleMouseButton(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        activeButton = button;
        lastMouseX = x;
        lastMouseY = y;
    } else {
        activeButton = -1;
    }

    // Scroll wheel zoom
    if (button == 3) { // scroll up
        handleScroll(1);
    } else if (button == 4) { // scroll down
        handleScroll(-1);
    }
}

void Camera::handleMouseMotion(int x, int y) {
    int dx = x - lastMouseX;
    int dy = y - lastMouseY;
    lastMouseX = x;
    lastMouseY = y;

    if (mode != Mode::ORBIT) return;

    if (activeButton == GLUT_LEFT_BUTTON) {
        // Orbit: rotate
        azimuth   -= dx * Cfg::CAM_ORBIT_SENSITIVITY;
        elevation += dy * Cfg::CAM_ORBIT_SENSITIVITY;
        if (elevation > Cfg::CAM_ELEVATION_MAX) elevation = Cfg::CAM_ELEVATION_MAX;
        if (elevation < Cfg::CAM_ELEVATION_MIN) elevation = Cfg::CAM_ELEVATION_MIN;
    } else if (activeButton == GLUT_RIGHT_BUTTON) {
        // Zoom: drag up/down
        distance += dy * Cfg::CAM_ZOOM_SENSITIVITY;
        if (distance < Cfg::CAM_MIN_DISTANCE) distance = Cfg::CAM_MIN_DISTANCE;
        if (distance > Cfg::CAM_MAX_DISTANCE) distance = Cfg::CAM_MAX_DISTANCE;
    } else if (activeButton == GLUT_MIDDLE_BUTTON) {
        // Pan
        panX -= dx * Cfg::CAM_PAN_SENSITIVITY * distance;
        panY += dy * Cfg::CAM_PAN_SENSITIVITY * distance;
    }

    glutPostRedisplay();
}

void Camera::handleScroll(int dir) {
    distance -= dir * Cfg::CAM_SCROLL_STEP;
    if (distance < Cfg::CAM_MIN_DISTANCE) distance = Cfg::CAM_MIN_DISTANCE;
    if (distance > Cfg::CAM_MAX_DISTANCE) distance = Cfg::CAM_MAX_DISTANCE;
    glutPostRedisplay();
}

void Camera::setPreset(int preset) {
    panX = 0.0f;
    panY = 0.0f;
    distance = Cfg::CAM_DEFAULT_DISTANCE;

    switch (preset) {
        case 1: // Front
            azimuth = 0.0f;   elevation = 0.0f;
            break;
        case 2: // Right side
            azimuth = 90.0f;  elevation = 0.0f;
            break;
        case 3: // Aft (behind)
            azimuth = 180.0f; elevation = 0.0f;
            break;
        case 4: // Top
            azimuth = 0.0f;   elevation = 89.0f;
            break;
        case 5: // 3/4 view
            azimuth = 35.0f;  elevation = 25.0f;
            break;
        case 6: // Launch pad (below, looking up)
            azimuth = 10.0f;  elevation = -30.0f;
            distance = 12.0f;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void Camera::getTitleInfo(char* buf, int bufSize) const {
    snprintf(buf, bufSize, "Space Shuttle — Azimuth: %.1f  Elevation: %.1f  Dist: %.1f  Mouse: (%d, %d)",
             azimuth, elevation, distance, lastMouseX, lastMouseY);
}
