#include "pch.h"

uintptr_t moduleBase = (uintptr_t)GetModuleHandle("ac_client.exe");

bool bHealth = false, bAmmo = false, bRecoil = false;

typedef BOOL(__stdcall* twglSwapBuffers) (HDC hDc);

twglSwapBuffers owglSwapBuffers;
twglSwapBuffers wglSwapBuffersGateway;

BOOL __stdcall hkwglSwapBuffers(HDC hDc)
{
	if (GetAsyncKeyState(VK_F1) & 1)
		bHealth = !bHealth;

	if (GetAsyncKeyState(VK_F2) & 1)
	{
		bAmmo = !bAmmo;
	}

	if (GetAsyncKeyState(VK_F3) & 1)
	{
		bRecoil = !bRecoil;

		if (bRecoil)
		{
			mem::Nop((BYTE*)(moduleBase + 0x63786), 10);
		}

		else
		{
			mem::Patch((BYTE*)(moduleBase + 0x63786), (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10);
		}
	}

	uintptr_t* localPlayerPtr = (uintptr_t*)(moduleBase + 0x10F4F4);

	if (*localPlayerPtr)
	{
		if (bHealth)
		{
			*(int*)(*localPlayerPtr + 0xF8) = 1337;
		}

		if (bAmmo)
		{
			*(int*)mem::FindDMAAddy(moduleBase + 0x10F4F4, { 0x374, 0x14, 0x0 }) = 1337;
		}
	}

	return wglSwapBuffersGateway(hDc);
}

DWORD WINAPI HackThread(HMODULE hModule)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	std::cout << "OG for a fee, stay sippin' fam\n";

	Hook SwapBuffersHook("wglSwapBuffers", "opengl32.dll", (BYTE*)hkwglSwapBuffers, (BYTE*)&wglSwapBuffersGateway, 5);
	SwapBuffersHook.Enable();

	Sleep(15000);
	SwapBuffersHook.Disable();

	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}