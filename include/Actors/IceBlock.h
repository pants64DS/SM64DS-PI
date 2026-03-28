#pragma once

struct IceBlock : Platform // internal name: dObjIceBlock_c
{
	static constexpr u16 staticActorID = 0x12;

	MovingCylinderClsn cylClsn;
    u16 meltTimer;
    u16 padding;
    Fix12i meltScale;
    u32 steamParticleID;
    u32 waterDropletsParticleID;
    Star* containedStar;

    static SpawnInfo spawnData;

	virtual s32 InitResources() override;
	virtual s32 CleanupResources() override;
	virtual s32 Behavior() override;
	virtual s32 Render() override;
    virtual ~IceBlock() override;
    virtual void OnHitByMegaChar(Player& megaChar) override;
    virtual void Kill() override;

    void SpawnPowerStarIfNecessary();
};

static_assert(sizeof(IceBlock) == 0x368, "sizeof(IceBlock) is incorrect!");