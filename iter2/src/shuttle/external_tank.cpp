// external_tank.cpp

// Iteration: 2
// Description: External Tank drawn at local origin along +Z.
//              Orange cylinder body with hemispherical nose cap at
//              forward end (+Z) and closed flat base at aft end.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "external_tank.h"
#include "../config.h"
#include "../primitives.h"

void drawET() {
    // Main tank body: cylinder along +Z
    glColor3fv(Cfg::COL_ET);
    DrawCylinder(Cfg::ET_RADIUS, Cfg::ET_RADIUS,
                 Cfg::ET_LENGTH, Cfg::ET_SLICES, true);

    // Hemispherical nose cap at forward end
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, Cfg::ET_LENGTH);
    glColor3fv(Cfg::COL_ET_DOME);
    DrawDome(Cfg::ET_RADIUS, Cfg::ET_SLICES, Cfg::ET_DOME_STACKS);
    glPopMatrix();
}
