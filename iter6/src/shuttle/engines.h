// engines.h

// Iteration: 2
// Description: SSME main engine nozzles (three bell-shaped annuli at aft)
//              and OMS pods (two blunt pods at aft sides).

#pragma once

// Draws all three SSME nozzles as a cluster. Drawn at local origin.
void drawSSMENozzles();

// Draws one OMS pod. Caller mirrors for left/right.
void drawOMSPod();
