#pragma once

#include "Math.h"

struct OamAttr
{
	// more OamAttr documentation here: https://problemkaputt.de/gbatek.htm#lcdobjoamattributes

	enum Attr0 : u16
	{
		Y_COORDINATE         = 0xff << 0,
		ROTATION_SCALE_FLAG  = 0x1  << 8,  // 0: off, 1: on
		DOUBLE_SIZE_FLAG     = 0x1  << 9,  // 0: normal, 1: double        (when ROTATION_SCALE_FLAG == 1)
		OBJ_DISABLE          = 0x1  << 9,  // 0: normal, 1: not displayed (when ROTATION_SCALE_FLAG == 0)
		OBJ_MODE             = 0x3  << 10, // 3: prohibited
			NORMAL           = 0x0  << 10,
			SEMI_TRANSPARENT = 0x1  << 10,
			OBJ_WINDOW       = 0x2  << 10,
		OBJ_MOSAIC           = 0x1  << 12, // 0: off, 1: on
		USES_256_PALETTE     = 0x1  << 13, // 0: 16/16, 1: 256/1
		OBJ_SHAPE            = 0x3  << 14, // 3: prohibited
			SQUARE           = 0x0  << 14,
			HORIZONTAL       = 0x1  << 14,
			VERTICAL         = 0x2  << 14,
	};

	enum Attr1 : u16
	{
		X_COORDINATE               = 0x1ff << 0,
		ROTATION_SCALING_PARAMETER = 0x1f  << 9,  // when ROTATION_SCALE_FLAG == 1
		HORIZONTAL_FLIP            = 0x1   << 12, // when ROTATION_SCALE_FLAG == 0
		VERTICAL_FLIP              = 0x1   << 13, // when ROTATION_SCALE_FLAG == 0
		OBJ_SIZE                   = 0x3   << 14, // depends on OBJ_SHAPE:  SQUARE  HORIZONTAL  VERTICAL
			OBJ_SIZE_0             = 0x0   << 14, //                           8x8        16x8      8x16
			OBJ_SIZE_1             = 0x1   << 14, //                         16x16        32x8      8x32
			OBJ_SIZE_2             = 0x2   << 14, //                         32x32       32x16     16x32
			OBJ_SIZE_3             = 0x3   << 14, //                         64x64       64x32     32x64
	};

	enum Attr2 : u16
	{
		TILE_NUMBER    = 0x3ff << 0,
		PRIORITY       = 0x3   << 10, // relative to BG (0 = highest)
		PALETTE_NUMBER = 0xf   << 12, // not used in 256/1 mode
	};

	enum Attr3 : u16
	{
		LAST = 0xffff,
	};

    u16 attr0;
    u16 attr1;
    u16 attr2;
    u16 attr3 = 0;
};

namespace OAM
{
	// internal functions
	void Render(bool sub, OamAttr* data, s32 x, s32 y, s32 palette, s32 priority, Matrix2x2* affineMtx);
	void Render(bool sub, OamAttr* data, s32 x, s32 y, s32 palette, s32 priority, Fix12i scale, s32 rotation);
	void Render(bool sub, OamAttr* data, s32 x, s32 y, s32 palette, s32 priority, Fix12i scaleX, Fix12i scaleY, s32 rotation, s32 mode);
	u8 GetObjWidth(s32 shape, s32 size);
	u8 GetObjHeight(s32 shape, s32 size);
	void LoadAffineParams(OamAttr* data, s32* affineSet, Matrix2x2* affineMtx);

	// indexing: [shape][size] (shape 4 is prohibited)
	extern u8 objWidth[3][4];
	extern u8 objHeight[3][4];
	extern bool subOAMDisabled;
	extern s32 curAffineSetMain;
	extern s32 curAffineSetSub;
	extern s32 objCountMain;
	extern s32 objCountSub;
	extern OamAttr bufferMain[128];
	extern OamAttr bufferSub[128];

