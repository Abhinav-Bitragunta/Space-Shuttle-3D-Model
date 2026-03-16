// scene.h

// Iteration: 1
// Description: Top-level scene draw call and scene state (wireframe, axes).

#pragma once

struct SceneState {
    bool wireframe;
    bool showAxes;
};

extern SceneState gScene;

void initScene();
void drawScene();
