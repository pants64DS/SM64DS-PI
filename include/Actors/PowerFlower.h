#pragma once

struct PowerFlower : Actor	// internal name: daObjPowerUpItem_c
{
	static constexpr u16 staticActorID = 0x132;

	enum States
	{
		ST_CLOSE,
		ST_OPEN,
		ST_OPEN_WAIT,

		NUM_STATES
	};

	struct State
	{
		void(PowerFlower::* init)();
		u32 unk04 = 0;
		void(PowerFlower::* main)();
		u32 unk0c = 0;
		char* stateName = nullptr;
	};

	// State states[NUM_STATES] = // 0x021097bc
	// {
	// 	{ &St_Close_Init,     0, &St_Close_Main,      0, "s_CLOSE" },
	// 	{ &St_Open_Init,  	  0, &St_Open_Main,       0, "s_OPEN" },
	// 	{ &St_Open_Wait_Init, 0, &St_Open_Wait_Main,  0, "s_OPEN_WAIT" },
	// };

	static SpawnInfo spawnData;
	static State states[NUM_STATES];

	Model closedModel; // 0xd4
	Model openModel; // 0x124
	ShadowModel shadowModel; // 0x174
	Matrix4x3 shadowMat; // 0x19c
    MovingCylinderClsn cylClsn; // 0x1cc
    WithMeshClsn wmClsn; // 0x200
	Fix12i floorY; // 0x3bc
	u32 currStateID;  // 0x3c0
	u32 particleID; // 0x3c4
	s16 openPhase; // 0x3c8
	u8 disappearTimer; // 0x3ca
	u8 openTimer; // 0x3cb

	virtual s32 InitResources() override;
	virtual s32 CleanupResources() override;
	virtual s32 Behavior() override;
	virtual s32 Render() override;
	virtual ~PowerFlower() override;
	virtual u32 OnYoshiTryEat() override;

	void ChangeState(u32 newStateID);
	void CallState();
	void CheckCollect();
	void DropShadow();
	void UpdateModelTransform();

	void St_Close_Init();
	void St_Close_Main();

	void St_Open_Init();
	void St_Open_Main();

	void St_Open_Wait_Init();
	void St_Open_Wait_Main();
};

static_assert(sizeof(PowerFlower) == 0x3cc, "sizeof(PowerFlower) is incorrect!");