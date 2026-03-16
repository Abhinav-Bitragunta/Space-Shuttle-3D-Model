// scene.h

// Iteration: 1 (Iter 2: highlight, Iter 3: lighting, Iter 4: doors, Iter 5: starfield/HUD)
// Description: Top-level scene draw call and scene state.

#pragma once

enum class HighlightPart {
    NONE = 0, ORBITER, ET, SRB_LEFT, SRB_RIGHT, SSME, OMS, COUNT
};

struct SceneState {
    bool wireframe;
    bool showAxes;
    HighlightPart highlightPart;
    bool lightingEnabled;
    bool smoothShading;
    // Iter 4
    float doorAngle;
    bool  doorOpening;
    bool  doorAnimating;
};

extern SceneState gScene;

// Globals for orbiter.cpp access (avoids circular includes)
extern bool  gInteriorMode;
extern float gDoorAngle;

void initScene();
void drawScene();
void resetScene();              // Iter 5
void cycleHighlight();
const char* getHighlightName();
void toggleDoorAnimation();     // Iter 4
void doorAnimationTick(int);    // Iter 4: glutTimerFunc callback