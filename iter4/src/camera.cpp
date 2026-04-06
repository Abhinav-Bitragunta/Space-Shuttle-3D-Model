// camera.cpp

// Iteration: 1 (Iter 4: interior first-person mode)
// Description: Orbit camera + interior first-person camera.

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
    mode = Mode::ORBIT;
    azimuth = Cfg::CAM_DEFAULT_AZIMUTH;
    elevation = Cfg::CAM_DEFAULT_ELEVATION;
    distance = Cfg::CAM_DEFAULT_DISTANCE;
    panX = 0.0f;
    panY = 0.0f;
    posX = Cfg::INTCAM_START_X;
    posY = Cfg::INTCAM_START_Y;
    posZ = Cfg::INTCAM_START_Z;
    yaw = Cfg::INTCAM_START_YAW;
    pitch = Cfg::INTCAM_START_PITCH;
    warpIgnore = false;
    lastMouseX = lastMouseY = 0;
    activeButton = -1;
}

void Camera::applyView() const {
    if (mode == Mode::ORBIT) {
        float azRad = static_cast<float>(azimuth * M_PI / 180.0);
        float elRad = static_cast<float>(elevation * M_PI / 180.0);
        float eyeX = distance * cosf(elRad) * sinf(azRad);
        float eyeY = distance * sinf(elRad);
        float eyeZ = distance * cosf(elRad) * cosf(azRad);
        gluLookAt(eyeX + panX, eyeY + panY, eyeZ,
            panX, panY, 0.0,
            0.0, 1.0, 0.0);
    }
    else if (mode == Mode::INTERIOR) {
        float yawRad = static_cast<float>(yaw * M_PI / 180.0);
        float pitchRad = static_cast<float>(pitch * M_PI / 180.0);
        // Look direction from yaw (around Y) and pitch (around X)
        float lookX = sinf(yawRad) * cosf(pitchRad);
        float lookY = sinf(pitchRad);
        float lookZ = cosf(yawRad) * cosf(pitchRad);
        gluLookAt(posX, posY, posZ,
            posX + lookX, posY + lookY, posZ + lookZ,
            0.0, 1.0, 0.0);
    }
    // TODO: Iter 5 — CINEMATIC mode
}

void Camera::toggleMode() {
    if (mode == Mode::ORBIT) {
        mode = Mode::INTERIOR;
        // Reset interior camera to start position
        posX = Cfg::INTCAM_START_X;
        posY = Cfg::INTCAM_START_Y;
        posZ = Cfg::INTCAM_START_Z;
        yaw = Cfg::INTCAM_START_YAW;
        pitch = Cfg::INTCAM_START_PITCH;
        warpIgnore = true;
        // Centre cursor
        glutWarpPointer(Cfg::WIN_W / 2, Cfg::WIN_H / 2);
        glutSetCursor(GLUT_CURSOR_NONE);
    }
    else {
        mode = Mode::ORBIT;
        glutSetCursor(GLUT_CURSOR_INHERIT);
    }
}

void Camera::handleMouseButton(int button, int state, int x, int y) {
    if (mode != Mode::ORBIT) return;

    if (state == GLUT_DOWN) {
        activeButton = button;
        lastMouseX = x;
        lastMouseY = y;
    }
    else {
        activeButton = -1;
    }
    if (button == 3) handleScroll(1);
    else if (button == 4) handleScroll(-1);
}

void Camera::handleMouseMotion(int x, int y) {
    if (mode == Mode::ORBIT) {
        int dx = x - lastMouseX;
        int dy = y - lastMouseY;
        lastMouseX = x;
        lastMouseY = y;

        if (activeButton == GLUT_LEFT_BUTTON) {
            azimuth -= dx * Cfg::CAM_ORBIT_SENSITIVITY;
            elevation += dy * Cfg::CAM_ORBIT_SENSITIVITY;
            if (elevation > Cfg::CAM_ELEVATION_MAX) elevation = Cfg::CAM_ELEVATION_MAX;
            if (elevation < Cfg::CAM_ELEVATION_MIN) elevation = Cfg::CAM_ELEVATION_MIN;
        }
        else if (activeButton == GLUT_RIGHT_BUTTON) {
            distance += dy * Cfg::CAM_ZOOM_SENSITIVITY;
            if (distance < Cfg::CAM_MIN_DISTANCE) distance = Cfg::CAM_MIN_DISTANCE;
            if (distance > Cfg::CAM_MAX_DISTANCE) distance = Cfg::CAM_MAX_DISTANCE;
        }
        else if (activeButton == GLUT_MIDDLE_BUTTON) {
            panX -= dx * Cfg::CAM_PAN_SENSITIVITY * distance;
            panY += dy * Cfg::CAM_PAN_SENSITIVITY * distance;
        }
        glutPostRedisplay();
    }
}

