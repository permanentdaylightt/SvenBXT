#ifdef SVENBXT_H_RECURSE_GUARD
#error Recursive header files inclusion detected in SvenBXT.h
#else // SVENBXT_H_RECURSE_GUARD

#define SVENBXT_H_RECURSE_GUARD

#ifndef SVENBXT_H_GUARD
#define SVENBXT_H_GUARD
#pragma once

#ifdef __cplusplus

// WINDOWS
#ifdef PLATFORM_WINDOWS
#include <windows.h>
#include <DbgHelp.h>
#else
#include <dlfcn.h>
#include <stdarg.h>
#include <cstring>
#endif

// STL
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <array>
#include <random>
#include <fstream>
#include <thread>

#include "external/funchook/include/funchook.h"

#ifdef PLATFORM_WINDOWS
#include "external/SPTLib/Utils.hpp"
#include "engine_patterns.hpp"
extern Utils utils;
#endif

#include <stdio.h>
#include "hlsdk_mini.hpp"

// OWN STUFF
#include "Utils.h"

extern funchook_t* g_lpFuncHook_Client;
extern dllhandle_t g_lpEngine;
extern dllhandle_t g_lpClient;
extern cl_enginefunc_t* g_lpEngfuncs;

#include "cl_dll/cdll_int.h"
#include "cl_dll/hud.h"
#include "cl_dll/view.h"

// HUD
#include "cl_dll/hud_speedometer.h"

#define Find(lib, func_name)                                                                                  \
	if ((ORIG_##func_name = reinterpret_cast<_##func_name>(Sys_GetProcAddress(g_lp##lib, "" #func_name "")))) \
		Sys_Printf("[" #lib "] Found " #func_name " at %p.\n", ORIG_##func_name);                             \
	else                                                                                                      \
		Sys_Printf("[" #lib "] Could not find " #func_name ".\n")

#define CreateHook(lib, func_name)                                                                           \
	do                                                                                                       \
	{                                                                                                        \
		Sys_Printf("[" #lib "] Creating hook for " #func_name "...\n");                                      \
		status = funchook_prepare(g_lpFuncHook_##lib, (void**)&ORIG_##func_name, (void*)HOOKED_##func_name); \
		if (status == FUNCHOOK_ERROR_SUCCESS)                                                                \
			Sys_Printf("[" #lib "] Hooked " #func_name "!\n");                                               \
		else                                                                                                 \
			Sys_Printf("[" #lib "] Failed to hook " #func_name "! Code: %i\n", status);                      \
	} while (0)

#else //!__cplusplus
#error C++ compiler required to compile SvenBXT.h
#endif //__cplusplus

#endif // SVENBXT_H_GUARD

#undef SVENBXT_H_RECURSE_GUARD
#endif // SVENBXT_H_RECURSE_GUARD
