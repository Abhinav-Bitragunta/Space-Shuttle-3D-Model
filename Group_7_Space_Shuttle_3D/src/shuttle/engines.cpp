// SSME main engine bell nozzles and OMS pods 

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "engines.h"
#include "../config.h"
#include "../primitives.h"
#include "../materials.h"
#include <cmath>

// single SSME bell nozzle at local origin, opening toward -Z.
static void drawOneBell() {
    matNozzle();

    // Bell frustum: throat at Z=0, flaring to bell radius at Z=-DEPTH
    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    DrawCylinder(Cfg::SSME_THROAT_RADIUS, Cfg::SSME_BELL_RADIUS,
                 Cfg::SSME_DEPTH, Cfg::SSME_SLICES, false);
    glPopMatrix();

    // Exit plane: nested annular disks at Z = -SSME_DEPTH
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -Cfg::SSME_DEPTH);
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);

    // Outer ring
    float ringMid = (Cfg::SSME_THROAT_RADIUS + Cfg::SSME_BELL_RADIUS) * 0.5f;
    DrawDisk(ringMid, Cfg::SSME_BELL_RADIUS, Cfg::SSME_SLICES);

    // Inner dark ring
    matNozzleInner();
    DrawDisk(0.0f, ringMid, Cfg::SSME_SLICES);

    glPopMatrix();
}

// cluster of three SSME bells in a triangle pattern.
void drawSSMENozzles() {
    
    float lowerY =  -Cfg::SSME_CLUSTER_Y;
    float upperY =   Cfg::SSME_CLUSTER_Y * 1.5f;
    float centroidY = (lowerY + lowerY + upperY) / 3.0f;

    // Lower-left nozzle
    glPushMatrix();
    glTranslatef(-Cfg::SSME_SPACING * 0.5f, lowerY - centroidY, 0.0f);
    drawOneBell();
    glPopMatrix();

    // Lower-right nozzle
    glPushMatrix();
    glTranslatef(Cfg::SSME_SPACING * 0.5f, lowerY - centroidY, 0.0f);
    drawOneBell();
    glPopMatrix();

    // Top-centre nozzle
    glPushMatrix();
    glTranslatef(0.0f, upperY - centroidY, 0.0f);
    drawOneBell();
    glPopMatrix();
}

// Exhaust Flames

static void drawFlame(float length, float radius) {
    // Cone pointing in -Z (out the nozzle)
    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    GLUquadric* q = gluNewQuadric();
    gluCylinder(q, radius, 0.0, length, Cfg::FLAME_SLICES, 1);
    gluDeleteQuadric(q);
    glPopMatrix();
}

