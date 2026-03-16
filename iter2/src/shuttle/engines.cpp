// engines.cpp

// Iteration: 2
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

// ---------------------------------------------------------------------------
// drawOneBell: single SSME bell nozzle at local origin, opening toward -Z.
//   Bell frustum from throat (small radius) flaring to exit (large radius).
//   Nested annular disks at the exit plane for visual detail.
// ---------------------------------------------------------------------------
static void drawOneBell() {
    glColor3fv(Cfg::COL_NOZZLE);

    // Bell frustum: throat radius at Z=0, flaring to bell radius at Z=-DEPTH
    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);  // flip to point toward -Z
    DrawCylinder(Cfg::SSME_THROAT_RADIUS, Cfg::SSME_BELL_RADIUS,
                 Cfg::SSME_DEPTH, Cfg::SSME_SLICES, false);
    glPopMatrix();

    // Exit plane: nested annular disks at Z = -SSME_DEPTH
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -Cfg::SSME_DEPTH);
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);  // normal faces -Z (outward)

    // Outer ring
    float ringMid = (Cfg::SSME_THROAT_RADIUS + Cfg::SSME_BELL_RADIUS) * 0.5f;
    DrawDisk(ringMid, Cfg::SSME_BELL_RADIUS, Cfg::SSME_SLICES);

    // Inner dark ring (throat opening visible)
    glColor3f(0.05f, 0.05f, 0.07f);
    DrawDisk(0.0f, ringMid, Cfg::SSME_SLICES);

    glPopMatrix();
}

// ---------------------------------------------------------------------------
// drawSSMENozzles: cluster of three SSME bells.
//   Arranged in a triangle pattern: two flanking + one top-centre.
//   Drawn at local origin; orbiter.cpp positions at the aft end.
// ---------------------------------------------------------------------------
void drawSSMENozzles() {
    // Lower-left nozzle
    glPushMatrix();
    glTranslatef(-Cfg::SSME_SPACING * 0.5f, -Cfg::SSME_CLUSTER_Y, 0.0f);
    drawOneBell();
    glPopMatrix();

    // Lower-right nozzle
    glPushMatrix();
    glTranslatef(Cfg::SSME_SPACING * 0.5f, -Cfg::SSME_CLUSTER_Y, 0.0f);
    drawOneBell();
    glPopMatrix();

    // Top-centre nozzle
    glPushMatrix();
    glTranslatef(0.0f, Cfg::SSME_CLUSTER_Y * 1.5f, 0.0f);
    drawOneBell();
    glPopMatrix();
}

// ---------------------------------------------------------------------------
// drawOMSPod: single OMS pod drawn at local origin along +Z.
//   A blunt cylinder with a rounded cap at the aft end.
//   Caller positions and mirrors for left/right.
// ---------------------------------------------------------------------------
void drawOMSPod() {
    glColor3fv(Cfg::COL_OMS);

    // Pod body: cylinder along +Z (forward)
    DrawCylinder(Cfg::OMS_RADIUS, Cfg::OMS_RADIUS,
                 Cfg::OMS_LENGTH, Cfg::OMS_SLICES, true);

    // Blunt aft cap: small dome at Z=0, facing -Z
    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);  // dome faces -Z
    DrawDome(Cfg::OMS_RADIUS, Cfg::OMS_SLICES, 8);
    glPopMatrix();
}
