// camera.h

// Iteration: 1 (Iter 4: interior, Iter 5: cinematic + smooth lerp)
// Description: Camera state and input handling. Three modes: orbit,
//              interior first-person, and cinematic smooth interpolation.

#pragma once

struct Camera {
    enum class Mode { ORBIT, INTERIOR, CINEMATIC } mode;

    // Orbit mode
    float azimuth, elevation, distance;
    float panX, panY;

    // Interior mode (Iter 4)
    float posX, posY, posZ;
    float yaw, pitch;
    bool  warpIgnore;

    // Cinematic lerp (Iter 5)
    float targetAz, targetEl, targetDist;
    bool  lerping;

    // Mouse tracking
    int lastMouseX, lastMouseY;
    int activeButton;

    void init();
    void reset();                                        // Iter 5
    void applyView() const;
    void toggleMode();                                   // Iter 4
    void handleMouseButton(int button, int state, int x, int y);
    void handleMouseMotion(int x, int y);
    void handlePassiveMotion(int x, int y);              // Iter 4
    void handleScroll(int dir);
    void moveForward(float amount);                      // Iter 4
    void moveRight(float amount);                        // Iter 4
    void clampPosition();                                // Iter 4
    void setPreset(int preset);
    void startLerp(float az, float el, float dist);      // Iter 5
    void getTitleInfo(char* buf, int bufSize) const;
    bool isInterior() const { return mode == Mode::INTERIOR; }
};

void cameraLerpTick(int value);   // Iter 5: glutTimerFunc callback

extern Camera gCamera;