// scene.h

// Iteration: 1 (extended in Iter 2)
// Description: Top-level scene draw call and scene state.
//              Iter 2 adds: part highlight cycling.

#pragma once

// Highlightable parts — H key cycles through these
enum class HighlightPart {
    NONE = 0,
    ORBITER,
    ET,
    SRB_LEFT,
    SRB_RIGHT,
    SSME,
    OMS,
    COUNT           // sentinel — must be last
};

struct SceneState {
    bool wireframe;
    bool showAxes;
    HighlightPart highlightPart;   // Iter 2
};

extern SceneState gScene;

void initScene();
void drawScene();
void cycleHighlight();             // Iter 2
const char* getHighlightName();    // Iter 2
