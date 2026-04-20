#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "starfield.h"
#include "config.h"
#include <cmath>
#include <cstdlib>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static GLuint sStarList = 0;

void initStarfield() {
    sStarList = glGenLists(1);
    glNewList(sStarList, GL_COMPILE);

    glBegin(GL_POINTS);
    srand(42);
    for (int i = 0; i < Cfg::STAR_COUNT; ++i) {
        float u = static_cast<float>(rand()) / RAND_MAX;
        float v = static_cast<float>(rand()) / RAND_MAX;
        float theta = 2.0f * static_cast<float>(M_PI) * u;
        float phi = acosf(2.0f * v - 1.0f);


        float x = Cfg::STAR_SPHERE_R * sinf(phi) * cosf(theta);
        float y = Cfg::STAR_SPHERE_R * sinf(phi) * sinf(theta);
        float z = Cfg::STAR_SPHERE_R * cosf(phi);

        // Slight brightness variation (0.5 - 1.0)
        float b = 0.5f + 0.5f * (static_cast<float>(rand()) / RAND_MAX);
        // Occasional warm or cool tint
        float r = b, g = b, bl = b;
        int tint = rand() % 10;
        if (tint == 0) { r *= 1.0f; g *= 0.85f; bl *= 0.7f; }  // warm
        if (tint == 1) { r *= 0.7f; g *= 0.85f; bl *= 1.0f; }  // cool

        glColor3f(r, g, bl);
        glVertex3f(x, y, z);
    }
    glEnd();

    glEndList();
}

void drawStarfield() {
    if (sStarList == 0) return;

    glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT | GL_CURRENT_BIT | GL_POINT_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);   // stars behind everything
    glDepthMask(GL_FALSE);      // don't write to depth buffer
    glPointSize(1.5f);

    glCallList(sStarList);

    glDepthMask(GL_TRUE);
    glPopAttrib();
}