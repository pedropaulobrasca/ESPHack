#pragma once
#ifndef DRAWING_H
#define DRAWING_H

#pragma comment(lib, "OpenGL32.lib")

namespace Draw
{
	Vector2 GetRes();
	void SetupOrtho();
	void RestoreGL();

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

		Vector3 centerText(float x, float y, float width, float height, float textWidth, float textHeight);
		float centerText(float x, float width, float textWidth);
	};
}

#endif