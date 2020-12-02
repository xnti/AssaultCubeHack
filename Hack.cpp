#include "pch.h"


namespace Hack {
	static Internal g_Internal;
	static Functions g_Functions;
	static Data g_Data;

	Internal* pInternal()
	{
		return &g_Internal;
	}
	Functions* pFunctions()
	{
		return &g_Functions;
	}
	Data* pData()
	{
		return &g_Data;
	}

	void Hack::Init()
	{
		//uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");
		//calling it with NULL also gives you the address of the .exe module
		// Init Data.
		float fMatrix[16];
		bool bHealth = false, bAmmo = false, bRecoil = false, bFastFire = false, bSpectator = false, bAkimbo = false, bbHop = false, bEsp = false;
		// Init Ptrs.
		EntList* entList = *(EntList**)0x50F4F8;
		uintptr_t* matrix = (uintptr_t*)0x501AE8;
		pData()->moduleBase = (uintptr_t)GetModuleHandle(NULL);
		pData()->localPlayer = *(playerEnt**)0x50F4F4;
		pData()->localPlayerPtr = (uintptr_t*)(pData()->moduleBase + 0x10F4F4);
		pData()->numOfPlayers = (int*)(0x50F500);

		pFunctions()->statusConsole(bHealth, bAmmo, bRecoil, bFastFire, bSpectator, bAkimbo, bbHop, bEsp);
		while (true)
		{
			if (GetAsyncKeyState(VK_END) & 1)
				break;
			if (GetAsyncKeyState(VK_F1) & 1)
			{
				bHealth = !bHealth;
				pFunctions()->statusConsole(bHealth, bAmmo, bRecoil, bFastFire, bSpectator, bAkimbo, bbHop, bEsp);
			}

			if (GetAsyncKeyState(VK_F2) & 1)
			{
				bAmmo = !bAmmo;
				pFunctions()->statusConsole(bHealth, bAmmo, bRecoil, bFastFire, bSpectator, bAkimbo, bbHop, bEsp);
			}

			if (GetAsyncKeyState(VK_F3) & 1)
			{
				bRecoil = !bRecoil;
				pFunctions()->statusConsole(bHealth, bAmmo, bRecoil, bFastFire, bSpectator, bAkimbo, bbHop, bEsp);
			}

			if (GetAsyncKeyState(VK_F4) & 1)
			{
				bFastFire = !bFastFire;
				pFunctions()->statusConsole(bHealth, bAmmo, bRecoil, bFastFire, bSpectator, bAkimbo, bbHop, bEsp);
			}

			if (GetAsyncKeyState(VK_F5) & 1)
			{
				bSpectator = !bSpectator;
				pFunctions()->statusConsole(bHealth, bAmmo, bRecoil, bFastFire, bSpectator, bAkimbo, bbHop, bEsp);
			}

			if (GetAsyncKeyState(VK_F6) & 1)
			{
				bAkimbo = !bAkimbo;
				pFunctions()->statusConsole(bHealth, bAmmo, bRecoil, bFastFire, bSpectator, bAkimbo, bbHop, bEsp);
			}

			if (GetAsyncKeyState(VK_F7) & 1)
			{
				bbHop = !bbHop;
				pFunctions()->statusConsole(bHealth, bAmmo, bRecoil, bFastFire, bSpectator, bAkimbo, bbHop, bEsp);
			}

			if (GetAsyncKeyState(VK_F8) & 1)
			{
				bEsp = !bEsp;
				pFunctions()->statusConsole(bHealth, bAmmo, bRecoil, bFastFire, bSpectator, bAkimbo, bbHop, bEsp);
			}

			//continuous writes / freeze
			if (pData()->localPlayerPtr)
			{
				if (bHealth)
				{

					//*localPlayerPtr = derference the pointer, to get the localPlayerAddr
					// add 0xF8 to get health address
					//cast to an int pointer, this pointer now points to the health address
					//derference it and assign the value 1337 to the health variable it points to
					//*(int*)(*localPlayerPtr + 0xF8) = 1337;
					//*(int*)mem::FindDMAAddy(moduleBase + 0x109B74, { 0xF8 }) = 1337;
					pData()->localPlayer->health = 1337;
					pData()->localPlayer->armor = 1337;
				}

				if (bAmmo)
				{
					//We aren't external now, we can now efficiently calculate all pointers dynamically
					//before we only resolved pointers when needed for efficiency reasons
					//we are executing internally, we can calculate everything when needed
					//uintptr_t ammoAddr = mem::FindDMAAddy(moduleBase + 0x10F4F4, { 0x374, 0x14, 0x0 });
					//int* ammo = (int*)ammoAddr;
					//*ammo = 1337;

					//or just
					//*(int*)mem::FindDMAAddy(moduleBase + 0x10F4F4, { 0x374, 0x14, 0x0 }) = 1337;

					* pData()->localPlayer->weapon->ammo = 444;
				}

				if (bRecoil)
				{
					pInternal()->Nop((BYTE*)(pData()->moduleBase + 0x63786), 10);
				}
				else
				{
					//50 8D 4C 24 1C 51 8B CE FF D2 the original stack setup and call
					pInternal()->Patch((BYTE*)(pData()->moduleBase + 0x63786), (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10);
				}

				if (bFastFire)
				{
					//*(int*)mem::FindDMAAddy(moduleBase + 0x10F4F4, { 0x384,0x14,0x28 }) = 0;
					pData()->localPlayer->KnifeWaitTime = 0;
					pData()->localPlayer->PistolWaitTime = 0;
					pData()->localPlayer->CarbineWaitTime = 0;
					pData()->localPlayer->ShotgunWaitTime = 0;
					pData()->localPlayer->SMGWaitTime = 0;
					pData()->localPlayer->SniperWaitTime = 0;
					pData()->localPlayer->AssaultWaitTime = 0;
				}

				if (bSpectator)
				{
					//*(int*)mem::FindDMAAddy(moduleBase + 0x10F4F4, { 0x338 }) = 5;
					pData()->localPlayer->state = 5;
				}
				else
				{
					//*(int*)mem::FindDMAAddy(moduleBase + 0x10F4F4, { 0x338 }) = 0;
					pData()->localPlayer->state = 0;
				}

				if (bAkimbo)
				{
					pData()->localPlayer->akimbo = 1;
				}
				else
				{
					pData()->localPlayer->akimbo = 0;
				}

				if (bbHop)
				{
					pData()->localPlayer->bHop = 256;
				}
				if (bEsp)
				{
					CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Render::DrawEsp, (matrix, fMatrix, entList), 0, 0);
				}

			}
			else {
				while (pData()->localPlayerPtr == NULL)
				{
					pData()->localPlayerPtr = (uintptr_t*)(pData()->moduleBase + 0x10F4F4);
				}
			}
			Sleep(5);
		}
	}

