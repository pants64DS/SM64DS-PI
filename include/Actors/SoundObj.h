#pragma once

// TODO: document state functions (jingles)
struct SoundObj : Actor
{
	static constexpr u16 staticActorID = 0x167;

	u32 musicID; // 0xd4
	u32 musicVolume; // 0xd8
	u16 timeElapsed; // 0xdc
	u16 musicDuration; // 0xde
	bool starting; // 0xe0
	u8 padding; // 0xe1
	u16 padding2; // 0xe2

	virtual s32 InitResources() override;
	virtual s32 CleanupResources() override;
	virtual s32 Behavior() override;
	virtual s32 Render() override;
	virtual void OnPendingDestroy() override;
	virtual ~SoundObj() override;
};

static_assert(sizeof(SoundObj) == 0xe4);