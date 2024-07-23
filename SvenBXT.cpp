//
// Created by scriptedsnark on 7/18/24.
//

#include "SvenBXT.h"

#ifdef PLATFORM_WINDOWS
Utils utils = Utils::Utils(NULL, NULL, NULL);
#endif

funchook_t* g_lpFuncHook_Client;

dllhandle_t g_lpEngine;
dllhandle_t g_lpClient;

cl_enginefunc_t* g_lpEngfuncs;

void SvenBXT_HookClient();

void SvenBXT_FindEngineStuff()
{
    TRACE("Finding engine stuff...\n");

#ifdef PLATFORM_LINUX
	g_lpEngfuncs = (cl_enginefunc_t*)Sys_GetProcAddress(g_lpEngine, "cl_enginefuncs");

    if (!g_lpEngfuncs)
    {
        Sys_Printf("[hw dll] Failed to get \"cl_enginefuncs\".\n");
        return;
    }
    else
    {
        Sys_Printf("[hw dll] Found cl_enginefuncs at %p.\n", g_lpEngfuncs);
        SvenBXT_HookClient();
    }
#else	
    void* handle;
    static void* base;
	static size_t size;

    if (!MemUtils::GetModuleInfo(L"hw.dll", &handle, &base, &size))
    {
        Sys_Printf("Failed to get module info from engine.\n");
        return;
    }

    utils = Utils::Utils(handle, base, size);

	void* ClientDLL_Init;
	auto fClientDLL_Init = utils.FindAsync(
		ClientDLL_Init,
		patterns::engine::ClientDLL_Init,
		[&](auto pattern) {
			switch (pattern - patterns::engine::ClientDLL_Init.cbegin())
			{
			default:
			case 0: // Sven-5.25
				Sys_Printf("Searching cl_enginefuncs in Sven-5.25 pattern...\n");
				g_lpEngfuncs = *reinterpret_cast<cl_enginefunc_t**>(reinterpret_cast<uintptr_t>(ClientDLL_Init) + 332);

                if (g_lpEngfuncs)
                {
                    Sys_Printf("[hw dll] Found cl_enginefuncs at 0x%p.\n", g_lpEngfuncs);
                    SvenBXT_HookClient();
                }
				break;
			}
		});
#endif
}

void SvenBXT_HookClient()
{
    TRACE("Hooking client...\n");
#ifdef PLATFORM_WINDOWS
    g_lpClient = Sys_GetModuleHandle("client");
#else
    g_lpClient = Sys_GetModuleHandle("svencoop/cl_dlls/client.so");
#endif

    if (!g_lpClient)
    {
        Sys_Printf("Failed to get client module handle.\n");
        return;
    }

    g_lpFuncHook_Client = funchook_create();

	CL_Initialize();

    funchook_install(g_lpFuncHook_Client, 0);
}

void SvenBXT_HookEngine()
{
    g_lpEngine = Sys_GetModuleHandle("hw" DLL_FORMAT);

    if (!g_lpEngine)
    {
        Sys_Printf("Failed to get engine module handle.\n");
        return;
    }

	SvenBXT_FindEngineStuff();
}

void SvenBXT_UnhookClient()
{
    if (g_lpFuncHook_Client)
    {
        funchook_uninstall(g_lpFuncHook_Client, 0);
        funchook_destroy(g_lpFuncHook_Client);
    }
}

void SvenBXT_UnhookEngine()
{

}

//-----------------------------------------------------------------------------
// Purpose: hook in right time a.k.a I don't wanna hook LoadLibraryA/dlopen
//-----------------------------------------------------------------------------
void WaitUntilClientLoads()
{
lbl_waitFor:
#ifdef PLATFORM_WINDOWS
    g_lpClient = Sys_GetModuleHandle("client");
#else
    g_lpClient = Sys_GetModuleHandle("svencoop/cl_dlls/client" DLL_FORMAT);
#endif

	if (g_lpClient)
	{
		SvenBXT_HookEngine();
    	//SvenBXT_HookClient();
	}
	else
		goto lbl_waitFor;
}


void SvenBXT_Main()
{
    TRACE("Initializing SvenBXT...\n");

	std::thread t(WaitUntilClientLoads);
	t.detach();
}

void SvenBXT_Shutdown()
{
    TRACE("Shutting down...\n");

    SvenBXT_UnhookEngine();
    SvenBXT_UnhookClient();
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
