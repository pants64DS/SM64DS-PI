#pragma once

#include "Math.h"

constexpr s32 NUM_LEVELS = 52;
constexpr s32 NUM_MAIN_LEVELS = 15;
constexpr s32 NUM_SECRET_LEVELS = 15;
constexpr s32 NUM_MINIGAMES = 36;
constexpr s32 NUM_MINIGAME_KEYS = 28;

extern s8 SUBLEVEL_LEVEL_TABLE[NUM_LEVELS];

namespace CourseIDs // aka act selector IDs
{
	enum
	{
		BoB   = 0,
		WF    = 1,
		JRB   = 2,
		CCM   = 3,
		BBH   = 4,
		HMC   = 5,
		LLL   = 6,
		SSL   = 7,
		DDD   = 8,
		SL    = 9,
		WDW   = 10,
		TTM   = 11,
		THI   = 12,
		TTC   = 13,
		RR    = 14,
		BitDW = 15,
		BitFS = 16,
		BitS  = 17,
		GB    = 18,
		BBB   = 19,
		CCC   = 20,
		PSS   = 21,
		SA    = 22,
		WMotR = 23,
		SutM  = 24,
		BtW   = 25,
		OtR   = 26,
		SI    = 27,
		BF    = 28,
		HUB   = 29,
	};
};

struct FileSaveData
{
	enum Flags1 : u32
	{
		FILE_SAVED                 = 1u << 0, // set when file is saved
		BASEMENT_KEY_OBTAINED      = 1u << 1,
		UPPER_HALL_KEY_OBTAINED    = 1u << 2, // removes the sub from DDD
		MARIO_KEY_OBTAINED         = 1u << 3,
		LUIGI_KEY_OBTAINED         = 1u << 4,
		WARIO_KEY_OBTAINED         = 1u << 5,
		MAIN_HALL_KEY_OBTAINED     = 1u << 6,
		WHITE_KEY_OBTAINED         = 1u << 7, // triggers the white room star
		BASEMENT_KEY_USED          = 1u << 8,
		UPPER_HALL_KEY_USED        = 1u << 9, // removes the sub from DDD
		MARIO_KEY_USED             = 1u << 10,
		LUIGI_KEY_USED             = 1u << 11,
		WARIO_KEY_USED             = 1u << 12,
		MAIN_HALL_KEY_USED         = 1u << 13,
		WHITE_KEY_USED             = 1u << 14, // removes the white room star
		WF_STAR_DOOR               = 1u << 15,
		CHARACTER_STAR_DOOR_OPENED = 1u << 16,
		JRB_STAR_DOOR_OPENED       = 1u << 17,
		CCM_STAR_DOOR_OPENED       = 1u << 18,
		MARIO_STAR_DOOR_OPENED     = 1u << 19,
		BOWSER_1_DOOR_OPENED       = 1u << 20,
		BOWSER_2_DOOR_OPENED       = 1u << 21,
		CLOCK_STAR_DOOR_OPENED     = 1u << 22,
		UNUSED_STAR_DOOR_OPENED    = 1u << 23, // BitS star door?
		MARIO_CAP_LOST             = 1u << 24,
		LUIGI_CAP_LOST             = 1u << 25,
		WARIO_CAP_LOST             = 1u << 26,
		MARIO_CAP_ON_FLOOR1_TOAD   = 1u << 27,
		LUIGI_CAP_ON_FLOOR1_TOAD   = 1u << 28,
		WARIO_CAP_ON_FLOOR1_TOAD   = 1u << 29,
		MINIGAMES_ACTIVATED        = 1u << 30, // talked to minigame toad
		RED_SWITCH_ACTIVATED       = 1u << 31, // if not set, the shine in main hall is rendered
	};

