#ifdef UTILS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in Utils.h
#else // UTILS_H_RECURSE_GUARD

#define UTILS_H_RECURSE_GUARD

#ifndef UTILS_H_GUARD
#define UTILS_H_GUARD
#pragma once

#ifdef __cplusplus

#ifdef PLATFORM_WINDOWS
using dllhandle_t = HMODULE;
using farproc_t = FARPROC;
#define DLL_FORMAT ".dll"
#else
using dllhandle_t = void*;
using farproc_t = void*;
#define DLL_FORMAT ".so"
#endif

#define TRACE(format, ...) Sys_Printf("%s::%s(%d): " format, __FILE__, __FUNCTION__, __LINE__)

bool UTIL_IsHost();

void Sys_Printf(const char* fmt, ...);
dllhandle_t Sys_GetModuleHandle(const char* pszModuleName);
farproc_t Sys_GetProcAddress(dllhandle_t handle, const char* name);

#else //!__cplusplus
#error C++ compiler required to compile Utils.h
#endif //__cplusplus

#endif // UTILS_H_GUARD

#undef UTILS_H_RECURSE_GUARD
#endif // UTILS_H_RECURSE_GUARD
