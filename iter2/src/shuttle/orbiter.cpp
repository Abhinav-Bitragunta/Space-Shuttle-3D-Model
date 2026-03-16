// orbiter.cpp

// Iteration: 1 (extended in Iter 2)
// Description: Draws the complete Orbiter by calling sub-component
//              draw functions with appropriate transforms.
//              Iter 2 adds: crew cabin, windshield, payload bay outline,
//              SSME nozzles, OMS pods.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "orbiter.h"
#include "fuselage.h"
#include "wings.h"
#include "engines.h"
#include "../config.h"
#include "../primitives.h"

// TODO: Iter 4 — add interior/ sub-modules

// ---------------------------------------------------------------------------
// drawCrewCabin: forward protrusion on upper fuselage with windshield
//                cutouts (dark recesses).
// ---------------------------------------------------------------------------
static void drawCrewCabin() {
    // Cabin hump: box on top of forward fuselage
    glPushMatrix();
    glTranslatef(0.0f,
                 Cfg::CABIN_HUMP_Y + Cfg::CABIN_HUMP_HEIGHT * 0.5f,
                 Cfg::CABIN_HUMP_Z);
    glColor3fv(Cfg::COL_CABIN);
    DrawBox(Cfg::CABIN_HUMP_WIDTH, Cfg::CABIN_HUMP_HEIGHT, Cfg::CABIN_HUMP_LENGTH);
    glPopMatrix();

    // Windshield panes: grid of small dark recesses on the forward face
    float totalW = Cfg::WINDSHIELD_COLS * (Cfg::WINDSHIELD_WIDTH + Cfg::WINDSHIELD_GAP)
                   - Cfg::WINDSHIELD_GAP;
    float totalH = Cfg::WINDSHIELD_ROWS * (Cfg::WINDSHIELD_HEIGHT + Cfg::WINDSHIELD_GAP)
                   - Cfg::WINDSHIELD_GAP;
    float startX = -totalW * 0.5f;
    float startY = Cfg::CABIN_HUMP_Y + Cfg::CABIN_HUMP_HEIGHT - totalH - Cfg::WINDSHIELD_GAP;
    float fwdZ   = Cfg::CABIN_HUMP_Z + Cfg::CABIN_HUMP_LENGTH * 0.5f + 0.001f; // tiny offset to avoid z-fight

    glColor3fv(Cfg::COL_WINDSHIELD);
    for (int r = 0; r < Cfg::WINDSHIELD_ROWS; ++r) {
        for (int c = 0; c < Cfg::WINDSHIELD_COLS; ++c) {
            float cx = startX + c * (Cfg::WINDSHIELD_WIDTH + Cfg::WINDSHIELD_GAP)
                       + Cfg::WINDSHIELD_WIDTH * 0.5f;
            float cy = startY + r * (Cfg::WINDSHIELD_HEIGHT + Cfg::WINDSHIELD_GAP)
                       + Cfg::WINDSHIELD_HEIGHT * 0.5f;

            float p0[3] = { cx - Cfg::WINDSHIELD_WIDTH * 0.5f,
                             cy - Cfg::WINDSHIELD_HEIGHT * 0.5f, fwdZ };
            float p1[3] = { cx + Cfg::WINDSHIELD_WIDTH * 0.5f,
                             cy - Cfg::WINDSHIELD_HEIGHT * 0.5f, fwdZ };
            float p2[3] = { cx + Cfg::WINDSHIELD_WIDTH * 0.5f,
                             cy + Cfg::WINDSHIELD_HEIGHT * 0.5f, fwdZ };
            float p3[3] = { cx - Cfg::WINDSHIELD_WIDTH * 0.5f,
                             cy + Cfg::WINDSHIELD_HEIGHT * 0.5f, fwdZ };
            DrawQuad(p0, p1, p2, p3);
        }
    }
}

