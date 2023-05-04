#include "pch.h"
#include "offsets.h"

//Sets some global addresses that wil be used
uintptr_t Offsets::base = NULL;
Entity* Offsets::localPlayer = NULL;
EntList* Offsets::entList = NULL;
uintptr_t Offsets::crosshair = 0x607c0;
uintptr_t Offsets::traceLine = 0x48a310;
uintptr_t Offsets::entityListAddr = 0x50f4f8;
tGetCrosshairEnt Offsets::GetCrosshairEnt = nullptr;
int* Offsets::numOfPlayers = (int*)(0x50f500);
glMatrix* Offsets::vMatix = (glMatrix*)0x501ae8;
int* Offsets::gameMode = (int*)0x50f49c;
HMODULE Offsets::showCursorMod = NULL;
uintptr_t Offsets::showCursorAddr = NULL;