// materials.cpp

// Iteration: 3
// Description: Material presets. Each function sets both glMaterialfv
//              (for lit mode) and glColor3fv (for unlit fallback).

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "materials.h"
#include "config.h"

// ---------------------------------------------------------------------------
// Helper: set material + colour in one call.
//   amb/diff are float[4], spec is float[4], shin is float.
//   col is float[3] used for glColor fallback when lighting is off.
// ---------------------------------------------------------------------------
static void applyMat(const float col[3],
    const float amb[4], const float diff[4],
    const float spec[4], float shininess) {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    // Reset emissive to black (highlight overlay sets this to yellow)
    float noEmit[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, noEmit);
    glColor3fv(col);
}

// ── Orbiter white tiles: low specular ───────────────────
void matOrbiterWhite() {
    float amb[] = { 0.25f, 0.25f, 0.24f, 1.0f };
    float diff[] = { 0.90f, 0.90f, 0.88f, 1.0f };
    float spec[] = { 0.15f, 0.15f, 0.15f, 1.0f };
    applyMat(Cfg::COL_ORBITER, amb, diff, spec, 10.0f);
}

// ── Orbiter black tiles: very low specular ──────────────
void matOrbiterBlack() {
    float amb[] = { 0.02f, 0.02f, 0.03f, 1.0f };
    float diff[] = { 0.08f, 0.08f, 0.10f, 1.0f };
    float spec[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    applyMat(Cfg::COL_TILE_BLACK, amb, diff, spec, 5.0f);
}

// ── ET: matte orange ────────────────────────────────────
void matET() {
    float amb[] = { 0.20f, 0.10f, 0.03f, 1.0f };
    float diff[] = { 0.85f, 0.40f, 0.10f, 1.0f };
    float spec[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    applyMat(Cfg::COL_ET, amb, diff, spec, 5.0f);
}

// ── ET dome ─────────────────────────────────────────────
void matETDome() {
    float amb[] = { 0.18f, 0.08f, 0.02f, 1.0f };
    float diff[] = { 0.80f, 0.35f, 0.08f, 1.0f };
    float spec[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    applyMat(Cfg::COL_ET_DOME, amb, diff, spec, 5.0f);
}

// ── SRB: light-grey metallic, mid specular ──────────────
void matSRB() {
    float amb[] = { 0.18f, 0.18f, 0.19f, 1.0f };
    float diff[] = { 0.72f, 0.72f, 0.74f, 1.0f };
    float spec[] = { 0.40f, 0.40f, 0.40f, 1.0f };
    applyMat(Cfg::COL_SRB, amb, diff, spec, 30.0f);
}

// ── SRB aft skirt ───────────────────────────────────────
void matSRBSkirt() {
    float amb[] = { 0.15f, 0.15f, 0.16f, 1.0f };
    float diff[] = { 0.58f, 0.58f, 0.60f, 1.0f };
    float spec[] = { 0.30f, 0.30f, 0.30f, 1.0f };
    applyMat(Cfg::COL_SRB_SKIRT, amb, diff, spec, 25.0f);
}

// ── SSME nozzle: dark steel, high specular ──────────────
void matNozzle() {
    float amb[] = { 0.05f, 0.05f, 0.06f, 1.0f };
    float diff[] = { 0.22f, 0.22f, 0.25f, 1.0f };
    float spec[] = { 0.70f, 0.70f, 0.70f, 1.0f };
    applyMat(Cfg::COL_NOZZLE, amb, diff, spec, 64.0f);
}

// ── Nozzle inner (throat) ───────────────────────────────
void matNozzleInner() {
    float col[] = { 0.05f, 0.05f, 0.07f };
    float amb[] = { 0.01f, 0.01f, 0.02f, 1.0f };
    float diff[] = { 0.03f, 0.03f, 0.05f, 1.0f };
    float spec[] = { 0.0f,  0.0f,  0.0f,  1.0f };
    applyMat(col, amb, diff, spec, 0.0f);
}

// ── Delta wing ──────────────────────────────────────────
void matWing() {
    float amb[] = { 0.05f, 0.05f, 0.06f, 1.0f };
    float diff[] = { 0.18f, 0.18f, 0.20f, 1.0f };
    float spec[] = { 0.08f, 0.08f, 0.08f, 1.0f };
    applyMat(Cfg::COL_WING, amb, diff, spec, 8.0f);
}

// ── Vertical stabilizer ────────────────────────────────
void matVStab() {
    float amb[] = { 0.22f, 0.22f, 0.22f, 1.0f };
    float diff[] = { 0.88f, 0.88f, 0.88f, 1.0f };
    float spec[] = { 0.12f, 0.12f, 0.12f, 1.0f };
    applyMat(Cfg::COL_VSTAB, amb, diff, spec, 10.0f);
}

// ── Crew cabin hump ─────────────────────────────────────
void matCabin() {
    float amb[] = { 0.04f, 0.04f, 0.05f, 1.0f };
    float diff[] = { 0.13f, 0.13f, 0.15f, 1.0f };
    float spec[] = { 0.06f, 0.06f, 0.06f, 1.0f };
    applyMat(Cfg::COL_CABIN, amb, diff, spec, 8.0f);
}

// ── Windshield ──────────────────────────────────────────
void matWindshield() {
    float amb[] = { 0.02f, 0.03f, 0.06f, 1.0f };
    float diff[] = { 0.06f, 0.10f, 0.22f, 1.0f };
    float spec[] = { 0.65f, 0.65f, 0.70f, 1.0f };
    applyMat(Cfg::COL_WINDSHIELD, amb, diff, spec, 80.0f);
}

// ── OMS pod ─────────────────────────────────────────────
void matOMS() {
    float amb[] = { 0.20f, 0.20f, 0.20f, 1.0f };
    float diff[] = { 0.82f, 0.82f, 0.80f, 1.0f };
    float spec[] = { 0.15f, 0.15f, 0.15f, 1.0f };
    applyMat(Cfg::COL_OMS, amb, diff, spec, 12.0f);
}

// ── Attachment strut ────────────────────────────────────
void matStrut() {
    float amb[] = { 0.12f, 0.12f, 0.13f, 1.0f };
    float diff[] = { 0.48f, 0.48f, 0.50f, 1.0f };
    float spec[] = { 0.20f, 0.20f, 0.20f, 1.0f };
    applyMat(Cfg::COL_STRUT, amb, diff, spec, 20.0f);
}

// ── Payload bay door seam ───────────────────────────────
void matPayloadLine() {
    float amb[] = { 0.07f, 0.07f, 0.08f, 1.0f };
    float diff[] = { 0.28f, 0.28f, 0.30f, 1.0f };
    float spec[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    applyMat(Cfg::COL_PBAY_LINE, amb, diff, spec, 5.0f);
}

// ══════════════════════════════════════════════════════════
// Interior materials (Iter 4)
// Now that GL_COLOR_MATERIAL is disabled for interior drawing,
// glMaterialfv values fully control the lit appearance.  Specular
// and shininess are tuned per-surface for appropriate reflectivity.
// ══════════════════════════════════════════════════════════

void matIntWall() {
    // Off-white painted panels — low specular, warm tint
    float amb[] = { 0.14f, 0.13f, 0.11f, 1.0f };
    float diff[] = { 0.52f, 0.50f, 0.46f, 1.0f };
    float spec[] = { 0.06f, 0.06f, 0.06f, 1.0f };
    applyMat(Cfg::COL_INT_WALL, amb, diff, spec, 5.0f);
}

void matIntFloor() {
    // Scuffed metal/composite floor — slightly glossy
    float amb[] = { 0.07f, 0.07f, 0.08f, 1.0f };
    float diff[] = { 0.28f, 0.28f, 0.30f, 1.0f };
    float spec[] = { 0.12f, 0.12f, 0.12f, 1.0f };
    applyMat(Cfg::COL_INT_FLOOR, amb, diff, spec, 15.0f);
}

void matIntPanel() {
    // Dark instrument panel backing — moderate gloss
    float amb[] = { 0.03f, 0.03f, 0.04f, 1.0f };
    float diff[] = { 0.10f, 0.11f, 0.14f, 1.0f };
    float spec[] = { 0.18f, 0.18f, 0.20f, 1.0f };
    applyMat(Cfg::COL_INT_PANEL, amb, diff, spec, 25.0f);
}

void matIntSeat() {
    // Fabric/padded seats — low sheen
    float amb[] = { 0.06f, 0.06f, 0.07f, 1.0f };
    float diff[] = { 0.24f, 0.24f, 0.26f, 1.0f };
    float spec[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    applyMat(Cfg::COL_INT_SEAT, amb, diff, spec, 8.0f);
}

void matIntFrame() {
    // Metallic structural frames — noticeable specular highlight
    float amb[] = { 0.05f, 0.05f, 0.06f, 1.0f };
    float diff[] = { 0.20f, 0.20f, 0.22f, 1.0f };
    float spec[] = { 0.35f, 0.35f, 0.35f, 1.0f };
    applyMat(Cfg::COL_INT_FRAME, amb, diff, spec, 40.0f);
}

void matIntLocker() {
    // Painted metal lockers — slight eggshell sheen
    float amb[] = { 0.12f, 0.11f, 0.10f, 1.0f };
    float diff[] = { 0.48f, 0.46f, 0.42f, 1.0f };
    float spec[] = { 0.10f, 0.10f, 0.10f, 1.0f };
    applyMat(Cfg::COL_INT_LOCKER, amb, diff, spec, 12.0f);
}

void matIntHatch() {
    // Metal hatch cover — moderate gloss
    float amb[] = { 0.06f, 0.06f, 0.05f, 1.0f };
    float diff[] = { 0.26f, 0.26f, 0.22f, 1.0f };
    float spec[] = { 0.20f, 0.20f, 0.18f, 1.0f };
    applyMat(Cfg::COL_INT_HATCH, amb, diff, spec, 25.0f);
}

void matIntLongeron() {
    // Bare aluminium structural beams — high specular
    float amb[] = { 0.10f, 0.10f, 0.09f, 1.0f };
    float diff[] = { 0.40f, 0.40f, 0.36f, 1.0f };
    float spec[] = { 0.45f, 0.45f, 0.42f, 1.0f };
    applyMat(Cfg::COL_INT_LONGERON, amb, diff, spec, 50.0f);
}

void matIntDoor() {
    // Door inner surface — painted metal, moderate brightness
    float amb[] = { 0.15f, 0.15f, 0.14f, 1.0f };
    float diff[] = { 0.55f, 0.55f, 0.52f, 1.0f };
    float spec[] = { 0.12f, 0.12f, 0.12f, 1.0f };
    applyMat(Cfg::COL_INT_DOOR, amb, diff, spec, 15.0f);
}

void matIntConsole() {
    // Dark console surfaces — slight plastic sheen
    float amb[] = { 0.03f, 0.03f, 0.04f, 1.0f };
    float diff[] = { 0.13f, 0.13f, 0.16f, 1.0f };
    float spec[] = { 0.22f, 0.22f, 0.24f, 1.0f };
    applyMat(Cfg::COL_INT_CONSOLE, amb, diff, spec, 30.0f);
}

void matGauge(int index) {
    // Cycle through instrument colours for visual variety
    static const float gaugeColors[][3] = {
        { 0.15f, 0.60f, 0.25f },  // green
        { 0.20f, 0.55f, 0.20f },  // darker green
        { 0.75f, 0.55f, 0.10f },  // amber
        { 0.18f, 0.35f, 0.65f },  // blue
        { 0.65f, 0.18f, 0.15f },  // red (warning)
        { 0.12f, 0.50f, 0.50f },  // teal
        { 0.55f, 0.55f, 0.10f },  // yellow-green
        { 0.40f, 0.20f, 0.55f },  // purple indicator
    };
    int i = index % 8;
    float amb[] = { gaugeColors[i][0] * 0.3f, gaugeColors[i][1] * 0.3f, gaugeColors[i][2] * 0.3f, 1.0f };
    float diff[] = { gaugeColors[i][0], gaugeColors[i][1], gaugeColors[i][2], 1.0f };
    float spec[] = { 0.45f, 0.45f, 0.45f, 1.0f };
    applyMat(gaugeColors[i], amb, diff, spec, 50.0f);
}

void matOverheadSwitch(int index) {
    static const float swColors[][3] = {
        { 0.10f, 0.45f, 0.10f },  // green LED
        { 0.70f, 0.50f, 0.05f },  // amber LED
        { 0.50f, 0.10f, 0.10f },  // red LED
        { 0.15f, 0.15f, 0.40f },  // blue LED
    };
    int i = index % 4;
    float amb[] = { swColors[i][0] * 0.5f, swColors[i][1] * 0.5f, swColors[i][2] * 0.5f, 1.0f };
    float diff[] = { swColors[i][0], swColors[i][1], swColors[i][2], 1.0f };
    float spec[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    float emit[] = { swColors[i][0] * 0.3f, swColors[i][1] * 0.3f, swColors[i][2] * 0.3f, 1.0f };
    // Emissive glow for switch indicators
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emit);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0f);
    glColor3fv(swColors[i]);
}