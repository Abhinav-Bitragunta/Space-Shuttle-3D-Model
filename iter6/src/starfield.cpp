#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "starfield.h"
#include "config.h"
#include <cmath>
#include <cstdlib>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static float rnd(float min, float max) {
    return min + (max - min) * (static_cast<float>(rand()) / RAND_MAX);
}

// --- Data Structures ---
enum GalaxyType { SPIRAL, ELLIPTICAL, NEBULA };

struct Meteor {
    float x, y, z, vx, vy, vz;
    float length, alpha, life, maxLife, delay;
    bool active;
};

struct Asteroid {
    float x, y, z;
    float rotAngle, rotSpeed;
    float rotAxis[3];
    float scaleX, scaleY, scaleZ;
    float orbitAngle, orbitSpeed, dist;
};

struct Planet {
    float x, y, z;
    float radius;
    float r, g, b;
    bool hasRings;
    float ringColor[3];
    float rotAngle, rotSpeed, tilt;
};

static GLuint sStarList = 0;
static GLuint sGalaxyList = 0;
static GLuint sAsteroidBaseList = 0;

static std::vector<Meteor> gMeteors;
static std::vector<Asteroid> gAsteroids;
static std::vector<Planet> gPlanets;

// --- Galaxy Generators ---
static void buildGalaxy(GalaxyType type, float cx, float cy, float cz, float radius, int stars, float rTint, float gTint, float bTint) {
    // Random 3D orientation
    float rotX = rnd(0, 360);
    float rotY = rnd(0, 360);
    float rotZ = rnd(0, 360);

    glPushMatrix();
    glTranslatef(cx, cy, cz);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);

    glBegin(GL_POINTS);
    
    int arms = (rand() % 3) + 2; 
    float winding = rnd(2.0f, 6.0f);

    for (int i = 0; i < stars; i++) {
        float px = 0, py = 0, pz = 0;
        
        // Inverse square probability: clumps heavily in the center
        float distFactor = pow(rnd(0.0f, 1.0f), 3.0f); 
        float dist = distFactor * radius; 
        
        if (type == SPIRAL) {
            float armOffset = (rand() % arms) * ((2.0f * M_PI) / arms);
            float theta = dist * winding + armOffset;
            float scatter = rnd(0.0f, radius * 0.3f) * distFactor;
            
            px = dist * cos(theta) + rnd(-scatter, scatter);
            py = rnd(-radius * 0.05f, radius * 0.05f); // Very flat disk
            pz = dist * sin(theta) + rnd(-scatter, scatter);
            
        } else if (type == ELLIPTICAL) {
            // Smooth, egg-like cluster
            float u = rnd(0, 1), v = rnd(0, 1);
            float theta = 2.0f * M_PI * u;
            float phi = acos(2.0f * v - 1.0f);
            
            px = dist * sin(phi) * cos(theta);
            py = dist * sin(phi) * sin(theta) * rnd(0.4f, 0.8f); // Squashed Y axis
            pz = dist * cos(phi);
            
        } else if (type == NEBULA) {
            // Clumpy, irregular gas cloud
            float u = rnd(0, 1), v = rnd(0, 1);
            float theta = 2.0f * M_PI * u;
            float phi = acos(2.0f * v - 1.0f);
            
            // Random offset for clumping
            float clumpX = rnd(-radius*0.5f, radius*0.5f);
            float clumpY = rnd(-radius*0.5f, radius*0.5f);
            float clumpZ = rnd(-radius*0.5f, radius*0.5f);
            
            px = (dist * sin(phi) * cos(theta)) + clumpX;
            py = (dist * sin(phi) * sin(theta)) + clumpY;
            pz = (dist * cos(phi)) + clumpZ;
        }

        // Color Math: Core is bright/white, edges take the tint
        float coreRatio = 1.0f - distFactor;
        float r = coreRatio * 1.0f + (1.0f - coreRatio) * rTint;
        float g = coreRatio * 0.9f + (1.0f - coreRatio) * gTint;
        float b = coreRatio * 0.8f + (1.0f - coreRatio) * bTint;
        
        // Alpha blending based on density (brighter in center)
        float alpha = rnd(0.1f, 0.8f) * coreRatio;

        glColor4f(r, g, b, alpha);
        glVertex3f(px, py, pz);
    }
    glEnd();
    glPopMatrix();
}

static void spawnMeteor(Meteor& m) {
    m.active = true;
    m.maxLife = rnd(0.5f, 1.5f);
    m.life = m.maxLife;
    m.alpha = 1.0f;
    m.length = Cfg::METEOR_LENGTH * rnd(0.8f, 1.5f);
    
    float u = rnd(0, 1), v = rnd(0, 1);
    float theta = 2.0f * M_PI * u;
    float phi = acos(2.0f * v - 1.0f);
    
    float r = Cfg::STAR_SPHERE_R * 0.9f;
    m.x = r * sin(phi) * cos(theta);
    m.y = r * sin(phi) * sin(theta);
    m.z = r * cos(phi);
    
    m.vx = -m.x * rnd(0.1f, 0.5f) + rnd(-10, 10);
    m.vy = -m.y * rnd(0.1f, 0.5f) + rnd(-10, 10);
    m.vz = -m.z * rnd(0.1f, 0.5f) + rnd(-10, 10);
    
    float len = sqrt(m.vx*m.vx + m.vy*m.vy + m.vz*m.vz);
    float speed = rnd(Cfg::METEOR_SPEED_MIN, Cfg::METEOR_SPEED_MAX);
    m.vx = (m.vx / len) * speed; m.vy = (m.vy / len) * speed; m.vz = (m.vz / len) * speed;
}

