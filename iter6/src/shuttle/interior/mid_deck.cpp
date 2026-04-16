#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "mid_deck.h"
#include "../../config.h"
#include "../../primitives.h"
#include "../../materials.h"


// Room dimensions

static const float kHalfW = Cfg::MD_WIDTH * 0.5f;
static const float kFloorY = Cfg::MD_FLOOR_Y;
static const float kCeilY = Cfg::MD_CEIL_Y;
static const float kWT = Cfg::WALL_T;
static const float kMidZ = (Cfg::MD_Z_AFT + Cfg::MD_Z_FWD) * 0.5f;
static const float kLen = Cfg::MD_Z_FWD - Cfg::MD_Z_AFT;
static const float kRoomH = Cfg::MD_CEIL_Y - Cfg::MD_FLOOR_Y;


// Room enclosure - same overlap strategy as flight deck

static void drawRoomEnclosure() {
    // Floor: extends past side walls
    matIntFloor();
    glPushMatrix();
    glTranslatef(0.0f, kFloorY - kWT * 0.5f, kMidZ);
    DrawBox(Cfg::MD_WIDTH + kWT * 2.0f, kWT, kLen + kWT * 2.0f);
    glPopMatrix();

    // Ceiling (= flight deck floor — shared slab)
    matIntWall();
    glPushMatrix();
    glTranslatef(0.0f, kCeilY + kWT * 0.5f, kMidZ);
    DrawBox(Cfg::MD_WIDTH + kWT * 2.0f, kWT, kLen + kWT * 2.0f);
    glPopMatrix();

    // Left wall: full Z span covers corner seams
    glPushMatrix();
    glTranslatef(-kHalfW - kWT * 0.5f, (kFloorY + kCeilY) * 0.5f, kMidZ);
    DrawBox(kWT, kRoomH, kLen + kWT * 2.0f);
    glPopMatrix();

    // Right wall
    glPushMatrix();
    glTranslatef(kHalfW + kWT * 0.5f, (kFloorY + kCeilY) * 0.5f, kMidZ);
    DrawBox(kWT, kRoomH, kLen + kWT * 2.0f);
    glPopMatrix();

    // Aft wall (fits inside side walls)
    glPushMatrix();
    glTranslatef(0.0f, (kFloorY + kCeilY) * 0.5f, Cfg::MD_Z_AFT - kWT * 0.5f);
    DrawBox(Cfg::MD_WIDTH, kRoomH, kWT);
    glPopMatrix();

    // Forward wall
    glPushMatrix();
    glTranslatef(0.0f, (kFloorY + kCeilY) * 0.5f, Cfg::MD_Z_FWD + kWT * 0.5f);
    DrawBox(Cfg::MD_WIDTH, kRoomH, kWT);
    glPopMatrix();

    //  Trim strips 
    matIntFrame();
    float trimH = 0.008f;
    float trimD = 0.008f;

    // Floor trim — all four walls
    glPushMatrix();
    glTranslatef(-kHalfW + trimD * 0.5f, kFloorY + trimH * 0.5f, kMidZ);
    DrawBox(trimD, trimH, kLen);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(kHalfW - trimD * 0.5f, kFloorY + trimH * 0.5f, kMidZ);
    DrawBox(trimD, trimH, kLen);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, kFloorY + trimH * 0.5f, Cfg::MD_Z_AFT + trimD * 0.5f);
    DrawBox(Cfg::MD_WIDTH, trimH, trimD);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, kFloorY + trimH * 0.5f, Cfg::MD_Z_FWD - trimD * 0.5f);
    DrawBox(Cfg::MD_WIDTH, trimH, trimD);
    glPopMatrix();

    // Ceiling trim
    glPushMatrix();
    glTranslatef(-kHalfW + trimD * 0.5f, kCeilY - trimH * 0.5f, kMidZ);
    DrawBox(trimD, trimH, kLen);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(kHalfW - trimD * 0.5f, kCeilY - trimH * 0.5f, kMidZ);
    DrawBox(trimD, trimH, kLen);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, kCeilY - trimH * 0.5f, Cfg::MD_Z_AFT + trimD * 0.5f);
    DrawBox(Cfg::MD_WIDTH, trimH, trimD);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, kCeilY - trimH * 0.5f, Cfg::MD_Z_FWD - trimD * 0.5f);
    DrawBox(Cfg::MD_WIDTH, trimH, trimD);
    glPopMatrix();
}


