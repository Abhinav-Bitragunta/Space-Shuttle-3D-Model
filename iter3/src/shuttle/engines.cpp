// engines.cpp

// Iteration: 2 (Iter 3: materials, SSME centroid fix)
// Description: SSME main engine bell nozzles (three, drawn as nested
//              disk annuli + frustum bells) and OMS pods (blunt cylinders
//              with dome caps).

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "engines.h"
#include "../config.h"
#include "../primitives.h"
#include "../materials.h"

// ---------------------------------------------------------------------------
// drawOneBell: single SSME bell nozzle at local origin, opening toward -Z.
// ---------------------------------------------------------------------------
static void drawOneBell() {
    matNozzle();

    // Bell frustum: throat at Z=0, flaring to bell radius at Z=-DEPTH
    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    DrawCylinder(Cfg::SSME_THROAT_RADIUS, Cfg::SSME_BELL_RADIUS,
                 Cfg::SSME_DEPTH, Cfg::SSME_SLICES, false);
    glPopMatrix();

    // Exit plane: nested annular disks at Z = -SSME_DEPTH
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -Cfg::SSME_DEPTH);
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);

    // Outer ring
    float ringMid = (Cfg::SSME_THROAT_RADIUS + Cfg::SSME_BELL_RADIUS) * 0.5f;
    DrawDisk(ringMid, Cfg::SSME_BELL_RADIUS, Cfg::SSME_SLICES);

    // Inner dark ring
    matNozzleInner();
    DrawDisk(0.0f, ringMid, Cfg::SSME_SLICES);

    glPopMatrix();
}

// ---------------------------------------------------------------------------
// drawSSMENozzles: cluster of three SSME bells in a triangle pattern.
//   The cluster is centred on its own centroid so that the caller's Y
//   offset (SSME_CLUSTER_Y) positions the whole group correctly.
//   Two lower bells at -CLUSTER_Y, one upper bell at +CLUSTER_Y*1.5.
//   Centroid Y = (-CY + -CY + 1.5*CY) / 3 = -CY/6.
//   We shift everything by +CY/6 to centre the group.
// ---------------------------------------------------------------------------
void drawSSMENozzles() {
    // Compute centroid offset to centre the triangle arrangement
    float lowerY =  -Cfg::SSME_CLUSTER_Y;
    float upperY =   Cfg::SSME_CLUSTER_Y * 1.5f;
    float centroidY = (lowerY + lowerY + upperY) / 3.0f;

    // Lower-left nozzle
    glPushMatrix();
    glTranslatef(-Cfg::SSME_SPACING * 0.5f, lowerY - centroidY, 0.0f);
    drawOneBell();
    glPopMatrix();

    // Lower-right nozzle
    glPushMatrix();
    glTranslatef(Cfg::SSME_SPACING * 0.5f, lowerY - centroidY, 0.0f);
    drawOneBell();
    glPopMatrix();

    // Top-centre nozzle
    glPushMatrix();
    glTranslatef(0.0f, upperY - centroidY, 0.0f);
    drawOneBell();
    glPopMatrix();
}

// ---------------------------------------------------------------------------
// drawOMSPod: single OMS pod at local origin along +Z.
// ---------------------------------------------------------------------------
void drawOMSPod() {
    matOMS();

    DrawCylinder(Cfg::OMS_RADIUS, Cfg::OMS_RADIUS,
                 Cfg::OMS_LENGTH, Cfg::OMS_SLICES, true);

    // Blunt aft cap
    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    DrawDome(Cfg::OMS_RADIUS, Cfg::OMS_SLICES, 8);
    glPopMatrix();
}
