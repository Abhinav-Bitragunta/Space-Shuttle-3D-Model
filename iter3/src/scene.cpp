// scene.cpp

// Iteration: 1 (Iter 2: full stack + highlight, Iter 3: lighting/shading)
// Description: Top-level scene draw function.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "scene.h"
#include "config.h"
#include "primitives.h"
#include "materials.h"
#include "lighting.h"
#include "shuttle/orbiter.h"
#include "shuttle/external_tank.h"
#include "shuttle/srb.h"
#include "shuttle/engines.h"

// TODO: Iter 5 — #include "starfield.h"

SceneState gScene;

void initScene() {
    gScene.wireframe       = false;
    gScene.showAxes        = true;
    gScene.highlightPart   = HighlightPart::NONE;
    gScene.lightingEnabled = true;
    gScene.smoothShading   = true;
}

void cycleHighlight() {
    int cur = static_cast<int>(gScene.highlightPart);
    cur = (cur + 1) % static_cast<int>(HighlightPart::COUNT);
    gScene.highlightPart = static_cast<HighlightPart>(cur);
}

// ---------------------------------------------------------------------------
// drawAxes
// ---------------------------------------------------------------------------
static void drawAxes() {
    // Temporarily disable lighting so axes show pure colour
    glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT | GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glLineWidth(1.5f);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(Cfg::AXIS_LENGTH, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, Cfg::AXIS_LENGTH, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, Cfg::AXIS_LENGTH);
    glEnd();

    glPopAttrib();
}

static const float kOrbiterShiftZ = -Cfg::FUS_LENGTH * 0.5f;

// ---------------------------------------------------------------------------
// Struts
// ---------------------------------------------------------------------------
static void drawETStruts() {
    float etTopY  = Cfg::ET_OFFSET_Y + Cfg::ET_RADIUS;
    float orbBotY = -Cfg::FUS_RADIUS_AFT;
    float midY    = (etTopY + orbBotY) * 0.5f;
    float height  = orbBotY - etTopY;

    matStrut();

    glPushMatrix();
    glTranslatef(0.0f, midY, kOrbiterShiftZ + Cfg::ET_STRUT_FWD_Z);
    DrawBox(Cfg::ET_STRUT_WIDTH, -height, Cfg::ET_STRUT_HEIGHT);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, midY, kOrbiterShiftZ + Cfg::ET_STRUT_AFT_Z);
    DrawBox(Cfg::ET_STRUT_WIDTH, -height, Cfg::ET_STRUT_HEIGHT);
    glPopMatrix();
}

static void drawSRBStrutsOneSide(float sideSign) {
    float srbInnerX = sideSign * (Cfg::SRB_OFFSET_X - Cfg::SRB_RADIUS);
    float etOuterX  = sideSign * Cfg::ET_RADIUS;
    float midX      = (srbInnerX + etOuterX) * 0.5f;
    float spanX     = (srbInnerX - etOuterX) * sideSign;

    matStrut();

    float zBase   = kOrbiterShiftZ + Cfg::ET_OFFSET_Z;
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
// Stack component draw helpers
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

static void drawFullStack() {
    drawOrbiterInStack();
    drawETInStack();
    drawLeftSRBInStack();
    drawRightSRBInStack();
    drawETStruts();
    drawSRBStrutsOneSide(-1.0f);
    drawSRBStrutsOneSide( 1.0f);
}

// ---------------------------------------------------------------------------
// Highlight overlay
// ---------------------------------------------------------------------------
static void drawHighlightOverlay() {
    if (gScene.highlightPart == HighlightPart::NONE) return;

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-1.0f, -1.0f);
    glDisable(GL_CULL_FACE);

    glEnable(GL_LIGHTING);
    float yellow[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    float black[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellow);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  black);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  black);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);

    switch (gScene.highlightPart) {
        case HighlightPart::ORBITER:   drawOrbiterInStack();  break;
        case HighlightPart::ET:        drawETInStack();       break;
        case HighlightPart::SRB_LEFT:  drawLeftSRBInStack();  break;
        case HighlightPart::SRB_RIGHT: drawRightSRBInStack(); break;
        case HighlightPart::SSME:
            glPushMatrix();
            glTranslatef(0.0f, Cfg::SSME_CLUSTER_Y, kOrbiterShiftZ);
            drawSSMENozzles();
            glPopMatrix();
            break;
        case HighlightPart::OMS:
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
// drawScene: main entry point.
// ---------------------------------------------------------------------------
void drawScene() {
    // Shading mode (Iter 3)
    glShadeModel(gScene.smoothShading ? GL_SMOOTH : GL_FLAT);

    // Lighting (Iter 3)
    if (gScene.lightingEnabled) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        applyLighting();
    } else {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
    }

    // Wireframe / solid
    if (gScene.wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (gScene.showAxes) {
        drawAxes();
    }

    drawFullStack();

    if (!gScene.wireframe) {
        drawHighlightOverlay();
    }

    // Restore
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_LIGHTING);
}
