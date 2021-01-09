#ifndef HACK_H
#define HACK_H

#pragma once
#include "pch.h"
//uintptr_t moduleBase = (uintptr_t)GetModuleHandle(NULL);
//uintptr_t* localPlayerPtr = (uintptr_t*)(moduleBase + 0x10F4F4);
//uintptr_t* numOfPlayers = (uintptr_t*)(0x50F500);
////playerEnt* localPlayer = *(playerEnt**)0x50F4F4;
//playerEnt* localPlayer = *(playerEnt**)localPlayerPtr;
namespace Hack
{
	struct Data {
		uintptr_t moduleBase;
		uintptr_t* localPlayerPtr;
		uintptr_t* viewMatrix;
		playerEnt* localPlayer;
		EntList* entList;
		bool bEsp;
		int* numOfPlayers;
		float fMatrix[16];
	};

	/* class External {
	public:
		/* External 
		// Patch the byte
		void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
		// Nop's the byte
		void NopEx(BYTE* dst, unsigned int size, HANDLE hProcess);
		// Finds Address of a pointer.
		uintptr_t FindDMAAddyEx(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);
	};
	*/

	class Internal {
	public:
		/* Internal */
		// Patch the byte
		void Patch(BYTE* dst, BYTE* src, unsigned int size);
		// Nop's the byte
		void Nop(BYTE* dst, unsigned int size);
		// Finds Address of a pointer.
		uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);
	};

	class Functions {
	public:
		// Init Hack.
		//void Init();
		// Updates Console.
		void statusConsole(bool bHealth, bool bAmmo, bool bRecoil, bool bFastFire, bool bSpectator, bool bAkimbo, bool bbHop, bool bEsp);
		// is Valid Entity ?
		bool IsValidEnt(playerEnt* ent);
	};

	Internal* pInternal();
	Functions* pFunctions();
	Data* pData();
	void Init();
};
#endif