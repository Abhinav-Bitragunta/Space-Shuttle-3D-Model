// Single Solid Rocket Booster with aft skirt, main body, nose cone.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "srb.h"
#include "../config.h"
#include "../primitives.h"
#include "../materials.h"

void drawSRB() {
    // Aft skirt
    matSRBSkirt();
    DrawCylinder(Cfg::SRB_SKIRT_RAD, Cfg::SRB_RADIUS,
                 Cfg::SRB_SKIRT_LEN, Cfg::SRB_SLICES, true);

    // Main body
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, Cfg::SRB_SKIRT_LEN);
    matSRB();
    DrawCylinder(Cfg::SRB_RADIUS, Cfg::SRB_RADIUS,
                 Cfg::SRB_LENGTH, Cfg::SRB_SLICES, false);
    glPopMatrix();

    // Nose cone
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, Cfg::SRB_SKIRT_LEN + Cfg::SRB_LENGTH);
    matSRB();
    DrawCone(Cfg::SRB_RADIUS, Cfg::SRB_NOSE_LEN, Cfg::SRB_SLICES);
    glPopMatrix();
}