void drawExhaustFlames(float stackShiftZ) {
    float t = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float flicker = 1.0f + Cfg::FLAME_FLICKER_AMP *
        sinf(t * Cfg::FLAME_FLICKER_SPEED * 2.0f * 3.14159f);

    // SSME flames
    float lowerY =  -Cfg::SSME_CLUSTER_Y;
    float upperY =   Cfg::SSME_CLUSTER_Y * 1.5f;
    float centroidY = (lowerY + lowerY + upperY) / 3.0f;

    struct { float x, y; } ssmePos[3] = {
        { -Cfg::SSME_SPACING * 0.5f, lowerY - centroidY },
        {  Cfg::SSME_SPACING * 0.5f, lowerY - centroidY },
        {  0.0f,                     upperY - centroidY  }
    };

    for (int i = 0; i < 3; ++i) {
        float phaseOff = i * 0.7f;
        float f = 1.0f + Cfg::FLAME_FLICKER_AMP *
            sinf(t * Cfg::FLAME_FLICKER_SPEED * 6.28f + phaseOff);
        float len = Cfg::FLAME_SSME_LENGTH * f;

        float flameZ = stackShiftZ - Cfg::SSME_DEPTH;

        // Core (bright white-yellow)
        glColor4f(1.0f, 0.95f, 0.7f, 0.6f);
        glPushMatrix();
        glTranslatef(ssmePos[i].x,
                     Cfg::SSME_CLUSTER_Y + ssmePos[i].y,
                     flameZ);
        drawFlame(len * 0.5f, Cfg::FLAME_SSME_RADIUS * 0.4f);
        glPopMatrix();

        // Outer glow (orange, larger)
        glColor4f(1.0f, 0.5f, 0.1f, 0.25f);
        glPushMatrix();
        glTranslatef(ssmePos[i].x,
                     Cfg::SSME_CLUSTER_Y + ssmePos[i].y,
                     flameZ);
        drawFlame(len, Cfg::FLAME_SSME_RADIUS);
        glPopMatrix();
    }

    // SRB flames
    float srbZ = stackShiftZ + Cfg::ET_OFFSET_Z;
    for (int side = -1; side <= 1; side += 2) {
        float phaseOff = (side > 0) ? 2.1f : 0.0f;
        float f = 1.0f + Cfg::FLAME_FLICKER_AMP *
            sinf(t * Cfg::FLAME_FLICKER_SPEED * 6.28f * 0.9f + phaseOff);
        float len = Cfg::FLAME_SRB_LENGTH * f;

        // Core
        glColor4f(1.0f, 0.9f, 0.5f, 0.5f);
        glPushMatrix();
        glTranslatef(side * Cfg::SRB_OFFSET_X, Cfg::SRB_OFFSET_Y, srbZ);
        drawFlame(len * 0.4f, Cfg::FLAME_SRB_RADIUS * 0.35f);
        glPopMatrix();

        // Outer
        glColor4f(1.0f, 0.45f, 0.05f, 0.2f);
        glPushMatrix();
        glTranslatef(side * Cfg::SRB_OFFSET_X, Cfg::SRB_OFFSET_Y, srbZ);
        drawFlame(len, Cfg::FLAME_SRB_RADIUS);
        glPopMatrix();
    }
}

// Thruster positions in orbiter-local coords + firing direction
static const float sRCSPos[][3] = {
    // Forward RCS (near nose)
    {  0.00f,  0.16f,  4.30f },   // nose top
    { -0.16f,  0.00f,  4.30f },   // nose left
    {  0.16f,  0.00f,  4.30f },   // nose right
    // Aft RCS (near OMS pods)
    { -0.26f,  0.18f,  0.15f },   // aft left-top
    {  0.26f,  0.18f,  0.15f },   // aft right-top
    {  0.00f, -0.20f,  0.10f },   // aft bottom
};
// Each thruster gets a unique frequency
static const float sRCSFreq[] = { 1.7f, 2.3f, 1.1f, 3.1f, 2.7f, 1.9f };

void drawRCSFlashes(float stackShiftZ) {
    float t = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

    for (int i = 0; i < Cfg::RCS_THRUSTER_COUNT; ++i) {
        float s = sinf(t * sRCSFreq[i] * 6.28f + i * 1.5f);
        if (s < Cfg::RCS_FIRE_THRESHOLD) continue;  // not firing

        // Brightness pulses with sin value
        float brightness = (s - Cfg::RCS_FIRE_THRESHOLD) /
                           (1.0f - Cfg::RCS_FIRE_THRESHOLD);

        glPushMatrix();
        glTranslatef(sRCSPos[i][0],
                     sRCSPos[i][1],
                     stackShiftZ + sRCSPos[i][2]);

        // Bright core
        glColor4f(1.0f, 1.0f, 0.8f, 0.8f * brightness);
        glutSolidSphere(Cfg::RCS_FLASH_RADIUS, 8, 8);

        // Larger dim glow
        glColor4f(1.0f, 0.6f, 0.2f, 0.3f * brightness);
        glutSolidSphere(Cfg::RCS_FLASH_RADIUS * 2.5f, 8, 8);

        glPopMatrix();
    }
}

// single OMS pod at local origin along +Z.
void drawOMSPod() {
    matOMS();

    DrawCylinder(Cfg::OMS_RADIUS, Cfg::OMS_RADIUS,
                 Cfg::OMS_LENGTH, Cfg::OMS_SLICES, true);

    // Blunt aft cap
    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    DrawDome(Cfg::OMS_RADIUS, Cfg::OMS_SLICES, 8);
    glPopMatrix();
}
