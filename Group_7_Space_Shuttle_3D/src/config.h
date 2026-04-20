#pragma once

namespace Cfg {

	//  Window 
	constexpr int    WIN_W = 1280;
	constexpr int    WIN_H = 720;
	constexpr float  FOV_Y = 45.0f;
	constexpr float  NEAR_CLIP = 0.1f;
	constexpr float  FAR_CLIP = 200.0f;
	constexpr float  INTERIOR_FOV = 70.0f;
	constexpr float  INTERIOR_NEAR = 0.01f;

	//  Orbiter Fuselage 
	constexpr float  FUS_LENGTH = 4.0f;
	constexpr float  FUS_RADIUS_AFT = 0.32f;
	constexpr float  FUS_RADIUS_FWD = 0.22f;
	constexpr float  NOSE_LENGTH = 0.60f;
	constexpr int    FUS_SLICES = 32;

	//  Fuselage Text 
	constexpr const char* FUSELAGE_TEXT = "CS 302N";
	constexpr float  FUSELAGE_TEXT_SCALE = 0.0015f;
	constexpr float  FUSELAGE_TEXT_Z = 2.0f;       // Middle of the fuselage
	constexpr float  FUSELAGE_TEXT_Y = 0.0f;       // Vertical alignment
	constexpr float  FUSELAGE_TEXT_OFFSET = 0.005f;

	//  Wings 
	constexpr float  WING_SPAN = 2.4f;
	constexpr float  WING_CHORD_ROOT = 1.2f;
	constexpr float  WING_CHORD_TIP = 0.3f;
	constexpr float  WING_THICKNESS = 0.04f;
	constexpr float  WING_SWEEP_DEG = 45.0f;
	constexpr float  WING_Z_ATTACH = 1.5f;

	//  Vertical Stabilizer 
	constexpr float  VSTAB_HEIGHT = 0.7f;
	constexpr float  VSTAB_CHORD_BASE = 0.9f;
	constexpr float  VSTAB_CHORD_TIP = 0.3f;
	constexpr float  VSTAB_Z_ATTACH = 0.3f;
	constexpr float  VSTAB_Y_BASE = 0.0f;

	//  Crew Cabin Exterior
	constexpr float  CABIN_HUMP_WIDTH = 0.30f;
	constexpr float  CABIN_HUMP_HEIGHT = 0.15f;
	constexpr float  CABIN_HUMP_LENGTH = 1.15f;
	constexpr float  CABIN_HUMP_Z = 2.925f;
	constexpr float  CABIN_HUMP_Y = 0.12f;
	constexpr float  WINDSHIELD_WIDTH = 0.08f;
	constexpr float  WINDSHIELD_HEIGHT = 0.06f;
	constexpr int    WINDSHIELD_ROWS = 2;
	constexpr int    WINDSHIELD_COLS = 3;
	constexpr float  WINDSHIELD_GAP = 0.02f;

	//  Payload Bay / Door Region 
	constexpr float  PBAY_WIDTH = CABIN_HUMP_WIDTH;  
	constexpr float  PBAY_LENGTH = CABIN_HUMP_LENGTH;
	constexpr float  PBAY_Z_START = CABIN_HUMP_Z - CABIN_HUMP_LENGTH * 0.5f;
	constexpr float  PBAY_Y = CABIN_HUMP_Y + CABIN_HUMP_HEIGHT;
	constexpr float  PBAY_BORDER = 0.015f;

	//  External Tank 
	constexpr float  ET_LENGTH = 4.8f;
	constexpr float  ET_RADIUS = 0.44f;
	constexpr float  ET_OFFSET_Y = -0.68f;
	constexpr float  ET_OFFSET_Z = -0.30f;
	constexpr int    ET_SLICES = 24;
	constexpr int    ET_DOME_STACKS = 12;

	//  ET Attachment Struts 
	constexpr float  ET_STRUT_WIDTH = 0.04f;
	constexpr float  ET_STRUT_HEIGHT = 0.03f;
	constexpr float  ET_STRUT_FWD_Z = 2.80f;
	constexpr float  ET_STRUT_AFT_Z = 0.40f;

	//  SRBs 
	constexpr float  SRB_LENGTH = 4.9f;
	constexpr float  SRB_RADIUS = 0.175f;
	constexpr float  SRB_OFFSET_X = 0.68f;
	constexpr float  SRB_OFFSET_Y = ET_OFFSET_Y;
	constexpr float  SRB_NOSE_LEN = 0.30f;
	constexpr float  SRB_SKIRT_RAD = 0.26f;
	constexpr float  SRB_SKIRT_LEN = 0.25f;
	constexpr int    SRB_SLICES = 24;

	//  SRB Attachment Struts 
	constexpr float  SRB_STRUT_WIDTH = 0.03f;
	constexpr float  SRB_STRUT_HEIGHT = 0.025f;

