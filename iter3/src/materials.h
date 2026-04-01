// materials.h

// Iteration: 3
// Description: Material presets for each shuttle component. Each function
//              sets glMaterialfv for ambient, diffuse, specular, shininess.
//              When lighting is off, also sets glColor for fallback.

#pragma once

void matOrbiterWhite();     // White thermal tiles (upper fuselage)
void matOrbiterBlack();     // Black thermal tiles (lower fuselage / nose)
void matET();               // Matte orange external tank
void matETDome();           // ET dome cap
void matSRB();              // Light-grey metallic SRB body
void matSRBSkirt();         // Darker SRB aft skirt
void matNozzle();           // Dark steel SSME nozzle (high specular)
void matNozzleInner();      // Black throat interior
void matWing();             // Dark delta wing surface
void matVStab();            // Light vertical stabilizer
void matCabin();            // Dark crew cabin hump
void matWindshield();       // Blue-tinted windshield
void matOMS();              // Light OMS pod
void matStrut();            // Neutral grey strut
void matPayloadLine();      // Bay door outline
