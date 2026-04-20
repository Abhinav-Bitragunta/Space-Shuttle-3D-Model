// Reusable geometry builder wrappers.
#pragma once

// Axis-aligned solid box centred at local origin. Computes normals.
void DrawBox(float w, float h, float d);

// Cylinder along +Z axis, both caps drawn if closed=true.
void DrawCylinder(float rBase, float rTop, float length, int slices, bool closed = true);
void DrawTexturedCylinder(float rBase, float rTop, float length, int slices);

// cone (rTop = 0)
inline void DrawCone(float rBase, float length, int slices) {
    DrawCylinder(rBase, 0.0f, length, slices, true);
}

// Annulus in XY plane.
void DrawDisk(float rInner, float rOuter, int slices);

// Arbitrary quad with auto-computed face normal.
void DrawQuad(float p0[3], float p1[3], float p2[3], float p3[3]);

// Hemispherical cap along +Z axis.
void DrawDome(float radius, int slices, int stacks);

// Circle
inline void DrawCircle(float r, int slices) { DrawDisk(0.0f, r, slices); }

// Render a bitmap string at 2D screen position (call inside HUD pass).
void DrawText2D(float x, float y, const char* text, void* font = nullptr);
