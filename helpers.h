#pragma once
#include "pch.h"

#ifndef HELPERS_H
#define HELPERS_H

bool WorldToScreen(Vector3 pos, Vector2& screen, glMatrix* matrix, int windowWidth, int windowHeight);

#endif