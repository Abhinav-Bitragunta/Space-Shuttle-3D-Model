// config.h

// Iteration: 1 (extended Iter 2, 3, 4)
// Description: Single source of truth for all magic numbers.

#pragma once

namespace Cfg {

	// ── Window ──────────────────────────────────────────────
	constexpr int    WIN_W = 1280;
	constexpr int    WIN_H = 720;
	constexpr float  FOV_Y = 45.0f;
	constexpr float  NEAR_CLIP = 0.1f;
	constexpr float  FAR_CLIP = 200.0f;
	constexpr float  INTERIOR_FOV = 70.0f;     // Iter 4: wider FOV for interior
	constexpr float  INTERIOR_NEAR = 0.01f;    // Iter 4: closer near-clip inside cabin

	// ── Orbiter Fuselage ────────────────────────────────────
	constexpr float  FUS_LENGTH = 4.0f;
	constexpr float  FUS_RADIUS_AFT = 0.32f;
	constexpr float  FUS_RADIUS_FWD = 0.22f;
	constexpr float  NOSE_LENGTH = 0.60f;
	constexpr int    FUS_SLICES = 32;

	// ── Wings ───────────────────────────────────────────────
	constexpr float  WING_SPAN = 2.4f;
	constexpr float  WING_CHORD_ROOT = 1.2f;
	constexpr float  WING_CHORD_TIP = 0.3f;
	constexpr float  WING_THICKNESS = 0.04f;
	constexpr float  WING_SWEEP_DEG = 45.0f;
	constexpr float  WING_Z_ATTACH = 1.5f;

	// ── Vertical Stabilizer ─────────────────────────────────
	constexpr float  VSTAB_HEIGHT = 0.7f;
	constexpr float  VSTAB_CHORD_BASE = 0.9f;
	constexpr float  VSTAB_CHORD_TIP = 0.3f;
	constexpr float  VSTAB_Z_ATTACH = 0.3f;
	constexpr float  VSTAB_Y_BASE = 0.0f;

	// ── Crew Cabin Exterior (Iter 2) ────────────────────────
	constexpr float  CABIN_HUMP_WIDTH = 0.30f;
	constexpr float  CABIN_HUMP_HEIGHT = 0.15f;
	constexpr float  CABIN_HUMP_LENGTH = 0.90f;
	constexpr float  CABIN_HUMP_Z = 2.80f;
	constexpr float  CABIN_HUMP_Y = 0.12f;
	constexpr float  WINDSHIELD_WIDTH = 0.08f;
	constexpr float  WINDSHIELD_HEIGHT = 0.06f;
	constexpr int    WINDSHIELD_ROWS = 2;
	constexpr int    WINDSHIELD_COLS = 3;
	constexpr float  WINDSHIELD_GAP = 0.02f;

	// ── Payload Bay Exterior (Iter 2) ───────────────────────
	constexpr float  PBAY_WIDTH = 0.36f;
	constexpr float  PBAY_LENGTH = 1.05f;       // structural bay extent
	constexpr float  PBAY_Z_START = 1.25f;
	constexpr float  PBAY_Y = 0.32f;       // door hinge Y — matches fuselage top
	constexpr float  PBAY_BORDER = 0.015f;

	// Full door span (bay section + crew cabin ceiling)
	constexpr float  DOOR_FULL_LENGTH = 2.20f;    // Z 1.25 → 3.45

	// ── External Tank ───────────────────────────────────────
	constexpr float  ET_LENGTH = 4.8f;
	constexpr float  ET_RADIUS = 0.44f;
	constexpr float  ET_OFFSET_Y = -0.68f;
	constexpr float  ET_OFFSET_Z = -0.30f;
	constexpr int    ET_SLICES = 24;
	constexpr int    ET_DOME_STACKS = 12;

	// ── ET Attachment Struts ────────────────────────────────
	constexpr float  ET_STRUT_WIDTH = 0.04f;
	constexpr float  ET_STRUT_HEIGHT = 0.03f;
	constexpr float  ET_STRUT_FWD_Z = 2.80f;
	constexpr float  ET_STRUT_AFT_Z = 0.40f;

	// ── SRBs ────────────────────────────────────────────────
	constexpr float  SRB_LENGTH = 4.9f;
	constexpr float  SRB_RADIUS = 0.175f;
	constexpr float  SRB_OFFSET_X = 0.68f;
	constexpr float  SRB_OFFSET_Y = ET_OFFSET_Y;
	constexpr float  SRB_NOSE_LEN = 0.30f;
	constexpr float  SRB_SKIRT_RAD = 0.22f;
	constexpr float  SRB_SKIRT_LEN = 0.25f;
	constexpr int    SRB_SLICES = 24;

