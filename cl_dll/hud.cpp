#include "SvenBXT.h"

CBXTHud gBXTHud;

// from OpenAG
static constexpr int ten_powers[] = {
	1,
	10,
	100,
	1000,
	10000,
	100000,
	1000000,
	10000000,
	100000000,
	1000000000};

// GetSpriteIndex()
// searches through the sprite list loaded from hud.txt for a name matching SpriteName
// returns an index into the gHUD.m_rghSprites[] array
// returns 0 if sprite not found
int CBXTHud::GetSpriteIndex(const char* SpriteName)
{
	// look through the loaded sprite name list for SpriteName
	for (int i = 0; i < m_iSpriteCount; i++)
	{
		if (strncmp(SpriteName, m_rgszSpriteNames + (i * MAX_SPRITE_NAME_LENGTH), MAX_SPRITE_NAME_LENGTH) == 0)
			return i;
	}

	return -1; // invalid sprite
}

void CBXTHud::Init(void)
{
	RegisterHUDElement<CHudSpeedometer>();

	for (CBXTHudBase* i : m_vecHudList)
	{
		i->Init();
	}
}

void CBXTHud::VidInit(void)
{
	m_scrinfo.iSize = sizeof(m_scrinfo);
	g_lpEngfuncs->GetScreenInfo(&m_scrinfo);

	if (ScreenWidth < 640)
		m_iRes = 320;
	else
		m_iRes = 640;

	// Only load this once
	if (!m_pSpriteList)
	{
		// we need to load the hud.txt, and all sprites within
		m_pSpriteList = SPR_GetList("sprites/hud.txt", &m_iSpriteCountAllRes);

		if (m_pSpriteList)
		{
			// count the number of sprites of the appropriate res
			m_iSpriteCount = 0;
			client_sprite_t* p = m_pSpriteList;
			int j;
			for (j = 0; j < m_iSpriteCountAllRes; j++)
			{
				if (p->iRes == m_iRes)
					m_iSpriteCount++;
				p++;
			}

			// allocated memory for sprite handle arrays
			m_rghSprites = new HSPRITE_HL[m_iSpriteCount];
			m_rgrcRects = new wrect_t[m_iSpriteCount];
			m_rgszSpriteNames = new char[m_iSpriteCount * MAX_SPRITE_NAME_LENGTH];

			p = m_pSpriteList;
			int index = 0;
			for (j = 0; j < m_iSpriteCountAllRes; j++)
			{
				if (p->iRes == m_iRes)
				{
					char sz[256];
					sprintf(sz, "sprites/%s.spr", p->szSprite);
					m_rghSprites[index] = SPR_Load(sz);
					m_rgrcRects[index] = p->rc;
					strncpy(&m_rgszSpriteNames[index * MAX_SPRITE_NAME_LENGTH], p->szName, MAX_SPRITE_NAME_LENGTH);

					index++;
				}

				p++;
			}
		}
	}
	else
	{
		// we have already have loaded the sprite reference from hud.txt, but
		// we need to make sure all the sprites have been loaded (we've gone through a transition, or loaded a save game)
		client_sprite_t* p = m_pSpriteList;
		int index = 0;
		for (int j = 0; j < m_iSpriteCountAllRes; j++)
		{
			if (p->iRes == m_iRes)
			{
				char sz[256];
				sprintf(sz, "sprites/%s.spr", p->szSprite);
				m_rghSprites[index] = SPR_Load(sz);
				index++;
			}

			p++;
		}
	}

	// assumption: number_1, number_2, etc, are all listed and loaded sequentially
	m_HUD_number_0 = GetSpriteIndex("number_0");

	m_iFontHeight = m_rgrcRects[m_HUD_number_0].bottom - m_rgrcRects[m_HUD_number_0].top;

	for (CBXTHudBase* i : m_vecHudList)
	{
		i->VidInit();
	}
}

int CBXTHud::Redraw(float flTime, int intermission)
{
	for (CBXTHudBase* i : m_vecHudList)
	{
		if (!intermission)
		{
			if (i->m_iFlags & HUD_ACTIVE)
				i->Draw(flTime);
		}
		else
		{ // it's an intermission,  so only draw hud elements that are set to draw during intermissions
			if (i->m_iFlags & HUD_INTERMISSION)
				i->Draw(flTime);
		}
	}

	return 1;
}

// should be in hud_redraw.cpp

int CBXTHud::DrawHudNumber(int x, int y, int iFlags, int iNumber, int r, int g, int b)
{
	int iWidth = GetSpriteRect(m_HUD_number_0).right - GetSpriteRect(m_HUD_number_0).left;
	int k;

	if (iNumber > 0)
	{
		// SPR_Draw 100's
		if (iNumber >= 100)
		{
			k = iNumber / 100;
			SPR_Set(GetSprite(m_HUD_number_0 + k), r, g, b);
			SPR_DrawAdditive(0, x, y, &GetSpriteRect(m_HUD_number_0 + k));
			x += iWidth;
		}
		else if (iFlags & (DHN_3DIGITS))
		{
			// SPR_DrawAdditive( 0, x, y, &rc );
			x += iWidth;
		}

		// SPR_Draw 10's
		if (iNumber >= 10)
		{
			k = (iNumber % 100) / 10;
			SPR_Set(GetSprite(m_HUD_number_0 + k), r, g, b);
			SPR_DrawAdditive(0, x, y, &GetSpriteRect(m_HUD_number_0 + k));
			x += iWidth;
		}
		else if (iFlags & (DHN_3DIGITS | DHN_2DIGITS))
		{
			// SPR_DrawAdditive( 0, x, y, &rc );
			x += iWidth;
		}

		// SPR_Draw ones
		k = iNumber % 10;
		SPR_Set(GetSprite(m_HUD_number_0 + k), r, g, b);
		SPR_DrawAdditive(0, x, y, &GetSpriteRect(m_HUD_number_0 + k));
		x += iWidth;
	}
	else if (iFlags & DHN_DRAWZERO)
	{
		SPR_Set(GetSprite(m_HUD_number_0), r, g, b);

		// SPR_Draw 100's
		if (iFlags & (DHN_3DIGITS))
		{
			// SPR_DrawAdditive( 0, x, y, &rc );
			x += iWidth;
		}

		if (iFlags & (DHN_3DIGITS | DHN_2DIGITS))
		{
			// SPR_DrawAdditive( 0, x, y, &rc );
			x += iWidth;
		}

		// SPR_Draw ones

		SPR_DrawAdditive(0, x, y, &GetSpriteRect(m_HUD_number_0));
		x += iWidth;
	}

	return x;
}

int CBXTHud::DrawHudNumber(int x, int y, int number, int r, int g, int b)
{
	size_t digit_width = GetSpriteRect(m_HUD_number_0).right - GetSpriteRect(m_HUD_number_0).left;
	size_t digit_count = count_digits(number);

	for (int i = digit_count; i > 0; --i)
	{
		int digit = number / ten_powers[i - 1];

		SPR_Set(GetSprite(m_HUD_number_0 + digit), r, g, b);
		SPR_DrawAdditive(0, x, y, &GetSpriteRect(m_HUD_number_0 + digit));
		x += digit_width;

		number -= digit * ten_powers[i - 1];
	}

	return x;
}

int CBXTHud::DrawHudNumberCentered(int x, int y, int number, int r, int g, int b)
{
	size_t digit_width = GetSpriteRect(m_HUD_number_0).right - GetSpriteRect(m_HUD_number_0).left;
	size_t digit_count = count_digits(number);

	return DrawHudNumber(x - (digit_width * digit_count) / 2, y, number, r, g, b);
}
