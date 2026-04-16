#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "flight_deck.h"
#include "../../config.h"
#include "../../primitives.h"
#include "../../materials.h"


// Room dimensions
static const float kHalfW = Cfg::FD_WIDTH * 0.5f;
static const float kFloorY = Cfg::FD_FLOOR_Y;
static const float kCeilY = Cfg::FD_FLOOR_Y + Cfg::FD_HEIGHT;
static const float kWT = Cfg::WALL_T;
static const float kMidZ = (Cfg::FD_Z_AFT + Cfg::FD_Z_FWD) * 0.5f;
static const float kLen = Cfg::FD_Z_FWD - Cfg::FD_Z_AFT;
static const float kRoomH = Cfg::FD_HEIGHT;


// Room enclosure
static void drawRoomEnclosure() {
    // Floor: extends past side walls to cover corner seams
    matIntFloor();
    glPushMatrix();
    glTranslatef(0.0f, kFloorY - kWT * 0.5f, kMidZ);
    DrawBox(Cfg::FD_WIDTH + kWT * 2.0f, kWT, kLen + kWT * 2.0f);
    glPopMatrix();

    // Left wall: full Z length covers aft/fwd wall ends
    glPushMatrix();
    glTranslatef(-kHalfW - kWT * 0.5f, (kFloorY + kCeilY) * 0.5f, kMidZ);
    DrawBox(kWT, kRoomH, kLen + kWT * 2.0f);
    glPopMatrix();

    // Right wall
    glPushMatrix();
    glTranslatef(kHalfW + kWT * 0.5f, (kFloorY + kCeilY) * 0.5f, kMidZ);
    DrawBox(kWT, kRoomH, kLen + kWT * 2.0f);
    glPopMatrix();

    // Aft wall: fits inside side walls (side walls cover corners)
    glPushMatrix();
    glTranslatef(0.0f, (kFloorY + kCeilY) * 0.5f, Cfg::FD_Z_AFT - kWT * 0.5f);
    DrawBox(Cfg::FD_WIDTH, kRoomH, kWT);
    glPopMatrix();

    // Forward wall (instrument panel backing)
    glPushMatrix();
    glTranslatef(0.0f, (kFloorY + kCeilY) * 0.5f, Cfg::FD_Z_FWD + kWT * 0.5f);
    DrawBox(Cfg::FD_WIDTH, kRoomH, kWT);
    glPopMatrix();

    matIntFrame();
    float trimH = 0.008f;
    float trimD = 0.008f;

    // Floor trim - left
    glPushMatrix();
    glTranslatef(-kHalfW + trimD * 0.5f, kFloorY + trimH * 0.5f, kMidZ);
    DrawBox(trimD, trimH, kLen);
    glPopMatrix();
    // Floor trim - right
    glPushMatrix();
    glTranslatef(kHalfW - trimD * 0.5f, kFloorY + trimH * 0.5f, kMidZ);
    DrawBox(trimD, trimH, kLen);
    glPopMatrix();
    // Floor trim — aft
    glPushMatrix();
    glTranslatef(0.0f, kFloorY + trimH * 0.5f, Cfg::FD_Z_AFT + trimD * 0.5f);
    DrawBox(Cfg::FD_WIDTH, trimH, trimD);
    glPopMatrix();
    // Floor trim — forward
    glPushMatrix();
    glTranslatef(0.0f, kFloorY + trimH * 0.5f, Cfg::FD_Z_FWD - trimD * 0.5f);
    DrawBox(Cfg::FD_WIDTH, trimH, trimD);
    glPopMatrix();

    // Wall-top trim at door hinge level (where walls meet door panels)
    glPushMatrix();
    glTranslatef(-kHalfW + trimD * 0.5f, kCeilY - trimH * 0.5f, kMidZ);
    DrawBox(trimD, trimH, kLen);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(kHalfW - trimD * 0.5f, kCeilY - trimH * 0.5f, kMidZ);
    DrawBox(trimD, trimH, kLen);
    glPopMatrix();

    // The doors (PBAY_WIDTH) are narrower than the room (FD_WIDTH).
    // These fixed strips bridge the gap on each side, acting as the
    // structural rail that the doors close against.
    matIntFrame();
    float doorHalfW = Cfg::PBAY_WIDTH * 0.5f;
    float stripW = kHalfW - doorHalfW;  // gap per side
    if (stripW > 0.001f) {
        float stripY = kCeilY;  // flush with wall tops
        // Left rail strip
        glPushMatrix();
        glTranslatef(-(doorHalfW + stripW * 0.5f), stripY, kMidZ);
        DrawBox(stripW, kWT, kLen + kWT * 2.0f);
        glPopMatrix();
        // Right rail strip
        glPushMatrix();
        glTranslatef(doorHalfW + stripW * 0.5f, stripY, kMidZ);
        DrawBox(stripW, kWT, kLen + kWT * 2.0f);
        glPopMatrix();
    }
}