	bool Hack::Functions::IsValidEnt(playerEnt* ent)
	{
		if (ent)
		{
			if (ent->vTable == 0x4E4A98 || ent->vTable == 0x4E4AC0)
			{
				return true;
			}
		}
		return false;
	}

	void Hack::Functions::statusConsole(bool bHealth, bool bAmmo, bool bRecoil, bool bFastFire, bool bSpectator, bool bAkimbo, bool bbHop, bool bEsp)
	{
		system("CLS");
		std::cout << "*                  --------------------------------------               *\n";
		std::cout << "*                     AssaultCube Trainer by anti#4444                  *\n";
		std::cout << "*                  --------------------------------------               *\n";
		std::cout << "*                                                                       *\n";
		std::cout << "*                  [F1] Infinite Health && Ammo          [" << bHealth << "]            *\n";
		std::cout << "*                  [F2] Infinite Ammo                    [" << bAmmo << "]            *\n";
		std::cout << "*                  [F3] No Recoil                        [" << bRecoil << "]            *\n";
		std::cout << "*                  [F4] Fast Fire                        [" << bFastFire << "]            *\n";
		std::cout << "*                  [F5] Fly                              [" << bSpectator << "]            *\n";
		std::cout << "*                  [F6] Activate Akimbo                  [" << bAkimbo << "]            *\n";
		std::cout << "*                  [F7] Unlimited Jump                   [" << bbHop << "]            *\n";
		std::cout << "*                  [F8] E S P                            [" << bEsp << "]            *\n";
		std::cout << "*                                                                       *\n";
		std::cout << "*                  [END] Close                                          *\n";
		std::cout << "*                                                                       *\n";
		std::cout << "*                  --------------------------------------               *\n";
	}

	void Hack::Internal::Patch(BYTE* dst, BYTE* src, unsigned int size)
	{
		DWORD oldprotect;
		VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
		memcpy(dst, src, size);
		VirtualProtect(dst, size, oldprotect, &oldprotect);
	}
	void Hack::Internal::Nop(BYTE* dst, unsigned int size)
	{
		DWORD oldprotect;
		VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
		memset(dst, 0x90, size);
		VirtualProtect(dst, size, oldprotect, &oldprotect);
	}
	uintptr_t Hack::Internal::FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets)
	{
		uintptr_t addr = ptr;
		for (unsigned int i = 0; i < offsets.size(); ++i)
		{
			addr = *(uintptr_t*)addr;
			addr += offsets[i];
		}
		return addr;

	}
}

