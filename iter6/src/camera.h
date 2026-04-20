#pragma once

struct Camera {
    enum class Mode { ORBIT, INTERIOR, CINEMATIC } mode;

    // Orbit mode
    float azimuth, elevation, distance;
    float panX, panY;

    // Interior mode
    float posX, posY, posZ;
    float yaw, pitch;
    bool  warpIgnore;

    // Cinematic lerp
    float targetAz, targetEl, targetDist;
    bool  lerping;
    bool  ortho;

    // Mouse tracking
    int lastMouseX, lastMouseY;
    int activeButton;

    void init();
    void reset();                                        
    void applyView() const;
    void toggleMode();                                   
    void handleMouseButton(int button, int state, int x, int y);
    void handleMouseMotion(int x, int y);
    void handlePassiveMotion(int x, int y);              
    void handleScroll(int dir);
    void moveForward(float amount);                      
    void moveRight(float amount);                        
    void moveUp(float amount);
    void clampPosition();                                
    void setPreset(int preset);
    void setPresetOrtho(int preset);
    void startLerp(float az, float el, float dist);      
    void getTitleInfo(char* buf, int bufSize) const;
    bool isInterior() const { return mode == Mode::INTERIOR; }
};

void cameraLerpTick(int value);

extern Camera gCamera;