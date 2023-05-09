#include "pch.h"

DrawUtils::Font font;

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

		DrawUtils::SetupOrtho();

        Vector2 screenRes = DrawUtils::GetRes();

        for (int i = 0; i < *Offsets::numOfPlayers; i++)
        {
            Entity* entity = Offsets::entList->ents[i];
            if (entity != 0 && entity->Health > 0)
            {
                try
                {
					Vector3 headPos = entity->HeadPos;
					Vector3 feetPos = entity->Pos;
					char* name = entity->Name;

					Vector2 headScreenPos, feetScreenPos;

					// Snapline
					if (WorldToScreen(headPos, headScreenPos, Offsets::vMatix, (int)screenRes.x, (int)screenRes.y) && WorldToScreen(feetPos, feetScreenPos, Offsets::vMatix, (int)screenRes.x, (int)screenRes.y))
					{
						float height = feetScreenPos.y - headScreenPos.y; //Get entity height
						float width = height / 2.0f; //Get entity width

						Vector2 tl; //Top left of box
						tl.x = headScreenPos.x - width / 2.0f;
						tl.y = headScreenPos.y;
						Vector2 br; //Bottom right of box
						br.x = headScreenPos.x + width / 2.0f;
						br.y = headScreenPos.y + height;

						// Snapline
						DrawUtils::DrawLine(screenRes.x / 2, screenRes.y, feetScreenPos.x, feetScreenPos.y, 1.0f, rgb::enemyBoxVisible);

						// Name
						DrawUtils::Font::PrintText(entity->Name, tl.x, headScreenPos.y - 10.0f, GLUT_BITMAP_HELVETICA_12, rgb::enemyBoxVisible);

						// Rectangle
						DrawUtils::DrawRectangle(tl.x, tl.y, br.x, br.y, rgb::enemyBoxVisible, 1.0f);
					}

                }
                catch (const std::exception&)
                {
                    std::cout << "Erro no ESP!" << std::endl;
                }
            }
        }

		DrawUtils::RestoreGL();
    }
}
