// external_tank.cpp

// Iteration: 2 (Iter 3: materials)
// Description: External Tank — orange cylinder with hemispherical dome.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "external_tank.h"
#include "../config.h"
#include "../primitives.h"
#include "../materials.h"

void drawET() {
    matET();
    DrawCylinder(Cfg::ET_RADIUS, Cfg::ET_RADIUS,
                 Cfg::ET_LENGTH, Cfg::ET_SLICES, true);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, Cfg::ET_LENGTH);
    matETDome();
    DrawDome(Cfg::ET_RADIUS, Cfg::ET_SLICES, Cfg::ET_DOME_STACKS);
    glPopMatrix();
}
