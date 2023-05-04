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

	if (GetAsyncKeyState(VK_DELETE) & 1)
	{
		return wglSwapBuffersGateway(hDc);
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

DWORD __stdcall HackThread(LPVOID param)
{

	//Shhhhhhh below is used for testing purposes only ;)
	/*AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);*/

	Hook SwapBuffersHook("wglSwapBuffers", "opengl32.dll", (BYTE*)hkwglSwapBuffers, (BYTE*)&wglSwapBuffersGateway, 5);

	SwapBuffersHook.Enable(); //Enables our hook

	while (1) //Infinite loop
	{
		if (GetAsyncKeyState(VK_DELETE) & 1) //Checks if we want to exit the hack entirely
		{
			break;
		}
	}

	SwapBuffersHook.Disable(); //Disables our hook

	//menu.Shutdown(); //Unloads our menu

	MessageBeep(MB_OK); //Lets user know that hack was closed
	Sleep(100); //Gives menu time to hurry up and close properly

	//fclose(f); Also used for testing ;)
	//FreeConsole(); Testing again ;)

	FreeLibraryAndExitThread((HMODULE)param, 0); //Finally we unload the DLL
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