	// ── SRB Attachment Struts ───────────────────────────────
	constexpr float  SRB_STRUT_WIDTH = 0.03f;
	constexpr float  SRB_STRUT_HEIGHT = 0.025f;

	// ── SSME Nozzles ────────────────────────────────────────
	constexpr float  SSME_BELL_RADIUS = 0.12f;
	constexpr float  SSME_THROAT_RADIUS = 0.04f;
	constexpr float  SSME_DEPTH = 0.20f;
	constexpr float  SSME_SPACING = 0.30f;
	constexpr int    SSME_SLICES = 24;
	constexpr float  SSME_CLUSTER_Y = 0.08f;

	// ── OMS Pods ────────────────────────────────────────────
	constexpr float  OMS_LENGTH = 0.70f;
	constexpr float  OMS_RADIUS = 0.10f;
	constexpr float  OMS_OFFSET_X = 0.28f;
	constexpr float  OMS_OFFSET_Y = 0.10f;
	constexpr float  OMS_OFFSET_Z = -0.10f;
	constexpr int    OMS_SLICES = 16;

	// ══════════════════════════════════════════════════════════
	// ── INTERIOR (Iter 4) ────────────────────────────────────
	// ══════════════════════════════════════════════════════════

	// All interior Z coords are in orbiter-local space (aft=0, fwd=4.0).
	// Y=0 is fuselage centreline. +Y is up.

	// ── Flight Deck ─────────────────────────────────────────
	constexpr float  FD_WIDTH = 0.40f;    // interior cabin width
	constexpr float  FD_HEIGHT = 0.34f;    // floor to door level (PBAY_Y)
	constexpr float  FD_FLOOR_Y = -0.02f;   // floor level
	constexpr float  FD_Z_AFT = 2.60f;    // aft wall
	constexpr float  FD_Z_FWD = 3.50f;    // forward wall (instrument panel)
	constexpr float  WALL_T = 0.025f;   // wall panel thickness (shared)

	// Seats
	constexpr float  SEAT_WIDTH = 0.10f;
	constexpr float  SEAT_DEPTH = 0.12f;
	constexpr float  SEAT_HEIGHT = 0.04f;    // seat pan thickness
	constexpr float  SEAT_BACK_H = 0.16f;    // backrest height
	constexpr float  SEAT_BACK_T = 0.02f;    // backrest thickness
	constexpr float  SEAT_LEG_H = 0.06f;    // leg height from floor
	constexpr float  SEAT_SPACING = 0.16f;    // distance between seat centres
	constexpr float  SEAT_Z = 2.90f;    // Z position of seats

	// Centre console
	constexpr float  CONSOLE_W = 0.06f;
	constexpr float  CONSOLE_H = 0.12f;
	constexpr float  CONSOLE_D = 0.30f;
	constexpr float  CONSOLE_Z = 3.05f;

	// Instrument panel (forward wall, 4 rows × 6 cols of gauges)
	constexpr int    INST_ROWS = 4;
	constexpr int    INST_COLS = 6;
	constexpr float  INST_GAUGE_W = 0.045f;
	constexpr float  INST_GAUGE_H = 0.038f;
	constexpr float  INST_GAP = 0.008f;
	constexpr float  INST_PANEL_Z = 3.48f;    // just inside forward wall

	// Overhead panel
	constexpr float  OVERHEAD_W = 0.32f;
	constexpr float  OVERHEAD_D = 0.25f;
	constexpr float  OVERHEAD_T = 0.015f;   // thickness
	constexpr float  OVERHEAD_Z = 3.10f;
	constexpr float  OVERHEAD_Y = 0.29f;    // near ceiling (below door panels)
	constexpr int    OH_SWITCH_ROWS = 3;
	constexpr int    OH_SWITCH_COLS = 8;
	constexpr float  OH_SW_SIZE = 0.012f;

	// Side consoles
	constexpr float  SIDE_CON_W = 0.03f;
	constexpr float  SIDE_CON_H = 0.10f;
	constexpr float  SIDE_CON_D = 0.30f;

	// Windshield interior frames
	constexpr float  WS_FRAME_T = 0.012f;   // frame member thickness
	constexpr int    WS_PANES_X = 3;        // panes across
	constexpr int    WS_PANES_Y = 2;        // panes vertically

	// ── Mid-Deck ────────────────────────────────────────────
	constexpr float  MD_FLOOR_Y = -0.26f;
	constexpr float  MD_CEIL_Y = FD_FLOOR_Y;   // mid-deck ceiling = flight deck floor
	constexpr float  MD_Z_AFT = 2.60f;
	constexpr float  MD_Z_FWD = 3.40f;
	constexpr float  MD_WIDTH = 0.38f;

