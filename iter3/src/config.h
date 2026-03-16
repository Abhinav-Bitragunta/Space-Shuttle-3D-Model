// config.h

// Iteration: 1 (extended Iter 2, Iter 3)
// Description: Single source of truth for all magic numbers.
//              No numeric literal may appear in geometry code.

#pragma once

namespace Cfg {

// ── Window ──────────────────────────────────────────────
constexpr int    WIN_W      = 1280;
constexpr int    WIN_H      = 720;
constexpr float  FOV_Y      = 45.0f;
constexpr float  NEAR_CLIP  = 0.1f;
constexpr float  FAR_CLIP   = 200.0f;

// ── Orbiter Fuselage ────────────────────────────────────
constexpr float  FUS_LENGTH      = 4.0f;
constexpr float  FUS_RADIUS_AFT  = 0.32f;
constexpr float  FUS_RADIUS_FWD  = 0.22f;
constexpr float  NOSE_LENGTH     = 0.60f;
constexpr int    FUS_SLICES      = 32;

// ── Wings ───────────────────────────────────────────────
constexpr float  WING_SPAN       = 2.4f;
constexpr float  WING_CHORD_ROOT = 1.2f;
constexpr float  WING_CHORD_TIP  = 0.3f;
constexpr float  WING_THICKNESS  = 0.04f;
constexpr float  WING_SWEEP_DEG  = 45.0f;
constexpr float  WING_Z_ATTACH   = 1.5f;    // user adjusted (was -0.5f)

// ── Vertical Stabilizer ─────────────────────────────────
constexpr float  VSTAB_HEIGHT     = 0.7f;
constexpr float  VSTAB_CHORD_BASE = 0.9f;
constexpr float  VSTAB_CHORD_TIP  = 0.3f;
constexpr float  VSTAB_Z_ATTACH   = 0.3f;   // user adjusted (was -1.6f)
constexpr float  VSTAB_Y_BASE     = 0.0f;   // base Y: 0 = fuselage centreline

// ── Crew Cabin (Iter 2) ────────────────────────────────
constexpr float  CABIN_HUMP_WIDTH   = 0.30f;
constexpr float  CABIN_HUMP_HEIGHT  = 0.18f;
constexpr float  CABIN_HUMP_LENGTH  = 0.90f;
constexpr float  CABIN_HUMP_Z       = 2.80f;
constexpr float  CABIN_HUMP_Y       = 0.12f;
constexpr float  WINDSHIELD_WIDTH   = 0.08f;
constexpr float  WINDSHIELD_HEIGHT  = 0.06f;
constexpr int    WINDSHIELD_ROWS    = 2;
constexpr int    WINDSHIELD_COLS    = 3;
constexpr float  WINDSHIELD_GAP     = 0.02f;

// ── Payload Bay (Iter 2) ────────────────────────────────
constexpr float  PBAY_WIDTH    = 0.36f;
constexpr float  PBAY_LENGTH   = 1.80f;
constexpr float  PBAY_Z_START  = 0.90f;
constexpr float  PBAY_Y        = 0.30f;
constexpr float  PBAY_BORDER   = 0.015f;

// ── External Tank ───────────────────────────────────────
constexpr float  ET_LENGTH    = 4.8f;
constexpr float  ET_RADIUS    = 0.44f;
constexpr float  ET_OFFSET_Y  = -0.68f;     // user adjusted (was -0.55f)
constexpr float  ET_OFFSET_Z  = -0.30f;
constexpr int    ET_SLICES    = 24;
constexpr int    ET_DOME_STACKS = 12;

// ── ET Attachment Struts (Iter 2) ───────────────────────
constexpr float  ET_STRUT_WIDTH   = 0.04f;
constexpr float  ET_STRUT_HEIGHT  = 0.03f;
constexpr float  ET_STRUT_FWD_Z   = 2.80f;
constexpr float  ET_STRUT_AFT_Z   = 0.40f;

// ── SRBs ────────────────────────────────────────────────
constexpr float  SRB_LENGTH     = 4.9f;
constexpr float  SRB_RADIUS     = 0.175f;
constexpr float  SRB_OFFSET_X   = 0.68f;
constexpr float  SRB_OFFSET_Y   = ET_OFFSET_Y;
constexpr float  SRB_NOSE_LEN   = 0.30f;
constexpr float  SRB_SKIRT_RAD  = 0.22f;
constexpr float  SRB_SKIRT_LEN  = 0.25f;
constexpr int    SRB_SLICES     = 24;

// ── SRB Attachment Struts (Iter 2) ──────────────────────
constexpr float  SRB_STRUT_WIDTH   = 0.03f;
constexpr float  SRB_STRUT_HEIGHT  = 0.025f;

// ── SSME Nozzles ────────────────────────────────────────
constexpr float  SSME_BELL_RADIUS   = 0.12f;
constexpr float  SSME_THROAT_RADIUS = 0.04f;
constexpr float  SSME_DEPTH         = 0.20f;
constexpr float  SSME_SPACING       = 0.30f;    // user adjusted (was 0.22f)
constexpr int    SSME_SLICES        = 24;
constexpr float  SSME_CLUSTER_Y     = 0.08f;    // user adjusted (was 0.05f)

// ── OMS Pods (Iter 2) ──────────────────────────────────
constexpr float  OMS_LENGTH   = 0.70f;
constexpr float  OMS_RADIUS   = 0.10f;
constexpr float  OMS_OFFSET_X = 0.28f;
constexpr float  OMS_OFFSET_Y = 0.10f;
constexpr float  OMS_OFFSET_Z = -0.10f;
constexpr int    OMS_SLICES   = 16;

// ── Interior (Iter 4) ──────────────────────────────────
constexpr float  CABIN_WIDTH  = 0.48f;
constexpr float  DECK_HEIGHT  = 0.45f;
constexpr int    PANEL_ROWS   = 4;
constexpr int    PANEL_COLS   = 6;

// ── Stars (Iter 5) ─────────────────────────────────────
constexpr int    STAR_COUNT    = 2000;
constexpr float  STAR_SPHERE_R = 80.0f;

// ── Animation (Iter 5) ─────────────────────────────────
constexpr float  DOOR_OPEN_DEG   = 175.0f;
constexpr float  DOOR_ANIM_SPEED = 60.0f;
constexpr float  SRB_SEP_SPEED   = 0.4f;

// ── Camera Defaults ─────────────────────────────────────
constexpr float  CAM_DEFAULT_AZIMUTH    = 30.0f;
constexpr float  CAM_DEFAULT_ELEVATION  = 20.0f;
constexpr float  CAM_DEFAULT_DISTANCE   = 8.0f;
constexpr float  CAM_MIN_DISTANCE       = 1.0f;
constexpr float  CAM_MAX_DISTANCE       = 50.0f;
constexpr float  CAM_ORBIT_SENSITIVITY  = 0.3f;
constexpr float  CAM_ZOOM_SENSITIVITY   = 0.3f;
constexpr float  CAM_PAN_SENSITIVITY    = 0.005f;
constexpr float  CAM_SCROLL_STEP        = 0.5f;
constexpr float  CAM_ELEVATION_MIN      = -89.0f;
constexpr float  CAM_ELEVATION_MAX      = 89.0f;

// ── Axis Lines ──────────────────────────────────────────
constexpr float  AXIS_LENGTH = 3.0f;

// ── Part Highlight (Iter 2) ─────────────────────────────
constexpr int    HIGHLIGHT_PART_COUNT = 7;
constexpr float  COL_HIGHLIGHT[]  = { 1.0f, 1.0f, 0.0f };

// ── Lighting (Iter 3) ──────────────────────────────────
// Sun light (GL_LIGHT0) — directional, white-yellow
constexpr float  SUN_DIR[]       = { 1.0f, 1.5f, 1.0f, 0.0f };  // w=0 → directional
constexpr float  SUN_AMBIENT[]   = { 0.15f, 0.15f, 0.12f, 1.0f };
constexpr float  SUN_DIFFUSE[]   = { 1.0f,  0.97f, 0.90f, 1.0f };
constexpr float  SUN_SPECULAR[]  = { 1.0f,  1.0f,  0.95f, 1.0f };

// Earth-glow fill light (GL_LIGHT1) — blue-tinted, from below
constexpr float  EARTH_DIR[]     = { 0.0f, -1.0f, 0.0f, 0.0f };
constexpr float  EARTH_AMBIENT[] = { 0.02f, 0.03f, 0.05f, 1.0f };
constexpr float  EARTH_DIFFUSE[] = { 0.10f, 0.12f, 0.20f, 1.0f };
constexpr float  EARTH_SPECULAR[]= { 0.0f,  0.0f,  0.0f,  1.0f };

// ── Colours (R, G, B) ──────────────────────────────────
constexpr float  COL_ORBITER[]    = { 0.93f, 0.93f, 0.92f };
constexpr float  COL_TILE_BLACK[] = { 0.08f, 0.08f, 0.10f };
constexpr float  COL_ET[]         = { 0.85f, 0.40f, 0.10f };
constexpr float  COL_ET_DOME[]    = { 0.80f, 0.35f, 0.08f };
constexpr float  COL_SRB[]        = { 0.75f, 0.75f, 0.77f };
constexpr float  COL_SRB_SKIRT[]  = { 0.60f, 0.60f, 0.62f };
constexpr float  COL_NOZZLE[]     = { 0.25f, 0.25f, 0.28f };
constexpr float  COL_WING[]       = { 0.20f, 0.20f, 0.22f };
constexpr float  COL_VSTAB[]      = { 0.90f, 0.90f, 0.90f };
constexpr float  COL_NOSE[]       = { 0.10f, 0.10f, 0.12f };
constexpr float  COL_BACKGROUND[] = { 0.02f, 0.02f, 0.05f };
constexpr float  COL_CABIN[]      = { 0.15f, 0.15f, 0.17f };
constexpr float  COL_WINDSHIELD[] = { 0.10f, 0.15f, 0.30f };
constexpr float  COL_OMS[]        = { 0.85f, 0.85f, 0.83f };
constexpr float  COL_STRUT[]      = { 0.50f, 0.50f, 0.52f };
constexpr float  COL_PBAY_LINE[]  = { 0.30f, 0.30f, 0.32f };

} // namespace Cfg
