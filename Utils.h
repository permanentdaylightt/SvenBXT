//
// Created by scriptedsnark on 7/18/24.
//

#ifndef UTILS_H
#define UTILS_H

#ifdef _WIN32
using dllhandle_t = HMODULE;
#define DLL_FORMAT ".dll"
#else
using dllhandle_t = void*;
#define DLL_FORMAT ".so"
#endif

void Sys_Printf(const char* fmt, ...);
dllhandle_t Sys_GetModuleHandle(const char *pszModuleName);
void* Sys_GetProcAddress(dllhandle_t handle, const char* name);

#endif //UTILS_H
