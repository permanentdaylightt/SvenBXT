#include "SvenBXT.h"

float AngleNormalize(float angle)
{
	angle = fmodf(angle, 360.0f);
	if (angle > 180)
	{
		angle -= 360;
	}
	if (angle < -180)
	{
		angle += 360;
	}
	return angle;
}

int CHudViewangles::Init()
{
	m_iFlags = HUD_ACTIVE;

	hud_viewangles = CVAR_CREATE("sbxt_hud_viewangles", "0", 0);
	hud_viewangles_anchor = CVAR_CREATE("sbxt_hud_viewangles_anchor", "1 0", 0);
	hud_viewangles_offset = CVAR_CREATE("sbxt_hud_viewangles_offset", "", 0);

	return 0;
}

int CHudViewangles::VidInit()
{
	return 1;
}

int CHudViewangles::Draw(float time)
{
	if (!hud_viewangles->value)
		return 0;

	int x, y;
	gBXTHud.GetPosition(hud_viewangles_offset, hud_viewangles_anchor, &x, &y, -200, (CharHeight * 10) + 2);

	float viewangle[2];
	viewangle[0] = AngleNormalize(g_RefParams.viewangles[0]);
	viewangle[1] = AngleNormalize(g_RefParams.viewangles[1]);

	std::ostringstream out;
	out.setf(std::ios::fixed);
	out.precision((int)gBXTHud.hud_precision->value);

	out << "Angles:"
		<< "\n"
		<< "Pitch: " << viewangle[0] << "\n"
		<< "Yaw: " << viewangle[1];

	gBXTHud.DrawMultilineString(x, y, out.str());

	return 0;
}
