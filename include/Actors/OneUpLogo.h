#pragma once

struct OneUpLogo : Actor // internal name: daObjOneUpLogo_c
{
	static constexpr u16 staticActorID = 0x14b;

	Model model;
	TextureSequence textureSequence;
	u32 spawnerUniqueID;
	Vector3 spawnPos;
	Fix12i yOffset;
	u16 delay;
	u8 numTimesBounced;
	u8 padding;

	static SpawnInfo spawnData;
    
	virtual s32 InitResources() override;
	virtual s32 CleanupResources() override;
	virtual s32 Behavior() override;
	virtual s32 Render() override;
	virtual ~OneUpLogo() override;

	void LinkToActor(Actor* actor);
};

static_assert(sizeof(OneUpLogo) == 0x150, "sizeof(OneUpLogo) is incorrect!");