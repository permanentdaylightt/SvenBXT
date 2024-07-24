#include "SvenBXT.h"

int CHudSpeedometer::Init()
{
	m_iFlags = HUD_ACTIVE;

	hud_speedometer = CVAR_CREATE("sbxt_hud_speedometer", "0", FCVAR_ARCHIVE);
	hud_speedometer_below_cross = CVAR_CREATE("sbxt_hud_speedometer_below_cross", "0", FCVAR_ARCHIVE);
	hud_speedometer_height = CVAR_CREATE("sbxt_hud_speedometer_height", "0", FCVAR_ARCHIVE);

	return 0;
}

int CHudSpeedometer::VidInit()
{
	return 1;
}

int CHudSpeedometer::Draw(float time)
{
	if (!hud_speedometer->value)
		return 0;

	int x = ScreenWidth / 2;
	int y = ScreenHeight - gBXTHud.m_iFontHeight - gBXTHud.m_iFontHeight / 2 - gBXTHud.m_iFontHeight;

	if (hud_speedometer_below_cross->value)
		y = ScreenHeight / 2 + gBXTHud.m_iFontHeight / 2;
	else if (hud_speedometer_height->value)
		y = hud_speedometer_height->value;

	gBXTHud.DrawHudNumberCentered(x, y, std::round(std::hypot(g_RefParams.simvel[0], g_RefParams.simvel[1])), 100, 130, 200);

	return 0;
}
