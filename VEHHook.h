#ifndef VEHHOOK_H
#define VEHHOOK_H
#pragma once
#include "pch.h"

namespace Hack {

	struct VEHData {
		DWORD dwJumpBack;
		DWORD hookAddr;
		void* hookFunc;
		PVOID VEHHandle;
	};

	class VEHHook {
	public:
		bool Init(void* address, void* hookFunction);
	private:
		static LONG WINAPI HandleException(EXCEPTION_POINTERS* pExceptionInfo);
	};

	VEHData* pVEHData();
	VEHHook* pVEHHook();
}
#endif // !VEHHOOK_H
