#ifdef HUD_H_RECURSE_GUARD
#error Recursive header files inclusion detected in hud.h
#else // HUD_H_RECURSE_GUARD

#define HUD_H_RECURSE_GUARD

#ifndef HUD_H_GUARD
#define HUD_H_GUARD
#pragma once

#ifdef __cplusplus

#define DHN_DRAWZERO 1
#define DHN_2DIGITS 2
#define DHN_3DIGITS 4

#define HUD_ACTIVE (1 << 0)	
#define HUD_INTERMISSION (1 << 1) 
#define HUD_ALWAYSRENDER (1 << 2)

#define MAX_SPRITE_NAME_LENGTH 24

#define SVEN_HUD_COLOR 100, 130, 200

// ScreenHeight returns the height of the screen, in pixels
#define ScreenHeight (gBXTHud.m_scrinfo.iHeight)
// ScreenWidth returns the width of the screen, in pixels
#define ScreenWidth (gBXTHud.m_scrinfo.iWidth)
// CharHeight returns the height of the char, in pixels
#define CharHeight (gBXTHud.m_scrinfo.iCharHeight)

#define NumberWidth (gBXTHud.GetSpriteRect(gBXTHud.m_HUD_number_0).right - gBXTHud.GetSpriteRect(gBXTHud.m_HUD_number_0).left)
#define NumberHeight (gBXTHud.GetSpriteRect(gBXTHud.m_HUD_number_0).bottom - gBXTHud.GetSpriteRect(gBXTHud.m_HUD_number_0).top)

//
//-----------------------------------------------------
//
class CBXTHudBase
{
public:
	int m_iFlags; // active, moving,
	virtual int Init(void) { return 0; }
	virtual int VidInit(void) { return 0; }
	virtual int Draw(float flTime) { return 0; }
	virtual void Think(void) { return; }
	virtual void Reset(void) { return; }
};

class CBXTHud
{
private:
	bool m_bInitializedHUD;
	std::vector<CBXTHudBase*> m_vecHudList;

	HSPRITE_HL m_hsprLogo;
	int m_iLogo;
	client_sprite_t* m_pSpriteList;
	int m_iSpriteCount;
	int m_iSpriteCountAllRes;

	// the memory for these arrays are allocated in the first call to CHud::VidInit(), when the hud.txt and associated sprites are loaded.
	// freed in ~CHud()
	HSPRITE_HL* m_rghSprites; /*[HUD_SPRITE_COUNT]*/ // the sprites loaded from hud.txt
	wrect_t* m_rgrcRects;							 /*[HUD_SPRITE_COUNT]*/
	char* m_rgszSpriteNames;						 /*[HUD_SPRITE_COUNT][MAX_SPRITE_NAME_LENGTH]*/

public:
	int GetSpriteIndex(const char* SpriteName);
	void GetPosition(cvar_t* offset, cvar_t* anchor, int* x, int* y, int rx, int ry);

	void Init(void);
	void VidInit(void);
	void Think(void);
	int RedrawAlwaysVisibleElements(float flTime);
	int Redraw(float flTime, int intermission);
	int DrawHudNumber(int x, int y, int iFlags, int iNumber, int r, int g, int b);
	int DrawHudNumber(int x, int y, int number, int r, int g, int b);
	int DrawHudNumberCentered(int x, int y, int number, int r, int g, int b);
	int DrawHudNumberString(int xpos, int ypos, int iMinX, int iNumber, int r, int g, int b);
	int DrawHudNumberStringFixed(int xpos, int ypos, int iNumber, int r, int g, int b);
	int DrawMultilineString(int x, int y, std::string s);
	int DrawNumberTimer(int number, int x, int y, int fieldMinWidth);
	int DrawBitmap(int x, int y, const int bitmap[], int width, int height, int r, int g, int b);
	void DrawDot(int x, int y, int r, int g, int b);
	void DrawLine(int x, int y, int length, int r, int g, int b);
	int DrawNumberXT(int number, int x, int y, int r, int g, int b, int fieldMinWidth);
	int DrawNumberTimer(int number, int x, int y, int r, int g, int b, int fieldMinWidth);
	void DrawDecimalSeparator(int x, int y, int r, int g, int b);
	void DrawDecimalSeparator(int x, int y);
	void DrawColon(int x, int y, int r, int g, int b);
	void DrawColon(int x, int y);
	HSPRITE_HL GetSprite(int index)
	{
		return (index < 0) ? 0 : m_rghSprites[index];
	}

	wrect_t& GetSpriteRect(int index)
	{
		return m_rgrcRects[index];
	}

