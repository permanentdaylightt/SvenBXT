#include "SvenBXT.h"

_SCR_BeginLoadingPlaque ORIG_SCR_BeginLoadingPlaque = NULL;
_SCR_EndLoadingPlaque ORIG_SCR_EndLoadingPlaque = NULL;

void HOOKED_SCR_BeginLoadingPlaque(qboolean reconnect)
{
	ORIG_SCR_BeginLoadingPlaque(reconnect);

	if (g_lpHUDTimer->IsInILMode())
		g_lpHUDTimer->TimerStop();
}

void HOOKED_SCR_EndLoadingPlaque()
{
	ORIG_SCR_EndLoadingPlaque();

	if (g_lpHUDTimer->IsInILMode() && g_RTATimer.GetMilliseconds() <= 0)
		g_lpHUDTimer->TimerStart();
}