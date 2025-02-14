#ifdef REGS_PATTERNS_HPP_RECURSE_GUARD
#error Recursive header files inclusion detected in engine_patterns.hpp
#else //REGS_PATTERNS_HPP_RECURSE_GUARD

#define REGS_PATTERNS_HPP_RECURSE_GUARD

#ifndef REGS_PATTERNS_HPP_GUARD
#define REGS_PATTERNS_HPP_GUARD
#pragma once

#include "external/SPTLib/patterns.hpp"
#include "external/SPTLib/MemUtils.h"

namespace patterns
{
	namespace server
	{
		PATTERNS(CNihilanth_DyingThink,
			"Sven-5.25",
			"A1 ?? ?? ?? ?? 83 EC 74 F3 0F 10 00",
			"Sven-5.26",
			"83 EC 6C A1 ?? ?? ?? ?? 53 56 8B F1 F3 0F 10 00 0F 5A C0 57 8B 46 ?? 51 C7 04 24 CD CC CC 3D F2 0F 58 05 ?? ?? ?? ??");
	}

	namespace engine
	{
		// STRINGS
		// ../engine/cdll_int.c, line %d: could not link client DLL for HUD initialization
		// joysupported
		// HUD_GetStudioModelInterface
		PATTERNS(ClientDLL_HudInit,
			"Sven-5.25",
			"A1 ?? ?? ?? ?? 85 C0 75 ?? 68 ?? ?? ?? ?? E8 ?? ?? ?? ?? A1 ?? ?? ?? ??"
		);

		// STRINGS
		// cl_dlls/client
		// ScreenShake
		// ScreenFade
		PATTERNS(ClientDLL_Init,
			"Sven-5.25",
			"81 EC 04 02 00 00 A1 ?? ?? ?? ?? 33 C4 89 84 24 ?? ?? ?? ?? 68 ?? ?? ?? ?? 8D 44 24 ?? 68 00 02 00 00",
			"Sven-5.26-rc1",
			"81 EC 04 02 00 00 A1 ?? ?? ?? ?? 33 C4 89 84 24 ?? ?? ?? ?? 68 00 02 00 00 8D 44 24 ?? 6A 00 50 E8 ?? ?? ?? ?? 68 ?? ?? ?? ?? 8D 44 24 ?? 68 FF 01 00 00"
		);

		PATTERNS(GL_Begin2D, // a.k.a GLBeginHud
			"Sven-5.25",
			"56 FF 35 ?? ?? ?? ?? FF 35 ?? ?? ?? ?? FF 35 ?? ?? ?? ??");

		PATTERNS(GL_Finish2D,
			"Sven-5.25",
			"56 68 01 17 00 00 FF 15 ?? ?? ?? ?? 8B 35 ?? ?? ?? ?? FF D6 68 00 17 00 00");

		// STRINGS
		// Clearing memory
		PATTERNS(Host_ClearMemory,
			"Sven-5.25",
			"E8 ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 7C 24 ?? 00 75 ??");

		PATTERNS(LoadThisDll,
			"Sven-5.25",
			"53 57 8B 7C 24 ?? 57 E8 ?? ?? ?? ?? 8B D8 83 C4 04 85 DB 75 ?? E8 ?? ?? ?? ??");

		PATTERNS(Netchan_CreateFragments,
			"Sven-5.25", "B8 1C 00 04 00 E8 ?? ?? ?? ?? A1 ?? ?? ?? ?? 33 C4 89 84 24 ?? ?? ?? ?? 55 8B AC 24 ?? ?? ?? ??");

		PATTERNS(SZ_Write,
			"Sven-5.25", "8B 4C 24 ?? 85 C9 75 ?? 56");

		PATTERNS(SZ_GetSpace,
			"Sven-5.25", "56 8B 74 24 08 57 8B 7C 24 10 8B 4E 10 8B 56 0C 8D 04 39 3B C2 0F 8E ?? ?? ?? ?? F6 46 04 01 75 2E 8B 06 85 D2 75 11 85 C0 75 05 B8 ?? ?? ?? ?? 50 68 ?? ?? ?? ?? EB 0F 85 C0 75 05 B8");

		PATTERNS(Mod_LoadTextures,
			"Sven-5.25", "83 EC 74 A1 ?? ?? ?? ?? 33 C4 89 44 24 ?? 53 8B 5C 24 ??");

		PATTERNS(SCR_BeginLoadingPlaque,
			"Sven-5.25",
			"?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? 83 C4 04 83 F8 03 74 ?? 83 F8 04 74 ?? 83 F8 05 75 ?? 83 3D ?? ?? ?? ?? 02");

		PATTERNS(SCR_EndLoadingPlaque,
			"Sven-5.25",
			"?? ?? ?? ?? ?? ?? ?? ?? ?? ?? E8 ?? ?? ?? ?? 68 ?? ?? ?? ?? 68 ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 C4 08 C7 05 ?? ?? ?? ?? 00 00 00 00");

		PATTERNS(GL_EndRendering,
			"Sven-5.25",
			"?? ?? ?? ?? ?? ?? ?? ?? 30 83 3D ?? ?? ?? ?? 00 53 55 56 57 0F 84 ?? ?? ?? ??");

		PATTERNS(S_StartDynamicSound,
			"Sven-5.25",
			"83 EC 58 A1 ?? ?? ?? ?? 33 C4 89 44 24 ?? 8B 44 24 ??");

		PATTERNS(S_StartStaticSound,
			"Sven-5.25",
			"83 EC 4C A1 ?? ?? ?? ?? 33 C4 89 44 24 ?? 57 8B 7C 24 ?? 85 FF 0F 84 ?? ?? ?? ?? 80 3F 2A 55 56");
	}
}

#endif //REGS_PATTERNS_HPP_GUARD

#undef REGS_PATTERNS_HPP_RECURSE_GUARD
#endif //REGS_PATTERNS_HPP_RECURSE_GUARD