#pragma once

struct StarMarker : Actor
{
	static constexpr u16 staticActorID = 0xb4;

	enum Types : u8
	{
		TYPE_STAR_BASE_RED_COIN        = 0,
		TYPE_STAR_SPHERE_VS 		   = 1,
		TYPE_STAR_MARKER			   = 2,
		TYPE_STAR_SPHERE_VS_HIDDEN     = 3,
		TYPE_STAR_SPHERE_EMPTY 		   = 4,
		TYPE_STAR_SPHERE_STAR_INSIDE   = 5,
		TYPE_STAR_SPHERE_SWITCH_STAR   = 6,

		NUM_TYPES = 6,
	};

	enum ModelTypes : u8
	{
		MT_STAR_BASE 				 = 0,
		MT_STAR_SPHERE_VS 		   	 = 1,
		MT_STAR_SPHERE_EMPTY		 = 2,
		MT_STAR_SPHERE_STAR_INSIDE   = 3,

		NUM_MODEL_TYPES = 4,
	};

	enum Flags2 : u8
	{
		F2_NO_COLLISION 		 = 1 << 0,
		F2_VISIBLE 				 = 1 << 1,
		F2_RED_COIN_STAR_SPAWNED = 1 << 2,
		F2_VS_PENDING_ACTIVATION = 1 << 3,
	};

	MovingCylinderClsnWithPos cylClsn; // 0xd4
	Model model; // 0x114
	ShadowModel shadowModel; // 0x164
	Matrix4x3 shadowMat; // 0x18c
	Vector3 spawnPos; // unused?
	Fix12i floorPosY; // 0x1c0
	u32 silverStarID; // 0x1cc
	Player* shatterer; // 0x1d0
	s16 nextVSStarSphereSpawnDelay; // 0x1d4
	s16 silverStarDeathTableID; // 0x1d6
	u8 modelType; // 0x1d8
	s8 starID; // 0x1d9
	u8 silverStarState; // 0x1da
	u8 flags2; // 0x1db

	void LinkSilverStarAndStarMarker(PowerStar* silverStar);
	void SpawnRedCoinStarIfNecessary();
	void ShatterStarSphere();
};

static_assert(sizeof(StarMarker) == 0x1dc, "sizeof(StarMarker) is incorrect!");
