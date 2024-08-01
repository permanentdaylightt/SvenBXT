#ifdef SERVER_H_RECURSE_GUARD
#error Recursive header files inclusion detected in server.h
#else //SERVER_H_RECURSE_GUARD

#define SERVER_H_RECURSE_GUARD

#ifndef SERVER_H_GUARD
#define SERVER_H_GUARD
#pragma once

#ifdef __cplusplus

typedef void (*_LoadThisDll)(char* szDllFilename);
extern _LoadThisDll ORIG_LoadThisDll;

extern int gmsgBXTTimer;

void HOOKED_LoadThisDll(char* szDllFilename);

void SV_SyncTimer();
void SV_Initialize();
void SV_HookStuff();

#else //!__cplusplus
#error C++ compiler required to compile server.h
#endif //__cplusplus

#endif //SERVER_H_GUARD

#undef SERVER_H_RECURSE_GUARD
#endif //SERVER_H_RECURSE_GUARD