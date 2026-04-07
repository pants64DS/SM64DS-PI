#pragma once

struct WingFeather : Actor	// internal name: daFeather_c
{
	static constexpr u16 staticActorID = 0x159;

	Model model; // 0xd4
    MovingCylinderClsn cylClsn; // 0x124
    WithMeshClsn wmClsn; // 0x158
	ShadowModel shadowModel; // 0x314
	Matrix4x3 shadowMat; // 0x33c
	u32 unk36c; // 0x36c unused
	u32 unk370; // 0x370 unused
	u32 unk374; // 0x374 unused
	Fix12i swaySpeed; // 0x378
	s16 swayPhase; // 0x37c
	u16 padding1; // 0x37e
	u32 particleID; // 0x380
	u8 disappearTimer; // 0x384
	u16 padding2; // 0x386

	static SpawnInfo spawnData;
	
	virtual s32 InitResources() override;
	virtual s32 CleanupResources() override;
	virtual s32 Behavior() override;
	virtual s32 Render() override;
	virtual ~WingFeather() override;

	void UpdateModelTransform();
};

static_assert(sizeof(WingFeather) == 0x388, "sizeof(WingFeather) is incorrect!");