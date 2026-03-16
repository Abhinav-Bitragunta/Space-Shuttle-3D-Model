// fuselage.cpp

// Iteration: 1 (Iter 3: materials)
// Description: Orbiter fuselage drawn as a tapered cylinder (frustum)
//              along +Z axis, and nose cone drawn as a cone.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "fuselage.h"
#include "../config.h"
#include "../primitives.h"
#include "../materials.h"

void drawFuselage() {
    matOrbiterWhite();
    DrawCylinder(Cfg::FUS_RADIUS_AFT, Cfg::FUS_RADIUS_FWD,
                 Cfg::FUS_LENGTH, Cfg::FUS_SLICES, true);
}

void drawNoseCone() {
    matOrbiterBlack();
    DrawCone(Cfg::FUS_RADIUS_FWD, Cfg::NOSE_LENGTH, Cfg::FUS_SLICES);
}
