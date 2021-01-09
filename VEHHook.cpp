#include "pch.h"
#include "VEHHook.h"

namespace Hack
{
	static VEHHook g_VEHHook;
	static VEHData g_VEHData;

	bool VEHHook::Init(void* address, void* hookFunction)
	{
		pVEHData()->hookAddr = (DWORD)address;
		pVEHData()->hookFunc = hookFunction;
		DWORD dwOldProtect;
		pVEHData()->VEHHandle = AddVectoredExceptionHandler(true, (PVECTORED_EXCEPTION_HANDLER)HandleException);
		if (pVEHData()->VEHHandle && VirtualProtect(address, 1, PAGE_EXECUTE | PAGE_GUARD, &dwOldProtect))
			return true;
	}

	LONG WINAPI VEHHook::HandleException(EXCEPTION_POINTERS* pExceptionInfo)
	{
		if (pExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_GUARD_PAGE_VIOLATION)
		{
			if (pExceptionInfo->ContextRecord->Eip == pVEHData()->hookAddr)
			{
				Hack::pVEHData()->dwJumpBack = (DWORD)pExceptionInfo->ContextRecord->Eip + 5;
				pExceptionInfo->ContextRecord->Eip = (DWORD)pVEHData()->hookFunc;
			}
			pExceptionInfo->ContextRecord->EFlags |= 0x100;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		if (pExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_SINGLE_STEP)
		{
			DWORD dwOld;
			VirtualProtect((void*)pVEHData()->hookAddr, 1, PAGE_EXECUTE | PAGE_GUARD, &dwOld);
			return EXCEPTION_CONTINUE_SEARCH;
		}
		return EXCEPTION_CONTINUE_SEARCH;
	};
	
	VEHData* pVEHData()
	{
		return &g_VEHData;
	}

	VEHHook* pVEHHook()
	{
		return &g_VEHHook;
	}
}

