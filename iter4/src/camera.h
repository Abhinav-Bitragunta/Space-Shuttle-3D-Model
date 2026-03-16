// camera.h

// Iteration: 1 (Iter 4: interior first-person mode)
// Description: Camera state and input handling.

#pragma once

struct Camera {
    enum class Mode { ORBIT, INTERIOR, CINEMATIC } mode;

    // Orbit mode
    float azimuth, elevation, distance;
    float panX, panY;

    // Interior mode (Iter 4)
    float posX, posY, posZ;
    float yaw, pitch;
    bool  warpIgnore;   // flag to ignore the warp-back event

    // Mouse tracking
    int lastMouseX, lastMouseY;
    int activeButton;

    void init();
    void applyView() const;
    void toggleMode();                                   // Iter 4
    void handleMouseButton(int button, int state, int x, int y);
    void handleMouseMotion(int x, int y);
    void handlePassiveMotion(int x, int y);              // Iter 4
    void handleScroll(int dir);
    void moveForward(float amount);                      // Iter 4
    void moveRight(float amount);                        // Iter 4
    void clampPosition();                                // Iter 4: boundary check
    void setPreset(int preset);
    void getTitleInfo(char* buf, int bufSize) const;
    bool isInterior() const { return mode == Mode::INTERIOR; }
};

extern Camera gCamera;