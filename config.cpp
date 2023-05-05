#include "pch.h"

int Config::health = 1337;
int Config::armor = 1337;
bool Config::bHealth = false;
int Config::ammo = 1337;
int Config::mag = 1337;
bool Config::bAmmo = false;
bool Config::bRecoilSpread = false;
bool Config::bESP = false;

ImVec4 rgb::enemyBox = ImColor(255, 0, 0, 1); //Default: Red
ImVec4 rgb::enemyBoxVisible = ImColor(0, 255, 0, 1);
ImVec4 rgb::teamBox = ImColor(0, 0, 255, 1);
ImVec4 rgb::text = ImColor(0, 0, 0, 1);
ImVec4 rgb::snapline = ImColor(0, 0, 0, 1);
ImVec4 rgb::healthBarBackground = ImColor(255, 0, 0, 1);
ImVec4 rgb::healthBar = ImColor(0, 255, 0, 1);