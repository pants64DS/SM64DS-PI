#pragma once

struct Number : Actor // internal name: daObjNumber_c
{
	static constexpr u16 staticActorID = 0x14a;

	Model model;
	TextureSequence textureSequence;
	u32 spawnerUniqueID;
	Vector3 spawnPos;
	Fix12i yOffset;
	u16 delay;
	u8 numTimesBounced;
	u8 padding;

	static SpawnInfo spawnData;
	Number();
	virtual s32 InitResources() override;
	virtual s32 CleanupResources() override;
	virtual s32 Behavior() override;
	virtual s32 Render() override;
	virtual ~Number() override;

	void InitFromSpawner(Actor* spawner);
};

static_assert(sizeof(Number) == 0x150, "Number is wrong size");