	// public functions
	void Reset(); // Resets the internal buffer
	void Flush(); // Flushes the cache on the internal buffer
	void Load();  // Loads the internal buffer to the OAM
	void RenderSub(OamAttr* data, s32 x, s32 y);
	void RenderSub(OamAttr* data, s32 x, s32 y, s32 palette, s32 priority);
	void EnableSubOAM(); // Enables the sub engine OAM

	// Disables the sub engine OAM
	[[gnu::always_inline]]
	inline void DisableSubOAM()
	{
		subOAMDisabled = true;
	}

	extern OamAttr COIN[];
	extern OamAttr POWER_STAR[];
	extern OamAttr TIMES[];

	extern OamAttr* NUMBERS[20]; //first 10 are gold versions of 0-9, last 10 are red versions of 0-9
	extern OamAttr* LIFE_ICONS[4];

	// Stage and HUD icons
	extern OamAttr RED_COIN[];
	extern OamAttr SILVER_STAR[];
	extern OamAttr BOUNCING_ARROW[];
	extern OamAttr TIME[];
	extern OamAttr MINUTES[];
	extern OamAttr SECONDS[];
	extern OamAttr HEALTH_METER_BG[];

	// camera buttons
	extern OamAttr CAM_BUTTON_L[];
	extern OamAttr CAM_BUTTON_L_PRESSED[];
	extern OamAttr CAM_BUTTON_R[];
	extern OamAttr CAM_BUTTON_R_PRESSED[];
	extern OamAttr CAM_ZOOM_BUTTON[];
	extern OamAttr CAM_ZOOM_BUTTON_PRESSED[];
	extern OamAttr S_CAM_BUTTON_L[];
	extern OamAttr S_CAM_BUTTON_L_PRESSED[];
	extern OamAttr S_CAM_BUTTON_R[];
	extern OamAttr S_CAM_BUTTON_R_PRESSED[];
	extern OamAttr S_CAM_ZOOM_BUTTON[];
	extern OamAttr S_CAM_ZOOM_BUTTON_PRESSED[];

	extern OamAttr* HEALTH_METERS[9];
	extern OamAttr HEALTH_METER_0[];
	extern OamAttr HEALTH_METER_1[];
	extern OamAttr HEALTH_METER_2[];
	extern OamAttr HEALTH_METER_3[];
	extern OamAttr HEALTH_METER_4[];
	extern OamAttr HEALTH_METER_5[];
	extern OamAttr HEALTH_METER_6[];
	extern OamAttr HEALTH_METER_7[];
	extern OamAttr HEALTH_METER_8[];

	// Minimap icons
	extern OamAttr MM_ARROW[];
	extern OamAttr MM_RED_COIN[];
	extern OamAttr MM_SPIKE_BOMB[];

	extern OamAttr* MM_VS_PLAYER_ICONS[16];
	extern OamAttr MM_VS_YOSHI_M_CAP_ICON[];
	extern OamAttr MM_VS_YOSHI_L_CAP_ICON[];
	extern OamAttr MM_VS_YOSHI_W_CAP_ICON[];
	extern OamAttr MM_VS_YOSHI_ICON[];
	extern OamAttr MM_VS_RED_YOSHI_M_CAP_ICON[];
	extern OamAttr MM_VS_RED_YOSHI_L_CAP_ICON[];
	extern OamAttr MM_VS_RED_YOSHI_W_CAP_ICON[];
	extern OamAttr MM_VS_RED_YOSHI_ICON[];
	extern OamAttr MM_VS_BLUE_YOSHI_M_CAP_ICON[];
	extern OamAttr MM_VS_BLUE_YOSHI_L_CAP_ICON[];
	extern OamAttr MM_VS_BLUE_YOSHI_W_CAP_ICON[];
	extern OamAttr MM_VS_BLUE_YOSHI_ICON[];
	extern OamAttr MM_VS_YELLOW_YOSHI_M_CAP_ICON[];
	extern OamAttr MM_VS_YELLOW_YOSHI_L_CAP_ICON[];
	extern OamAttr MM_VS_YELLOW_YOSHI_W_CAP_ICON[];
	extern OamAttr MM_VS_YELLOW_YOSHI_ICON[];

