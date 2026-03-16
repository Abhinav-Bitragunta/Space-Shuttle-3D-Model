// scene.cpp

// Iteration: 1
// Description: Top-level scene draw function. Draws axis lines and
//              positions the full shuttle stack.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "scene.h"
#include "config.h"
#include "shuttle/orbiter.h"

// TODO: Iter 2 — #include "shuttle/external_tank.h", "shuttle/srb.h"
// TODO: Iter 5 — #include "starfield.h"

SceneState gScene;

void initScene() {
    gScene.wireframe = false;
    gScene.showAxes  = true;
}

// ---------------------------------------------------------------------------
// drawAxes: coloured reference lines (X=red, Y=green, Z=blue).
// ---------------------------------------------------------------------------
static void drawAxes() {
    glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT);
    glLineWidth(1.5f);

    glBegin(GL_LINES);

    // X axis — red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(Cfg::AXIS_LENGTH, 0.0f, 0.0f);

    // Y axis — green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, Cfg::AXIS_LENGTH, 0.0f);

    // Z axis — blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, Cfg::AXIS_LENGTH);

    glEnd();
    glPopAttrib();
}

// ---------------------------------------------------------------------------
// drawFullStack: positions Orbiter, ET, and SRBs relative to world origin.
// ---------------------------------------------------------------------------
static void drawFullStack() {
    // Centre the orbiter so its midpoint is near the origin.
    // Fuselage spans Z=0..FUS_LENGTH, so shift back by half.
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -Cfg::FUS_LENGTH * 0.5f);
    drawOrbiter();
    glPopMatrix();

    // TODO: Iter 2 — ET below and slightly aft
    // TODO: Iter 2 — Left SRB
    // TODO: Iter 2 — Right SRB (mirrored)
}

// ---------------------------------------------------------------------------
// drawScene: main entry point called from display callback.
// ---------------------------------------------------------------------------
void drawScene() {
    // Wireframe / solid toggle
    if (gScene.wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // Axis reference lines
    if (gScene.showAxes) {
        drawAxes();
    }

    // Draw the shuttle stack
    drawFullStack();

    // Restore fill mode so other drawing (HUD etc.) is not wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
