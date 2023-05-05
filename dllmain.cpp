#include "pch.h"

Init init;

typedef BOOL(__stdcall* twglSwapBuffers) (HDC hDc);

twglSwapBuffers wglSwapBuffersGateway;

BOOL __stdcall hkwglSwapBuffers(HDC hDc)
{
	if (GetAsyncKeyState(VK_F1) & 1)
	{
		Config::bHealth = !Config::bHealth;
		std::cout << "Health ativado!" << std::endl;
	}

	if (GetAsyncKeyState(VK_F2) & 1)
	{
		Config::bAmmo = !Config::bAmmo;
		std::cout << "Ammo ativado!" << std::endl;
	}

	if (GetAsyncKeyState(VK_F3) & 1)
	{
		Config::bRecoilSpread = !Config::bRecoilSpread;
		std::cout << "noRecoil ativado!" << std::endl;
	}

	if (GetAsyncKeyState(VK_F4) & 1)
	{
		Config::bESP = !Config::bESP;
		std::cout << "ESP ativado!" << std::endl;
	}

	init.DoHacks();

	return wglSwapBuffersGateway(hDc);
}

DWORD __stdcall HackThread(LPVOID param)
{

	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	Hook SwapBuffersHook("wglSwapBuffers", "opengl32.dll", (BYTE*)hkwglSwapBuffers, (BYTE*)&wglSwapBuffersGateway, 5);

	SwapBuffersHook.Enable();

	while (1)
	{
		if (GetAsyncKeyState(VK_DELETE) & 1)
		{
			break;
		}
	}

	SwapBuffersHook.Disable();

	MessageBeep(MB_OK);
	Sleep(100);

	fclose(f);
	FreeConsole();

	FreeLibraryAndExitThread((HMODULE)param, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, HackThread, hModule, NULL, NULL);
		DisableThreadLibraryCalls(hModule);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}