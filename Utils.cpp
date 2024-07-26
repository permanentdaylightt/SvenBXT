//
// Created by scriptedsnark on 7/18/24.
//

#include "SvenBXT.h"

/*
================
Sys_Printf
================
*/
void Sys_Printf(const char* fmt, ...)
{
	char msg[4096];
	va_list va;

	va_start(va, fmt);
	vsnprintf(msg, sizeof(msg), fmt, va);
	va_end(va);

	FILE* file = fopen("svenbxt.log", "a");
	if (file)
	{
		fprintf(file, "%s", msg);
		fclose(file);
	}

	printf("%s", msg);
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
