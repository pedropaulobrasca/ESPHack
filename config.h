#pragma once
#include "Imgui/imgui.h"

#ifndef CONFIG_H
#define CONFIG_H

namespace Config
{
	extern int health;
	extern int armor;
	extern bool bHealth;
	extern int ammo;
	extern int mag;
	extern bool bAmmo;
	extern bool bRecoilSpread;
	extern bool bESP;
}

namespace rgb
{
	extern ImVec4 enemyBox;
	extern ImVec4 enemyBoxVisible;
	extern ImVec4 teamBox;
	extern ImVec4 text;
	extern ImVec4 snapline;
	extern ImVec4 healthBarBackground;
	extern ImVec4 healthBar;
}

#endif