	extern OamAttr* MM_VS_PLAYER_ICONS_S[16];
	extern OamAttr MM_VS_YOSHI_M_CAP_ICON_S[];
	extern OamAttr MM_VS_YOSHI_L_CAP_ICON_S[];
	extern OamAttr MM_VS_YOSHI_W_CAP_ICON_S[];
	extern OamAttr MM_VS_YOSHI_ICON_S[];
	extern OamAttr MM_VS_RED_YOSHI_M_CAP_ICON_S[];
	extern OamAttr MM_VS_RED_YOSHI_L_CAP_ICON_S[];
	extern OamAttr MM_VS_RED_YOSHI_W_CAP_ICON_S[];
	extern OamAttr MM_VS_RED_YOSHI_ICON_S[];
	extern OamAttr MM_VS_BLUE_YOSHI_M_CAP_ICON_S[];
	extern OamAttr MM_VS_BLUE_YOSHI_L_CAP_ICON_S[];
	extern OamAttr MM_VS_BLUE_YOSHI_W_CAP_ICON_S[];
	extern OamAttr MM_VS_BLUE_YOSHI_ICON_S[];
	extern OamAttr MM_VS_YELLOW_YOSHI_M_CAP_ICON_S[];
	extern OamAttr MM_VS_YELLOW_YOSHI_L_CAP_ICON_S[];
	extern OamAttr MM_VS_YELLOW_YOSHI_W_CAP_ICON_S[];
	extern OamAttr MM_VS_YELLOW_YOSHI_ICON_S[];

	extern OamAttr* MM_PLAYER_ICONS[16];
	extern OamAttr MM_MARIO_ICON[];
	extern OamAttr MM_MARIO_L_CAP_ICON[];
	extern OamAttr MM_MARIO_W_CAP_ICON[];
	extern OamAttr MM_MARIO_NO_CAP_ICON[];
	extern OamAttr MM_LUIGI_M_CAP_ICON[];
	extern OamAttr MM_LUIGI_ICON[];
	extern OamAttr MM_LUIGI_W_CAP_ICON[];
	extern OamAttr MM_LUIGI_NO_CAP_ICON[];
	extern OamAttr MM_WARIO_M_CAP_ICON[];
	extern OamAttr MM_WARIO_L_CAP_ICON[];
	extern OamAttr MM_WARIO_ICON[];
	extern OamAttr MM_WARIO_NO_CAP_ICON[];
	extern OamAttr MM_YOSHI_M_CAP_ICON[];
	extern OamAttr MM_YOSHI_L_CAP_ICON[];
	extern OamAttr MM_YOSHI_W_CAP_ICON[];
	extern OamAttr MM_YOSHI_ICON[];

	extern OamAttr* MM_STAR_MARKERS[8];
	extern OamAttr MM_SMALL_STAR[];
	extern OamAttr MM_SMALL_STAR_FADED[];
	extern OamAttr MM_SILVER_STAR[];
	extern OamAttr MM_SILVER_STAR_FADED[];
	extern OamAttr MM_STAR[];
	extern OamAttr MM_STAR_FADED[];
	extern OamAttr MM_TRANSPARENT_STAR[];
	extern OamAttr MM_TRANSPARENT_STAR_BRIGHT[];

	extern OamAttr* MM_STAR_KEYS[2];
	extern OamAttr MM_STAR_KEY[];
	extern OamAttr MM_STAR_KEY_BRIGHT[];

	// Stage icons (LevelClearScreen)
	extern OamAttr LC_CONGRATULATIONS[];
	extern OamAttr LC_HIGH_SCORE[];

	// Stage icons (PauseScreen)
	extern OamAttr PAUSE[];
	extern OamAttr VS_PAUSE[];
	extern OamAttr ARROW_POINTING_LEFT[];
	extern OamAttr ARROW_POINTING_RIGHT[];
	extern OamAttr SMALL_STAR_EMPTY[];
	extern OamAttr TINY_STAR[];
	extern OamAttr SMALL_ARROW_POINTING_LEFT[];
	extern OamAttr SMALL_ARROW_POINTING_RIGHT[];

