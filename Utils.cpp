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
    va_list	argptr;

    va_start(argptr, fmt);
    vprintf(fmt, argptr);
    va_end(argptr);
}

/*
================
Sys_GetModuleHandle
================
*/
dllhandle_t Sys_GetModuleHandle(const char *pszModuleName)
{
#ifdef PLATFORM_WINDOWS
    return GetModuleHandleA(pszModuleName);
#else
    void *handle = dlopen(pszModuleName, RTLD_LAZY | RTLD_NOLOAD);
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
    return GetProcAddress( handle, name );
#else
    return dlsym(handle, name);
#endif
}