// Seat with armrests and headrest

static void drawSeat() {
    matIntSeat();

    float legH = Cfg::SEAT_LEG_H;
    float panH = Cfg::SEAT_HEIGHT;
    float panY = legH + panH * 0.5f;

    // Seat pan
    glPushMatrix();
    glTranslatef(0.0f, panY, 0.0f);
    DrawBox(Cfg::SEAT_WIDTH, panH, Cfg::SEAT_DEPTH);
    glPopMatrix();

    // Backrest
    float backY = legH + panH + Cfg::SEAT_BACK_H * 0.5f;
    glPushMatrix();
    glTranslatef(0.0f, backY,
        -Cfg::SEAT_DEPTH * 0.5f + Cfg::SEAT_BACK_T * 0.5f);
    DrawBox(Cfg::SEAT_WIDTH, Cfg::SEAT_BACK_H, Cfg::SEAT_BACK_T);
    glPopMatrix();

    // Headrest
    float headY = legH + panH + Cfg::SEAT_BACK_H + 0.015f;
    glPushMatrix();
    glTranslatef(0.0f, headY,
        -Cfg::SEAT_DEPTH * 0.5f + Cfg::SEAT_BACK_T * 0.5f);
    DrawBox(Cfg::SEAT_WIDTH * 0.6f, 0.03f, Cfg::SEAT_BACK_T + 0.005f);
    glPopMatrix();

    // Four legs
    float legW = 0.012f;
    float hx = Cfg::SEAT_WIDTH * 0.5f - legW * 0.5f;
    float hz = Cfg::SEAT_DEPTH * 0.5f - legW * 0.5f;
    matIntFrame();
    for (int i = 0; i < 4; ++i) {
        float sx = (i & 1) ? hx : -hx;
        float sz = (i & 2) ? hz : -hz;
        glPushMatrix();
        glTranslatef(sx, legH * 0.5f, sz);
        DrawBox(legW, legH, legW);
        glPopMatrix();
    }

    // Armrests
    float armY = legH + panH + 0.02f;
    float armLen = Cfg::SEAT_DEPTH * 0.7f;
    float armW = 0.015f;
    float armH = 0.01f;
    float armX = Cfg::SEAT_WIDTH * 0.5f + armW * 0.3f;
    matIntFrame();
    for (int side = -1; side <= 1; side += 2) {
        // Arm rest pad
        glPushMatrix();
        glTranslatef(side * armX, armY, 0.0f);
        DrawBox(armW, armH, armLen);
        glPopMatrix();
        // Support post
        glPushMatrix();
        glTranslatef(side * armX, (panY + armY) * 0.5f, -armLen * 0.3f);
        DrawBox(0.008f, armY - panY, 0.008f);
        glPopMatrix();
    }
}


// T-shaped stick in front of seat

