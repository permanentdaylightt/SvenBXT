#ifdef CDLL_INT_H_RECURSE_GUARD
#error Recursive header files inclusion detected in cdll_int.h
#else //CDLL_INT_H_RECURSE_GUARD

#define CDLL_INT_H_RECURSE_GUARD

#ifndef CDLL_INT_H_GUARD
#define CDLL_INT_H_GUARD
#pragma once

#ifdef __cplusplus

extern cvar_t* hud_bordersize;

void CL_Initialize();

// From hl_weapons
typedef void (*_HUD_PostRunCmd)(struct local_state_s* from, struct local_state_s* to, struct usercmd_s* cmd, int runfuncs, double time, unsigned int random_seed);

// From cdll_int
typedef int (*_Initialize)(cl_enginefunc_t* pEnginefuncs, int iVersion);
typedef int (*_HUD_VidInit)(void);
typedef void (*_HUD_Init)(void);
typedef int (*_HUD_Redraw)(float flTime, int intermission);
typedef int (*_HUD_UpdateClientData)(client_data_t* cdata, float flTime);
typedef void (*_HUD_Reset)(void);
typedef void (*_HUD_PlayerMove)(struct playermove_s* ppmove, int server);
typedef void (*_HUD_PlayerMoveInit)(struct playermove_s* ppmove);
typedef char (*_HUD_PlayerMoveTexture)(char* name);
typedef int (*_HUD_ConnectionlessPacket)(const struct netadr_s* net_from, const char* args, char* response_buffer, int* response_buffer_size);
typedef int (*_HUD_GetHullBounds)(int hullnumber, float* mins, float* maxs);
typedef void (*_HUD_Frame)(double time);
typedef void (*_HUD_VoiceStatus)(int entindex, qboolean bTalking);
typedef void (*_HUD_DirectorMessage)(int iSize, void* pbuf);
typedef void (*_HUD_ChatInputPosition)(int* x, int* y);

// From demo
typedef void (*_Demo_ReadBuffer)(int size, unsigned char* buffer);

// From entity
typedef int (*_HUD_AddEntity)(int type, struct cl_entity_s* ent, const char* modelname);
typedef void (*_HUD_CreateEntities)(void);
typedef void (*_HUD_StudioEvent)(const struct mstudioevent_s* event, const struct cl_entity_s* entity);
typedef void (*_HUD_TxferLocalOverrides)(struct entity_state_s* state, const struct clientdata_s* client);
typedef void (*_HUD_ProcessPlayerState)(struct entity_state_s* dst, const struct entity_state_s* src);
typedef void (*_HUD_TxferPredictionData)(struct entity_state_s* ps, const struct entity_state_s* pps, struct clientdata_s* pcd, const struct clientdata_s* ppcd, struct weapon_data_s* wd, const struct weapon_data_s* pwd);
typedef void (*_HUD_TempEntUpdate)(double frametime, double client_time, double cl_gravity, struct tempent_s** ppTempEntFree, struct tempent_s** ppTempEntActive, int (*Callback_AddVisibleEntity)(struct cl_entity_s* pEntity), void (*Callback_TempEntPlaySound)(struct tempent_s* pTemp, float damp));
typedef struct cl_entity_s* (*_HUD_GetUserEntity)(int index);

// From in_camera
typedef void (*_CAM_Think)(void);
typedef int (*_CL_IsThirdPerson)(void);
typedef void (*_CL_CameraOffset)(float* ofs);

// From input
typedef struct kbutton_s* (*_KB_Find)(const char* name);
typedef void (*_CL_CreateMove)(float frametime, struct usercmd_s* cmd, int active);
typedef void (*_HUD_Shutdown)(void);
typedef int (*_HUD_Key_Event)(int eventcode, int keynum, const char* pszCurrentBinding);

// From inputw32
typedef void (*_IN_ActivateMouse)(void);
typedef void (*_IN_DeactivateMouse)(void);
typedef void (*_IN_MouseEvent)(int mstate);
typedef void (*_IN_Accumulate)(void);
typedef void (*_IN_ClearStates)(void);

