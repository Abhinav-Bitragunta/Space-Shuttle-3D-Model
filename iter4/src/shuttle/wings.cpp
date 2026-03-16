// wings.cpp

// Iteration: 1 (Iter 2: vstab fixes, Iter 3: materials)
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
#include "../materials.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ---------------------------------------------------------------------------
// Helper: draw one wing on the +X side. Caller mirrors for -X side.
// ---------------------------------------------------------------------------
static void drawOneWing() {
    float halfThick = Cfg::WING_THICKNESS * 0.5f;

    float xRoot = Cfg::FUS_RADIUS_AFT;
    float xTip  = Cfg::WING_SPAN * 0.5f;

    float sweepRad    = static_cast<float>(Cfg::WING_SWEEP_DEG * M_PI / 180.0);
    float sweepOffset = (xTip - xRoot) * tanf(sweepRad);

    float zRootLE = Cfg::WING_Z_ATTACH;
    float zRootTE = Cfg::WING_Z_ATTACH - Cfg::WING_CHORD_ROOT;
    float zTipLE  = zRootLE - sweepOffset;
    float zTipTE  = zTipLE  - Cfg::WING_CHORD_TIP;

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

    matWing();

    DrawQuad(topRL, topRT, topTT, topTL);      // Top face
    DrawQuad(botRL, botTL, botTT, botRT);      // Bottom face
    DrawQuad(topRL, topTL, botTL, botRL);      // Leading edge
    DrawQuad(topRT, botRT, botTT, topTT);      // Trailing edge
    DrawQuad(topTL, topTT, botTT, botTL);      // Tip edge
}

void drawWings() {
    glPushMatrix();
    drawOneWing();
    glPopMatrix();

    glPushMatrix();
    glScalef(-1.0f, 1.0f, 1.0f);
    drawOneWing();
    glPopMatrix();
}

// ---------------------------------------------------------------------------
// drawVerticalStabilizer: upright trapezoid at the aft end.
//   Wide chord at base, narrow at top. Trailing edge is vertical (straight up),
//   leading edge sweeps aft from base to top.
//   yBase uses VSTAB_Y_BASE constant (no hardcoded literal).
// ---------------------------------------------------------------------------
void drawVerticalStabilizer() {
    float halfThick = Cfg::WING_THICKNESS * 0.5f;

    float yBase = Cfg::VSTAB_Y_BASE;
    float yTop  = yBase + Cfg::VSTAB_HEIGHT;

    // Trailing edge is at VSTAB_Z_ATTACH (aft, vertical).
    // Leading edge extends forward (+Z) by chord length.
    float zBaseLE = Cfg::VSTAB_Z_ATTACH + Cfg::VSTAB_CHORD_BASE;  // base leading edge (forward)
    float zBaseTE = Cfg::VSTAB_Z_ATTACH;                           // base trailing edge (aft)
    float zTopLE  = Cfg::VSTAB_Z_ATTACH + Cfg::VSTAB_CHORD_TIP;   // top leading edge (swept back)
    float zTopTE  = Cfg::VSTAB_Z_ATTACH;                           // top trailing edge (aft, aligned)

    matVStab();

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

    // Leading edge (front)
    float fBL[3] = { -halfThick, yBase, zBaseLE };
    float fBR[3] = {  halfThick, yBase, zBaseLE };
    float fTR[3] = {  halfThick, yTop,  zTopLE  };
    float fTL[3] = { -halfThick, yTop,  zTopLE  };
    DrawQuad(fBL, fBR, fTR, fTL);

    // Trailing edge (back)
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
