#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "lighting.h"
#include "config.h"

void setupLighting() {
    // Sun
    glLightfv(GL_LIGHT0, GL_AMBIENT,  Cfg::SUN_AMBIENT);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  Cfg::SUN_DIFFUSE);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Cfg::SUN_SPECULAR);

    // Earth glow
    glLightfv(GL_LIGHT1, GL_AMBIENT,  Cfg::EARTH_AMBIENT);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  Cfg::EARTH_DIFFUSE);
    glLightfv(GL_LIGHT1, GL_SPECULAR, Cfg::EARTH_SPECULAR);

    // Cabin light
    glLightfv(GL_LIGHT2, GL_AMBIENT,  Cfg::CABIN_LIGHT_AMB);
    glLightfv(GL_LIGHT2, GL_DIFFUSE,  Cfg::CABIN_LIGHT_DIFF);
    glLightfv(GL_LIGHT2, GL_SPECULAR, Cfg::CABIN_LIGHT_SPEC);
    glLightf (GL_LIGHT2, GL_CONSTANT_ATTENUATION,  Cfg::CABIN_LIGHT_ATTEN_CONST);
    glLightf (GL_LIGHT2, GL_LINEAR_ATTENUATION,    Cfg::CABIN_LIGHT_ATTEN_LINEAR);
    glLightf (GL_LIGHT2, GL_QUADRATIC_ATTENUATION,  Cfg::CABIN_LIGHT_ATTEN_QUAD);
}

void applyLighting() {
    glLightfv(GL_LIGHT0, GL_POSITION, Cfg::SUN_DIR);
    glLightfv(GL_LIGHT1, GL_POSITION, Cfg::EARTH_DIR);
}

void applyCabinLighting() {
    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_POSITION, Cfg::CABIN_LIGHT_POS);
}

void disableCabinLighting() {
    glDisable(GL_LIGHT2);
}
