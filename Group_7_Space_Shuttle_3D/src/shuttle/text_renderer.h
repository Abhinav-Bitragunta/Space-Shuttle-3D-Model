#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

// Generates an OpenGL texture from a TrueType font string
GLuint loadStringTexture(const char* text, const char* fontPath);