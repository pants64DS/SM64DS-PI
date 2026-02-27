#pragma once

struct StarMarker : Actor
{
	static constexpr u16 staticActorID = 0xb4;

	enum Types
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

	enum Flags2
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
	Fix12i floorPosY;
	u32 silverStarID;
	Player* shatterer;
	s16 nextVSStarSphereSpawnDelay; // 0x1d4
	s16 silverStarDeathTableID; // 0x1d6
	ModelTypes modelType; // 0x1d8
	s8 starID; // 0x1d9
	u8 silverStarState;
	u8 flags2;

	StarMarker();
	virtual s32 InitResources() override;
	virtual s32 CleanupResources() override;
	virtual s32 Behavior() override;
	virtual s32 Render() override;
	virtual void OnPendingDestroy() override;
	virtual ~StarMarker() override;

	void ShatterStarSphere();
	void SpawnRedCoinStarIfNecessary();
	void LinkSilverStarAndStarMarker(PowerStar* silverStar);
};

static_assert(sizeof(StarMarker) == 0x1dc, "sizeof(StarMarker) is incorrect!");
