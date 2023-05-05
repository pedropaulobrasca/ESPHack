#pragma once
#ifndef DRAWING_H
#define DRAWING_H

#pragma comment(lib, "OpenGL32.lib")

namespace rgb
{
	const GLubyte red[3] = { 255,0,0 };
	const GLubyte green[3] = { 0,255,0 };
	const GLubyte gray[3] = { 55,55,55 };
	const GLubyte lightgray[3] = { 192,192,192 };
	const GLubyte black[3] = { 0,0,0 };
}

namespace Draw
{
	Vector2 GetRes();
	void SetupOrtho();
	void RestoreGL();

	void DrawLine(float startx, float starty, float endx, float endy, float lineWidth, const GLubyte color[3], float alpha);

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