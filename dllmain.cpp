// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Hack.h"


using namespace Hack;

DWORD WINAPI MainThread(HMODULE hModule)
{
	//Hack::Functions* f = new Hack::Functions();
	AllocConsole();
	SetConsoleTitleA("anti#4444");
	system("mode 73,20");
	FILE* x;
	freopen_s(&x, "CONOUT$", "w", stdout);

	//
	Init();
	//

	fclose(x);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CloseHandle((CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr)));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}



