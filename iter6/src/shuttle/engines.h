// SSME main engine nozzles and OMS pods

#pragma once

// Draws all three SSME nozzles as a cluster
void drawSSMENozzles();

// Draws one OMS pod. Caller mirrors for left/right
void drawOMSPod();

// Translucent exhaust flame effects (call with blending enabled)
void drawExhaustFlames(float stackShiftZ);

// RCS thruster flash effects (call with blending enabled)
void drawRCSFlashes(float stackShiftZ);