static void drawControlYoke() {
    matIntFrame();

    float baseY = kFloorY + Cfg::SEAT_LEG_H + Cfg::SEAT_HEIGHT;
    float stickH = 0.10f;
    float stickR = 0.006f;

    // Vertical post
    glPushMatrix();
    glTranslatef(0.0f, baseY, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    DrawCylinder(stickR, stickR, stickH, 8, true);
    glPopMatrix();

    // Horizontal grip (T-bar)
    float gripW = 0.06f;
    float gripR = 0.005f;
    glPushMatrix();
    glTranslatef(0.0f, baseY + stickH, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 0.0f, -gripW * 0.5f);
    DrawCylinder(gripR, gripR * 0.7f, gripW, 8, true);
    glPopMatrix();
}


// Instrument panel — 4×6 gauges with full bezel framing

static void drawInstrumentPanel() {
    float panelW = Cfg::INST_COLS * (Cfg::INST_GAUGE_W + Cfg::INST_GAP) - Cfg::INST_GAP + 0.05f;
    float panelH = Cfg::INST_ROWS * (Cfg::INST_GAUGE_H + Cfg::INST_GAP) - Cfg::INST_GAP + 0.05f;
    float panelMidY = kFloorY + kRoomH * 0.5f;

    // Panel backing board
    matIntPanel();
    glPushMatrix();
    glTranslatef(0.0f, panelMidY, Cfg::INST_PANEL_Z);
    DrawBox(panelW, panelH, 0.025f);
    glPopMatrix();

    // Outer frame surround
    matIntFrame();
    float ft = 0.012f;
    float outerW = panelW + ft * 2.0f;
    float outerH = panelH + ft * 2.0f;
    // Top
    glPushMatrix();
    glTranslatef(0.0f, panelMidY + panelH * 0.5f + ft * 0.5f, Cfg::INST_PANEL_Z - 0.005f);
    DrawBox(outerW, ft, 0.015f);
    glPopMatrix();
    // Bottom
    glPushMatrix();
    glTranslatef(0.0f, panelMidY - panelH * 0.5f - ft * 0.5f, Cfg::INST_PANEL_Z - 0.005f);
    DrawBox(outerW, ft, 0.015f);
    glPopMatrix();
    // Left
    glPushMatrix();
    glTranslatef(-panelW * 0.5f - ft * 0.5f, panelMidY, Cfg::INST_PANEL_Z - 0.005f);
    DrawBox(ft, panelH, 0.015f);
    glPopMatrix();
    // Right
    glPushMatrix();
    glTranslatef(panelW * 0.5f + ft * 0.5f, panelMidY, Cfg::INST_PANEL_Z - 0.005f);
    DrawBox(ft, panelH, 0.015f);
    glPopMatrix();

    // Gauges
    float totalW = Cfg::INST_COLS * (Cfg::INST_GAUGE_W + Cfg::INST_GAP) - Cfg::INST_GAP;
    float totalH = Cfg::INST_ROWS * (Cfg::INST_GAUGE_H + Cfg::INST_GAP) - Cfg::INST_GAP;
    float startX = -totalW * 0.5f;
    float startY = panelMidY - totalH * 0.5f;
    float gaugeZ = Cfg::INST_PANEL_Z - 0.014f;

    int idx = 0;
    for (int r = 0; r < Cfg::INST_ROWS; ++r) {
        for (int c = 0; c < Cfg::INST_COLS; ++c) {
            float cx = startX + c * (Cfg::INST_GAUGE_W + Cfg::INST_GAP) + Cfg::INST_GAUGE_W * 0.5f;
            float cy = startY + r * (Cfg::INST_GAUGE_H + Cfg::INST_GAP) + Cfg::INST_GAUGE_H * 0.5f;

            matGauge(idx);
            glPushMatrix();
            glTranslatef(cx, cy, gaugeZ);
            DrawBox(Cfg::INST_GAUGE_W, Cfg::INST_GAUGE_H, 0.005f);
            glPopMatrix();

            // Full bezel (all four sides)
            matIntFrame();
            float bt = 0.004f;
            float bz = gaugeZ + 0.003f;
            float hw = Cfg::INST_GAUGE_W * 0.5f;
            float hh = Cfg::INST_GAUGE_H * 0.5f;
            glPushMatrix();
            glTranslatef(cx, cy + hh + bt * 0.5f, bz);
            DrawBox(Cfg::INST_GAUGE_W + bt * 2.0f, bt, 0.004f);
            glPopMatrix();
            glPushMatrix();
            glTranslatef(cx, cy - hh - bt * 0.5f, bz);
            DrawBox(Cfg::INST_GAUGE_W + bt * 2.0f, bt, 0.004f);
            glPopMatrix();
            glPushMatrix();
            glTranslatef(cx - hw - bt * 0.5f, cy, bz);
            DrawBox(bt, Cfg::INST_GAUGE_H, 0.004f);
            glPopMatrix();
            glPushMatrix();
            glTranslatef(cx + hw + bt * 0.5f, cy, bz);
            DrawBox(bt, Cfg::INST_GAUGE_H, 0.004f);
            glPopMatrix();

            idx++;
        }
    }

    // Reset emissive from gauge materials
    float noEmit[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, noEmit);
}


// Overhead panel with switch indicators

static void drawOverheadPanel() {
    matIntPanel();
    glPushMatrix();
    glTranslatef(0.0f, Cfg::OVERHEAD_Y, Cfg::OVERHEAD_Z);
    DrawBox(Cfg::OVERHEAD_W, Cfg::OVERHEAD_T, Cfg::OVERHEAD_D);
    glPopMatrix();

    // Panel edge trim
    matIntFrame();
    float ft = 0.006f;
    float panelBottom = Cfg::OVERHEAD_Y - Cfg::OVERHEAD_T * 0.5f;
    glPushMatrix();
    glTranslatef(0.0f, panelBottom - ft * 0.5f,
        Cfg::OVERHEAD_Z + Cfg::OVERHEAD_D * 0.5f - ft * 0.5f);
    DrawBox(Cfg::OVERHEAD_W, ft, ft);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, panelBottom - ft * 0.5f,
        Cfg::OVERHEAD_Z - Cfg::OVERHEAD_D * 0.5f + ft * 0.5f);
    DrawBox(Cfg::OVERHEAD_W, ft, ft);
    glPopMatrix();

    // Switch indicator grid
    float totalW = Cfg::OH_SWITCH_COLS * (Cfg::OH_SW_SIZE * 1.5f) - Cfg::OH_SW_SIZE * 0.5f;
    float totalD = Cfg::OH_SWITCH_ROWS * (Cfg::OH_SW_SIZE * 1.5f) - Cfg::OH_SW_SIZE * 0.5f;
    float startX = -totalW * 0.5f;
    float startZ = Cfg::OVERHEAD_Z - totalD * 0.5f;
    float swY = panelBottom - 0.003f;

    int idx = 0;
    for (int r = 0; r < Cfg::OH_SWITCH_ROWS; ++r) {
        for (int c = 0; c < Cfg::OH_SWITCH_COLS; ++c) {
            float sx = startX + c * Cfg::OH_SW_SIZE * 1.5f;
            float sz = startZ + r * Cfg::OH_SW_SIZE * 1.5f;
            matOverheadSwitch(idx);
            glPushMatrix();
            glTranslatef(sx, swY, sz);
            DrawBox(Cfg::OH_SW_SIZE, 0.004f, Cfg::OH_SW_SIZE);
            glPopMatrix();
            idx++;
        }
    }

    float noEmit[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, noEmit);
}


