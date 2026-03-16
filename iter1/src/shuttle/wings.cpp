// wings.cpp

// Iteration: 1
// Description: Delta wings (swept trapezoidal planform, both sides)
//              and vertical stabilizer drawn as flat polygons with thickness.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "wings.h"
#include "../config.h"
#include "../primitives.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ---------------------------------------------------------------------------
// Helper: draw one wing on the +X side. Caller mirrors for -X side.
//   The wing is a swept trapezoid with slight thickness.
//   Root attaches at fuselage side, tip at WING_SPAN/2.
// ---------------------------------------------------------------------------
static void drawOneWing() {
    float halfThick = Cfg::WING_THICKNESS * 0.5f;

    // Wing root is at the fuselage radius, tip at half-span
    float xRoot = Cfg::FUS_RADIUS_AFT;
    float xTip  = Cfg::WING_SPAN * 0.5f;

    // Sweep offset: how far back the tip leading edge is from root leading edge
    float sweepRad    = static_cast<float>(Cfg::WING_SWEEP_DEG * M_PI / 180.0);
    float sweepOffset = (xTip - xRoot) * tanf(sweepRad);

    // Z coordinates (fuselage runs along +Z, aft is Z=0)
    float zRootLE = Cfg::WING_Z_ATTACH;                          // root leading edge
    float zRootTE = Cfg::WING_Z_ATTACH - Cfg::WING_CHORD_ROOT;  // root trailing edge
    float zTipLE  = zRootLE - sweepOffset;                        // tip leading edge (swept back)
    float zTipTE  = zTipLE  - Cfg::WING_CHORD_TIP;               // tip trailing edge

    // Four corners of wing planform (Y = +/- halfThick for top/bottom)
    // Top surface
    float topRL[3] = { xRoot, halfThick, zRootLE };
    float topRT[3] = { xRoot, halfThick, zRootTE };
    float topTT[3] = { xTip,  halfThick, zTipTE  };
    float topTL[3] = { xTip,  halfThick, zTipLE  };

    // Bottom surface
    float botRL[3] = { xRoot, -halfThick, zRootLE };
    float botRT[3] = { xRoot, -halfThick, zRootTE };
    float botTT[3] = { xTip,  -halfThick, zTipTE  };
    float botTL[3] = { xTip,  -halfThick, zTipLE  };

    glColor3fv(Cfg::COL_WING);

    // Top face (normal +Y)
    DrawQuad(topRL, topRT, topTT, topTL);

    // Bottom face (normal -Y) — reverse winding
    DrawQuad(botRL, botTL, botTT, botRT);

    // Leading edge (front of wing)
    DrawQuad(topRL, topTL, botTL, botRL);

    // Trailing edge (back of wing)
    DrawQuad(topRT, botRT, botTT, topTT);

    // Tip edge (outer)
    DrawQuad(topTL, topTT, botTT, botTL);
}

// ---------------------------------------------------------------------------
// drawWings: draws both left and right delta wings.
// ---------------------------------------------------------------------------
void drawWings() {
    // Right wing (+X side)
    glPushMatrix();
    drawOneWing();
    glPopMatrix();

    // Left wing (-X side) — mirror
    glPushMatrix();
    glScalef(-1.0f, 1.0f, 1.0f);
    drawOneWing();
    glPopMatrix();
}

// ---------------------------------------------------------------------------
// drawVerticalStabilizer: upright trapezoid at the aft end on the Y-Z plane.
// ---------------------------------------------------------------------------
void drawVerticalStabilizer() {
    float halfThick = Cfg::WING_THICKNESS * 0.5f;

    float yBase = 0.0f;
    float yTop  = yBase + Cfg::VSTAB_HEIGHT;

    float zBaseLE = Cfg::VSTAB_Z_ATTACH + Cfg::VSTAB_CHORD_BASE;  // base leading edge (forward)
    float zBaseTE = Cfg::VSTAB_Z_ATTACH;                           // base trailing edge (aft)
    float zTopLE = Cfg::VSTAB_Z_ATTACH + Cfg::VSTAB_CHORD_TIP;   // top leading edge (swept back)
    float zTopTE = Cfg::VSTAB_Z_ATTACH;                           // top trailing edge (aft, aligned with base)

    glColor3fv(Cfg::COL_VSTAB);

    // Right face (+X)
    float rBL[3] = { halfThick, yBase, zBaseLE };
    float rBR[3] = { halfThick, yBase, zBaseTE };
    float rTR[3] = { halfThick, yTop,  zTopTE  };
    float rTL[3] = { halfThick, yTop,  zTopLE  };
    DrawQuad(rBL, rBR, rTR, rTL);

    // Left face (-X)
    float lBL[3] = { -halfThick, yBase, zBaseTE };
    float lBR[3] = { -halfThick, yBase, zBaseLE };
    float lTR[3] = { -halfThick, yTop,  zTopLE  };
    float lTL[3] = { -halfThick, yTop,  zTopTE  };
    DrawQuad(lBL, lBR, lTR, lTL);

    // Front edge (leading)
    float fBL[3] = { -halfThick, yBase, zBaseLE };
    float fBR[3] = {  halfThick, yBase, zBaseLE };
    float fTR[3] = {  halfThick, yTop,  zTopLE  };
    float fTL[3] = { -halfThick, yTop,  zTopLE  };
    DrawQuad(fBL, fBR, fTR, fTL);

    // Back edge (trailing)
    float bBL[3] = {  halfThick, yBase, zBaseTE };
    float bBR[3] = { -halfThick, yBase, zBaseTE };
    float bTR[3] = { -halfThick, yTop,  zTopTE  };
    float bTL[3] = {  halfThick, yTop,  zTopTE  };
    DrawQuad(bBL, bBR, bTR, bTL);

    // Top edge
    float tBL[3] = { -halfThick, yTop, zTopLE };
    float tBR[3] = {  halfThick, yTop, zTopLE };
    float tTR[3] = {  halfThick, yTop, zTopTE };
    float tTL[3] = { -halfThick, yTop, zTopTE };
    DrawQuad(tBL, tBR, tTR, tTL);
}
