#ifdef GL_SCREEN_H_RECURSE_GUARD
#error Recursive header files inclusion detected in gl_screen.h
#else //GL_SCREEN_H_RECURSE_GUARD

#define GL_SCREEN_H_RECURSE_GUARD

#ifndef GL_SCREEN_H_GUARD
#define GL_SCREEN_H_GUARD
#pragma once

#ifdef __cplusplus

typedef void (*_SCR_BeginLoadingPlaque)(qboolean reconnect);
typedef void (*_SCR_EndLoadingPlaque)();

extern _SCR_BeginLoadingPlaque ORIG_SCR_BeginLoadingPlaque;
extern _SCR_EndLoadingPlaque ORIG_SCR_EndLoadingPlaque;

void HOOKED_SCR_BeginLoadingPlaque(qboolean reconnect);
void HOOKED_SCR_EndLoadingPlaque();

#else //!__cplusplus
#error C++ compiler required to compile gl_screen.h
#endif //__cplusplus

#endif //GL_SCREEN_H_GUARD

#undef GL_SCREEN_H_RECURSE_GUARD
#endif //GL_SCREEN_H_RECURSE_GUARD