// config.h

// Iteration: 1
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
constexpr float  WING_Z_ATTACH   = 1.5f;   // Z position where wing root meets fuselage

// ── Vertical Stabilizer ─────────────────────────────────
constexpr float  VSTAB_HEIGHT     = 0.7f;
constexpr float  VSTAB_CHORD_BASE = 0.9f;
constexpr float  VSTAB_CHORD_TIP  = 0.3f;
constexpr float  VSTAB_Z_ATTACH   = 0.3f;  // aft end of fuselage

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

// ── Colours (R, G, B) ──────────────────────────────────
constexpr float  COL_ORBITER[]    = { 0.93f, 0.93f, 0.92f };
constexpr float  COL_TILE_BLACK[] = { 0.08f, 0.08f, 0.10f };
constexpr float  COL_ET[]         = { 0.85f, 0.40f, 0.10f };
constexpr float  COL_SRB[]        = { 0.75f, 0.75f, 0.77f };
constexpr float  COL_NOZZLE[]     = { 0.25f, 0.25f, 0.28f };
constexpr float  COL_WING[]       = { 0.20f, 0.20f, 0.22f };
constexpr float  COL_VSTAB[]      = { 0.90f, 0.90f, 0.90f };
constexpr float  COL_NOSE[]       = { 0.10f, 0.10f, 0.12f };
constexpr float  COL_BACKGROUND[] = { 0.02f, 0.02f, 0.05f };

} // namespace Cfg
