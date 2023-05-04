#include "pch.h"

void doHealth()
{
	if (Config::bHealth)
	{
		Offsets::localPlayer->Armor = Config::armor;
		Offsets::localPlayer->Health = Config::health;
	}
}

void doAmmo()
{
	if (Config::bAmmo)
	{
		*(int*)Offsets::localPlayer->CurrentWeaponPtr->Ammo = Config::ammo;
		*(int*)Offsets::localPlayer->CurrentWeaponPtr->Mag = Config::mag;
	}
}

//Prevents recoil and spread(More info can be found at the start here guide)
void doRecoilSpread()
{
	if (Config::bRecoilSpread)
	{
		mem::Nop((BYTE*)0x463786, 10);
	}
	else
	{
		mem::Patch((BYTE*)0x463786, (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10);
	}
}