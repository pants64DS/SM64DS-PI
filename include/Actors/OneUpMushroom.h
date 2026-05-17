#pragma once

struct OneUpMushroom : Enemy // internal name: da1up_c
{
	using StateFunction = void(OneUpMushroom::*)();

	enum States
	{ 
		ST_SPIN_AROUND_WALK,
		ST_SPIN_AROUND_AVOID_PLAYER,
		ST_SLIDE,
		ST_STATIC,
		ST_JUMP_ON_APPROACH,
		ST_WAIT_FOR_TAGS_AVOID_PLAYER,
		ST_SPAWN_TWO_COIN_TAG_AVOID_PLAYER, // used in THI - Huge. The Coin Tags spawn with a X offset 500._f  away on either side, the Mushroom itself spawns with a Y offset of 50._f
		ST_HIDDEN_TAG_AVOID_PLAYER,
		ST_WAIT_FOR_TAGS_CHASE_PLAYER,
		ST_HIDDEN_TAG_CHASE_PLAYER,
		ST_JUMP_THEN_SPIN_AROUND_WALK,
		ST_COIN_TAG_AVOID_PLAYER,
		ST_COIN_TAG_CHASE_PLAYER,
		ST_BOUNCE, // static unless in the air or on a slope

		NUM_STATES
	};

	static StateFunction states[NUM_STATES];

	static SpawnInfo oneUpMushroomSpawnData;
	static SpawnInfo superMushroomSpawnData;

	MovingCylinderClsn cylClsn;
	WithMeshClsn wmClsn;
	Model model;
	ShadowModel shadowModel;
	Vector3 originalPos;
    States behaviorType;
    u32 stateState;
    u16 disappearTimer;
    bool isVisible;
    bool isBlinkOn;
    u32 tagCount;
    u32 sparklesEmitterID;

	virtual s32 InitResources() override;
	virtual s32 CleanupResources() override;
	virtual s32 Behavior() override;
	virtual s32 Render() override;
	virtual void OnPendingDestroy() override;
	virtual ~OneUpMushroom() override;
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

	void St_SpinAroundWalk();
	void St_SpinAroundAvoidPlayer();
	void St_Slide();
	void St_Static();
	void St_JumpOnApproach();
	void St_WaitForTagsAvoidPlayer();
	void St_SpawnTwoCoinTagAvoidPlayer();
	void St_HiddenTagAvoidPlayer();
	void St_WaitForTagsChasePlayer();
	void St_HiddenTagChasePlayer();
	void St_JumpThenSpinAroundWalk();
	void St_CoinTagAvoidPlayer();
	void St_CoinTagChasePlayer();
	void St_Bounce();

	static const bool COLLIDER_ENABLED_ON_INIT_TABLE[OneUpMushroom::NUM_STATES];
	static const bool NO_BEHAVIOR_IF_OFF_SCREEN_TABLE[OneUpMushroom::NUM_STATES];
};

static_assert(sizeof(OneUpMushroom) == 0x398, "sizeof(OneUpMushroom) is incorrect!");

using SuperMushroom = Actor::Alias<OneUpMushroom, 0x115>;