// From tri
typedef void (*_HUD_DrawNormalTriangles)(void);
typedef void (*_HUD_DrawTransparentTriangles)(void);

// From view
typedef void (*_V_CalcRefdef)(struct ref_params_s* pparams);

// From GameStudioModelRenderer
typedef int (*_HUD_GetStudioModelInterface)(int version, struct r_studio_interface_s** ppinterface, struct engine_studio_api_s* pstudio);

extern _HUD_PostRunCmd ORIG_HUD_PostRunCmd;
extern _Initialize ORIG_Initialize;
extern _HUD_VidInit ORIG_HUD_VidInit;
extern _HUD_Init ORIG_HUD_Init;
extern _HUD_Redraw ORIG_HUD_Redraw;
extern _HUD_UpdateClientData ORIG_HUD_UpdateClientData;
extern _HUD_Reset ORIG_HUD_Reset;
extern _HUD_PlayerMove ORIG_HUD_PlayerMove;
extern _HUD_PlayerMoveInit ORIG_HUD_PlayerMoveInit;
extern _HUD_PlayerMoveTexture ORIG_HUD_PlayerMoveTexture;
extern _HUD_ConnectionlessPacket ORIG_HUD_ConnectionlessPacket;
extern _HUD_GetHullBounds ORIG_HUD_GetHullBounds;
extern _HUD_Frame ORIG_HUD_Frame;
extern _HUD_VoiceStatus ORIG_HUD_VoiceStatus;
extern _HUD_DirectorMessage ORIG_HUD_DirectorMessage;
extern _HUD_ChatInputPosition ORIG_HUD_ChatInputPosition;
extern _Demo_ReadBuffer ORIG_Demo_ReadBuffer;
extern _HUD_AddEntity ORIG_HUD_AddEntity;
extern _HUD_CreateEntities ORIG_HUD_CreateEntities;
extern _HUD_StudioEvent ORIG_HUD_StudioEvent;
extern _HUD_TxferLocalOverrides ORIG_HUD_TxferLocalOverrides;
extern _HUD_ProcessPlayerState ORIG_HUD_ProcessPlayerState;
extern _HUD_TxferPredictionData ORIG_HUD_TxferPredictionData;
extern _HUD_TempEntUpdate ORIG_HUD_TempEntUpdate;
extern _HUD_GetUserEntity ORIG_HUD_GetUserEntity;
extern _CAM_Think ORIG_CAM_Think;
extern _CL_IsThirdPerson ORIG_CL_IsThirdPerson;
extern _CL_CameraOffset ORIG_CL_CameraOffset;
extern _KB_Find ORIG_KB_Find;
extern _CL_CreateMove ORIG_CL_CreateMove;
extern _HUD_Shutdown ORIG_HUD_Shutdown;
extern _HUD_Key_Event ORIG_HUD_Key_Event;
extern _IN_ActivateMouse ORIG_IN_ActivateMouse;
extern _IN_DeactivateMouse ORIG_IN_DeactivateMouse;
extern _IN_MouseEvent ORIG_IN_MouseEvent;
extern _IN_Accumulate ORIG_IN_Accumulate;
extern _IN_ClearStates ORIG_IN_ClearStates;
extern _HUD_DrawNormalTriangles ORIG_HUD_DrawNormalTriangles;
extern _HUD_DrawTransparentTriangles ORIG_HUD_DrawTransparentTriangles;
extern _V_CalcRefdef ORIG_V_CalcRefdef;
extern _HUD_GetStudioModelInterface ORIG_HUD_GetStudioModelInterface;

#else //!__cplusplus
#error C++ compiler required to compile cdll_int.h
#endif //__cplusplus

#endif //CDLL_INT_H_GUARD

#undef CDLL_INT_H_RECURSE_GUARD
#endif //CDLL_INT_H_RECURSE_GUARD