	//  SSME Nozzles 
	constexpr float  SSME_BELL_RADIUS = 0.12f;
	constexpr float  SSME_THROAT_RADIUS = 0.04f;
	constexpr float  SSME_DEPTH = 0.20f;
	constexpr float  SSME_SPACING = 0.30f;
	constexpr int    SSME_SLICES = 24;
	constexpr float  SSME_CLUSTER_Y = 0.08f;

	//  OMS Pods 
	constexpr float  OMS_LENGTH = 0.70f;
	constexpr float  OMS_RADIUS = 0.10f;
	constexpr float  OMS_OFFSET_X = 0.28f;
	constexpr float  OMS_OFFSET_Y = 0.10f;
	constexpr float  OMS_OFFSET_Z = -0.10f;
	constexpr int    OMS_SLICES = 16;

	//  INTERIOR 

	// All interior Z coords are in orbiter-local space (aft=0, fwd=4.0).
	// Y=0 is fuselage centreline. +Y is up.

	//  Flight Deck 
	constexpr float  FD_WIDTH = 0.40f; 
	constexpr float  FD_HEIGHT = 0.29f;
	constexpr float  FD_FLOOR_Y = -0.02f;
	constexpr float  FD_Z_AFT = 2.60f;
	constexpr float  FD_Z_FWD = 3.50f;
	constexpr float  WALL_T = 0.025f; 

	// Seats
	constexpr float  SEAT_WIDTH = 0.10f;
	constexpr float  SEAT_DEPTH = 0.12f;
	constexpr float  SEAT_HEIGHT = 0.04f;
	constexpr float  SEAT_BACK_H = 0.12f;
	constexpr float  SEAT_BACK_T = 0.02f;
	constexpr float  SEAT_LEG_H = 0.04f;    // leg height from floor
	constexpr float  SEAT_SPACING = 0.16f;    // distance between seat centres
	constexpr float  SEAT_Z = 2.90f;    // Z position of seats

	// Centre console
	constexpr float  CONSOLE_W = 0.06f;
	constexpr float  CONSOLE_H = 0.12f;
	constexpr float  CONSOLE_D = 0.30f;
	constexpr float  CONSOLE_Z = 3.05f;

	// Instrument panel (forward wall, 4 rows x 6 cols of gauges)
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
	constexpr float  WS_FRAME_T = 0.012f;
	constexpr int    WS_PANES_X = 3;        // panes across
	constexpr int    WS_PANES_Y = 2;        // panes vertically

	//  Mid-Deck 
	constexpr float  MD_FLOOR_Y = -0.26f;
	constexpr float  MD_CEIL_Y = FD_FLOOR_Y;
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

	//  Payload Bay Interior 
	constexpr float  PBAY_FLOOR_Y = -0.22f;
	constexpr float  PBAY_INT_W = 0.32f;

	// structural beams along the bay
	constexpr float  LONGERON_W = 0.015f;
	constexpr float  LONGERON_H = 0.025f;
	constexpr int    LONGERON_COUNT = 6;        // per side

	// Frames (ribs across the bay)
	constexpr float  FRAME_W = 0.012f;
	constexpr float  FRAME_H = 0.020f;
	constexpr int    FRAME_COUNT = 8;

	//  Cabin Doors
	constexpr float  DOOR_GAP_MARGIN = 0.0f;
	constexpr float  DOOR_GAP_Z_AFT = OVERHEAD_Z - OVERHEAD_D * 0.5f - DOOR_GAP_MARGIN;
	constexpr float  DOOR_GAP_Z_FWD = OVERHEAD_Z + OVERHEAD_D * 0.5f + DOOR_GAP_MARGIN;

	// Back door segment (behind overhead panel)
	constexpr float  DOOR_AFT_Z_START = PBAY_Z_START;
	constexpr float  DOOR_AFT_LENGTH = DOOR_GAP_Z_AFT - DOOR_AFT_Z_START;

	// Forward door segment (ahead of overhead panel)
	constexpr float  DOOR_FWD_Z_START = DOOR_GAP_Z_FWD;                                    
	constexpr float  DOOR_FWD_LENGTH = (PBAY_Z_START + PBAY_LENGTH) - DOOR_FWD_Z_START;

	constexpr float  DOOR_PANEL_T = 0.015f; 
	constexpr float  DOOR_RIB_W = 0.01f;    
	constexpr int    DOOR_AFT_RIB_COUNT = 4;
	constexpr int    DOOR_FWD_RIB_COUNT = 2;

	//  Door Animation 
	constexpr float  DOOR_OPEN_DEG = 175.0f;
	constexpr float  DOOR_ANIM_SPEED = 60.0f;  // degrees per second
	constexpr int    ANIM_TICK_MS = 16;      // ~60 fps timer tick

	//  Starfield 
	constexpr int    STAR_COUNT = 2000;
	constexpr float  STAR_SPHERE_R = 80.0f;

	// Galaxies
	constexpr int    GALAXY_COUNT = 20;
	constexpr int    GALAXY_STARS_MIN = 2000;
	constexpr int    GALAXY_STARS_MAX = 5000;
	constexpr float  GALAXY_MAX_RADIUS = 15.0f;

