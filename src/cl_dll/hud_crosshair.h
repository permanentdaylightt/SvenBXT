#ifdef HUD_CROSSHAIR_H_RECURSE_GUARD
#error Recursive header files inclusion detected in hud_crosshair.h
#else //HUD_CROSSHAIR_H_RECURSE_GUARD

#define HUD_CROSSHAIR_H_RECURSE_GUARD

#ifndef HUD_CROSSHAIR_H_GUARD
#define HUD_CROSSHAIR_H_GUARD
#pragma once

#ifdef __cplusplus

class CHudCrosshair: public CBXTHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float time);

private:
	cvar_t* bxt_cross;
	cvar_t* bxt_cross_color;
	cvar_t* bxt_cross_alpha;
	cvar_t* bxt_cross_thickness;
	cvar_t* bxt_cross_size;
	cvar_t* bxt_cross_gap;
	cvar_t* bxt_cross_outline;
	cvar_t* bxt_cross_circle_radius;
	cvar_t* bxt_cross_dot_color;
	cvar_t* bxt_cross_dot_size;
	cvar_t* bxt_cross_top_line;
	cvar_t* bxt_cross_bottom_line;
	cvar_t* bxt_cross_left_line;
	cvar_t* bxt_cross_right_line;
};


#else //!__cplusplus
#error C++ compiler required to compile hud_crosshair.h
#endif //__cplusplus

#endif //HUD_CROSSHAIR_H_GUARD

#undef HUD_CROSSHAIR_H_RECURSE_GUARD
#endif //HUD_CROSSHAIR_H_RECURSE_GUARD