// ---------------------------------------------------------------------------
// drawPayloadBayOutline: rectangular outline on upper fuselage marking the
//                        cargo bay door seams.
// ---------------------------------------------------------------------------
static void drawPayloadBayOutline() {
    float halfW = Cfg::PBAY_WIDTH * 0.5f;
    float z0    = Cfg::PBAY_Z_START;
    float z1    = Cfg::PBAY_Z_START + Cfg::PBAY_LENGTH;
    float y     = Cfg::FUS_RADIUS_AFT - 0.01f; // just above fuselage top to avoid z-fight
    float b     = Cfg::PBAY_BORDER;

    glColor3fv(Cfg::COL_PBAY_LINE);

    // Four border strips forming a rectangle (thin quads)
    // Front edge
    float f0[3] = { -halfW, y, z1 };
    float f1[3] = {  halfW, y, z1 };
    float f2[3] = {  halfW, y, z1 - b };
    float f3[3] = { -halfW, y, z1 - b };
    DrawQuad(f0, f1, f2, f3);

    // Aft edge
    float a0[3] = { -halfW, y, z0 + b };
    float a1[3] = {  halfW, y, z0 + b };
    float a2[3] = {  halfW, y, z0 };
    float a3[3] = { -halfW, y, z0 };
    DrawQuad(a0, a1, a2, a3);

    // Left edge
    float l0[3] = { -halfW,     y, z0 };
    float l1[3] = { -halfW + b, y, z0 };
    float l2[3] = { -halfW + b, y, z1 };
    float l3[3] = { -halfW,     y, z1 };
    DrawQuad(l0, l1, l2, l3);

    // Right edge
    float r0[3] = { halfW - b, y, z0 };
    float r1[3] = { halfW,     y, z0 };
    float r2[3] = { halfW,     y, z1 };
    float r3[3] = { halfW - b, y, z1 };
    DrawQuad(r0, r1, r2, r3);

    // Centre seam (splits the two doors)
    float c0[3] = { -b * 0.5f, y, z0 };
    float c1[3] = {  b * 0.5f, y, z0 };
    float c2[3] = {  b * 0.5f, y, z1 };
    float c3[3] = { -b * 0.5f, y, z1 };
    DrawQuad(c0, c1, c2, c3);
}

// ---------------------------------------------------------------------------
// drawOrbiter: assembles all Orbiter sub-components.
// ---------------------------------------------------------------------------
void drawOrbiter() {
    // Fuselage: aft at Z=0, forward at Z=FUS_LENGTH
    glPushMatrix();
    drawFuselage();
    glPopMatrix();

    // Nose cone: attached at forward end of fuselage
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, Cfg::FUS_LENGTH);
    drawNoseCone();
    glPopMatrix();

    // Delta wings
    glPushMatrix();
    drawWings();
    glPopMatrix();

    // Vertical stabilizer
    glPushMatrix();
    drawVerticalStabilizer();
    glPopMatrix();

    // ── Iter 2 additions ────────────────────────────────

    // Crew cabin hump with windshield
    glPushMatrix();
    drawCrewCabin();
    glPopMatrix();

    // Payload bay outline on upper fuselage
    glPushMatrix();
    drawPayloadBayOutline();
    glPopMatrix();

    // SSME nozzles at the aft base (Z=0, facing -Z)
    glPushMatrix();
    glTranslatef(0.0f, Cfg::SSME_CLUSTER_Y, 0.0f);
    drawSSMENozzles();
    glPopMatrix();

    // OMS pod — right side
    glPushMatrix();
    glTranslatef(Cfg::OMS_OFFSET_X, Cfg::OMS_OFFSET_Y, Cfg::OMS_OFFSET_Z);
    drawOMSPod();
    glPopMatrix();

    // OMS pod — left side (mirrored)
    glPushMatrix();
    glTranslatef(-Cfg::OMS_OFFSET_X, Cfg::OMS_OFFSET_Y, Cfg::OMS_OFFSET_Z);
    glScalef(-1.0f, 1.0f, 1.0f);
    drawOMSPod();
    glPopMatrix();
}
