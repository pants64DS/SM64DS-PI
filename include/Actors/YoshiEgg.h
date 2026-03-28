#pragma once

struct YoshiEgg : Enemy	// internal name: Yegg
{
	static constexpr u16 staticActorID = 0x9;

	// MovingCylinderClsn cylClsn; // 0x110
	// WithMeshClsn wmClsn; // 0x144
	// ModelAnim modelAnim; // 0x300
	// ShadowModel shadow; // 0x364

	// members not documented
};

// static_assert(sizeof(YoshiEgg) == 0x42c, "sizeof(YoshiEgg) is incorrect!");