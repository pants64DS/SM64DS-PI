#pragma once

struct Mushroom : Enemy // internal name: da1up_c
{
	enum Behaviors
	{ 
		BH_SPIN_AROUND_WALK,
		BH_SPIN_AROUND_AVOID_PLAYER,
		BH_SLIDE,
		BH_STATIC,
		BH_JUMP_ON_APPROACH,
		BH_WAIT_FOR_TAGS_AVOID_PLAYER,
		BH_SPAWN_TWO_COIN_TAG_AVOID_PLAYER, // used in THI - Huge. The Coin Tags spawn with a X offset 500._f  away on either side, the Mushroom itself spawns with a Y offset of 50._f
		BH_HIDDEN_TAG_AVOID_PLAYER,
		BH_WAIT_FOR_TAGS_CHASE_PLAYER,
		BH_HIDDEN_TAG_CHASE_PLAYER,
		BH_JUMP_THEN_SPIN_AROUND_WALK,
		BH_COIN_TAG_AVOID_PLAYER,
		BH_COIN_TAG_CHASE_PLAYER,
		BH_BOUNCE, // static unless in the air or on a slope

		NUM_BEHAVIORS
	};

	using BehaviorFunc = void(Mushroom::*)();

	struct Behavior
	{
		BehaviorFunc func;
		u32 unk04 = 0;
	};

	static Behavior behaviors[NUM_BEHAVIORS];

	MovingCylinderClsn cylClsn;
	WithMeshClsn wmClsn;
	Model model;
	ShadowModel shadowModel;
	Vector3 originalPos;
    Behaviors behaviorType;
    u32 behaviorState;
    u16 disappearTimer;
    bool isVisible;
    bool isBlinkOn;
    u32 tagCount;
    u32 sparklesParticleID;

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
	void Bh_Bounce();
};

struct OneUpMushroom : Mushroom
{
	static constexpr u16 staticActorID = 0x114;

	static SpawnInfo spawnData;
};

struct SuperMushroom : Mushroom
{
	static constexpr u16 staticActorID = 0x115;

	static SpawnInfo spawnData;
};

static_assert(sizeof(Mushroom) == 0x398, "sizeof(Mushroom) is incorrect!");
static_assert(sizeof(OneUpMushroom) == 0x398, "sizeof(OneUpMushroom) is incorrect!");
static_assert(sizeof(SuperMushroom) == 0x398, "sizeof(SuperMushroom) is incorrect!");

extern bool MUSHROOM_CYL_CLSN_ENABLED_ON_INIT[Mushroom::NUM_BEHAVIORS];
extern bool MUSHROOM_NO_BEHAVIOR_IF_OFF_SCREEN[Mushroom::NUM_BEHAVIORS];