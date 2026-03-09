#pragma once

struct Door : Actor
{
	static constexpr u16 staticActorID = 0x161;

	ModelAnim model;
	u32 unk138;
	u32 unk13c;
	u32 unk140;
	u32 unk144;

	virtual s32 InitResources() override;
	virtual s32 CleanupResources() override;
	virtual s32 Behavior() override;
	virtual s32 Render() override;
	virtual void OnPendingDestroy() override;
	virtual ~Door() override;

	static bool StopBowserMessageSound();
	static bool ContinueBowserMessageSound();
};

static_assert(sizeof(Door) == 0x148);
