#define _USE_MATH_DEFINES
#include "pch.h"

bool WorldToScreen(Vector3 pos, Vector2& screen, glMatrix* matrix, int windowWidth, int windowHeight)
{
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	Vector4 clipCoords;
	clipCoords.x = pos.x * matrix->matrix[0] + pos.y * matrix->matrix[4] + pos.z * matrix->matrix[8] + matrix->matrix[12];
	clipCoords.y = pos.x * matrix->matrix[1] + pos.y * matrix->matrix[5] + pos.z * matrix->matrix[9] + matrix->matrix[13];
	clipCoords.z = pos.x * matrix->matrix[2] + pos.y * matrix->matrix[6] + pos.z * matrix->matrix[10] + matrix->matrix[14];
	clipCoords.w = pos.x * matrix->matrix[3] + pos.y * matrix->matrix[7] + pos.z * matrix->matrix[11] + matrix->matrix[15];

	if (clipCoords.w < 0.1f)
		return false;

	//Perspective division, dividing by clip.W = Normalized Device Coordinates
	Vector3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	//Transform to window coordinates
	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}