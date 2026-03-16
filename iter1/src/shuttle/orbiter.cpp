// orbiter.cpp

// Iteration: 1
// Description: Draws the complete Orbiter by calling sub-component
//              draw functions with appropriate transforms.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "orbiter.h"
#include "fuselage.h"
#include "wings.h"
#include "../config.h"

// TODO: Iter 2 — add engines.h, crew cabin, payload bay outline
// TODO: Iter 4 — add interior/ sub-modules

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

    // Delta wings: positioned relative to fuselage centre
    glPushMatrix();
    drawWings();
    glPopMatrix();

    // Vertical stabilizer: at aft upper fuselage
    glPushMatrix();
    drawVerticalStabilizer();
    glPopMatrix();
}
