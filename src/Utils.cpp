//
// Created by scriptedsnark on 7/18/24.
//

#include "SvenBXT.h"

/*
================
UTIL_IsHost
================
*/
bool UTIL_IsHost()
{
	if (!sv)
		return false;

	return sv->active;
}

/*
================
Sys_Printf
================
*/
void Sys_Printf(const char* fmt, ...)
{
	va_list va;

	FILE* file = fopen("svenbxt.log", "a");

	va_start(va, fmt);

	if (file)
	{
		vfprintf(file, fmt, va);
		fclose(file);
	}

	vprintf(fmt, va);
	va_end(va);
}

/*
================
Sys_GetModuleHandle
================
*/
dllhandle_t Sys_GetModuleHandle(const char* pszModuleName)
{
#ifdef PLATFORM_WINDOWS
	return GetModuleHandleA(pszModuleName);
#else
	void* handle = dlopen(pszModuleName, RTLD_LAZY | RTLD_NOLOAD);
	if (handle == NULL)
	{
		if (dlerror() && dlerror()[0])
			Sys_Printf("dlopen error: %s\n", dlerror());

		return NULL;
	}

	return reinterpret_cast<dllhandle_t>(handle);
#endif
}

/*
================
Sys_GetProcAddress
================
*/
farproc_t Sys_GetProcAddress(dllhandle_t handle, const char* name)
{
#ifdef PLATFORM_WINDOWS
	return GetProcAddress(handle, name);
#else
	return dlsym(handle, name);
#endif
}
