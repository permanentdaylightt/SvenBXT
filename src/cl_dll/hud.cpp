#include "SvenBXT.h"

#undef max
#undef min

CBXTHud gBXTHud;

// some code is from HL SDK, OpenAG, BunnymodXT

constexpr int ten_powers[] = {
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

void CBXTHud::GetPosition(cvar_t* offset, cvar_t* anchor, int* x, int* y, int rx = 0, int ry = 0)
{
	std::istringstream iss;

	if (offset && offset->string[0])
	{
		iss.str(offset->string);
		iss >> rx >> ry;
		iss.str(std::string());
		iss.clear();
	}

	iss.str(anchor->string);
	float w = 0, h = 0;
	iss >> w >> h;

	rx += static_cast<int>(w * ScreenWidth);
	ry += static_cast<int>(h * ScreenHeight);

	if (x) *x = rx;
	if (y) *y = ry;
}

void CBXTHud::Init(void)
{
	hud_precision = CVAR_CREATE("sbxt_hud_precision", "6", 0);

	RegisterHUDElement<CHudSpeedometer>();
	RegisterHUDElement<CHudViewangles>();
	RegisterHUDElement<CHudOrigin>();
	RegisterHUDElement<CHudTimer>();

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

int CBXTHud::DrawMultilineString(int x, int y, std::string s)
{
	int max_new_x = 0;

	while (s.size() > 0)
	{
		size_t pos = s.find('\n');

		int new_x = g_lpEngfuncs->DrawConsoleString(x, y, const_cast<char*>(s.substr(0, pos).c_str()));
		max_new_x = std::max(new_x, max_new_x);
		y += CharHeight;

		if (pos != std::string::npos)
			s = s.substr(pos + 1, std::string::npos);
		else
			s.erase();
	};

	return max_new_x;
}

int CBXTHud::DrawBitmap(int x, int y, const int bitmap[], int width, int height, int r, int g, int b)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			FillRGBA(x + j, y + i, 1, 1, r, g, b, bitmap[i * width + j]);

	return width;
}

void CBXTHud::DrawDot(int x, int y, int r, int g, int b)
{
	const int Dot320[] = {
		143, 199, 122,
		255, 255, 218,
		120, 169, 95};

	const int Dot640[] = {
		21, 114, 128, 128, 83, 21,
		150, 255, 255, 255, 255, 104,
		239, 255, 255, 255, 255, 192,
		226, 255, 255, 255, 255, 165,
		114, 255, 255, 255, 255, 65,
		29, 43, 89, 89, 29, 29};

	if (ScreenWidth < 640)
		DrawBitmap(x, y, Dot320, 3, 3, r, g, b);
	else
		DrawBitmap(x, y, Dot640, 6, 6, r, g, b);
}

void CBXTHud::DrawLine(int x, int y, int length, int r, int g, int b)
{
	if ((ScreenWidth < 640 && length < 3) || length < 5)
	{
		// might as well draw a dot
		DrawDot(x, y, r, g, b);
		return;
	}


	const int Line640_left[] = {
		21, 114,
		150, 255,
		239, 255,
		226, 255,
		114, 255,
		29, 43};

	const int Line640_repeat[] = {
		128,
		255,
		255,
		255,
		255,
		89};

	const int Line640_Right[] = {
		83, 21,
		255, 104,
		255, 192,
		255, 165,
		255, 65,
		29, 29};

	const int Line320_left[] = {
		143,
		255,
		120,
	};

	const int Line320_repeat[] = {
		199,
		255,
		169,
	};

	const int Line320_Right[] = {
		122,
		218,
		95};

	const int* line_left;
	const int* line_repeat;
	const int* line_right;
	int linesprite_height;
	int linesprite_width;

	if (ScreenWidth <= 640)
	{
		line_left = Line320_left;
		line_repeat = Line320_repeat;
		line_right = Line320_Right;
		linesprite_height = 3;
		linesprite_width = 1;
	}
	else
	{
		line_left = Line640_left;
		line_repeat = Line640_repeat;
		line_right = Line640_Right;
		linesprite_height = 6;
		linesprite_width = 2;
	}

	y -= linesprite_height / 2;

	x += DrawBitmap(x, y, line_left, linesprite_width, linesprite_height, r, g, b);

	for (int xOffset = 0; xOffset < length - linesprite_width * 2; xOffset++)
	{
		x += DrawBitmap(x, y, line_repeat, 1, linesprite_height, r, g, b);
	}

	DrawBitmap(x, y, line_right, linesprite_width, linesprite_height, r, g, b);
}

int CBXTHud::DrawNumberXT(int number, int x, int y, int r, int g, int b, int fieldMinWidth)
{
	if (number < 0)
	{
		if (number == std::numeric_limits<int>::min())
		{
			number = 0;
		}
		else
		{
			number = abs(number);
			DrawLine(x - NumberWidth, y + NumberHeight / 2, NumberWidth, r, g, b);
		}
	}

	static_assert(sizeof(int) >= 4, "Int less than 4 bytes in size is not supported.");

	int digits[10] = {0};
	int i;
	for (i = 0; i < 10; ++i)
	{
		if (number == 0)
			break;

		digits[i] = number % 10;
		number /= 10;
	}

	for (; fieldMinWidth > 10; --fieldMinWidth)
	{
		DrawHudNumber(x, y, 0, r, g, b);
		x += NumberWidth;
	}
	if (fieldMinWidth > i)
		i = fieldMinWidth;

	for (int j = i; j > 0; --j)
	{
		DrawHudNumber(x, y, digits[j - 1], r, g, b);
		x += NumberWidth;
	}

	return x;
}

int CBXTHud::DrawNumberTimer(int number, int x, int y, int fieldMinWidth)
{
	return DrawNumberXT(number, x, y, SVEN_HUD_COLOR, fieldMinWidth);
}

int CBXTHud::DrawNumberTimer(int number, int x, int y, int r, int g, int b, int fieldMinWidth)
{
	return DrawNumberXT(number, x, y, r, g, b, fieldMinWidth);
}

void CBXTHud::DrawDecimalSeparator(int x, int y, int r, int g, int b)
{
	x += (NumberWidth - 6) / 2;
	y += NumberHeight - 5;
	DrawDot(x + 1, y, r, g, b);
}

void CBXTHud::DrawDecimalSeparator(int x, int y)
{
	return DrawDecimalSeparator(x, y, SVEN_HUD_COLOR);
}

void CBXTHud::DrawColon(int x, int y, int r, int g, int b)
{
	x += (NumberWidth - 6) / 2;
	DrawDot(x + 1, y + 2, r, g, b);
	y += NumberHeight - 5;
	DrawDot(x + 1, y - 2, r, g, b);
}

void CBXTHud::DrawColon(int x, int y)
{
	return DrawColon(x, y, SVEN_HUD_COLOR);
}