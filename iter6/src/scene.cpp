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
#include "camera.h"
#include "starfield.h"
#include "hud.h"
#include "shuttle/orbiter.h"
#include "shuttle/external_tank.h"
#include "shuttle/srb.h"
#include "shuttle/engines.h"

SceneState gScene;
bool  gInteriorMode = false;
float gDoorAngle = 0.0f;

// Display lists
static GLuint sETList = 0;
static GLuint sLeftSRBList = 0;
static GLuint sRightSRBList = 0;

static void compileDisplayLists() {
    float kShiftZ = -Cfg::FUS_LENGTH * 0.5f;

    // ET display list
    sETList = glGenLists(1);
    glNewList(sETList, GL_COMPILE);
    glPushMatrix();
    glTranslatef(0.0f, Cfg::ET_OFFSET_Y, kShiftZ + Cfg::ET_OFFSET_Z);
    drawET();
    glPopMatrix();
    glEndList();

    // Left SRB
    sLeftSRBList = glGenLists(1);
    glNewList(sLeftSRBList, GL_COMPILE);
    glPushMatrix();
    glTranslatef(-Cfg::SRB_OFFSET_X, Cfg::SRB_OFFSET_Y, kShiftZ + Cfg::ET_OFFSET_Z);
    drawSRB();
    glPopMatrix();
    glEndList();

    // Right SRB
    sRightSRBList = glGenLists(1);
    glNewList(sRightSRBList, GL_COMPILE);
    glPushMatrix();
    glTranslatef(Cfg::SRB_OFFSET_X, Cfg::SRB_OFFSET_Y, kShiftZ + Cfg::ET_OFFSET_Z);
    drawSRB();
    glPopMatrix();
    glEndList();
}

void initScene() {
    gScene.wireframe = false;
    gScene.showAxes = true;
    gScene.highlightPart = HighlightPart::NONE;
    gScene.lightingEnabled = true;
    gScene.smoothShading = true;
    gScene.doorAngle = 0.0f;
    gScene.doorOpening = false;
    gScene.doorAnimating = false;

    initStarfield();
    compileDisplayLists();
}

void resetScene() {
    gScene.doorAngle = 0.0f;
    gScene.doorOpening = false;
    gScene.doorAnimating = false;
    gScene.highlightPart = HighlightPart::NONE;
    gScene.wireframe = false;
    gScene.showAxes = true;
    gScene.lightingEnabled = true;
    gScene.smoothShading = true;
}

void cycleHighlight() {
    int cur = static_cast<int>(gScene.highlightPart);
    cur = (cur + 1) % static_cast<int>(HighlightPart::COUNT);
    gScene.highlightPart = static_cast<HighlightPart>(cur);
}

void toggleDoorAnimation() {
    gScene.doorOpening = !gScene.doorOpening;
    if (!gScene.doorAnimating) {
        gScene.doorAnimating = true;
        glutTimerFunc(Cfg::ANIM_TICK_MS, doorAnimationTick, 0);
    }
}

void doorAnimationTick(int /*value*/) {
    float dt = Cfg::ANIM_TICK_MS / 1000.0f;
    float step = Cfg::DOOR_ANIM_SPEED * dt;

    if (gScene.doorOpening) {
        gScene.doorAngle += step;
        if (gScene.doorAngle >= Cfg::DOOR_OPEN_DEG) {
            gScene.doorAngle = Cfg::DOOR_OPEN_DEG;
            gScene.doorAnimating = false;
        }
    }
    else {
        gScene.doorAngle -= step;
        if (gScene.doorAngle <= 0.0f) {
            gScene.doorAngle = 0.0f;
            gScene.doorAnimating = false;
        }
    }

    gDoorAngle = gScene.doorAngle;
    glutPostRedisplay();

    if (gScene.doorAnimating) {
        glutTimerFunc(Cfg::ANIM_TICK_MS, doorAnimationTick, 0);
    }
}

static void drawAxes() {
    glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT | GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(Cfg::AXIS_LENGTH, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, Cfg::AXIS_LENGTH, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, Cfg::AXIS_LENGTH);
    glEnd();
    glPopAttrib();
}

// Stack positioning
static const float kShiftZ = -Cfg::FUS_LENGTH * 0.5f;

static void drawOrbiterInStack() {
    glPushMatrix(); glTranslatef(0.0f, 0.0f, kShiftZ); drawOrbiter(); glPopMatrix();
}
static void drawETInStack() {
    glCallList(sETList);
}
static void drawLeftSRBInStack() {
    glCallList(sLeftSRBList);
}
static void drawRightSRBInStack() {
    glCallList(sRightSRBList);
}

