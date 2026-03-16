// payload_bay.h

// Iteration: 4
// Description: Payload bay interior — longerons, structural frames,
//              and animated cargo bay doors.

#pragma once

// Draw the payload bay interior structure (longerons + frames).
void drawPayloadBayInterior();

// Draw both payload bay doors at the given animation angle.
// doorAngleDeg: 0 = fully closed, DOOR_OPEN_DEG = fully open.
void drawPayloadBayDoors(float doorAngleDeg);
