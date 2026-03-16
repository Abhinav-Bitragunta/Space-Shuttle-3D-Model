// scene.h

// Iteration: 1 (Iter 2: highlight, Iter 3: lighting, Iter 4: interior/doors)
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
    float doorAngle;       // current door angle (0 = closed)
    bool  doorOpening;     // true = animating toward open
    bool  doorAnimating;   // true = timer is running
};

extern SceneState gScene;

// Globals for orbiter.cpp access (avoids circular includes)
extern bool  gInteriorMode;
extern float gDoorAngle;

void initScene();
void drawScene();
void cycleHighlight();
const char* getHighlightName();
void toggleDoorAnimation();     // Iter 4
void doorAnimationTick(int);    // Iter 4: glutTimerFunc callback
