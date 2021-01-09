// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Hack.h"
#include <thread>
using namespace Hack;

void EspThread()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	while (true)
	{
		if (GetAsyncKeyState(VK_END) & 1)
			break;
		if(pData()->bEsp)
			Render::DrawEsp(pData()->viewMatrix, pData()->fMatrix, pData()->entList);
	}
}

void test() {
	while (true) {
		std::cout << "anti test" << std::endl;
	}
}

DWORD WINAPI MainThread(HMODULE hModule)
{
	//////////////////////////////////////////////////
	AllocConsole();
	SetConsoleTitleA("anti#4444");
	system("mode 73,20");
	FILE* x;
	freopen_s(&x, "CONOUT$", "w", stdout);
	//////////////////////////////////////////////////
	//std::thread EspT(EspThread);
	//std::thread InitT(Init);
	test();
	//EspT.join();
	//InitT.join();
	//////////////////////////////////////////////////
	fclose(x);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
	//////////////////////////////////////////////////
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



