// lighting.cpp

// Iteration: 3
// Description: Configures GL_LIGHT0 (distant sun, white-yellow, directional)
//              and GL_LIGHT1 (Earth glow, blue-tinted, from below).

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "lighting.h"
#include "config.h"

// ---------------------------------------------------------------------------
// setupLighting: called once at startup. Sets light colour properties.
//                Does NOT enable GL_LIGHTING — that's toggled by scene state.
// ---------------------------------------------------------------------------
void setupLighting() {
    // GL_LIGHT0 — Sun
    glLightfv(GL_LIGHT0, GL_AMBIENT,  Cfg::SUN_AMBIENT);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  Cfg::SUN_DIFFUSE);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Cfg::SUN_SPECULAR);

    // GL_LIGHT1 — Earth glow
    glLightfv(GL_LIGHT1, GL_AMBIENT,  Cfg::EARTH_AMBIENT);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  Cfg::EARTH_DIFFUSE);
    glLightfv(GL_LIGHT1, GL_SPECULAR, Cfg::EARTH_SPECULAR);
}

// ---------------------------------------------------------------------------
// applyLighting: called each frame after modelview is set.
//                Positions lights in world space.
// ---------------------------------------------------------------------------
void applyLighting() {
    glLightfv(GL_LIGHT0, GL_POSITION, Cfg::SUN_DIR);
    glLightfv(GL_LIGHT1, GL_POSITION, Cfg::EARTH_DIR);
}
