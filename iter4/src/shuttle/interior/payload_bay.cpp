// payload_bay.cpp

// Iteration: 4
// Description: Payload bay interior structure (longerons + frames)
//              and animated cargo bay doors with structural ribs.

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
// drawPayloadBayInterior: skeletal longerons and frames visible when
//                         bay doors are open.
// ---------------------------------------------------------------------------
void drawPayloadBayInterior() {
    float halfW = Cfg::PBAY_INT_W * 0.5f;
    float bayLen = Cfg::PBAY_LENGTH;
    float z0 = Cfg::PBAY_Z_START;
    float z1 = z0 + bayLen;
    float midZ = (z0 + z1) * 0.5f;

    // ── Longerons: horizontal beams along the bay on each side ──
    matIntLongeron();
    float longeronSpacing = (Cfg::PBAY_Y - Cfg::PBAY_FLOOR_Y) /
        (Cfg::LONGERON_COUNT + 1);
    for (int side = -1; side <= 1; side += 2) {
        float x = side * halfW;
        for (int i = 1; i <= Cfg::LONGERON_COUNT; ++i) {
            float y = Cfg::PBAY_FLOOR_Y + longeronSpacing * i;
            glPushMatrix();
            glTranslatef(x, y, midZ);
            DrawBox(Cfg::LONGERON_W, Cfg::LONGERON_H, bayLen);
            glPopMatrix();
        }
    }

    // ── Frames: vertical ribs across the bay ──
    float frameSpacing = bayLen / (Cfg::FRAME_COUNT + 1);
    for (int i = 1; i <= Cfg::FRAME_COUNT; ++i) {
        float z = z0 + frameSpacing * i;

        // Bottom beam
        matIntLongeron();
        glPushMatrix();
        glTranslatef(0.0f, Cfg::PBAY_FLOOR_Y, z);
        DrawBox(Cfg::PBAY_INT_W, Cfg::FRAME_H, Cfg::FRAME_W);
        glPopMatrix();

        // Side uprights
        float uprightH = Cfg::PBAY_Y - Cfg::PBAY_FLOOR_Y;
        float uprightMidY = (Cfg::PBAY_FLOOR_Y + Cfg::PBAY_Y) * 0.5f;
        for (int side = -1; side <= 1; side += 2) {
            glPushMatrix();
            glTranslatef(side * halfW, uprightMidY, z);
            DrawBox(Cfg::FRAME_W, uprightH, Cfg::FRAME_W);
            glPopMatrix();
        }
    }

    // ── Bay floor ──
    matIntFloor();
    glPushMatrix();
    glTranslatef(0.0f, Cfg::PBAY_FLOOR_Y - 0.005f, midZ);
    DrawBox(Cfg::PBAY_INT_W, 0.01f, bayLen);
    glPopMatrix();
}

// ---------------------------------------------------------------------------
// drawOneDoor: a single door panel with structural ribs on its interior.
//              Drawn in local coords where the hinge is at X=0.
//              Panel extends in +X direction (width = PBAY_WIDTH/2).
// ---------------------------------------------------------------------------
static void drawOneDoor() {
    float doorW = Cfg::PBAY_WIDTH * 0.5f;
    float doorLen = Cfg::DOOR_FULL_LENGTH;
    float halfW = doorW * 0.5f;

    // Outer skin (white)
    matIntDoor();
    glPushMatrix();
    glTranslatef(halfW, 0.0f, 0.0f);
    DrawBox(doorW, Cfg::DOOR_PANEL_T, doorLen);
    glPopMatrix();

    // Interior structural ribs (visible when doors open)
    matIntLongeron();
    float ribSpacing = doorLen / (Cfg::DOOR_RIB_COUNT + 1);
    for (int i = 1; i <= Cfg::DOOR_RIB_COUNT; ++i) {
        float z = -doorLen * 0.5f + ribSpacing * i;
        glPushMatrix();
        glTranslatef(halfW, -Cfg::DOOR_PANEL_T * 0.5f - 0.005f, z);
        DrawBox(doorW * 0.9f, 0.008f, Cfg::DOOR_RIB_W);
        glPopMatrix();
    }

    // Longitudinal rib along centre of door
    glPushMatrix();
    glTranslatef(halfW, -Cfg::DOOR_PANEL_T * 0.5f - 0.005f, 0.0f);
    DrawBox(Cfg::DOOR_RIB_W, 0.008f, doorLen * 0.95f);
    glPopMatrix();
}

// ---------------------------------------------------------------------------
// drawPayloadBayDoors: two door panels hinged at the fuselage edges.
//   doorAngleDeg: 0 = closed, DOOR_OPEN_DEG = fully open.
//   Left door hinge at -PBAY_WIDTH/2, opens by rotating +angle about Z.
//   Right door hinge at +PBAY_WIDTH/2, opens by rotating -angle about Z.
// ---------------------------------------------------------------------------
void drawPayloadBayDoors(float doorAngleDeg) {
    float halfW = Cfg::PBAY_WIDTH * 0.5f;
    float midZ = Cfg::PBAY_Z_START + Cfg::DOOR_FULL_LENGTH * 0.5f;

    // Left door
    glPushMatrix();
    glTranslatef(-halfW, Cfg::PBAY_Y, midZ);
    glRotatef(doorAngleDeg, 0.0f, 0.0f, 1.0f);
    drawOneDoor();
    glPopMatrix();

    // Right door (mirrored)
    glPushMatrix();
    glTranslatef(halfW, Cfg::PBAY_Y, midZ);
    glRotatef(-doorAngleDeg, 0.0f, 0.0f, 1.0f);
    glScalef(-1.0f, 1.0f, 1.0f);
    drawOneDoor();
    glPopMatrix();
}