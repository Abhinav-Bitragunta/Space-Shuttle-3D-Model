// scene.cpp

// Iteration: 1 (major extension in Iter 2)
// Description: Top-level scene draw function. Draws axis lines and
//              positions the full shuttle stack.
//              Iter 2 adds: ET, SRBs, attachment struts, highlight overlay.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "scene.h"
#include "config.h"
#include "primitives.h"
#include "shuttle/orbiter.h"
#include "shuttle/external_tank.h"
#include "shuttle/srb.h"
#include "shuttle/engines.h"

// TODO: Iter 5 — #include "starfield.h"

SceneState gScene;

void initScene() {
    gScene.wireframe     = false;
    gScene.showAxes      = true;
    gScene.highlightPart = HighlightPart::NONE;
}

void cycleHighlight() {
    int cur = static_cast<int>(gScene.highlightPart);
    cur = (cur + 1) % static_cast<int>(HighlightPart::COUNT);
    gScene.highlightPart = static_cast<HighlightPart>(cur);
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
// Common Z-shift: orbiter centred so midpoint is at world origin.
// ---------------------------------------------------------------------------
static const float kOrbiterShiftZ = -Cfg::FUS_LENGTH * 0.5f;

// ---------------------------------------------------------------------------
// drawETStruts: two thin box struts connecting ET to Orbiter.
//   Struts are vertical, bridging from ET top surface to Orbiter underside.
// ---------------------------------------------------------------------------
static void drawETStruts() {
    float etTopY    = Cfg::ET_OFFSET_Y + Cfg::ET_RADIUS;
    float orbBotY   = -Cfg::FUS_RADIUS_AFT;
    float strutLen  = orbBotY - etTopY;   // vertical extent (negative = going down)
    float midY      = (etTopY + orbBotY) * 0.5f;

    glColor3fv(Cfg::COL_STRUT);

    // Forward strut
    glPushMatrix();
    glTranslatef(0.0f, midY, kOrbiterShiftZ + Cfg::ET_STRUT_FWD_Z);
    DrawBox(Cfg::ET_STRUT_WIDTH, -strutLen, Cfg::ET_STRUT_HEIGHT);
    glPopMatrix();

    // Aft strut
    glPushMatrix();
    glTranslatef(0.0f, midY, kOrbiterShiftZ + Cfg::ET_STRUT_AFT_Z);
    DrawBox(Cfg::ET_STRUT_WIDTH, -strutLen, Cfg::ET_STRUT_HEIGHT);
    glPopMatrix();
}

// ---------------------------------------------------------------------------
// drawSRBStruts: four thin box struts from one SRB to the ET.
//   Struts are horizontal (X direction), bridging from SRB inner surface
//   to ET outer surface. Called once per SRB; sign parameter gives side.
// ---------------------------------------------------------------------------
static void drawSRBStrutsOneSide(float sideSign) {
    float srbInnerX = sideSign * (Cfg::SRB_OFFSET_X - Cfg::SRB_RADIUS);
    float etOuterX  = sideSign * Cfg::ET_RADIUS;
    float midX      = (srbInnerX + etOuterX) * 0.5f;
    float spanX     = (srbInnerX - etOuterX) * sideSign; // always positive

    glColor3fv(Cfg::COL_STRUT);

    // Four struts evenly spaced along the length
    float zBase = kOrbiterShiftZ + Cfg::ET_OFFSET_Z;
    float spacing = Cfg::SRB_LENGTH * 0.25f;

    for (int i = 0; i < 4; ++i) {
        float z = zBase + Cfg::SRB_SKIRT_LEN + spacing * (0.5f + i);
        glPushMatrix();
        glTranslatef(midX, Cfg::SRB_OFFSET_Y, z);
        DrawBox(spanX, Cfg::SRB_STRUT_HEIGHT, Cfg::SRB_STRUT_WIDTH);
        glPopMatrix();
    }
}

// ---------------------------------------------------------------------------
// Drawing individual stack components (separated for highlight reuse).
// ---------------------------------------------------------------------------
static void drawOrbiterInStack() {
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, kOrbiterShiftZ);
    drawOrbiter();
    glPopMatrix();
}

