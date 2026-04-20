// External Tank: orange cylinder with hemispherical dome and procedural foam texture.

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include "external_tank.h"
#include "../config.h"
#include "../primitives.h"
#include "../materials.h"
#include <cstdlib>

static GLuint sFoamTex = 0;

static unsigned int foamHash(unsigned int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

static void drawTexturedDisk(float radius, int slices) {
    GLUquadric* q = gluNewQuadric();
    gluQuadricNormals(q, GLU_SMOOTH);
    gluQuadricTexture(q, GL_TRUE);
    gluDisk(q, 0.0, radius, slices, 1);
    gluDeleteQuadric(q);
}

// Hemisphere along +Z with texture coordinates
static void drawTexturedDome(float radius, int slices, int stacks) {
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

        float t0 = static_cast<float>(i)     / stacks;
        float t1 = static_cast<float>(i + 1) / stacks;

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= slices; ++j) {
            float lon = 2.0f * PI * static_cast<float>(j) / slices;
            float cosLon = cosf(lon);
            float sinLon = sinf(lon);
            float s = static_cast<float>(j) / slices;

            // Upper ring first, then lower - flips winding to CCW from outside
            float nx1 = cosLat1 * cosLon;
            float ny1 = cosLat1 * sinLon;
            float nz1 = sinLat1;
            glTexCoord2f(s, t1);
            glNormal3f(nx1, ny1, nz1);
            glVertex3f(r1 * cosLon, r1 * sinLon, z1);

            float nx0 = cosLat0 * cosLon;
            float ny0 = cosLat0 * sinLon;
            float nz0 = sinLat0;
            glTexCoord2f(s, t0);
            glNormal3f(nx0, ny0, nz0);
            glVertex3f(r0 * cosLon, r0 * sinLon, z0);
        }
        glEnd();
    }
}

void initET() {
    if (sFoamTex != 0) return;

    const int S = Cfg::ET_TEX_SIZE;
    unsigned char* data = new unsigned char[S * S * 3];

    for (int y = 0; y < S; ++y) {
        for (int x = 0; x < S; ++x) {
            unsigned int h = foamHash(y * S + x + 7919);
            float noise = (h % 1000) / 1000.0f;

            float variation = 0.85f + 0.30f * noise;
            if ((h % 17) == 0) variation *= 0.7f;

            int r = static_cast<int>(Cfg::COL_ET[0] * variation * 255.0f);
            int g = static_cast<int>(Cfg::COL_ET[1] * variation * 255.0f);
            int b = static_cast<int>(Cfg::COL_ET[2] * variation * 255.0f);
            if (r > 255) r = 255;
            if (g > 255) g = 255;
            if (b > 255) b = 255;

            int idx = (y * S + x) * 3;
            data[idx + 0] = static_cast<unsigned char>(r);
            data[idx + 1] = static_cast<unsigned char>(g);
            data[idx + 2] = static_cast<unsigned char>(b);
        }
    }

    glGenTextures(1, &sFoamTex);
    glBindTexture(GL_TEXTURE_2D, sFoamTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, S, S, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    delete[] data;
}

void drawET() {
    matET();

    if (sFoamTex != 0) {
        glPushAttrib(GL_TEXTURE_BIT | GL_ENABLE_BIT | GL_POLYGON_BIT);
        glDisable(GL_CULL_FACE);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, sFoamTex);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        // Set texture matrix for tiling (~4x around, ~2x along length)
        glMatrixMode(GL_TEXTURE);
        glPushMatrix();
        glLoadIdentity();
        glScalef(4.0f, 2.0f, 1.0f);
        glMatrixMode(GL_MODELVIEW);

        // Cylinder body
        DrawTexturedCylinder(Cfg::ET_RADIUS, Cfg::ET_RADIUS,
                             Cfg::ET_LENGTH, Cfg::ET_SLICES);

        // Aft cap
        glPushMatrix();
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
        drawTexturedDisk(Cfg::ET_RADIUS, Cfg::ET_SLICES);
        glPopMatrix();

        // Forward dome
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, Cfg::ET_LENGTH);
        matETDome();
        drawTexturedDome(Cfg::ET_RADIUS, Cfg::ET_SLICES, Cfg::ET_DOME_STACKS);
        glPopMatrix();

        // Restore
        glMatrixMode(GL_TEXTURE);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopAttrib();
    } else {
        // if no texture
        DrawCylinder(Cfg::ET_RADIUS, Cfg::ET_RADIUS,
                     Cfg::ET_LENGTH, Cfg::ET_SLICES, true);

        glPushMatrix();
        glTranslatef(0.0f, 0.0f, Cfg::ET_LENGTH);
        matETDome();
        DrawDome(Cfg::ET_RADIUS, Cfg::ET_SLICES, Cfg::ET_DOME_STACKS);
        glPopMatrix();
    }
}
