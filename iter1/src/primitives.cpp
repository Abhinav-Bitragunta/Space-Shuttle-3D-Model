// primitives.cpp

// Iteration: 1
// Description: Implementations of reusable geometry builder functions.

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include "primitives.h"
#include <cmath>
#include <cstring>

// ---------------------------------------------------------------------------
// DrawBox: axis-aligned box centred at local origin, with outward normals.
// ---------------------------------------------------------------------------
void DrawBox(float w, float h, float d) {
    float hw = w * 0.5f;
    float hh = h * 0.5f;
    float hd = d * 0.5f;

    glBegin(GL_QUADS);

    // Front face (+Z)
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-hw, -hh,  hd);
    glVertex3f( hw, -hh,  hd);
    glVertex3f( hw,  hh,  hd);
    glVertex3f(-hw,  hh,  hd);

    // Back face (-Z)
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f( hw, -hh, -hd);
    glVertex3f(-hw, -hh, -hd);
    glVertex3f(-hw,  hh, -hd);
    glVertex3f( hw,  hh, -hd);

    // Top face (+Y)
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-hw,  hh,  hd);
    glVertex3f( hw,  hh,  hd);
    glVertex3f( hw,  hh, -hd);
    glVertex3f(-hw,  hh, -hd);

    // Bottom face (-Y)
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-hw, -hh, -hd);
    glVertex3f( hw, -hh, -hd);
    glVertex3f( hw, -hh,  hd);
    glVertex3f(-hw, -hh,  hd);

    // Right face (+X)
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f( hw, -hh, -hd);
    glVertex3f( hw,  hh, -hd);
    glVertex3f( hw,  hh,  hd);
    glVertex3f( hw, -hh,  hd);

    // Left face (-X)
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-hw, -hh,  hd);
    glVertex3f(-hw,  hh,  hd);
    glVertex3f(-hw,  hh, -hd);
    glVertex3f(-hw, -hh, -hd);

    glEnd();
}

// ---------------------------------------------------------------------------
// DrawCylinder: along +Z axis using GLU quadric. Caps drawn if closed.
// ---------------------------------------------------------------------------
void DrawCylinder(float rBase, float rTop, float length, int slices, bool closed) {
    GLUquadric* q = gluNewQuadric();
    gluQuadricNormals(q, GLU_SMOOTH);

    // Cylinder body
    gluCylinder(q, rBase, rTop, length, slices, 1);

    if (closed) {
        // Base cap (at Z=0, normal facing -Z)
        if (rBase > 0.0f) {
            glPushMatrix();
            glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
            gluDisk(q, 0.0, rBase, slices, 1);
            glPopMatrix();
        }
        // Top cap (at Z=length, normal facing +Z)
        if (rTop > 0.0f) {
            glPushMatrix();
            glTranslatef(0.0f, 0.0f, length);
            gluDisk(q, 0.0, rTop, slices, 1);
            glPopMatrix();
        }
    }

    gluDeleteQuadric(q);
}

// ---------------------------------------------------------------------------
// DrawDisk: flat ring (annulus) in XY plane at Z=0.
// ---------------------------------------------------------------------------
void DrawDisk(float rInner, float rOuter, int slices) {
    GLUquadric* q = gluNewQuadric();
    gluQuadricNormals(q, GLU_SMOOTH);
    gluDisk(q, rInner, rOuter, slices, 1);
    gluDeleteQuadric(q);
}

// ---------------------------------------------------------------------------
// DrawQuad: arbitrary quad with auto-computed face normal.
// ---------------------------------------------------------------------------
void DrawQuad(float p0[3], float p1[3], float p2[3], float p3[3]) {
    // Compute two edge vectors
    float e1[3] = { p1[0]-p0[0], p1[1]-p0[1], p1[2]-p0[2] };
    float e2[3] = { p3[0]-p0[0], p3[1]-p0[1], p3[2]-p0[2] };

    // Cross product for normal
    float nx = e1[1]*e2[2] - e1[2]*e2[1];
    float ny = e1[2]*e2[0] - e1[0]*e2[2];
    float nz = e1[0]*e2[1] - e1[1]*e2[0];

    // Normalize
    float len = sqrtf(nx*nx + ny*ny + nz*nz);
    if (len > 1e-6f) { nx /= len; ny /= len; nz /= len; }

    glBegin(GL_QUADS);
    glNormal3f(nx, ny, nz);
    glVertex3f(p0[0], p0[1], p0[2]);
    glVertex3f(p1[0], p1[1], p1[2]);
    glVertex3f(p2[0], p2[1], p2[2]);
    glVertex3f(p3[0], p3[1], p3[2]);
    glEnd();
}

// ---------------------------------------------------------------------------
// DrawDome: hemispherical cap along +Z axis.
// ---------------------------------------------------------------------------
void DrawDome(float radius, int slices, int stacks) {
    GLUquadric* q = gluNewQuadric();
    gluQuadricNormals(q, GLU_SMOOTH);
    gluSphere(q, radius, slices, stacks);
    gluDeleteQuadric(q);
    // Note: draws full sphere; callers should clip or only use half.
    // TODO: Iter 2 — implement proper hemisphere clipping if needed.
}

// ---------------------------------------------------------------------------
// DrawText2D: bitmap string at screen position. Call inside HUD pass.
// ---------------------------------------------------------------------------
void DrawText2D(float x, float y, const char* text, void* font) {
    if (!font) font = GLUT_BITMAP_HELVETICA_12;
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(font, *c);
    }
}
