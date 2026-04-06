#pragma once

struct YoshiEgg : Enemy	// internal name: daYegg_c
{
	static constexpr u16 staticActorID = 0x9;

	struct EggContents
	{
		enum EggType
		{
			ET_CUBE   = 0x0,
			ET_NORMAL = 0x1,
		};

		u8   eggType		: 2 = ET_CUBE;
		u8	 numYellowCoins	: 4 = 0;
		bool hasBlueCoin	: 1 = false;
		bool hasSilverStar	: 1 = false;
	};

	// MovingCylinderClsn cylClsn; // 0x110
	// WithMeshClsn wmClsn; // 0x144
	// ModelAnim modelAnim; // 0x300
	// ShadowModel shadow; // 0x364
	// Matrix4x3 shadowMat; // 0x38c

	// members not documented
};

// static_assert(sizeof(YoshiEgg) == 0x42c, "sizeof(YoshiEgg) is incorrect!");