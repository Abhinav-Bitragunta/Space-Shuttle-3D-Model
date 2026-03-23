// camera.h

// Iteration: 1
// Description: Camera state and input handling. Supports orbit mode
//              with mouse drag for rotate/zoom/pan and preset viewpoints.

#pragma once

struct Camera {
    enum class Mode { ORBIT, INTERIOR, CINEMATIC } mode;

    // Orbit mode state
    float azimuth;
    float elevation;
    float distance;
    float panX, panY;

    // Interior mode (TODO: Iter 4)
    float posX, posY, posZ;
    float yaw, pitch;

    // Mouse tracking
    int lastMouseX, lastMouseY;
    int activeButton;           // which button is held (-1 = none)

    void init();
    void applyView() const;
    void handleMouseButton(int button, int state, int x, int y);
    void handleMouseMotion(int x, int y);
    void handleScroll(int dir);
    void setPreset(int preset);  // 1-6
    void getTitleInfo(char* buf, int bufSize) const;
};

extern Camera gCamera;
