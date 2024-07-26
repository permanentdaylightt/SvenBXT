/**
 * Copyright - xWhitey, 2024.
 * svenmod_emulation.cpp - actual implementation of the emulation system
 *
 * Lightning a.k.a. lightning.tech (Sven Co-op) source file
 * Authors: xWhitey. Refer to common.hpp file for dependencies and their authors.
 * Do not delete this comment block. Respect others' work!
 */

#include "SvenBXT.h"
#include "svenmod_emulation.hpp"

CSMSvenBXT g_SMSvenBXT;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CSMSvenBXT, IClientPlugin, "ClientPlugin002", g_SMSvenBXT);

CSMSvenBXT* g_lpSMSvenBXT = &g_SMSvenBXT;

api_version_t CSMSvenBXT::GetAPIVersion() {
	return { (4), (0) };
}

bool CSMSvenBXT::Load(CreateInterfaceFn _Factory, void* _SvenModAPI, void* _Unused) {
	return true;
}

void CSMSvenBXT::PostLoad(bool _GlobalLoad) {}

void CSMSvenBXT::Unload() {
}

bool CSMSvenBXT::Pause() {
	return false;
}

void CSMSvenBXT::Unpause() {}

void CSMSvenBXT::OnFirstClientdataReceived(void *pcldata, float flTime) {

}

void CSMSvenBXT::OnBeginLoading() {

}

void CSMSvenBXT::OnEndLoading() {

}

void CSMSvenBXT::OnDisconnect() {

}

void CSMSvenBXT::GameFrame(void*, double, bool) {}

PLUGIN_RESULT CSMSvenBXT::Draw() {
	return PLUGIN_RESULT::PLUGIN_CONTINUE;
}

PLUGIN_RESULT CSMSvenBXT::DrawHUD(float time, int intermission) {
	return PLUGIN_RESULT::PLUGIN_CONTINUE;
}

const char* CSMSvenBXT::GetName() {
	return "SvenBXT";
}

const char* CSMSvenBXT::GetAuthor() {
	return "ScriptedSnark";
}

const char* CSMSvenBXT::GetVersion() {
	return SVENBXT_VERSION;
}

const char* CSMSvenBXT::GetDescription() {
	return "an advanced utility mod for Sven Co-op providing speedrunning tools";
}

const char* CSMSvenBXT::GetURL() {
	return SVENBXT_GITHUB_URL;
}

const char* CSMSvenBXT::GetDate() {
	return __TIMESTAMP__;
}

const char* CSMSvenBXT::GetLogTag() {
	return "SvenBXT";
}

enum
{
	IFACE_OK = 0,
	IFACE_FAILED
};

extern "C" __declspec(dllexport) void* CreateInterface(const char* _lpszName,int* _lpReturnCode) {
	InterfaceReg *pCur;

	for (pCur = InterfaceReg::s_pInterfaceRegs; pCur; pCur = pCur->m_pNext)
	{
		if (!strcmp(pCur->m_pName, _lpszName))
		{
			if (_lpReturnCode)
				*_lpReturnCode = IFACE_OK;

			return pCur->m_CreateFn();
		}
	}

	if (_lpReturnCode)
		*_lpReturnCode = IFACE_FAILED;

	return NULL;
}