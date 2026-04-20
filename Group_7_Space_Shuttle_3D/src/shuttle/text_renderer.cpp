// text_renderer.cpp
#define STB_TRUETYPE_IMPLEMENTATION
#include "../stb_truetype.h"
#include "text_renderer.h"

#ifndef GL_CLAMP_TO_BORDER
#define GL_CLAMP_TO_BORDER 0x812D
#endif

#include <iostream>
#include <vector>
#include <cstdio>

GLuint loadStringTexture(const char* text, const char* fontPath) {
    FILE* file = fopen(fontPath, "rb");
    if (!file) {
        std::cerr << "Failed to open font: " << fontPath << std::endl;
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    std::vector<unsigned char> fontBuffer(size);
    fread(fontBuffer.data(), 1, size, file);
    fclose(file);

    stbtt_fontinfo font;
    if (!stbtt_InitFont(&font, fontBuffer.data(), stbtt_GetFontOffsetForIndex(fontBuffer.data(), 0))) {
        return 0;
    }

    int pixelHeight = 128; // High resolution
    float scale = stbtt_ScaleForPixelHeight(&font, pixelHeight);
    int ascent, descent, lineGap;
    stbtt_GetFontVMetrics(&font, &ascent, &descent, &lineGap);

    // Total string width
    int totalWidth = 0;
    int i = 0;
    while (text[i]) {
        int advance, lsb;
        stbtt_GetCodepointHMetrics(&font, text[i], &advance, &lsb);
        totalWidth += advance * scale;
        if (text[i + 1]) totalWidth += stbtt_GetCodepointKernAdvance(&font, text[i], text[i + 1]) * scale;
        i++;
    }

    // Allocating bitmap
    int texHeight = pixelHeight;
    int texWidth = totalWidth + 20; // 20px padding
    std::vector<unsigned char> bitmap(texWidth * texHeight, 0);

    float xpos = 10.0f; // Padding offset
    int baseline = (int)(ascent * scale);

    // Rendering characters to bitmap
    i = 0;
    while (text[i]) {
        int advance, lsb, x0, y0, x1, y1;
        stbtt_GetCodepointHMetrics(&font, text[i], &advance, &lsb);
        stbtt_GetCodepointBitmapBox(&font, text[i], scale, scale, &x0, &y0, &x1, &y1);

        int charWidth = x1 - x0;
        int charHeight = y1 - y0;
        int byteOffset = (int)xpos + x0 + (baseline + y0) * texWidth;

        stbtt_MakeCodepointBitmap(&font, &bitmap[byteOffset], charWidth, charHeight, texWidth, scale, scale, text[i]);

        xpos += (advance * scale);
        if (text[i + 1]) xpos += scale * stbtt_GetCodepointKernAdvance(&font, text[i], text[i + 1]);
        i++;
    }

    // Converting 8-bit monochrome to 32-bit RGBA 
    std::vector<unsigned char> rgba(texWidth * texHeight * 4);
    for (int j = 0; j < texWidth * texHeight; ++j) {
        rgba[j * 4 + 0] = 38;  
        rgba[j * 4 + 1] = 38;  
        rgba[j * 4 + 2] = 38;  
        rgba[j * 4 + 3] = bitmap[j]; 
    }

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba.data());

    return tex;
}