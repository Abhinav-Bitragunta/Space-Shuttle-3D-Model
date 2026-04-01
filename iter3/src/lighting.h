// lighting.h

// Iteration: 3
// Description: OpenGL lighting setup — sun directional light (GL_LIGHT0)
//              and Earth-reflected fill light (GL_LIGHT1).

#pragma once

// Call once at startup to configure light parameters.
void setupLighting();

// Call each frame to position lights (after camera/modelview is set).
void applyLighting();
