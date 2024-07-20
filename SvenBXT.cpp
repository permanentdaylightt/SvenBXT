//
// Created by scriptedsnark on 7/18/24.
//

#include "SvenBXT.h"

void SvenBXT_Main()
{
    Sys_Printf("SvenBXT_Main\n");
}

void SvenBXT_Shutdown()
{

}

#ifdef WIN32
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            AllocConsole();
            FILE* in, *out;
            freopen_s(&in, "conin$", "r", stdin);
            freopen_s(&out, "conout$", "w+", stdout);
            CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(SvenBXT_Main), NULL, NULL, NULL);
            break;

        case DLL_PROCESS_DETACH:
            SvenBXT_Shutdown();
            break;
    }

    return TRUE;
}
#else
static __attribute__((constructor)) void Construct()
{
    SvenBXT_Main();
}

static __attribute__((destructor)) void Destruct()
{
    SvenBXT_Shutdown();
}
#endif
