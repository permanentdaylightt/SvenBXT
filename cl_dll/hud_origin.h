#ifdef HUD_ORIGIN_H_RECURSE_GUARD
#error Recursive header files inclusion detected in hud_origin.h
#else //HUD_ORIGIN_H_RECURSE_GUARD

#define HUD_ORIGIN_H_RECURSE_GUARD

#ifndef HUD_ORIGIN_H_GUARD
#define HUD_ORIGIN_H_GUARD
#pragma once

#ifdef __cplusplus

class CHudOrigin: public CBXTHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float time);

private:
	cvar_t* hud_origin;
	cvar_t* hud_origin_anchor;
	cvar_t* hud_origin_offset;
};

#else //!__cplusplus
#error C++ compiler required to compile hud_origin.h
#endif //__cplusplus

#endif //HUD_ORIGIN_H_GUARD

#undef HUD_ORIGIN_H_RECURSE_GUARD
#endif //HUD_ORIGIN_H_RECURSE_GUARD