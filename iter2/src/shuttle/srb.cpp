// srb.cpp

// Iteration: 2
// Description: Single Solid Rocket Booster drawn at local origin along +Z.
//              Layout:  aft skirt (Z=0) → main body → nose cone (forward).
//              Scene.cpp mirrors this for left/right placement.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "srb.h"
#include "../config.h"
#include "../primitives.h"

void drawSRB() {
    // ── Aft skirt: wider cylinder at base ──
    glColor3fv(Cfg::COL_SRB_SKIRT);
    DrawCylinder(Cfg::SRB_SKIRT_RAD, Cfg::SRB_RADIUS,
                 Cfg::SRB_SKIRT_LEN, Cfg::SRB_SLICES, true);

    // ── Main body: cylinder from top of skirt to top ──
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, Cfg::SRB_SKIRT_LEN);
    glColor3fv(Cfg::COL_SRB);
    DrawCylinder(Cfg::SRB_RADIUS, Cfg::SRB_RADIUS,
                 Cfg::SRB_LENGTH, Cfg::SRB_SLICES, false);
    glPopMatrix();

    // ── Nose cone at forward end ──
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, Cfg::SRB_SKIRT_LEN + Cfg::SRB_LENGTH);
    glColor3fv(Cfg::COL_SRB);
    DrawCone(Cfg::SRB_RADIUS, Cfg::SRB_NOSE_LEN, Cfg::SRB_SLICES);
    glPopMatrix();
}
