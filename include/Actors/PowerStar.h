#pragma once

struct PowerStar : Enemy
{
	static constexpr u16 staticActorID = 0xb2;

	MovingCylinderClsnWithPos cylClsn;
	WithMeshClsn wmClsn;
	ModelAnim modelAnim1;
	ModelAnim modelAnim2;
	ShadowModel shadowModel;
	u32 unk3fc;
	u32 unk400;
	u32 unk404;
	u32 unk408;
	u32 unk40c;
	u32 unk410;
	u32 unk414;
	u32 unk418;
	u32 unk41c;
	u32 unk420;
	u32 unk424;
	u32 unk428;
	u32 unk42c;
	u32 unk430;
	u32 unk434;
	u32 unk438;
	u32 unk43c;
	u32 unk440;
	u32 unk444;
	u32 unk448;
	u32 unk44c;
	u32 unk450;
	u32 unk454;
	u32 unk458;
	u32 unk45c;
	Vector3 unkVec460;
	Vector3 unkVec46c;
	u32 unk478;
	u32 unk47c;
	u32 unk480;
	u32 unk484;
	u32 unk488;
	u32 unk48c;
	u32 unk490;
	u16 unk494;
	s16 spawnFrameCounter;
	u32 unk498;
	u8 unk49c;
	u8 starID;
	u16 unk49e;
	u16 unk4a0;
	u16 unk4a2;
	u32 unk4a4;
	u32 unk4a8;
	u32 unk4ac;
	u32 unk4b0;
	u32 unk4b4;
	u32 unk4b8;
	u32 unk4bc;
	u32 unk4c0;

	void AddStarMarker();
};

static_assert(sizeof(PowerStar) == 0x4c4, "sizeof(PowerStar) is incorrect!");
