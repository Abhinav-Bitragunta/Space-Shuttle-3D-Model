// lighting.h

// Iteration: 3 (Iter 4: GL_LIGHT2 cabin light)
// Description: OpenGL lighting setup.

#pragma once

void setupLighting();       // call once at startup
void applyLighting();       // call each frame (exterior lights)
void applyCabinLighting();  // Iter 4: enable warm cabin light
void disableCabinLighting();// Iter 4: disable cabin light