static void drawETInStack() {
    glPushMatrix();
    glTranslatef(0.0f, Cfg::ET_OFFSET_Y, kOrbiterShiftZ + Cfg::ET_OFFSET_Z);
    drawET();
    glPopMatrix();
}

static void drawLeftSRBInStack() {
    glPushMatrix();
    glTranslatef(-Cfg::SRB_OFFSET_X, Cfg::SRB_OFFSET_Y,
                 kOrbiterShiftZ + Cfg::ET_OFFSET_Z);
    drawSRB();
    glPopMatrix();
}

static void drawRightSRBInStack() {
    glPushMatrix();
    glTranslatef(Cfg::SRB_OFFSET_X, Cfg::SRB_OFFSET_Y,
                 kOrbiterShiftZ + Cfg::ET_OFFSET_Z);
    drawSRB();
    glPopMatrix();
}

// ---------------------------------------------------------------------------
// drawFullStack: positions Orbiter, ET, SRBs, and struts.
// ---------------------------------------------------------------------------
static void drawFullStack() {
    drawOrbiterInStack();
    drawETInStack();
    drawLeftSRBInStack();
    drawRightSRBInStack();

    // Attachment struts
    drawETStruts();
    drawSRBStrutsOneSide(-1.0f);  // left
    drawSRBStrutsOneSide( 1.0f);  // right
}

// ---------------------------------------------------------------------------
// drawHighlightOverlay: redraws the selected part in yellow wireframe
//   with polygon offset to avoid z-fighting. Gives a bright yellow
//   outline around the inspected component.
// ---------------------------------------------------------------------------
static void drawHighlightOverlay() {
    if (gScene.highlightPart == HighlightPart::NONE) return;

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    // Yellow wireframe overlay
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-1.0f, -1.0f);
    glDisable(GL_CULL_FACE);

    // Force yellow: enable lighting so glColor calls inside draw functions
    // are ignored, then set emissive material to yellow (needs no light sources).
    glEnable(GL_LIGHTING);
    float yellow[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    float black[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  yellow);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   black);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   black);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  black);

    switch (gScene.highlightPart) {
        case HighlightPart::ORBITER:  drawOrbiterInStack();  break;
        case HighlightPart::ET:       drawETInStack();       break;
        case HighlightPart::SRB_LEFT: drawLeftSRBInStack();  break;
        case HighlightPart::SRB_RIGHT:drawRightSRBInStack(); break;
        case HighlightPart::SSME:
            // SSME nozzles positioned within orbiter frame
            glPushMatrix();
            glTranslatef(0.0f, Cfg::SSME_CLUSTER_Y, kOrbiterShiftZ);
            drawSSMENozzles();
            glPopMatrix();
            break;
        case HighlightPart::OMS:
            // Both OMS pods
            glPushMatrix();
            glTranslatef(Cfg::OMS_OFFSET_X, Cfg::OMS_OFFSET_Y,
                         kOrbiterShiftZ + Cfg::OMS_OFFSET_Z);
            drawOMSPod();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(-Cfg::OMS_OFFSET_X, Cfg::OMS_OFFSET_Y,
                         kOrbiterShiftZ + Cfg::OMS_OFFSET_Z);
            glScalef(-1.0f, 1.0f, 1.0f);
            drawOMSPod();
            glPopMatrix();
            break;
        default: break;
    }

    glPopAttrib();
}

// ---------------------------------------------------------------------------
// getHighlightName: returns readable name for HUD / title bar use.
// ---------------------------------------------------------------------------
const char* getHighlightName() {
    switch (gScene.highlightPart) {
        case HighlightPart::NONE:      return "NONE";
        case HighlightPart::ORBITER:   return "ORBITER";
        case HighlightPart::ET:        return "EXT TANK";
        case HighlightPart::SRB_LEFT:  return "LEFT SRB";
        case HighlightPart::SRB_RIGHT: return "RIGHT SRB";
        case HighlightPart::SSME:      return "SSME NOZZLES";
        case HighlightPart::OMS:       return "OMS PODS";
        default:                       return "";
    }
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

    // Highlight overlay (Iter 2)
    if (!gScene.wireframe) {
        drawHighlightOverlay();
    }

    // Restore fill mode so other drawing (HUD etc.) is not wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