	template <typename T>
	inline T* RegisterHUDElement()
	{
		T* p = new T();
		m_vecHudList.push_back(p);
		return p;
	}

public:
	SCREENINFO m_scrinfo;
	int m_iRes;
	int m_HUD_number_0;
	int m_iFontHeight;
	cvar_t* hud_precision;
};

extern CBXTHud gBXTHud;

// Macros to hook function calls into the HUD object
#define HOOK_MESSAGE(x) g_lpEngfuncs->HookUserMsg(#x, __MsgFunc_##x);

#define DECLARE_MESSAGE(y, x)                                     \
	int __MsgFunc_##x(const char* pszName, int iSize, void* pbuf) \
	{                                                             \
		return gBXTHud.y.MsgFunc_##x(pszName, iSize, pbuf);       \
	}


#define HOOK_COMMAND(x, y) g_lpEngfuncs->AddCommand(x, __CmdFunc_##y);
#define DECLARE_COMMAND(y, x)    \
	void __CmdFunc_##x(void)     \
	{                            \
		gBXTHud.y.UserCmd_##x(); \
	}

inline float CVAR_GET_FLOAT(const char* x) { return g_lpEngfuncs->GetCvarFloat(x); }
inline char* CVAR_GET_STRING(const char* x) { return g_lpEngfuncs->GetCvarString(x); }
inline struct cvar_s* CVAR_CREATE(const char* cv, const char* val, const int flags) { return g_lpEngfuncs->RegisterVariable(cv, val, flags); }

#define SPR_Load (*g_lpEngfuncs->SPR_Load)
#define SPR_Set (*g_lpEngfuncs->SPR_Set)
#define SPR_Frames (*g_lpEngfuncs->SPR_Frames)
#define SPR_GetList (*g_lpEngfuncs->SPR_GetList)

// SPR_Draw  draws a the current sprite as solid
#define SPR_Draw (*g_lpEngfuncs->SPR_Draw)
// SPR_DrawHoles  draws the current sprites,  with color index255 not drawn (transparent)
#define SPR_DrawHoles (*g_lpEngfuncs->SPR_DrawHoles)
// SPR_DrawAdditive  adds the sprites RGB values to the background  (additive transulency)
#define SPR_DrawAdditive (*g_lpEngfuncs->SPR_DrawAdditive)

// SPR_EnableScissor  sets a clipping rect for HUD sprites.  (0,0) is the top-left hand corner of the screen.
#define SPR_EnableScissor (*g_lpEngfuncs->SPR_EnableScissor)
// SPR_DisableScissor  disables the clipping rect
#define SPR_DisableScissor (*g_lpEngfuncs->SPR_DisableScissor)
//
#define FillRGBA (*g_lpEngfuncs->FillRGBA)

#define BASE_XRES 640.f

// use this to project world coordinates to screen coordinates
#define XPROJECT(x) ((1.0f + (x)) * ScreenWidth * 0.5f)
#define YPROJECT(y) ((1.0f - (y)) * ScreenHeight * 0.5f)

static inline float XRES(float x)
{
	return x * ScreenWidth / 640;
}

static inline float YRES(float y)
{
	return y * ScreenHeight / 480;
}

#define ServerCmd (*g_lpEngfuncs->ServerCmd)
#define EngineClientCmd (*g_lpEngfuncs->ClientCmd)
#define SetCrosshair (*g_lpEngfuncs->SetCrosshair)
#define AngleVectors (*g_lpEngfuncs->AngleVectors)

#define VectorSubtract(a, b, c)   \
	{                             \
		(c)[0] = (a)[0] - (b)[0]; \
		(c)[1] = (a)[1] - (b)[1]; \
		(c)[2] = (a)[2] - (b)[2]; \
	}
#define VectorAdd(a, b, c)        \
	{                             \
		(c)[0] = (a)[0] + (b)[0]; \
		(c)[1] = (a)[1] + (b)[1]; \
		(c)[2] = (a)[2] + (b)[2]; \
	}
#define VectorCopy(a, b) \
	{                    \
		(b)[0] = (a)[0]; \
		(b)[1] = (a)[1]; \
		(b)[2] = (a)[2]; \
	}


// Gets the height & width of a sprite,  at the specified frame
inline int SPR_Height(HSPRITE_HL x, int f) { return g_lpEngfuncs->SPR_Height(x, f); }
inline int SPR_Width(HSPRITE_HL x, int f) { return g_lpEngfuncs->SPR_Width(x, f); }

static size_t count_digits(int n)
{
	size_t result = 0;

	do
	{
		++result;
	} while ((n /= 10) != 0);

	return result;
}


#else //!__cplusplus
#error C++ compiler required to compile hud.h
#endif //__cplusplus

#endif // HUD_H_GUARD

#undef HUD_H_RECURSE_GUARD
#endif // HUD_H_RECURSE_GUARD