	// Meteors (Shooting Stars)
	constexpr int    METEOR_COUNT = 50;
	constexpr float  METEOR_SPEED_MIN = 30.0f;
	constexpr float  METEOR_SPEED_MAX = 70.0f;
	constexpr float  METEOR_LENGTH = 8.0f;

	// Asteroids
	constexpr int    ASTEROID_COUNT = 10;
	constexpr float  ASTEROID_DIST_MIN = 30.0f;
	constexpr float  ASTEROID_DIST_MAX = 60.0f;
	constexpr float  ASTEROID_SCALE_MIN = 0.2f;
	constexpr float  ASTEROID_SCALE_MAX = 0.8f;

	// Background Planets
	constexpr int    PLANET_COUNT = 0;
	constexpr float  PLANET_DIST_MIN = 60.0f;
	constexpr float  PLANET_DIST_MAX = 80.0f;
	constexpr float  PLANET_RADIUS_MIN = 1.0f;
	constexpr float  PLANET_RADIUS_MAX = 4.5f;

	//  HUD 
	constexpr float  HUD_MARGIN_X = 12.0f;
	constexpr float  HUD_MARGIN_Y = 16.0f;
	constexpr float  HUD_LINE_H = 16.0f;
	constexpr float  COL_HUD[] = { 0.0f, 1.0f, 0.4f };   // green text
	constexpr float  COL_HUD_DIM[] = { 0.0f, 0.55f, 0.25f };  // dimmer for labels

	//  Camera Defaults 
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

	//  Cinematic Camera 
	constexpr float  CAM_LERP_SPEED = 3.0f;    // interpolation rate (higher = faster)
	constexpr int    CAM_LERP_TICK_MS = 16;       // ~60 fps timer

	//  Interior Camera 
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

	//  Axis Lines 
	constexpr float  AXIS_LENGTH = 3.0f;

	//  Part Highlight 
	constexpr int    HIGHLIGHT_PART_COUNT = 7;
	constexpr float  COL_HIGHLIGHT[] = { 1.0f, 1.0f, 0.0f };

	//  Lighting 
	constexpr float  SUN_DIR[] = { 1.0f, 1.5f, 1.0f, 0.0f };
	constexpr float  SUN_AMBIENT[] = { 0.15f, 0.15f, 0.12f, 1.0f };
	constexpr float  SUN_DIFFUSE[] = { 1.0f,  0.97f, 0.90f, 1.0f };
	constexpr float  SUN_SPECULAR[] = { 1.0f,  1.0f,  0.95f, 1.0f };
	constexpr float  EARTH_DIR[] = { 0.0f, -1.0f, 0.0f, 0.0f };
	constexpr float  EARTH_AMBIENT[] = { 0.02f, 0.03f, 0.05f, 1.0f };
	constexpr float  EARTH_DIFFUSE[] = { 0.10f, 0.12f, 0.20f, 1.0f };
	constexpr float  EARTH_SPECULAR[] = { 0.0f,  0.0f,  0.0f,  1.0f };

	//  Cabin Light - GL_LIGHT2 
	constexpr float  CABIN_LIGHT_POS[] = { 0.0f, 0.30f, 1.10f, 1.0f };
	constexpr float  CABIN_LIGHT_AMB[] = { 0.20f, 0.18f, 0.14f, 1.0f };
	constexpr float  CABIN_LIGHT_DIFF[] = { 0.85f, 0.80f, 0.65f, 1.0f };
	constexpr float  CABIN_LIGHT_SPEC[] = { 0.40f, 0.38f, 0.30f, 1.0f };
	constexpr float  CABIN_LIGHT_ATTEN_CONST = 1.0f;
	constexpr float  CABIN_LIGHT_ATTEN_LINEAR = 0.8f;
	constexpr float  CABIN_LIGHT_ATTEN_QUAD = 0.3f;

	//  Exhaust Flames
	constexpr float  FLAME_SSME_LENGTH    = 0.60f;
	constexpr float  FLAME_SSME_RADIUS    = 0.10f;
	constexpr float  FLAME_SRB_LENGTH     = 0.80f;
	constexpr float  FLAME_SRB_RADIUS     = 0.20f;
	constexpr int    FLAME_SLICES         = 16;
	constexpr float  FLAME_FLICKER_SPEED  = 8.0f;   // Hz
	constexpr float  FLAME_FLICKER_AMP    = 0.25f;   // fraction of length

	//  Fog
	constexpr float  FOG_DENSITY = 0.012f;
	constexpr float  COL_FOG[]   = { 0.03f, 0.03f, 0.08f };

	//  ET Procedural Texture
	constexpr int    ET_TEX_SIZE = 64;

	//  RCS Thruster Flashes
	constexpr float  RCS_FLASH_RADIUS  = 0.018f;
	constexpr int    RCS_THRUSTER_COUNT = 6;
	constexpr float  RCS_FIRE_THRESHOLD = 0.75f;   // sin > this = firing

	//  Colours (R, G, B) 
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

	// Interior colours unlit fallback. Lit appearance controlled by materials.cpp
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