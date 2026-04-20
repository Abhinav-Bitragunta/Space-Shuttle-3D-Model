// Top-level scene draw call and scene state.
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
    float doorAngle;
    bool  doorOpening;
    bool  doorAnimating;
    bool  thrustEnabled;
    bool  fogEnabled;
};

extern SceneState gScene;

extern bool  gInteriorMode;
extern float gDoorAngle;

void initScene();
void drawScene();
void resetScene();
void cycleHighlight();
const char* getHighlightName();
void toggleDoorAnimation(); 
void doorAnimationTick(int);
void backgroundAnimationTick(int value);