// Windshield frames with dark glass panes

static void drawWindshieldFrames() {
    matIntFrame();

    float z = Cfg::INST_PANEL_Z + 0.015f;
    float botY = kFloorY + kRoomH * 0.35f;
    float topY = kCeilY;
    float paneH = topY - botY;
    float paneW = Cfg::FD_WIDTH;
    float t = Cfg::WS_FRAME_T;

    // Outer frame border
    glPushMatrix();
    glTranslatef(0.0f, topY - t * 0.5f, z);
    DrawBox(paneW + t * 2.0f, t, t);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, botY + t * 0.5f, z);
    DrawBox(paneW + t * 2.0f, t, t);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-kHalfW - t * 0.5f, botY + paneH * 0.5f, z);
    DrawBox(t, paneH, t);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(kHalfW + t * 0.5f, botY + paneH * 0.5f, z);
    DrawBox(t, paneH, t);
    glPopMatrix();

    // Vertical dividers
    for (int i = 1; i < Cfg::WS_PANES_X; ++i) {
        float x = -kHalfW + paneW * static_cast<float>(i) / Cfg::WS_PANES_X;
        glPushMatrix();
        glTranslatef(x, botY + paneH * 0.5f, z);
        DrawBox(t, paneH, t);
        glPopMatrix();
    }

    // Horizontal dividers
    for (int i = 1; i < Cfg::WS_PANES_Y; ++i) {
        float y = botY + paneH * static_cast<float>(i) / Cfg::WS_PANES_Y;
        glPushMatrix();
        glTranslatef(0.0f, y, z);
        DrawBox(paneW, t, t);
        glPopMatrix();
    }

    // Glass panes behind frames
    matWindshield();
    for (int r = 0; r < Cfg::WS_PANES_Y; ++r) {
        for (int c = 0; c < Cfg::WS_PANES_X; ++c) {
            float gx = -kHalfW + (c + 0.5f) * paneW / Cfg::WS_PANES_X;
            float gy = botY + (r + 0.5f) * paneH / Cfg::WS_PANES_Y;
            float gw = paneW / Cfg::WS_PANES_X - t * 1.5f;
            float gh = paneH / Cfg::WS_PANES_Y - t * 1.5f;
            glPushMatrix();
            glTranslatef(gx, gy, z + 0.003f);
            DrawBox(gw, gh, 0.002f);
            glPopMatrix();
        }
    }
}


