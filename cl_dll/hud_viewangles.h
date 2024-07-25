#ifdef HUD_VIEWANGLES_H_RECURSE_GUARD
#error Recursive header files inclusion detected in hud_viewangles.h
#else //HUD_VIEWANGLES_H_RECURSE_GUARD

#define HUD_VIEWANGLES_H_RECURSE_GUARD

#ifndef HUD_VIEWANGLES_H_GUARD
#define HUD_VIEWANGLES_H_GUARD
#pragma once

#ifdef __cplusplus

class CHudViewangles: public CBXTHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float time);

private:
	cvar_t* hud_viewangles;
	cvar_t* hud_viewangles_anchor;
	cvar_t* hud_viewangles_offset;
};

#else //!__cplusplus
#error C++ compiler required to compile hud_viewangles.h
#endif //__cplusplus

#endif //HUD_VIEWANGLES_H_GUARD

#undef HUD_VIEWANGLES_H_RECURSE_GUARD
#endif //HUD_VIEWANGLES_H_RECURSE_GUARD