// Locker wall: grid of lockers with handles and label strips

static void drawLockerWall(float wallX, float faceSign) {
    float totalW = Cfg::LOCKER_COLS * (Cfg::LOCKER_W + Cfg::LOCKER_GAP) - Cfg::LOCKER_GAP;
    float startZ = Cfg::MD_Z_AFT + (kLen - totalW) * 0.5f;
    float startY = kFloorY + 0.02f;

    for (int r = 0; r < Cfg::LOCKER_ROWS; ++r) {
        for (int c = 0; c < Cfg::LOCKER_COLS; ++c) {
            float z = startZ + c * (Cfg::LOCKER_W + Cfg::LOCKER_GAP) + Cfg::LOCKER_W * 0.5f;
            float y = startY + r * (Cfg::LOCKER_H + Cfg::LOCKER_GAP) + Cfg::LOCKER_H * 0.5f;
            float x = wallX + faceSign * Cfg::LOCKER_D * 0.5f;

            // Locker body
            matIntLocker();
            glPushMatrix();
            glTranslatef(x, y, z);
            DrawBox(Cfg::LOCKER_D, Cfg::LOCKER_H, Cfg::LOCKER_W);
            glPopMatrix();

            // Handle (small protruding rectangle)
            matIntFrame();
            float handleX = wallX + faceSign * (Cfg::LOCKER_D + 0.003f);
            glPushMatrix();
            glTranslatef(handleX, y, z);
            DrawBox(0.005f, Cfg::LOCKER_H * 0.10f, Cfg::LOCKER_W * 0.25f);
            glPopMatrix();

            // Label strip above handle
            matIntPanel();
            glPushMatrix();
            glTranslatef(handleX, y + Cfg::LOCKER_H * 0.25f, z);
            DrawBox(0.003f, 0.008f, Cfg::LOCKER_W * 0.5f);
            glPopMatrix();

            // Door seam line (thin frame around face)
            matIntFrame();
            float seam = 0.002f;
            float faceX = wallX + faceSign * (Cfg::LOCKER_D + 0.001f);
            // Top seam
            glPushMatrix();
            glTranslatef(faceX, y + Cfg::LOCKER_H * 0.5f - seam * 0.5f, z);
            DrawBox(seam, seam, Cfg::LOCKER_W);
            glPopMatrix();
            // Bottom seam
            glPushMatrix();
            glTranslatef(faceX, y - Cfg::LOCKER_H * 0.5f + seam * 0.5f, z);
            DrawBox(seam, seam, Cfg::LOCKER_W);
            glPopMatrix();
        }
    }
}


// Floor grid: panel lines on the mid-deck floor

static void drawFloorGrid() {
    matIntFrame();

    float y = kFloorY + 0.001f;
    float t = Cfg::FLOOR_LINE_T;

    // Lines parallel to Z (across the width)
    for (int i = 0; i <= Cfg::FLOOR_GRID_X; ++i) {
        float x = -kHalfW + (Cfg::MD_WIDTH * static_cast<float>(i) / Cfg::FLOOR_GRID_X);
        glPushMatrix();
        glTranslatef(x, y, kMidZ);
        DrawBox(t, 0.002f, kLen);
        glPopMatrix();
    }

    // Lines parallel to X (across the length)
    for (int i = 0; i <= Cfg::FLOOR_GRID_Z; ++i) {
        float z = Cfg::MD_Z_AFT + (kLen * static_cast<float>(i) / Cfg::FLOOR_GRID_Z);
        glPushMatrix();
        glTranslatef(0.0f, y, z);
        DrawBox(Cfg::MD_WIDTH, 0.002f, t);
        glPopMatrix();
    }
}


// Ladder: vertical ladder on the aft wall connecting to flight deck