	enum Flags2 : u32
	{
		MARIO_UNLOCKED             = 1u << 0,
		LUIGI_UNLOCKED             = 1u << 1,
		WARIO_UNLOCKED             = 1u << 2,
		SAVE_STARTED               = 1u << 3, // always set
		// Bits 4-6 may be unused
		CHARACTER_CONTROL_GIVEN    = 1u << 7, // got control of the character
		// Bit 8 may be unused
		BOWSER_INTRODUCED          = 1u << 9,
		FEATHER_INTRODUCED         = 1u << 10,
		BALLOON_INTRODUCED         = 1u << 11,
		VANISH_LUIGI_INTRODUCED    = 1u << 12,
		METAL_WARIO_INTRODUCED     = 1u << 13,
		FIRE_YOSHI_INTRODUCED      = 1u << 14,
		BOB_INTRODUCED             = 1u << 15,
		INTRO_LAKITU_SUMMONED      = 1u << 16, // set when trying to enter the castle for the first time
		INTRO_LAKITU_DONE          = 1u << 17,
		DDD_ENTRANCE_MOVED         = 1u << 18, // set every frame if DDD star 1 is collected & player is in basement
		CASTLE_WATER_DRAINED       = 1u << 19,
		GLOWING_RABBITS            = 0xffu << 20,
		MARIO_CAP_INTRODUCED       = 1u << 28,
		// Bits 29-31 may be unused
	};

	enum MinigameRabbits : u32
	{
		RABBIT_M_LEFT_BRIDGE    = 1u << 0,
		RABBIT_L_BACKYARD       = 1u << 1,
		RABBIT_W_CASTLE_RIGHT   = 1u << 2,
		RABBIT_Y_CASTLE_1       = 1u << 3,
		RABBIT_M_AQUARIUM_ROOM  = 1u << 4,
		RABBIT_L_WATER_DRAINAGE = 1u << 5,
		RABBIT_W_TTM_ROOM       = 1u << 6,
		RABBIT_Y_CASTLE_2       = 1u << 7,
		RABBIT_M_MIRROR_ROOM    = 1u << 8,
		RABBIT_L_MARIO_ROOM     = 1u << 9,
		RABBIT_W_BASEMENT       = 1u << 10,
		RABBIT_Y_CASTLE_3       = 1u << 11,
		RABBIT_M_BASEMENT_1     = 1u << 12,
		RABBIT_L_BOB_ROOM       = 1u << 13,
		RABBIT_W_BACKYARD       = 1u << 14,
		RABBIT_Y_CASTLE_RIGHT   = 1u << 15,
		RABBIT_M_BASEMENT_2     = 1u << 16,
		RABBIT_L_HEDGE_MAZE     = 1u << 17,
		RABBIT_W_THI_ROOM       = 1u << 18,
		RABBIT_Y_HEDGE_MAZE     = 1u << 19,
		RABBIT_M_MOAT           = 1u << 20,
		RABBIT_L_SECOND_FLOOR   = 1u << 21,
		RABBIT_W_THIRD_FLOOR_1  = 1u << 22,
		RABBIT_Y_BASEMENT       = 1u << 23,
		RABBIT_M_UPPER_HALL     = 1u << 24,
		RABBIT_L_CASTLE_ROOF    = 1u << 25,
		RABBIT_W_THIRD_FLOOR_2  = 1u << 26,
		RABBIT_Y_MOAT           = 1u << 27,
		// Bits 28-31 may be unused
	};

	enum CannonsUnlocked : u32
	{
		CANNON_BOB = 1u << 0,
		CANNON_WF  = 1u << 1,
		CANNON_JRB = 1u << 2,
		CANNON_CCM = 1u << 3,
		CANNON_SSL = 1u << 7,
		CANNON_SL  = 1u << 9,
		CANNON_WDW = 1u << 10,
		CANNON_TTM = 1u << 11,
		CANNON_THI = 1u << 12,
		CANNON_RR  = 1u << 14,
		CANNON_OTR = 1u << 26,
		// Other bits may be unused
	};

	u32 magic8000; // 8000 in ASCII
	u32 flags1;
	u32 flags2;
	u32 minigameRabbits;
	u32 cannonsUnlocked;
	u8 stars[NUM_MAIN_LEVELS + NUM_SECRET_LEVELS];  // Stars in each level
		/* Secret levels:
		15: Bowser 1 (0x02=Red, 0x04=Time)
		16: Bowser 2 (0x02=Red, 0x04=Time)
		17: Bowser 3 (0x02=Red, 0x04=Time)
		18: Mario painting (0x02=Red, 0x04=Time)
		19: Luigi painting (0x02=Red, 0x04=Std)
		20: Wario painting (0x02=Red, 0x04=Wario)
		21: Slide stars (0x02=Std, 0x04=20s)
		22: Water temple (0x02=Red)
		23: Switch palace (0x02=Red)
		24: Moat secret (0x02=Red, 0x04=Time)
		25: Behind the waterfall (0x02=Red, 0x04=Std)
		26: Rainbow secret (0x02=Red, 0x04=Wario)
		27: Beach painting (0x02=SS)
		28: Battle fort (0x02=SS)
		29: Castle secrets (0x02=Red, 0x04=Toad[HMC], 0x08=Toad[2ndF], 0x10=Toad[3rdF], 0x20=White[2ndF], 0x40=White[CR]) */

