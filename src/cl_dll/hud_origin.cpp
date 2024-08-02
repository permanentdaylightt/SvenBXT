#include "SvenBXT.h"

int CHudOrigin::Init()
{
	m_iFlags |= HUD_ACTIVE;

	hud_origin = CVAR_CREATE("sbxt_hud_origin", "0", 0);
	hud_origin_anchor = CVAR_CREATE("sbxt_hud_origin_anchor", "1 0", 0);
	hud_origin_offset = CVAR_CREATE("sbxt_hud_origin_offset", "", 0);

	return 0;
}

int CHudOrigin::VidInit()
{
	return 1;
}

int CHudOrigin::Draw(float time)
{
	if (!hud_origin->value)
		return 0;

	int x, y;
	gBXTHud.GetPosition(hud_origin_offset, hud_origin_anchor, &x, &y, -200, (CharHeight * 6) + 1);

	g_lpEngfuncs->DrawConsoleString(x, y, "Origin:");

	y += CharHeight;

	std::ostringstream out;
	out.setf(std::ios::fixed);
	out.precision((int)gBXTHud.hud_precision->value);

	out << "X: " << g_RefParams.simorg[0] << "\n"
		<< "Y: " << g_RefParams.simorg[1] << "\n"
		<< "Z: " << g_RefParams.simorg[2];

	gBXTHud.DrawMultilineString(x, y, out.str());

	return 0;
}