// Side consoles with button rows

static void drawSideConsoles() {
    for (int side = -1; side <= 1; side += 2) {
        float cx = side * (kHalfW - Cfg::SIDE_CON_W * 0.5f);
        float cy = kFloorY + Cfg::SIDE_CON_H * 0.5f;
        float cz = Cfg::CONSOLE_Z;

        matIntConsole();
        glPushMatrix();
        glTranslatef(cx, cy, cz);
        DrawBox(Cfg::SIDE_CON_W, Cfg::SIDE_CON_H, Cfg::SIDE_CON_D);
        glPopMatrix();

        // Button row on top surface
        matIntFrame();
        float topY = kFloorY + Cfg::SIDE_CON_H + 0.002f;
        float btnSize = 0.008f;
        float btnGap = 0.015f;
        int nButtons = 5;
        float startZ = cz - (nButtons - 1) * btnGap * 0.5f;
        for (int b = 0; b < nButtons; ++b) {
            glPushMatrix();
            glTranslatef(cx, topY, startZ + b * btnGap);
            DrawBox(btnSize, 0.004f, btnSize);
            glPopMatrix();
        }
    }
}


// Centre console with throttle levers

static void drawCentreConsole() {
    matIntConsole();
    glPushMatrix();
    glTranslatef(0.0f, kFloorY + Cfg::CONSOLE_H * 0.5f, Cfg::CONSOLE_Z);
    DrawBox(Cfg::CONSOLE_W, Cfg::CONSOLE_H, Cfg::CONSOLE_D);
    glPopMatrix();

    // Throttle levers
    matIntFrame();
    float topY = kFloorY + Cfg::CONSOLE_H;
    float leverH = 0.04f;
    float leverR = 0.004f;
    for (int i = -1; i <= 1; i += 2) {
        glPushMatrix();
        glTranslatef(i * 0.012f, topY, Cfg::CONSOLE_Z + 0.02f);
        glRotatef(-75.0f, 1.0f, 0.0f, 0.0f);
        DrawCylinder(leverR, leverR * 0.7f, leverH, 8, true);
        glPopMatrix();
    }
}


// main()

void drawFlightDeck() {
    drawRoomEnclosure();

    // Commander seat (left)
    glPushMatrix();
    glTranslatef(-Cfg::SEAT_SPACING * 0.5f, kFloorY, Cfg::SEAT_Z);
    drawSeat();
    glPopMatrix();

    // Pilot seat (right)
    glPushMatrix();
    glTranslatef(Cfg::SEAT_SPACING * 0.5f, kFloorY, Cfg::SEAT_Z);
    drawSeat();
    glPopMatrix();

    // Control yokes
    glPushMatrix();
    glTranslatef(-Cfg::SEAT_SPACING * 0.5f, 0.0f,
        Cfg::SEAT_Z + Cfg::SEAT_DEPTH * 0.5f + 0.04f);
    drawControlYoke();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(Cfg::SEAT_SPACING * 0.5f, 0.0f,
        Cfg::SEAT_Z + Cfg::SEAT_DEPTH * 0.5f + 0.04f);
    drawControlYoke();
    glPopMatrix();

    drawCentreConsole();
    drawSideConsoles();
    drawInstrumentPanel();
    drawOverheadPanel();
    drawWindshieldFrames();
}