// hud.cpp

// Iteration: 5
// Description: 2D HUD overlay — switches to orthographic projection,
//              renders status text and control legend, then restores state.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "hud.h"
#include "config.h"
#include "primitives.h"
#include "scene.h"
#include "camera.h"

#include <cstdio>

// ---------------------------------------------------------------------------
// Helper: draw a single line of text.  x,y in screen pixels from bottom-left.
// ---------------------------------------------------------------------------
static void hudText(float x, float y, const char* str, void* font = nullptr) {
    if (!font) font = GLUT_BITMAP_HELVETICA_12;
    DrawText2D(x, y, str, font);
}

// ---------------------------------------------------------------------------
// drawHUD: called at the end of each frame after the 3D scene.
// ---------------------------------------------------------------------------
void drawHUD() {
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);

    // ── Save GL state and switch to 2D ortho ────────────
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, static_cast<double>(w), 0.0, static_cast<double>(h));

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    float mx = Cfg::HUD_MARGIN_X;
    float my = Cfg::HUD_MARGIN_Y;
    float lh = Cfg::HUD_LINE_H;

    // ── Status block (top-left) ─────────────────────────
    float y = h - my;

    // View mode
    const char* viewStr = "EXTERIOR";
    if (gCamera.mode == Camera::Mode::INTERIOR)  viewStr = "INTERIOR";
    if (gCamera.mode == Camera::Mode::CINEMATIC) viewStr = "CINEMATIC";
    char buf[128];

    glColor3fv(Cfg::COL_HUD);
    snprintf(buf, sizeof(buf), "[VIEW: %s]", viewStr);
    hudText(mx, y, buf);
    y -= lh;

    snprintf(buf, sizeof(buf), "[LIGHT: %s]  [SHADING: %s]",
        gScene.lightingEnabled ? "ON" : "OFF",
        gScene.smoothShading ? "SMOOTH" : "FLAT");
    hudText(mx, y, buf);
    y -= lh;

    const char* doorStr = "CLOSED";
    if (gScene.doorAnimating)       doorStr = "MOVING";
    else if (gScene.doorAngle > 1.0f) doorStr = "OPEN";
    snprintf(buf, sizeof(buf), "[DOORS: %s]  [WIRE: %s]",
        doorStr,
        gScene.wireframe ? "ON" : "OFF");
    hudText(mx, y, buf);
    y -= lh;

    const char* hlName = getHighlightName();
    if (gScene.highlightPart != HighlightPart::NONE) {
        snprintf(buf, sizeof(buf), "[HIGHLIGHT: %s]", hlName);
        hudText(mx, y, buf);
    }

    // ── Control legend (bottom-left) ────────────────────
    glColor3fv(Cfg::COL_HUD_DIM);
    y = my + lh * 8;
    if (gCamera.mode == Camera::Mode::INTERIOR) {
        hudText(mx, y, "WASD: Move  |  Mouse: Look");  y -= lh;
        hudText(mx, y, "O: Doors  |  L: Light  |  Esc: Exit Interior");
    }
    else {
        hudText(mx, y, "LMB: Orbit  |  RMB: Zoom  |  MMB: Pan");  y -= lh;
        hudText(mx, y, "1-6: Presets  |  W: Wire  |  A: Axes  |  S: Shading");  y -= lh;
        hudText(mx, y, "L: Light  |  H: Highlight  |  O: Doors  |  F: Interior");  y -= lh;
        hudText(mx, y, "R: Reset  |  Esc: Quit");
    }

    // ── Restore GL state ────────────────────────────────
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib();

    // Re-enable depth test (Iter 5 common pitfall)
    glEnable(GL_DEPTH_TEST);
}