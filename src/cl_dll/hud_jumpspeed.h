#ifdef HUD_JUMPSPEED_H_RECURSE_GUARD
#error Recursive header files inclusion detected in hud_jumpspeed.h
#else //HUD_JUMPSPEED_H_RECURSE_GUARD

#define HUD_JUMPSPEED_H_RECURSE_GUARD

#ifndef HUD_JUMPSPEED_H_GUARD
#define HUD_JUMPSPEED_H_GUARD
#pragma once

#ifdef __cplusplus

#define FADE_DURATION_JUMPSPEED 0.7f

class CHudJumpspeed: public CBXTHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float time);

	void UpdateSpeed(const float velocity[3]);

private:
	uint16_t speed;

	cvar_t* hud_jumpspeed;
	cvar_t* hud_jumpspeed_below_cross;
	cvar_t* hud_jumpspeed_height;

	int fadingFrom[3];
	float prevVel[3] = {0.0f, 0.0f, 0.0f};
	float lastTime;
	double passedTime;
};

extern CHudJumpspeed* g_lpJumpspeedHUD;

#else //!__cplusplus
#error C++ compiler required to compile hud_jumpspeed.h
#endif //__cplusplus

#endif //HUD_JUMPSPEED_H_GUARD

#undef HUD_JUMPSPEED_H_RECURSE_GUARD
#endif //HUD_JUMPSPEED_H_RECURSE_GUARD