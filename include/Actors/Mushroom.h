#pragma once

struct Mushroom : Enemy // internal name: da1up_c
{
	MovingCylinderClsn cylClsn;
	WithMeshClsn wmClsn;
	Model model;
	ShadowModel shadowModel;
	Vector3 originalPos;
    u32 behaviorType;
    u32 behaviorState;
    u16 disappearTimer;
    bool isVisible;
    bool isBlinkOn;
    u32 tagCount;
    u32 sparklesParticleID;

	Mushroom();
	virtual s32 InitResources() override;
	virtual s32 CleanupResources() override;
	virtual s32 Behavior() override;
	virtual s32 Render() override;
	virtual void OnPendingDestroy() override;
	virtual ~Mushroom() override;
	virtual u32 OnYoshiTryEat() override;
	virtual void OnTurnIntoEgg(Player& player) override;

	void UpdateSparkleParticles();
	void SetYoshiTongueVulnerableFlag();
	void Move();
	void ChasePlayer();
	Player* GetCollidingPlayer();
	void UpdateVisibilityByPlayerRange(u32 maxRange);
	bool FlickerAndDisappear(s16 disappearTimer);
	void CheckCollect();
	void SpinAround();
	void UpdateModelTransform();
	void CollectTag(u32 matchingBehaviorType, Player& player);
	void SlidingMove();
	void AvoidPlayer();

	void Bh_SpinAroundWalk();
	void Bh_SpinAroundAvoidPlayer();
	void Bh_Slide();
	void Bh_Static();
	void Bh_JumpOnApproach();
	void Bh_WaitForTagsAvoidPlayer();
	void Bh_SpawnTwoCoinTagAvoidPlayer();
	void Bh_HiddenTagAvoidPlayer();
	void Bh_WaitForTagsChasePlayer();
	void Bh_HiddenTagChasePlayer();
	void Bh_JumpThenSpinAroundWalk();
	void Bh_CoinTagAvoidPlayer();
	void Bh_CoinTagChasePlayer();
	void Bh_WalkPermanent();
};

struct OneUpMushroom : Mushroom
{
	static constexpr u16 staticActorID = 0x114;

	static SpawnInfo spawnData;

	OneUpMushroom();
	virtual ~OneUpMushroom() override;
};

struct SuperMushroom : Mushroom
{
	static constexpr u16 staticActorID = 0x115;

	static SpawnInfo spawnData;

	SuperMushroom();
	virtual ~SuperMushroom() override;
};

static_assert(sizeof(Mushroom) == 0x398, "sizeof(Mushroom) is incorrect!");
static_assert(sizeof(OneUpMushroom) == 0x398, "sizeof(OneUpMushroom) is incorrect!");
static_assert(sizeof(SuperMushroom) == 0x398, "sizeof(SuperMushroom) is incorrect!");