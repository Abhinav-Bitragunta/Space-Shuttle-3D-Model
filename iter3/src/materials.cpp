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
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  spec);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS,  shininess);
    // Reset emissive to black (highlight overlay sets this to yellow)
    float noEmit[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, noEmit);
    glColor3fv(col);
}

// ── Orbiter white tiles: low specular ───────────────────
void matOrbiterWhite() {
    float amb[]  = { 0.25f, 0.25f, 0.24f, 1.0f };
    float diff[] = { 0.90f, 0.90f, 0.88f, 1.0f };
    float spec[] = { 0.15f, 0.15f, 0.15f, 1.0f };
    applyMat(Cfg::COL_ORBITER, amb, diff, spec, 10.0f);
}

// ── Orbiter black tiles: very low specular ──────────────
void matOrbiterBlack() {
    float amb[]  = { 0.02f, 0.02f, 0.03f, 1.0f };
    float diff[] = { 0.08f, 0.08f, 0.10f, 1.0f };
    float spec[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    applyMat(Cfg::COL_TILE_BLACK, amb, diff, spec, 5.0f);
}

// ── ET: matte orange ────────────────────────────────────
void matET() {
    float amb[]  = { 0.20f, 0.10f, 0.03f, 1.0f };
    float diff[] = { 0.85f, 0.40f, 0.10f, 1.0f };
    float spec[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    applyMat(Cfg::COL_ET, amb, diff, spec, 5.0f);
}

// ── ET dome ─────────────────────────────────────────────
void matETDome() {
    float amb[]  = { 0.18f, 0.08f, 0.02f, 1.0f };
    float diff[] = { 0.80f, 0.35f, 0.08f, 1.0f };
    float spec[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    applyMat(Cfg::COL_ET_DOME, amb, diff, spec, 5.0f);
}

// ── SRB: light-grey metallic, mid specular ──────────────
void matSRB() {
    float amb[]  = { 0.18f, 0.18f, 0.19f, 1.0f };
    float diff[] = { 0.72f, 0.72f, 0.74f, 1.0f };
    float spec[] = { 0.40f, 0.40f, 0.40f, 1.0f };
    applyMat(Cfg::COL_SRB, amb, diff, spec, 30.0f);
}

// ── SRB aft skirt ───────────────────────────────────────
void matSRBSkirt() {
    float amb[]  = { 0.15f, 0.15f, 0.16f, 1.0f };
    float diff[] = { 0.58f, 0.58f, 0.60f, 1.0f };
    float spec[] = { 0.30f, 0.30f, 0.30f, 1.0f };
    applyMat(Cfg::COL_SRB_SKIRT, amb, diff, spec, 25.0f);
}

// ── SSME nozzle: dark steel, high specular ──────────────
void matNozzle() {
    float amb[]  = { 0.05f, 0.05f, 0.06f, 1.0f };
    float diff[] = { 0.22f, 0.22f, 0.25f, 1.0f };
    float spec[] = { 0.70f, 0.70f, 0.70f, 1.0f };
    applyMat(Cfg::COL_NOZZLE, amb, diff, spec, 64.0f);
}

// ── Nozzle inner (throat) ───────────────────────────────
void matNozzleInner() {
    float col[]  = { 0.05f, 0.05f, 0.07f };
    float amb[]  = { 0.01f, 0.01f, 0.02f, 1.0f };
    float diff[] = { 0.03f, 0.03f, 0.05f, 1.0f };
    float spec[] = { 0.0f,  0.0f,  0.0f,  1.0f };
    applyMat(col, amb, diff, spec, 0.0f);
}

// ── Delta wing ──────────────────────────────────────────
void matWing() {
    float amb[]  = { 0.05f, 0.05f, 0.06f, 1.0f };
    float diff[] = { 0.18f, 0.18f, 0.20f, 1.0f };
    float spec[] = { 0.08f, 0.08f, 0.08f, 1.0f };
    applyMat(Cfg::COL_WING, amb, diff, spec, 8.0f);
}

// ── Vertical stabilizer ────────────────────────────────
void matVStab() {
    float amb[]  = { 0.22f, 0.22f, 0.22f, 1.0f };
    float diff[] = { 0.88f, 0.88f, 0.88f, 1.0f };
    float spec[] = { 0.12f, 0.12f, 0.12f, 1.0f };
    applyMat(Cfg::COL_VSTAB, amb, diff, spec, 10.0f);
}

// ── Crew cabin hump ─────────────────────────────────────
void matCabin() {
    float amb[]  = { 0.04f, 0.04f, 0.05f, 1.0f };
    float diff[] = { 0.13f, 0.13f, 0.15f, 1.0f };
    float spec[] = { 0.06f, 0.06f, 0.06f, 1.0f };
    applyMat(Cfg::COL_CABIN, amb, diff, spec, 8.0f);
}

// ── Windshield ──────────────────────────────────────────
void matWindshield() {
    float amb[]  = { 0.02f, 0.03f, 0.06f, 1.0f };
    float diff[] = { 0.08f, 0.12f, 0.28f, 1.0f };
    float spec[] = { 0.50f, 0.50f, 0.60f, 1.0f };
    applyMat(Cfg::COL_WINDSHIELD, amb, diff, spec, 50.0f);
}

// ── OMS pod ─────────────────────────────────────────────
void matOMS() {
    float amb[]  = { 0.20f, 0.20f, 0.20f, 1.0f };
    float diff[] = { 0.82f, 0.82f, 0.80f, 1.0f };
    float spec[] = { 0.15f, 0.15f, 0.15f, 1.0f };
    applyMat(Cfg::COL_OMS, amb, diff, spec, 12.0f);
}

// ── Attachment strut ────────────────────────────────────
void matStrut() {
    float amb[]  = { 0.12f, 0.12f, 0.13f, 1.0f };
    float diff[] = { 0.48f, 0.48f, 0.50f, 1.0f };
    float spec[] = { 0.20f, 0.20f, 0.20f, 1.0f };
    applyMat(Cfg::COL_STRUT, amb, diff, spec, 20.0f);
}

// ── Payload bay door seam ───────────────────────────────
void matPayloadLine() {
    float amb[]  = { 0.07f, 0.07f, 0.08f, 1.0f };
    float diff[] = { 0.28f, 0.28f, 0.30f, 1.0f };
    float spec[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    applyMat(Cfg::COL_PBAY_LINE, amb, diff, spec, 5.0f);
}
