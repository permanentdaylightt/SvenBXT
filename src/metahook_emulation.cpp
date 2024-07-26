/**
 * Copyright - xWhitey, 2024.
 * svenmod_emulation.cpp - actual implementation of the emulation system
 *
 * Lightning a.k.a. lightning.tech (Sven Co-op) source file
 * Authors: xWhitey. Refer to common.hpp file for dependencies and their authors.
 * Do not delete this comment block. Respect others' work!
 */

#include "SvenBXT.h"
#include "metahook_emulation.hpp"

void CMHSvenBXT::Init(void* _MetaHookAPI, void* _Interface, void* _Save) {
}

void CMHSvenBXT::Shutdown() {
}

void CMHSvenBXT::LoadEngine(void* _Engfuncs) {
	//g_lpEngfuncs = indirect_cast<decltype(g_lpEngfuncs)>(_Engfuncs);
}

void CMHSvenBXT::LoadClient(void* _ExportFunc) {
}

void CMHSvenBXT::ExitGame(int _Result) {
}

EXPOSE_SINGLE_INTERFACE(CMHSvenBXT, CMHSvenBXT, METAHOOK_PLUGIN_API_VERSION_V3);