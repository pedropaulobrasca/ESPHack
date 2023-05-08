#pragma once
#ifndef DRAWING_H
#define DRAWING_H

#pragma comment(lib, "OpenGL32.lib")
#include "Imgui/imgui.h"

namespace DrawUtils
{
    Vector2 GetRes();
    void SetupOrtho();
    void RestoreGL();

    void DrawLine(float startx, float starty, float endx, float endy, float lineWidth, ImVec4 color);

    class Font
    {
    public:
        bool bBuilt = false;
        unsigned int base;
        HDC hdc = nullptr;
        int height;
        int width;

        void Build(int height);
        //void Print(float x, float y, ImVec4 color, const char* format, ...);
        static void PrintText(const std::string& text, float x, float y, void* font, ImVec4 color);

        Vector3 centerText(float x, float y, float width, float height, float textWidth, float textHeight);
        float centerText(float x, float width, float textWidth);
    };
}

#endif