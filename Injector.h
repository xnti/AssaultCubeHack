#ifndef INJECTOR_H
#define INJECTOR_H

extern "C" {
#pragma once
#include "pch.h"
#include <TlHelp32.h>

	class Injector
	{
		ANTI_API DWORD GetProcId(const char* procName);
		ANTI_API int InjectorMain(const char* dll);

	};
}


#endif // !INJECTOR_H



