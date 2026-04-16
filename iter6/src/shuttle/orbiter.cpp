// orbiter.cpp

// Iteration: 1 (Iter 2: exterior details, Iter 3: materials, Iter 4: interior)
// Description: Draws the complete Orbiter — exterior + interior.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "orbiter.h"
#include "fuselage.h"
#include "wings.h"
#include "engines.h"
#include "interior/flight_deck.h"
#include "interior/mid_deck.h"
#include "interior/payload_bay.h"
#include "../config.h"
#include "../primitives.h"
#include "../materials.h"

// Declared in scene.h — avoids circular include
extern bool gInteriorMode;
extern float gDoorAngle;

// ---------------------------------------------------------------------------
// drawCrewCabin: forward protrusion on upper fuselage with windshield.
// ---------------------------------------------------------------------------
static void drawCrewCabin() {
    glPushMatrix();
    glTranslatef(0.0f,
        Cfg::CABIN_HUMP_Y + Cfg::CABIN_HUMP_HEIGHT * 0.5f,
        Cfg::CABIN_HUMP_Z);
    matCabin();
    DrawBox(Cfg::CABIN_HUMP_WIDTH, Cfg::CABIN_HUMP_HEIGHT, Cfg::CABIN_HUMP_LENGTH);
    glPopMatrix();

    float totalW = Cfg::WINDSHIELD_COLS * (Cfg::WINDSHIELD_WIDTH + Cfg::WINDSHIELD_GAP)
        - Cfg::WINDSHIELD_GAP;
    float totalH = Cfg::WINDSHIELD_ROWS * (Cfg::WINDSHIELD_HEIGHT + Cfg::WINDSHIELD_GAP)
        - Cfg::WINDSHIELD_GAP;
    float startX = -totalW * 0.5f;
    float startY = Cfg::CABIN_HUMP_Y + Cfg::CABIN_HUMP_HEIGHT - totalH - Cfg::WINDSHIELD_GAP;
    float fwdZ = Cfg::CABIN_HUMP_Z + Cfg::CABIN_HUMP_LENGTH * 0.5f + 0.001f;

    matWindshield();
    for (int r = 0; r < Cfg::WINDSHIELD_ROWS; ++r) {
        for (int c = 0; c < Cfg::WINDSHIELD_COLS; ++c) {
            float cx = startX + c * (Cfg::WINDSHIELD_WIDTH + Cfg::WINDSHIELD_GAP)
                + Cfg::WINDSHIELD_WIDTH * 0.5f;
            float cy = startY + r * (Cfg::WINDSHIELD_HEIGHT + Cfg::WINDSHIELD_GAP)
                + Cfg::WINDSHIELD_HEIGHT * 0.5f;
            float p0[3] = { cx - Cfg::WINDSHIELD_WIDTH * 0.5f,
                             cy - Cfg::WINDSHIELD_HEIGHT * 0.5f, fwdZ };
            float p1[3] = { cx + Cfg::WINDSHIELD_WIDTH * 0.5f,
                             cy - Cfg::WINDSHIELD_HEIGHT * 0.5f, fwdZ };
            float p2[3] = { cx + Cfg::WINDSHIELD_WIDTH * 0.5f,
                             cy + Cfg::WINDSHIELD_HEIGHT * 0.5f, fwdZ };
            float p3[3] = { cx - Cfg::WINDSHIELD_WIDTH * 0.5f,
                             cy + Cfg::WINDSHIELD_HEIGHT * 0.5f, fwdZ };
            DrawQuad(p0, p1, p2, p3);
        }
    }
}

// ---------------------------------------------------------------------------
// drawOrbiter
// ---------------------------------------------------------------------------
void drawOrbiter() {
    // ── Exterior shell ──────────────────────────────────
    glPushMatrix(); drawFuselage();           glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, Cfg::FUS_LENGTH);
    drawNoseCone();
    glPopMatrix();

    glPushMatrix(); drawWings();              glPopMatrix();
    glPushMatrix(); drawVerticalStabilizer(); glPopMatrix();
    glPushMatrix(); drawCrewCabin();          glPopMatrix();

    // Payload bay doors (always drawn — animated)
    glPushMatrix(); drawPayloadBayDoors(gDoorAngle); glPopMatrix();

    // SSME nozzles
    glPushMatrix();
    glTranslatef(0.0f, Cfg::SSME_CLUSTER_Y, 0.0f);
    drawSSMENozzles();
    glPopMatrix();

    // OMS pods
    glPushMatrix();
    glTranslatef(Cfg::OMS_OFFSET_X, Cfg::OMS_OFFSET_Y, Cfg::OMS_OFFSET_Z);
    drawOMSPod();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-Cfg::OMS_OFFSET_X, Cfg::OMS_OFFSET_Y, Cfg::OMS_OFFSET_Z);
    glScalef(-1.0f, 1.0f, 1.0f);
    glFrontFace(GL_CW);   // negative scale flips winding — tell GL
    drawOMSPod();
    glFrontFace(GL_CCW);  // restore default winding
    glPopMatrix();

    // ── Interior (Iter 4) — only in interior mode ───────
    if (gInteriorMode) {
        glPushAttrib(GL_ENABLE_BIT | GL_LIGHTING_BIT);
        glDisable(GL_CULL_FACE);
        // Disable GL_COLOR_MATERIAL so glMaterialfv values (ambient, diffuse,
        // specular, shininess) actually drive the lighting equation instead of
        // being overridden by glColor3fv.  glColor still works as the unlit
        // fallback when lighting is toggled off.
        glDisable(GL_COLOR_MATERIAL);

        drawFlightDeck();
        drawMidDeck();

        glPopAttrib();
    }
}