	// Lockers
	constexpr float  LOCKER_W = 0.08f;
	constexpr float  LOCKER_H = 0.10f;
	constexpr float  LOCKER_D = 0.06f;
	constexpr int    LOCKER_ROWS = 2;
	constexpr int    LOCKER_COLS = 4;
	constexpr float  LOCKER_GAP = 0.01f;

	// Floor panel grid
	constexpr int    FLOOR_GRID_X = 4;
	constexpr int    FLOOR_GRID_Z = 6;
	constexpr float  FLOOR_LINE_T = 0.003f;

	// Hatch (floor opening to payload bay)
	constexpr float  HATCH_SIZE = 0.14f;
	constexpr float  HATCH_Z = 2.65f;

	// ── Payload Bay Interior ────────────────────────────────
	constexpr float  PBAY_FLOOR_Y = -0.22f;
	constexpr float  PBAY_INT_W = 0.32f;

	// Longerons (structural beams along the bay)
	constexpr float  LONGERON_W = 0.015f;
	constexpr float  LONGERON_H = 0.025f;
	constexpr int    LONGERON_COUNT = 6;        // per side

	// Frames (ribs across the bay)
	constexpr float  FRAME_W = 0.012f;
	constexpr float  FRAME_H = 0.020f;
	constexpr int    FRAME_COUNT = 8;

	// ── Payload Bay Doors (Iter 4 animation) ────────────────
	constexpr float  DOOR_PANEL_T = 0.015f;   // door panel thickness
	constexpr float  DOOR_RIB_W = 0.01f;    // structural rib width on door interior
	constexpr int    DOOR_RIB_COUNT = 10;       // ribs per door panel (longer doors)

	// ── Door Animation ──────────────────────────────────────
	constexpr float  DOOR_OPEN_DEG = 175.0f;
	constexpr float  DOOR_ANIM_SPEED = 60.0f;  // degrees per second
	constexpr int    ANIM_TICK_MS = 16;      // ~60 fps timer tick

	// ── Stars (Iter 5) ─────────────────────────────────────
	constexpr int    STAR_COUNT = 2000;
	constexpr float  STAR_SPHERE_R = 80.0f;

	// ── Separation Animation (Iter 5) ──────────────────────
	constexpr float  SRB_SEP_SPEED = 0.4f;

	// ── Camera Defaults ─────────────────────────────────────
	constexpr float  CAM_DEFAULT_AZIMUTH = 30.0f;
	constexpr float  CAM_DEFAULT_ELEVATION = 20.0f;
	constexpr float  CAM_DEFAULT_DISTANCE = 8.0f;
	constexpr float  CAM_MIN_DISTANCE = 1.0f;
	constexpr float  CAM_MAX_DISTANCE = 50.0f;
	constexpr float  CAM_ORBIT_SENSITIVITY = 0.3f;
	constexpr float  CAM_ZOOM_SENSITIVITY = 0.3f;
	constexpr float  CAM_PAN_SENSITIVITY = 0.005f;
	constexpr float  CAM_SCROLL_STEP = 0.5f;
	constexpr float  CAM_ELEVATION_MIN = -89.0f;
	constexpr float  CAM_ELEVATION_MAX = 89.0f;

	// ── Interior Camera (Iter 4) ────────────────────────────
	// Start position in WORLD coords (orbiter shifted by -FUS_LENGTH/2)
	constexpr float  INTCAM_START_X = 0.0f;
	constexpr float  INTCAM_START_Y = 0.18f;
	constexpr float  INTCAM_START_Z = 1.10f;   // ~Z=3.1 orbiter-local - 2.0 shift
	constexpr float  INTCAM_START_YAW = 0.0f;  // looking forward (+Z)
	constexpr float  INTCAM_START_PITCH = 0.0f;
	constexpr float  INTCAM_LOOK_SENS = 0.15f;
	constexpr float  INTCAM_MOVE_SPEED = 0.03f;  // per keypress step
	constexpr float  INTCAM_PITCH_MIN = -80.0f;
	constexpr float  INTCAM_PITCH_MAX = 80.0f;

	// Interior camera boundary clamp (world coords)
	constexpr float  INTCAM_MIN_X = -0.16f;
	constexpr float  INTCAM_MAX_X = 0.16f;
	constexpr float  INTCAM_MIN_Y = -0.22f;
	constexpr float  INTCAM_MAX_Y = 0.24f;
	constexpr float  INTCAM_MIN_Z = 0.64f;
	constexpr float  INTCAM_MAX_Z = 1.46f;

	// ── Axis Lines ──────────────────────────────────────────
	constexpr float  AXIS_LENGTH = 3.0f;

	// ── Part Highlight (Iter 2) ─────────────────────────────
	constexpr int    HIGHLIGHT_PART_COUNT = 7;
	constexpr float  COL_HIGHLIGHT[] = { 1.0f, 1.0f, 0.0f };

