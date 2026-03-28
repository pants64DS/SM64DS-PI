#pragma once

struct EnemySpawner : Actor // internal name: daECreate_c
{
	static constexpr u16 staticActorID = 0x166;

    u32 spawnedActorID;
    u32 prevEventBit;
    u32 eventID;

    static SpawnInfo spawnData;

	virtual s32 InitResources() override;
	virtual s32 CleanupResources() override;
	virtual s32 Behavior() override;
    virtual ~EnemySpawner() override;
};

static_assert(sizeof(EnemySpawner) == 0xe0, "sizeof(EnemySpawner) is incorrect!");