static void drawLadder() {
    matIntFrame();

    float ladderW = 0.10f;
    float rungR = 0.004f;
    float railW = 0.008f;
    float ladderZ = Cfg::MD_Z_AFT + 0.04f;
    float ladderH = kCeilY - kFloorY + 0.02f;
    float railX = ladderW * 0.5f;

    // Two vertical rails
    for (int side = -1; side <= 1; side += 2) {
        glPushMatrix();
        glTranslatef(side * railX, kFloorY + ladderH * 0.5f, ladderZ);
        DrawBox(railW, ladderH, railW);
        glPopMatrix();
    }

    // Horizontal rungs
    int nRungs = 5;
    float rungSpacing = ladderH / (nRungs + 1);
    for (int i = 1; i <= nRungs; ++i) {
        float ry = kFloorY + rungSpacing * i;
        glPushMatrix();
        glTranslatef(0.0f, ry, ladderZ);
        glRotatef(90.0f, 0.0f, 90.0f, 1.0f);
        glTranslatef(0.0f, 0.0f, -ladderW * 0.5f);
        DrawCylinder(rungR, rungR, ladderW, 8, true);
        glPopMatrix();
    }
}


// Equipment rack on aft wall

static void drawEquipmentRack() {
    float rackW = 0.12f;
    float rackH = kRoomH * 0.6f;
    float rackD = 0.04f;
    float rackZ = Cfg::MD_Z_AFT + rackD * 0.5f + kWT + 0.005f;
    float rackY = kFloorY + rackH * 0.5f + 0.01f;
    float rackX = kHalfW - 0.325f;

    matIntConsole();
    glPushMatrix();
    glTranslatef(rackX, rackY, rackZ);
    DrawBox(rackW, rackH, rackD);
    glPopMatrix();

    // Shelf dividers
    matIntFrame();
    int nShelves = 3;
    float shelfSpacing = rackH / (nShelves + 1);
    for (int i = 1; i <= nShelves; ++i) {
        float sy = kFloorY + 0.01f + shelfSpacing * i;
        glPushMatrix();
        glTranslatef(rackX, sy, rackZ);
        DrawBox(rackW, 0.004f, rackD + 0.003f);
        glPopMatrix();
    }
}


// Floor hatch frame and cover

static void drawFloorHatch() {
    matIntHatch();

    float hs = Cfg::HATCH_SIZE * 0.5f;
    float hatchY = kFloorY + 0.002f;
    float hatchT = 0.006f;

    // Hatch cover plate (slightly recessed look)
    glPushMatrix();
    glTranslatef(0.0f, hatchY + 0.001f, Cfg::HATCH_Z);
    DrawBox(Cfg::HATCH_SIZE - hatchT, 0.004f, Cfg::HATCH_SIZE - hatchT);
    glPopMatrix();

    // Frame surround (four sides)
    matIntFrame();
    // Aft
    glPushMatrix();
    glTranslatef(0.0f, hatchY, Cfg::HATCH_Z - hs);
    DrawBox(Cfg::HATCH_SIZE + hatchT, hatchT, hatchT);
    glPopMatrix();
    // Forward
    glPushMatrix();
    glTranslatef(0.0f, hatchY, Cfg::HATCH_Z + hs);
    DrawBox(Cfg::HATCH_SIZE + hatchT, hatchT, hatchT);
    glPopMatrix();
    // Left
    glPushMatrix();
    glTranslatef(-hs, hatchY, Cfg::HATCH_Z);
    DrawBox(hatchT, hatchT, Cfg::HATCH_SIZE);
    glPopMatrix();
    // Right
    glPushMatrix();
    glTranslatef(hs, hatchY, Cfg::HATCH_Z);
    DrawBox(hatchT, hatchT, Cfg::HATCH_SIZE);
    glPopMatrix();

    // Handle
    matIntFrame();
    glPushMatrix();
    glTranslatef(0.0f, hatchY + 0.008f, Cfg::HATCH_Z);
    DrawBox(0.04f, 0.005f, 0.012f);
    glPopMatrix();
}


// drawMidDeck: assembles all mid-deck components

void drawMidDeck() {
    drawRoomEnclosure();
    drawLockerWall(-kHalfW, 1.0f);   // left wall — face +X
    drawLockerWall(kHalfW, -1.0f);   // right wall — face -X
    drawFloorGrid();
    drawLadder();
    drawEquipmentRack();
    drawFloorHatch();
}