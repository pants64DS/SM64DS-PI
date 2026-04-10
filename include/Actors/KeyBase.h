#pragma once

struct KeyBase : Enemy // internal name: daObjKey_c
{
	enum KeyTypes : u8
	{
		KEY_BOWSER,
		KEY_MARIO,
		KEY_LUIGI,
		KEY_WARIO,
		KEY_CASTLE_ENTRANCE,
		KEY_WHITE_DOOR,
		KEY_LAST_STAR,

		NUM_KEY_TYPES
	};

	// members not documented

    static void LoadKeyModels(u8 keyType);
    static void UnloadKeyModels(u8 keyType);
};

struct Key : KeyBase
{
	static constexpr u16 staticActorID = 0x11a;

	// members not documented
};

struct LastStar : KeyBase
{
	static constexpr u16 staticActorID = 0x11b;

	// members not documented
};

// static_assert(sizeof(KeyBase) == 0x470, "sizeof(KeyBase) is incorrect!");
// static_assert(sizeof(Key) == 0x470, "sizeof(Key) is incorrect!");
// static_assert(sizeof(LastStar) == 0x470, "sizeof(LastStar) is incorrect!");