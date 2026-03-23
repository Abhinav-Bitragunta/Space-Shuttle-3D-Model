// fuselage.cpp

// Iteration: 1
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

// ---------------------------------------------------------------------------
// drawFuselage: tapered cylinder from aft (Z=0) to forward (Z=FUS_LENGTH).
//   Wider at aft (FUS_RADIUS_AFT), narrower at forward (FUS_RADIUS_FWD).
//   Drawn at local origin; caller positions it.
// ---------------------------------------------------------------------------
void drawFuselage() {
    // Upper fuselage — white orbiter tiles
    glColor3fv(Cfg::COL_ORBITER);
    DrawCylinder(Cfg::FUS_RADIUS_AFT, Cfg::FUS_RADIUS_FWD,
                 Cfg::FUS_LENGTH, Cfg::FUS_SLICES, true);
}

// ---------------------------------------------------------------------------
// drawNoseCone: cone at the forward end of the fuselage.
//   Base radius = FUS_RADIUS_FWD, tip radius = 0, length = NOSE_LENGTH.
//   Drawn at local origin; caller translates to fuselage forward end.
// ---------------------------------------------------------------------------
void drawNoseCone() {
    glColor3fv(Cfg::COL_NOSE);
    DrawCone(Cfg::FUS_RADIUS_FWD, Cfg::NOSE_LENGTH, Cfg::FUS_SLICES);
}
