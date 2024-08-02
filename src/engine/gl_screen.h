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
typedef void (*_GL_Begin2D)();
typedef void (*_GL_Finish2D)();
typedef void (*_GL_EndRendering)();

extern _SCR_BeginLoadingPlaque ORIG_SCR_BeginLoadingPlaque;
extern _SCR_EndLoadingPlaque ORIG_SCR_EndLoadingPlaque;
extern _GL_Begin2D ORIG_GL_Begin2D;
extern _GL_Finish2D ORIG_GL_Finish2D;
extern _GL_EndRendering ORIG_GL_EndRendering;

void HOOKED_SCR_BeginLoadingPlaque(qboolean reconnect);
void HOOKED_SCR_EndLoadingPlaque();
void HOOKED_GL_EndRendering();

#else //!__cplusplus
#error C++ compiler required to compile gl_screen.h
#endif //__cplusplus

#endif //GL_SCREEN_H_GUARD

#undef GL_SCREEN_H_RECURSE_GUARD
#endif //GL_SCREEN_H_RECURSE_GUARD