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

// along +Z axis. Caps drawn if closed.
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

void DrawTexturedCylinder(float rBase, float rTop, float length, int slices, bool closed) {
    GLUquadric* q = gluNewQuadric();
    gluQuadricNormals(q, GLU_SMOOTH);
    gluQuadricTexture(q, GL_TRUE); // texture mapping

    gluCylinder(q, rBase, rTop, length, slices, 1);
    gluDeleteQuadric(q); // omit cap
}


// Annulus in XY plane
void DrawDisk(float rInner, float rOuter, int slices) {
    GLUquadric* q = gluNewQuadric();
    gluQuadricNormals(q, GLU_SMOOTH);
    gluDisk(q, rInner, rOuter, slices, 1);
    gluDeleteQuadric(q);
}

void DrawQuad(float p0[3], float p1[3], float p2[3], float p3[3]) {
    // Compute two edge vectors
    float e1[3] = { p1[0]-p0[0], p1[1]-p0[1], p1[2]-p0[2] };
    float e2[3] = { p3[0]-p0[0], p3[1]-p0[1], p3[2]-p0[2] };

    // Cross product for normal
    float nx = e1[1]*e2[2] - e1[2]*e2[1];
    float ny = e1[2]*e2[0] - e1[0]*e2[2];
    float nz = e1[0]*e2[1] - e1[1]*e2[0];

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
// DrawDome: hemispherical cap along +Z axis (latitude 0° at base to 90°
//           at pole). Base sits at Z=0, pole at Z=+radius.
// ---------------------------------------------------------------------------
void DrawDome(float radius, int slices, int stacks) {
    const float PI = 3.14159265358979323846f;

    for (int i = 0; i < stacks; ++i) {
        float lat0 = (PI * 0.5f) * static_cast<float>(i)     / stacks;
        float lat1 = (PI * 0.5f) * static_cast<float>(i + 1) / stacks;

        float cosLat0 = cosf(lat0), sinLat0 = sinf(lat0);
        float cosLat1 = cosf(lat1), sinLat1 = sinf(lat1);

        float r0 = radius * cosLat0;
        float z0 = radius * sinLat0;
        float r1 = radius * cosLat1;
        float z1 = radius * sinLat1;

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= slices; ++j) {
            float lon = 2.0f * PI * static_cast<float>(j) / slices;
            float cosLon = cosf(lon);
            float sinLon = sinf(lon);

            // Lower ring
            float nx0 = cosLat0 * cosLon;
            float ny0 = cosLat0 * sinLon;
            float nz0 = sinLat0;
            glNormal3f(nx0, ny0, nz0);
            glVertex3f(r0 * cosLon, r0 * sinLon, z0);

            // Upper ring
            float nx1 = cosLat1 * cosLon;
            float ny1 = cosLat1 * sinLon;
            float nz1 = sinLat1;
            glNormal3f(nx1, ny1, nz1);
            glVertex3f(r1 * cosLon, r1 * sinLon, z1);
        }
        glEnd();
    }
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
