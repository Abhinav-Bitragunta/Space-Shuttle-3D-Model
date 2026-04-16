// fuselage.cpp

// Iteration: 1 (Iter 3: materials, Iter 5: Fuselage Text)
// Description: Orbiter fuselage drawn as a tapered cylinder (frustum)
//              along +Z axis, and nose cone drawn as a cone.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

#include "fuselage.h"
#include "text_renderer.h"
#include "../config.h"
#include "../primitives.h"
#include "../materials.h"

static GLuint sTextTex = 0;

void drawFuselage() {
    // 1. Draw the underlying solid white hull
    matOrbiterWhite();
    DrawCylinder(Cfg::FUS_RADIUS_AFT, Cfg::FUS_RADIUS_FWD, Cfg::FUS_LENGTH, Cfg::FUS_SLICES, true);

    // 2. Initialise the text texture once
    if (sTextTex == 0) {
        sTextTex = loadStringTexture(Cfg::FUSELAGE_TEXT, "arial.ttf");
    }

    // 3. Draw the Decal Layer
    if (sTextTex != 0) {
        glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TEXTURE_BIT | GL_LIGHTING_BIT);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // We set the decal material to dark so the lighting equations treat the text as matte paint
        float darkPaint[] = { 0.15f, 0.15f, 0.15f, 1.0f };
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkPaint);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, darkPaint);
        float noSpec[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, noSpec);

        glBindTexture(GL_TEXTURE_2D, sTextTex);

        // -- Text UV Mapping Matrix --
        float textCenterT = Cfg::FUSELAGE_TEXT_Z / Cfg::FUS_LENGTH;
        glMatrixMode(GL_TEXTURE);

        // PORT SIDE DECAL (-X) -> gluCylinder S coordinate is roughly 0.75
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(0.5f, 0.5f, 0.0f);             // 4. Move pivot back to center of texture

        // length, height, depth of text.
        glScalef(8.0f, -6.0f, 3.0f);

        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);         // 2. Rotate 90 degrees to run longitudinally
        glTranslatef(-0.75f, -textCenterT, 0.0f);   // 1. Move UV frame to Port side center

        DrawTexturedCylinder(Cfg::FUS_RADIUS_AFT + 0.002f, Cfg::FUS_RADIUS_FWD + 0.002f, Cfg::FUS_LENGTH, Cfg::FUS_SLICES, false);
        glPopMatrix();


        // We invert the U-scale (-8.0f) here because looking at the opposite side 
        // of a cylinder naturally mirrors the texture. 
        glScalef(-8.0f, 4.0f, 1.0f);

        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        glTranslatef(-0.25f, -textCenterT, 0.0f);

        DrawTexturedCylinder(Cfg::FUS_RADIUS_AFT + 0.002f, Cfg::FUS_RADIUS_FWD + 0.002f, Cfg::FUS_LENGTH, Cfg::FUS_SLICES, false);
        glPopMatrix();

        glMatrixMode(GL_MODELVIEW); // Reset matrix mode
        glPopAttrib();
    }
}

void drawNoseCone() {
    matOrbiterBlack();
    DrawCone(Cfg::FUS_RADIUS_FWD, Cfg::NOSE_LENGTH, Cfg::FUS_SLICES);
}