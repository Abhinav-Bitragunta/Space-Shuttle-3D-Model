// starfield.h

// Iteration: 5
// Description: 2000 random stars on a large sphere, compiled into a
//              display list. Drawn with depth writes disabled so stars
//              always appear behind all geometry.

#pragma once

void initStarfield();   // call once at startup, builds display list
void drawStarfield();   // call each frame before the main scene