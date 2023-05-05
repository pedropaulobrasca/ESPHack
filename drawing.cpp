#define _USE_MATH_DEFINES
#include "pch.h"

class Draw::Font f;

Vector2 Draw::GetRes()
{
	Vector2 screenResolution;

	float viewport[4] = { 0 };
	glGetFloatv(GL_VIEWPORT, viewport);

	screenResolution.x = viewport[2];
	screenResolution.y = viewport[3];

	return screenResolution;
}

//Sets up viewport for drawing
void Draw::SetupOrtho()
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
void Draw::RestoreGL()
{
	glPopMatrix();
	glPopAttrib();
}

void Draw::DrawLine(float startx, float starty, float endx, float endy, float lineWidth, const GLubyte color[3], float alpha = 1.0f)
{
	glColor4f(color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f, alpha);
	glBegin(GL_LINES);
	glVertex2f(startx, starty);
	glVertex2f(endx, endy);
	glEnd();
}
