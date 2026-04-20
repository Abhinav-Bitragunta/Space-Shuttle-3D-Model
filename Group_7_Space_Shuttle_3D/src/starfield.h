// Dynamic Starfield, Galaxies, Meteors, and Asteroids
#pragma once

void initStarfield();              // Call once at startup
void updateBackground(float dt);   // Call every frame with delta time
void drawStarfield();              // Draw unlit background elements (stars, galaxies, meteors)
void drawBackgroundAsteroids();    // Draw lit background elements (asteroids)
void drawBackgroundPlanets();      // Draws lit planets