void Camera::handlePassiveMotion(int x, int y) {
    if (mode != Mode::INTERIOR) return;

    int winW = glutGet(GLUT_WINDOW_WIDTH);
    int winH = glutGet(GLUT_WINDOW_HEIGHT);
    int cx = winW / 2;
    int cy = winH / 2;

    // Skip the warp-back event
    if (warpIgnore) {
        if (x == cx && y == cy) {
            warpIgnore = false;
            return;
        }
        warpIgnore = false;
    }

    int dx = x - cx;
    int dy = y - cy;

    if (dx == 0 && dy == 0) return;

    yaw -= dx * Cfg::INTCAM_LOOK_SENS;
    pitch -= dy * Cfg::INTCAM_LOOK_SENS;

    if (pitch > Cfg::INTCAM_PITCH_MAX) pitch = Cfg::INTCAM_PITCH_MAX;
    if (pitch < Cfg::INTCAM_PITCH_MIN) pitch = Cfg::INTCAM_PITCH_MIN;

    warpIgnore = true;
    glutWarpPointer(cx, cy);
    glutPostRedisplay();
}

void Camera::moveForward(float amount) {
    float yawRad = static_cast<float>(yaw * M_PI / 180.0);
    posX += sinf(yawRad) * amount;
    posZ += cosf(yawRad) * amount;
    clampPosition();
}

void Camera::moveRight(float amount) {
    float yawRad = static_cast<float>(yaw * M_PI / 180.0);
    posX -= cosf(yawRad) * amount;
    posZ += sinf(yawRad) * amount;
    clampPosition();
}

void Camera::clampPosition() {
    if (posX < Cfg::INTCAM_MIN_X) posX = Cfg::INTCAM_MIN_X;
    if (posX > Cfg::INTCAM_MAX_X) posX = Cfg::INTCAM_MAX_X;
    if (posY < Cfg::INTCAM_MIN_Y) posY = Cfg::INTCAM_MIN_Y;
    if (posY > Cfg::INTCAM_MAX_Y) posY = Cfg::INTCAM_MAX_Y;
    if (posZ < Cfg::INTCAM_MIN_Z) posZ = Cfg::INTCAM_MIN_Z;
    if (posZ > Cfg::INTCAM_MAX_Z) posZ = Cfg::INTCAM_MAX_Z;
}

void Camera::handleScroll(int dir) {
    if (mode != Mode::ORBIT) return;
    distance -= dir * Cfg::CAM_SCROLL_STEP;
    if (distance < Cfg::CAM_MIN_DISTANCE) distance = Cfg::CAM_MIN_DISTANCE;
    if (distance > Cfg::CAM_MAX_DISTANCE) distance = Cfg::CAM_MAX_DISTANCE;
    glutPostRedisplay();
}

void Camera::setPreset(int preset) {
    if (mode != Mode::ORBIT) return;
    panX = 0.0f;
    panY = 0.0f;
    distance = Cfg::CAM_DEFAULT_DISTANCE;
    switch (preset) {
    case 1: azimuth = 0.0f;   elevation = 0.0f;   break;
    case 2: azimuth = 90.0f;  elevation = 0.0f;   break;
    case 3: azimuth = 180.0f; elevation = 0.0f;   break;
    case 4: azimuth = 0.0f;   elevation = 89.0f;  break;
    case 5: azimuth = 35.0f;  elevation = 25.0f;  break;
    case 6: azimuth = 10.0f;  elevation = -30.0f; distance = 12.0f; break;
    default: break;
    }
    glutPostRedisplay();
}

void Camera::getTitleInfo(char* buf, int bufSize) const {
    if (mode == Mode::ORBIT) {
        snprintf(buf, bufSize, "EXTERIOR  Az:%.0f El:%.0f D:%.1f Mouse: (%d, %d)",
            azimuth, elevation, distance, lastMouseX, lastMouseY);
    }
    else {
        snprintf(buf, bufSize, "INTERIOR  Pos:(%.2f,%.2f,%.2f) Yaw:%.0f",
            posX, posY, posZ, yaw);
    }
}