static void drawETStruts() {
    float etTopY = Cfg::ET_OFFSET_Y + Cfg::ET_RADIUS;
    float orbBotY = -Cfg::FUS_RADIUS_AFT;
    float midY = (etTopY + orbBotY) * 0.5f;
    float h = orbBotY - etTopY;
    matStrut();
    glPushMatrix();
    glTranslatef(0.0f, midY, kShiftZ + Cfg::ET_STRUT_FWD_Z);
    DrawBox(Cfg::ET_STRUT_WIDTH, -h, Cfg::ET_STRUT_HEIGHT); glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, midY, kShiftZ + Cfg::ET_STRUT_AFT_Z);
    DrawBox(Cfg::ET_STRUT_WIDTH, -h, Cfg::ET_STRUT_HEIGHT); glPopMatrix();
}

static void drawSRBStrutsOneSide(float sign) {
    float srbX = sign * (Cfg::SRB_OFFSET_X - Cfg::SRB_RADIUS);
    float etX = sign * Cfg::ET_RADIUS;
    float midX = (srbX + etX) * 0.5f;
    float span = (srbX - etX) * sign;
    matStrut();
    float zBase = kShiftZ + Cfg::ET_OFFSET_Z;
    float sp = Cfg::SRB_LENGTH * 0.25f;
    for (int i = 0; i < 4; ++i) {
        float z = zBase + Cfg::SRB_SKIRT_LEN + sp * (0.5f + i);
        glPushMatrix();
        glTranslatef(midX, Cfg::SRB_OFFSET_Y, z);
        DrawBox(span, Cfg::SRB_STRUT_HEIGHT, Cfg::SRB_STRUT_WIDTH);
        glPopMatrix();
    }
}

static void drawFullStack() {
    drawOrbiterInStack();
    drawETInStack();
    drawLeftSRBInStack();
    drawRightSRBInStack();
    drawETStruts();
    drawSRBStrutsOneSide(-1.0f);
    drawSRBStrutsOneSide(1.0f);
}

// Highlight
static GLuint sYellowTex = 0;

static void ensureYellowTexture() {
    if (sYellowTex != 0) return;
    unsigned char data[] = { 255, 255, 0, 255 };
    glGenTextures(1, &sYellowTex);
    glBindTexture(GL_TEXTURE_2D, sYellowTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

static void drawHighlightOverlay() {
    if (gScene.highlightPart == HighlightPart::NONE) return;

    ensureYellowTexture();

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(3.0f);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-2.0f, -2.0f);
    glDisable(GL_CULL_FACE);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sYellowTex);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    switch (gScene.highlightPart) {
    case HighlightPart::ORBITER:   drawOrbiterInStack();  break;
    case HighlightPart::ET:        drawETInStack();       break;
    case HighlightPart::SRB_LEFT:  drawLeftSRBInStack();  break;
    case HighlightPart::SRB_RIGHT: drawRightSRBInStack(); break;
    case HighlightPart::SSME:
        glPushMatrix(); glTranslatef(0.0f, Cfg::SSME_CLUSTER_Y, kShiftZ);
        drawSSMENozzles(); glPopMatrix(); break;
    case HighlightPart::OMS:
        glPushMatrix();
        glTranslatef(Cfg::OMS_OFFSET_X, Cfg::OMS_OFFSET_Y, kShiftZ + Cfg::OMS_OFFSET_Z);
        drawOMSPod(); glPopMatrix();
        glPushMatrix();
        glTranslatef(-Cfg::OMS_OFFSET_X, Cfg::OMS_OFFSET_Y, kShiftZ + Cfg::OMS_OFFSET_Z);
        glScalef(-1, 1, 1); drawOMSPod(); glPopMatrix();
        break;
    default: break;
    }

    glDisable(GL_TEXTURE_2D);
    glPopAttrib();
}

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

void drawScene() {
    gInteriorMode = gCamera.isInterior();
    gDoorAngle = gScene.doorAngle;

    // Starfield drawn first, behind everything
    // Visible through open doors in interior mode.
    drawStarfield();

    glShadeModel(gScene.smoothShading ? GL_SMOOTH : GL_FLAT);

    if (gScene.lightingEnabled) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        applyLighting();

        if (gInteriorMode) {
            applyCabinLighting();
        }
        else {
            disableCabinLighting();
        }
    }
    else {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        disableCabinLighting();
    }

    if (gScene.wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (gScene.showAxes && !gInteriorMode) {
        drawAxes();
    }

    drawFullStack();

    if (!gScene.wireframe && !gInteriorMode) {
        drawHighlightOverlay();
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_LIGHTING);

    drawHUD();
}