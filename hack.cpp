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

void doESP()
{
    if (1)
    {
		float viewport[4];
		glGetFloatv(GL_VIEWPORT, viewport);

		Draw::SetupOrtho();

        Vector2 screenRes = Draw::GetRes();

        for (int i = 0; i < *Offsets::numOfPlayers; i++)
        {
            Entity* entity = Offsets::entList->ents[i];
            if (entity != 0)
            {
                try
                {
					Vector3 headPos = entity->HeadPos;
					Vector3 feetPos = entity->Pos;
					char* name = entity->Name;

					Vector2 headScreenPos, feetScreenPos;
					if (WorldToScreen(headPos, headScreenPos, Offsets::vMatix, (int)screenRes.x, (int)screenRes.y) && WorldToScreen(headPos, feetScreenPos, Offsets::vMatix, (int)screenRes.x, (int)screenRes.y))
					{
						Draw::DrawLine(screenRes.x / 2, screenRes.y, feetScreenPos.x, feetScreenPos.y, 2.0f, rgb::enemyBoxVisible);
					}
                }
                catch (const std::exception&)
                {
                    std::cout << "Erro no ESP!" << std::endl;
                }
            }
        }

		Draw::RestoreGL();
    }
}