	extern OamAttr* CONTROLLER_MODE_TEXTS[3];
	extern OamAttr STANDARD_MODE_TEXT[];
	extern OamAttr TOUCH_MODE_TEXT[];
	extern OamAttr DUAL_HAND_MODE_TEXT[];

	// Stage and HUD icons (VS mode)
	extern OamAttr VS_GET_THE_STAR[];
	extern OamAttr VS_GO[];
	extern OamAttr VS_NEW_STAR_APPEARED[];
	extern OamAttr VS_TIME[];
	extern OamAttr VS_TIME_UP[];

	extern OamAttr* VS_YELLOW_NUMBERS[10];
	extern OamAttr VS_YELLOW_NUMBER_0[];
	extern OamAttr VS_YELLOW_NUMBER_1[];
	extern OamAttr VS_YELLOW_NUMBER_2[];
	extern OamAttr VS_YELLOW_NUMBER_3[];
	extern OamAttr VS_YELLOW_NUMBER_4[];
	extern OamAttr VS_YELLOW_NUMBER_5[];
	extern OamAttr VS_YELLOW_NUMBER_6[];
	extern OamAttr VS_YELLOW_NUMBER_7[];
	extern OamAttr VS_YELLOW_NUMBER_8[];
	extern OamAttr VS_YELLOW_NUMBER_9[];

	extern OamAttr* VS_RED_NUMBERS[3];
	extern OamAttr VS_RED_NUMBER_3[];
	extern OamAttr VS_RED_NUMBER_2[];
	extern OamAttr VS_RED_NUMBER_1[];

	// StarSelect icons
	extern OamAttr SS_BIG_GRAY_STAR[];
	extern OamAttr SS_SMALL_GRAY_STAR[];
	extern OamAttr SS_YELLOW_ARROW_DOWN[];
	extern OamAttr SS_YELLOW_ARROW_RIGHT[];
	extern OamAttr SS_MARIO_HEAD[];
	extern OamAttr SS_LUIGI_HEAD[];
	extern OamAttr SS_WARIO_HEAD[];
	extern OamAttr SS_YOSHI_HEAD[];
	extern OamAttr SS_TOUCH_ME[];
	extern OamAttr SS_TOUCH_ME_UNUSED[];

	extern OamAttr* SS_CAP_ICONS[6];
	extern OamAttr SS_SPEECH_BUBBLE_UP[];
	extern OamAttr SS_SPEECH_BUBBLE_LEFT[];
	extern OamAttr SS_SPEECH_BUBBLE_RIGHT[];
	extern OamAttr SS_MARIO_CAP[];
	extern OamAttr SS_LUIGI_CAP[];
	extern OamAttr SS_WARIO_CAP[];
	// extern OamAttr SS_SPEECH_BUBBLE_M_CAP[]; // unused
	// extern OamAttr SS_SPEECH_BUBBLE_L_W_CAP[]; // unused
	// extern OamAttr SS_SPEECH_BUBBLE_M_L_W_CAP[]; // unused

	extern OamAttr* SS_STAR_NUMBERS[7];
	extern OamAttr SS_STAR_NUMBER_1[];
	extern OamAttr SS_STAR_NUMBER_2[];
	extern OamAttr SS_STAR_NUMBER_3[];
	extern OamAttr SS_STAR_NUMBER_4[];
	extern OamAttr SS_STAR_NUMBER_5[];
	extern OamAttr SS_STAR_NUMBER_6[];
	extern OamAttr SS_STAR_NUMBER_7[];
}

inline void ShowDecimalInt(u32 val, s32 x, s32 y, bool onBottomScreen = false, bool isRed = false)
{
	u8 digits[10]; // 32-bit integers can have up to 10 decimal digits
	s32 numDigits = 0;

	if (val == 0)
	{
		digits[0] = 0;
		numDigits = 1;
	}
	else while (val)
	{
		digits[numDigits++] = val % 10;
		val /= 10;
	}

	const u32 offset = isRed * 10;

	for (s32 i = numDigits - 1; i >= 0; --i)
	{
		OAM::Render(onBottomScreen, OAM::NUMBERS[offset + digits[i]], x, y, -1, 1, nullptr);
		x += 9;
	}
}
