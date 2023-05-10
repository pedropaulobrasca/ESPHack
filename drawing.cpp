#define _USE_MATH_DEFINES
#include "pch.h"
#include "Imgui/imgui.h"

class DrawUtils::Font f;

Vector2 DrawUtils::GetRes()
{
	Vector2 screenResolution;

	float viewport[4] = { 0 };
	glGetFloatv(GL_VIEWPORT, viewport);

	screenResolution.x = viewport[2];
	screenResolution.y = viewport[3];

	return screenResolution;
}

//Sets up viewport for drawing
void DrawUtils::SetupOrtho()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, viewport[2], viewport[3]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
}

//Basically does what the name states
void DrawUtils::RestoreGL()
{
	glPopMatrix();
	glPopAttrib();
}

void DrawUtils::DrawLine(float startx, float starty, float endx, float endy, float lineWidth, ImVec4 color)
{
	glColor4f(color.x, color.y, color.z, color.w);
	glBegin(GL_LINES);
	glVertex2f(startx, starty);
	glVertex2f(endx, endy);
	glEnd();
}

void initGLUTBitmapFont() {
	// Função vazia, pois o GLUT não requer inicialização da fonte bitmap
}

void DrawUtils::Font::PrintText(const std::string& text, float x, float y, void* font, ImVec4 color) {
	glColor4f(color.x, color.y, color.z, color.w);
	glRasterPos2f(x, y);

	for (const auto& c : text) {
		glutBitmapCharacter(font, c);
	}
}

void DrawUtils::DrawRectangle(float x, float y, float width, float height, ImVec4 color, float lineWidth) {
	glLineWidth(lineWidth);
	glColor4f(color.x, color.y, color.z, color.w);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(width, y);
	glVertex2f(width, height);
	glVertex2f(x, height);
	glEnd();
}

void DrawUtils::DrawFilledRect(float x, float y, float x2, float y2, ImVec4 color)
{
	glColor4f(color.x, color.y, color.z, color.w);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x2, y);
	glVertex2f(x2, y2);
	glVertex2f(x, y2);
	glEnd();
}