void initStarfield() {
    srand(1337); 

    // 1. Compile Standard Stars
    sStarList = glGenLists(1);
    glNewList(sStarList, GL_COMPILE);
    glBegin(GL_POINTS);
    for (int i = 0; i < Cfg::STAR_COUNT; ++i) {
        float u = rnd(0, 1), v = rnd(0, 1);
        float theta = 2.0f * M_PI * u;
        float phi = acos(2.0f * v - 1.0f);

        float x = Cfg::STAR_SPHERE_R * sin(phi) * cos(theta);
        float y = Cfg::STAR_SPHERE_R * sin(phi) * sin(theta);
        float z = Cfg::STAR_SPHERE_R * cos(phi);

        float b = rnd(0.3f, 1.0f);
        float r = b, g = b, bl = b;
        int tint = rand() % 10;
        if (tint == 0) { r *= 1.0f; g *= 0.8f; bl *= 0.6f; }
        if (tint == 1) { r *= 0.6f; g *= 0.8f; bl *= 1.0f; }

        glColor3f(r, g, bl);
        glVertex3f(x, y, z);
    }
    glEnd();
    glEndList();

    // 2. Compile Galaxies (Now using Alpha Blending)
    sGalaxyList = glGenLists(1);
    glNewList(sGalaxyList, GL_COMPILE);
    for(int i = 0; i < Cfg::GALAXY_COUNT; ++i) {
        float u = rnd(0, 1), v = rnd(0, 1);
        float theta = 2.0f * M_PI * u;
        float phi = acos(2.0f * v - 1.0f);
        
        float r = Cfg::STAR_SPHERE_R * rnd(0.7f, 0.95f);
        float cx = r * sin(phi) * cos(theta);
        float cy = r * sin(phi) * sin(theta);
        float cz = r * cos(phi);
        
        int stars = (int)rnd(Cfg::GALAXY_STARS_MIN, Cfg::GALAXY_STARS_MAX);
        float rad = rnd(Cfg::GALAXY_MAX_RADIUS * 0.4f, Cfg::GALAXY_MAX_RADIUS);
        
        float rTint = rnd(0.1f, 0.9f);
        float gTint = rnd(0.1f, 0.5f);
        float bTint = rnd(0.4f, 1.0f);
        
        GalaxyType type = static_cast<GalaxyType>(rand() % 3);
        buildGalaxy(type, cx, cy, cz, rad, stars, rTint, gTint, bTint);
    }
    glEndList();

    // 3. Setup Meteors & Asteroids (Same logic as before)
    gMeteors.resize(Cfg::METEOR_COUNT);
    for (auto& m : gMeteors) { m.active = false; m.delay = rnd(0.0f, 5.0f); }

    sAsteroidBaseList = glGenLists(1);
    glNewList(sAsteroidBaseList, GL_COMPILE); glutSolidDodecahedron(); glEndList();

    gAsteroids.resize(Cfg::ASTEROID_COUNT);
    for (auto& a : gAsteroids) {
        a.orbitAngle = rnd(0, M_PI * 2.0f);
        a.dist = rnd(Cfg::ASTEROID_DIST_MIN, Cfg::ASTEROID_DIST_MAX);
        a.orbitSpeed = rnd(0.02f, 0.1f) * (rand() % 2 == 0 ? 1 : -1);
        a.y = rnd(-20.0f, 20.0f);
        a.rotAngle = rnd(0, 360);
        a.rotAxis[0] = rnd(-1, 1); a.rotAxis[1] = rnd(-1, 1); a.rotAxis[2] = rnd(-1, 1);
        a.rotSpeed = rnd(5.0f, 30.0f);
        a.scaleX = rnd(Cfg::ASTEROID_SCALE_MIN, Cfg::ASTEROID_SCALE_MAX);
        a.scaleY = rnd(Cfg::ASTEROID_SCALE_MIN, Cfg::ASTEROID_SCALE_MAX);
        a.scaleZ = rnd(Cfg::ASTEROID_SCALE_MIN, Cfg::ASTEROID_SCALE_MAX);
    }

    // 4. Setup Distant Planets
    gPlanets.resize(Cfg::PLANET_COUNT);
    for(int i = 0; i < Cfg::PLANET_COUNT; i++) {
        auto& p = gPlanets[i];
        
        // Distribute them evenly around the sphere horizon
        float angle = (i * (2.0f * M_PI / Cfg::PLANET_COUNT)) + rnd(-0.5f, 0.5f);
        float dist = rnd(Cfg::PLANET_DIST_MIN, Cfg::PLANET_DIST_MAX);
        
        p.x = cos(angle) * dist;
        p.y = rnd(-20.0f, 20.0f); // Slight vertical offset
        p.z = sin(angle) * dist;
        
        p.radius = rnd(Cfg::PLANET_RADIUS_MIN, Cfg::PLANET_RADIUS_MAX);
        
        // Random planet color (Earthy, Martian, or Gas Giant)
        p.r = rnd(0.2f, 0.9f);
        p.g = rnd(0.2f, 0.7f);
        p.b = rnd(0.2f, 0.8f);
        
        p.hasRings = (rand() % 3 == 0); // 33% chance for rings
        if (p.hasRings) {
            p.ringColor[0] = p.r * rnd(0.8f, 1.2f);
            p.ringColor[1] = p.g * rnd(0.8f, 1.2f);
            p.ringColor[2] = p.b * rnd(0.8f, 1.2f);
        }
        
        p.tilt = rnd(10.0f, 45.0f);
        p.rotAngle = rnd(0.0f, 360.0f);
        p.rotSpeed = rnd(5.0f, 20.0f);
    }
}

