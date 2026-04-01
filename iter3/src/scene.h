// scene.h

// Iteration: 1 (Iter 2: highlight, Iter 3: lighting/shading state)
// Description: Top-level scene draw call and scene state.

#pragma once

enum class HighlightPart {
    NONE = 0,
    ORBITER,
    ET,
    SRB_LEFT,
    SRB_RIGHT,
    SSME,
    OMS,
    COUNT
};

struct SceneState {
    bool wireframe;
    bool showAxes;
    HighlightPart highlightPart;
    bool lightingEnabled;    // Iter 3 — L key
    bool smoothShading;      // Iter 3 — S key
};

extern SceneState gScene;

void initScene();
void drawScene();
void cycleHighlight();
const char* getHighlightName();
