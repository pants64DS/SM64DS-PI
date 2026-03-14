#pragma once

struct PowerStar : Enemy
{
	static constexpr u16 staticActorID = 0xb2;

	MovingCylinderClsnWithPos cylClsn;
	WithMeshClsn wmClsn;
	ModelAnim modelAnim1;
	ModelAnim modelAnim2;
	ShadowModel shadowModel;
	Matrix4x3 shadowMat;
	u32 unk42c;
	u32 unk430;
	u32 starMarkerUniqueID;
	u32 unk438;
	u32 type;
	u32 unk440;
	u32 unk444;
	Vector3 unkVec448; // 0x448
	Vector3 unkVec454; // 0x454
	Vector3 unkVec460; // 0x460
	Vector3 unkVec46c; // 0x46c
	u32 unk478;
	u32 unk47c;
	u32 unk480;
	u32 unk484;
	u32 unk488;
	u32 unk48c;
	u32 unk490;
	u16 unk494;
	s16 spawnFrameCounter;
	u32 starMarkerType;
	u8 unk49c;
	u8 starID;
	u8 unk49e;
	bool inIceBlock; // 0x49f
	bool searchedForIceBlock; // 0x4a0
	u8 unk4a1; // 0x4a1
	u16 unk4a2; // 0x4a2
	u32 unk4a4;
	u32 unk4a8;
	u32 unk4ac;
	u32 unk4b0;
	u32 unk4b4;
	u32 unk4b8;
	u32 unk4bc;
	u32 unk4c0;

	void AddStarMarker();
	void InitBouncingStar(Player* player, bool spawnNumber, bool isSilver); // isSilver is overwritten in the function
};

static_assert(sizeof(PowerStar) == 0x4c4, "sizeof(PowerStar) is incorrect!");

extern Vector3 POWER_STAR_CYL_CLSN_OFFSET; // { 0._f, -50._f, 0._f }