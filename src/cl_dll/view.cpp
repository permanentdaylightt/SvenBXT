#include "SvenBXT.h"

ref_params_s g_RefParams;

void HOOKED_V_CalcRefdef(struct ref_params_s* pparams)
{
	g_RefParams = *pparams;
	ORIG_V_CalcRefdef(pparams);

	g_lpJumpspeedHUD->UpdateSpeed(g_RefParams.simvel);
}