	// ── Lighting (Iter 3) ──────────────────────────────────
	constexpr float  SUN_DIR[] = { 1.0f, 1.5f, 1.0f, 0.0f };
	constexpr float  SUN_AMBIENT[] = { 0.15f, 0.15f, 0.12f, 1.0f };
	constexpr float  SUN_DIFFUSE[] = { 1.0f,  0.97f, 0.90f, 1.0f };
	constexpr float  SUN_SPECULAR[] = { 1.0f,  1.0f,  0.95f, 1.0f };
	constexpr float  EARTH_DIR[] = { 0.0f, -1.0f, 0.0f, 0.0f };
	constexpr float  EARTH_AMBIENT[] = { 0.02f, 0.03f, 0.05f, 1.0f };
	constexpr float  EARTH_DIFFUSE[] = { 0.10f, 0.12f, 0.20f, 1.0f };
	constexpr float  EARTH_SPECULAR[] = { 0.0f,  0.0f,  0.0f,  1.0f };

	// ── Cabin Light (Iter 4) — GL_LIGHT2 ───────────────────
	// Warm white point light inside the flight deck
	constexpr float  CABIN_LIGHT_POS[] = { 0.0f, 0.30f, 1.10f, 1.0f }; // world coords, w=1 → positional
	constexpr float  CABIN_LIGHT_AMB[] = { 0.20f, 0.18f, 0.14f, 1.0f };
	constexpr float  CABIN_LIGHT_DIFF[] = { 0.85f, 0.80f, 0.65f, 1.0f };
	constexpr float  CABIN_LIGHT_SPEC[] = { 0.40f, 0.38f, 0.30f, 1.0f };
	constexpr float  CABIN_LIGHT_ATTEN_CONST = 1.0f;
	constexpr float  CABIN_LIGHT_ATTEN_LINEAR = 0.8f;
	constexpr float  CABIN_LIGHT_ATTEN_QUAD = 0.3f;

	// ── Colours (R, G, B) ──────────────────────────────────
	constexpr float  COL_ORBITER[] = { 0.93f, 0.93f, 0.92f };
	constexpr float  COL_TILE_BLACK[] = { 0.08f, 0.08f, 0.10f };
	constexpr float  COL_ET[] = { 0.85f, 0.40f, 0.10f };
	constexpr float  COL_ET_DOME[] = { 0.80f, 0.35f, 0.08f };
	constexpr float  COL_SRB[] = { 0.75f, 0.75f, 0.77f };
	constexpr float  COL_SRB_SKIRT[] = { 0.60f, 0.60f, 0.62f };
	constexpr float  COL_NOZZLE[] = { 0.25f, 0.25f, 0.28f };
	constexpr float  COL_WING[] = { 0.20f, 0.20f, 0.22f };
	constexpr float  COL_VSTAB[] = { 0.90f, 0.90f, 0.90f };
	constexpr float  COL_NOSE[] = { 0.10f, 0.10f, 0.12f };
	constexpr float  COL_BACKGROUND[] = { 0.02f, 0.02f, 0.05f };
	constexpr float  COL_CABIN[] = { 0.15f, 0.15f, 0.17f };
	constexpr float  COL_WINDSHIELD[] = { 0.10f, 0.15f, 0.30f };
	constexpr float  COL_OMS[] = { 0.85f, 0.85f, 0.83f };
	constexpr float  COL_STRUT[] = { 0.50f, 0.50f, 0.52f };
	constexpr float  COL_PBAY_LINE[] = { 0.30f, 0.30f, 0.32f };

	// Interior colours (unlit fallback — lit appearance controlled by materials.cpp)
	constexpr float  COL_INT_WALL[] = { 0.55f, 0.53f, 0.48f };
	constexpr float  COL_INT_FLOOR[] = { 0.30f, 0.30f, 0.32f };
	constexpr float  COL_INT_PANEL[] = { 0.12f, 0.13f, 0.16f };
	constexpr float  COL_INT_SEAT[] = { 0.26f, 0.26f, 0.28f };
	constexpr float  COL_INT_FRAME[] = { 0.22f, 0.22f, 0.24f };
	constexpr float  COL_INT_LOCKER[] = { 0.50f, 0.48f, 0.44f };
	constexpr float  COL_INT_HATCH[] = { 0.28f, 0.28f, 0.24f };
	constexpr float  COL_INT_LONGERON[] = { 0.42f, 0.42f, 0.38f };
	constexpr float  COL_INT_DOOR[] = { 0.58f, 0.58f, 0.55f };
	constexpr float  COL_INT_CONSOLE[] = { 0.15f, 0.15f, 0.18f };

} // namespace Cfg