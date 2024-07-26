#ifdef HUD_SPEEDOMETER_H_RECURSE_GUARD
#error Recursive header files inclusion detected in hud_speedometer.h
#else // HUD_SPEEDOMETER_H_RECURSE_GUARD

#define HUD_SPEEDOMETER_H_RECURSE_GUARD

#ifndef HUD_SPEEDOMETER_H_GUARD
#define HUD_SPEEDOMETER_H_GUARD
#pragma once

#ifdef __cplusplus

class CHudSpeedometer: public CBXTHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float time);

private:
	cvar_t* hud_speedometer;
	cvar_t* hud_speedometer_below_cross;
	cvar_t* hud_speedometer_height;
};

#else //!__cplusplus
#error C++ compiler required to compile hud_speedometer.h
#endif //__cplusplus

#endif // HUD_SPEEDOMETER_H_GUARD

#undef HUD_SPEEDOMETER_H_RECURSE_GUARD
#endif // HUD_SPEEDOMETER_H_RECURSE_GUARD