void updateBackground(float dt) {
    for (auto& m : gMeteors) {
        if (!m.active) {
            m.delay -= dt;
            if (m.delay <= 0.0f) spawnMeteor(m);
            continue;
        }
        m.x += m.vx * dt; m.y += m.vy * dt; m.z += m.vz * dt;
        m.life -= dt;
        m.alpha = m.life / m.maxLife;
        if (m.life <= 0.0f) { m.active = false; m.delay = rnd(1.0f, 6.0f); }
    }
    for (auto& a : gAsteroids) {
        a.orbitAngle += a.orbitSpeed * dt;
        a.x = cos(a.orbitAngle) * a.dist;
        a.z = sin(a.orbitAngle) * a.dist;
        a.rotAngle += a.rotSpeed * dt;
    }
    for (auto& p : gPlanets) {
        p.rotAngle += p.rotSpeed * dt;
    }
}

void drawStarfield() {
    glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT | GL_CURRENT_BIT | GL_POINT_BIT | GL_LINE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);

    // Standard stars
    glPointSize(1.2f);
    if (sStarList != 0) glCallList(sStarList);

    // Galaxies (NOW WITH ADDITIVE BLENDING FOR NEBULA EFFECT)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Additive blend makes overlapping points glow brightly
    glPointSize(1.5f);
    if (sGalaxyList != 0) glCallList(sGalaxyList);

    // Meteors
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (const auto& m : gMeteors) {
        if (!m.active) continue;
        glColor4f(1.0f, 1.0f, 1.0f, m.alpha);
        glVertex3f(m.x, m.y, m.z);
        
        float tx = m.x - (m.vx * m.length * 0.05f);
        float ty = m.y - (m.vy * m.length * 0.05f);
        float tz = m.z - (m.vz * m.length * 0.05f);
        glColor4f(0.5f, 0.8f, 1.0f, 0.0f); 
        glVertex3f(tx, ty, tz);
    }
    glEnd();

    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
    glPopAttrib();
}

void drawBackgroundAsteroids() {
    if (sAsteroidBaseList == 0) return;
    glPushAttrib(GL_CURRENT_BIT | GL_LIGHTING_BIT);
    
    GLfloat mat_ambient[]  = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat mat_diffuse[]  = { 0.4f, 0.38f, 0.35f, 1.0f };
    GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    for (const auto& a : gAsteroids) {
        glPushMatrix();
        glTranslatef(a.x, a.y, a.z);
        glRotatef(a.rotAngle, a.rotAxis[0], a.rotAxis[1], a.rotAxis[2]);
        glScalef(a.scaleX, a.scaleY, a.scaleZ);
        glCallList(sAsteroidBaseList);
        glPopMatrix();
    }
    glPopAttrib();
}

void drawBackgroundPlanets() {
    glPushAttrib(GL_CURRENT_BIT | GL_LIGHTING_BIT);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    // Low specularity so they look matte/dusty like a planet
    GLfloat mat_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

    for(const auto& p : gPlanets) {
        glPushMatrix();
        glTranslatef(p.x, p.y, p.z);
        
        // Tilt the planet on its axis
        glRotatef(p.tilt, 1.0f, 0.0f, 1.0f);
        glRotatef(p.rotAngle, 0.0f, 1.0f, 0.0f);

        // Draw the Planet Sphere
        glColor3f(p.r, p.g, p.b);
        glutSolidSphere(p.radius, 32, 32);

        // Draw Rings if it has them
        if (p.hasRings) {
            glColor3f(p.ringColor[0], p.ringColor[1], p.ringColor[2]);
            // Torus (inner radius, outer radius, sides, rings)
            glutSolidTorus(0.2f, p.radius * 1.8f, 12, 48);
        }
        
        glPopMatrix();
    }
    glPopAttrib();
}