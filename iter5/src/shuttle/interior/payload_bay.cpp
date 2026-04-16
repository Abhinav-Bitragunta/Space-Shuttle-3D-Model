// payload_bay.cpp

// Iteration: 4 (Iter 5: two-segment doors around overhead panel)
// Description: Animated cabin roof doors — split into aft and forward
//              segments to clear the overhead switch panel.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "payload_bay.h"
#include "../../config.h"
#include "../../primitives.h"
#include "../../materials.h"

// ---------------------------------------------------------------------------
// drawOneDoorPanel: a single door panel with structural ribs.
//   Drawn in local coords: hinge at X=0, extends in +X.
//   doorLen: Z-extent of this segment.
//   ribCount: number of transverse ribs.
// ---------------------------------------------------------------------------
static void drawOneDoorPanel(float doorLen, int ribCount) {
    float doorW = Cfg::PBAY_WIDTH * 0.5f;
    float halfW = doorW * 0.5f;

    // Outer skin
    matIntDoor();
    glPushMatrix();
    glTranslatef(halfW, 0.0f, 0.0f);
    DrawBox(doorW, Cfg::DOOR_PANEL_T, doorLen);
    glPopMatrix();

    // Interior structural ribs (transverse)
    matIntLongeron();
    float ribSpacing = doorLen / (ribCount + 1);
    for (int i = 1; i <= ribCount; ++i) {
        float z = -doorLen * 0.5f + ribSpacing * i;
        glPushMatrix();
        glTranslatef(halfW, -Cfg::DOOR_PANEL_T * 0.5f - 0.005f, z);
        DrawBox(doorW * 0.9f, 0.008f, Cfg::DOOR_RIB_W);
        glPopMatrix();
    }

    // Longitudinal rib along centre
    glPushMatrix();
    glTranslatef(halfW, -Cfg::DOOR_PANEL_T * 0.5f - 0.005f, 0.0f);
    DrawBox(Cfg::DOOR_RIB_W, 0.008f, doorLen * 0.95f);
    glPopMatrix();
}

// ---------------------------------------------------------------------------
// drawDoorPair: left + right door panels for one segment.
//   segMidZ: Z centre of this segment (orbiter-local).
//   segLen:  Z length of this segment.
//   ribCount: ribs per panel.
//   doorAngleDeg: 0 = closed, DOOR_OPEN_DEG = fully open.
// ---------------------------------------------------------------------------
static void drawDoorPair(float segMidZ, float segLen, int ribCount,
    float doorAngleDeg) {
    float halfW = Cfg::PBAY_WIDTH * 0.5f;

    // Left door
    glPushMatrix();
    glTranslatef(-halfW, Cfg::PBAY_Y, segMidZ);
    glRotatef(doorAngleDeg, 0.0f, 0.0f, 1.0f);
    drawOneDoorPanel(segLen, ribCount);
    glPopMatrix();

    // Right door (mirrored)
    glPushMatrix();
    glTranslatef(halfW, Cfg::PBAY_Y, segMidZ);
    glRotatef(-doorAngleDeg, 0.0f, 0.0f, 1.0f);
    glScalef(-1.0f, 1.0f, 1.0f);
    glFrontFace(GL_CW);   // negative scale flips winding
    drawOneDoorPanel(segLen, ribCount);
    glFrontFace(GL_CCW);  // restore
    glPopMatrix();
}

// ---------------------------------------------------------------------------
// drawPayloadBayDoors: two door segments — aft and forward — that together
//   cover the cabin roof while clearing the overhead switch panel.
// ---------------------------------------------------------------------------
void drawPayloadBayDoors(float doorAngleDeg) {
    // Aft segment (behind overhead panel)
    float aftMidZ = Cfg::DOOR_AFT_Z_START + Cfg::DOOR_AFT_LENGTH * 0.5f;
    drawDoorPair(aftMidZ, Cfg::DOOR_AFT_LENGTH, Cfg::DOOR_AFT_RIB_COUNT,
        doorAngleDeg);

    // Forward segment (ahead of overhead panel)
    float fwdMidZ = Cfg::DOOR_FWD_Z_START + Cfg::DOOR_FWD_LENGTH * 0.5f;
    drawDoorPair(fwdMidZ, Cfg::DOOR_FWD_LENGTH, Cfg::DOOR_FWD_RIB_COUNT,
        doorAngleDeg);
}