	u8 coinRecords[NUM_MAIN_LEVELS]; // Coin counts in each main level
	u8 currentCharacter; // (Mario: 0, Luigi: 1, Wario: 2, Yoshi: 3)
	u8 controllerMode;
	u8 unk43;

	[[gnu::always_inline]]
	void CollectStar(s32 levelID, s32 starID)
	{
		s32 courseID = SUBLEVEL_LEVEL_TABLE[levelID];
		stars[courseID] |= 1u << starID;
	}

	[[gnu::always_inline]]
	bool WasBowserSubRemoved() const
	{
		return flags1 & 0x204;
	}
};

static_assert(sizeof(FileSaveData) == 0x44);

struct MinigameSaveData
{
	u32 magic5000;           //5000 in ASCII
	u8 minigamesUnlocked[4]; /*  Minigame bits: 0x1=Mario, 0x2=Luigi, 0x4=Wario, 0x8=Yoshi; minigame location: P=Page, R=Row, C=Column
	                             0: Minigames unlocked 1
	                             0x0n: P1R1C3
	                             0xn0: P1R2C1
	                             1: Minigames unlocked 2
	                             0x0n: P1R2C2
	                             0xn0: P1R2C3
	                             2: Minigames unlocked 3
	                             0x0n: P2R1C1
	                             0xn0: P2R1C2
	                             3: Minigames unlocked 4
	                             0x0n: P2R1C3
	                             0x10: ??? //Unused
	                             0x20: ??? //Unused
	                             0x40: ??? //Unused
	                             0x80: Always set, marks started minigame save   */
	u8 minigamesPlayed[5];
	/* Minigames played 1-4 (exact same IDs like minigamesUnlocked, upper bits (4-7) of [3] are unused)
	   Minigames played 5:
			0x0n: P1R1C1
			0xn0: P1R1C2 */
	u8 unused_0x51[3];                      //Unused
	u32 minigameRecords[NUM_MINIGAMES][5];  /*  Minigame records 1-36; each minigame stores 5 scores */
	u8 unused_0x324[4];                     //Unused
};

struct SaveData : FileSaveData, MinigameSaveData
{
	u32 currentFile; // 0, 1 or 2

	static bool SaveCurrentFile();
	static bool SaveFile(u32 fileID, FileSaveData* saveData);
	static bool SaveMinigames(MinigameSaveData* saveData);
	static s32  SaveDataToCart(char* saveData, u32 saveSize, u32 fileID);
	static u32  EraseAllSaveData();
	static bool EraseSaveFile(u32 saveFileID, char* saveArea);
	static void SetDefaultValues(FileSaveData* saveData);
	static void SetDefaultValuesMg(MinigameSaveData* saveData);

	static s32  ReadDataFromCart(char* saveData, u32 saveSize, u32 fileID);
	static bool ReadMinigameData(MinigameSaveData* saveData);
	static bool ReadFileData(u32 fileID, FileSaveData* saveData);

	static u32  CountStarsCollectedInLevel(u32 courseID);
	static bool IsCharacterUnlocked(u32 characterID);
	static u8   GetCoinRecord(u32 courseID);
	static void SetCoinRecordIfHigher(s8 courseID, u8 coinCount);
	static bool HasRabbitKeyBeenCollected(u32 keyID, u32 characterID);
	static u32  NumMinigameKeysFound();
	static void SetNumGlowingRabbitsAndWhiteKey();
	static u32  NumGlowingRabbitsFound();
	static void SetCharacterIntro(s32 keyID);

	static bool CheckFloor1ToadHasCap();
	static void PlayerLoseCap();
	static s32  CanPlayerHaveCap();
	static s32  HasPlayerLostCap();
};

extern SaveData SAVE_DATA;
