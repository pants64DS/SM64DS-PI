#pragma once

#include "Stage.h"

extern "C" void ChangeArea(s8 newAreaID);

struct Player : Actor
{
	static constexpr u16 staticActorID = 0xbf;

	enum Characters : u8
	{
		CH_MARIO,
		CH_LUIGI,
		CH_WARIO,
		CH_YOSHI,

		NUM_CHARACTERS,
	};

	enum Animations : u32
	{
		ANIM_ED_KISS_WAIT,
		ANIM_ED_KISS_TO_POSE,
		ANIM_L_ED_AMAZED = ANIM_ED_KISS_TO_POSE,
		ANIM_W_ED_AMAZED_WAIR = ANIM_ED_KISS_TO_POSE,
		ANIM_Y_ED_SHY_WAIT = ANIM_ED_KISS_TO_POSE,
		ANIM_E_DOWN,
		ANIM_SHF_DIE,
		ANIM_S_DIE,
		ANIM_GAS_WAIT,
		ANIM_GAS_DIE,
		ANIM_FALL_DIE,
		ANIM_LIE_END,
		ANIM_LIE_WAIT,
		ANIM_SLEEP_TO_LIE,
		ANIM_SLEEP_END,
		ANIM_SLEEP_WAIT,
		ANIM_SLEEP_START,
		ANIM_DAMAGE_START,
		ANIM_DAMAGE_WAIT,
		ANIM_RETURN_DOWN,
		ANIM_E_SHOCK, // start of arc0.narc
		ANIM_SDOWN,
		ANIM_BKDWN,
		ANIM_SHFDN,
		ANIM_JFDWN,
		ANIM_FIREJMP,
		ANIM_FJPEND,
		ANIM_CARRY_LOST,
		ANIM_STAR_GET,
		ANIM_BROAD_JUMP,
		ANIM_BROAD_JUMP_END,
		ANIM_HANDSTAND_JUMP,
		ANIM_HANDSTAND_WAIT,
		ANIM_HANDSTAND_START,
		ANIM_HANDSTAND_END,
		ANIM_HANG_JUMP_UP,
		ANIM_HANG_WAIT,
		ANIM_HANG_START,
		ANIM_HANG_UP,
		ANIM_TREE_CLIMB,
		ANIM_TREE_POSE,
		ANIM_TREE_WAIT,
		ANIM_TREE_START,
		ANIM_WJMP,
		ANIM_WSLD,
		ANIM_BACK_JUMP,
		ANIM_BACK_JUMP_END,
		ANIM_SQUAT_WAIT,
		ANIM_SQUAT_START,
		ANIM_SQUAT_END,
		ANIM_CARRY_START,
		ANIM_CARRY_THROW,
		ANIM_CARRY_POSE,
		ANIM_CARRY_WALK,
		ANIM_CARRY_WAIT,
		ANIM_RIDE,
		ANIM_RIDE_START,
		ANIM_BRAKE,
		ANIM_BREND,
		ANIM_ATTACK_1,
		ANIM_ATTACK_2,
		ANIM_ATTACK_3,
		ANIM_HIPSR,
		ANIM_HIPAT,
		ANIM_HIPED,
		ANIM_LOST,
		ANIM_RUN,
		ANIM_SLDCT,
		ANIM_SLIP,
		ANIM_SLIPED,
		ANIM_SLPBK,
		ANIM_SLPLA,
		ANIM_TRNED,
		ANIM_TURN,
		ANIM_WAIT,
		ANIM_WALK,
		ANIM_FLY_POSE,
		ANIM_JUMP_TO_FLY,
		ANIM_ROLL_JUMP,
		ANIM_ROLL_JUMP_END,
		ANIM_TJMP1,
		ANIM_TJMP2,
		ANIM_2JMP1,
		ANIM_2JMP2,
		ANIM_2JMPED,
		ANIM_JMPED,
		ANIM_JUMP,
		ANIM_LAND,
		ANIM_LAEND,
		ANIM_ROLL,
		ANIM_MONKEY_WAIT_L,
		ANIM_MONKEY_WAIT_R,
		ANIM_MONKEY_L_TO_R,
		ANIM_MONKEY_R_TO_L,
		ANIM_MONKEY_START,
		ANIM_WALL_WALK_L,
		ANIM_WALL_WALK_R,
		ANIM_WALL_WAIT,
		ANIM_SPIN_JUMP,
		ANIM_SPIN_JUMP_END,
		ANIM_SOFT_STEP,
		ANIM_CRAWL_END,
		ANIM_CRAWL,
		ANIM_CRAWL_START,
		ANIM_PUSH,
		ANIM_SLIDING_KICK_END,
		ANIM_SLIDING_KICK,
		ANIM_ROLL_KICK,
		ANIM_SFBDN,
		ANIM_SFFDN,
		ANIM_PUTON_CAP,
		ANIM_Y_EAT,
		ANIM_W_GSWING_START = ANIM_Y_EAT,
		ANIM_Y_EAT_OUT,
		ANIM_W_GSWING_POSE = ANIM_Y_EAT_OUT,
		ANIM_Y_EAT_FAIL,
		ANIM_W_GSWING_THROW = ANIM_Y_EAT_FAIL,
		ANIM_Y_EAT_SUCCESS,
		ANIM_W_GSWING_END = ANIM_Y_EAT_SUCCESS,
		ANIM_Y_LAY_EGG,
		ANIM_STRUGGLE, // end of arc0.narc
		ANIM_SHOOT_TO_FLY,
		ANIM_SHOOT,
		ANIM_SDROP_LEG,
		ANIM_SDROP_LEG_WAIT,
		ANIM_SDROP_LEG_END,
		ANIM_SDROP_HIP_END,
		ANIM_SDROP_HIP,
		ANIM_SDROP_HIP_WAIT,
		ANIM_SDROP_HEAD_END,
		ANIM_SDROP_HEAD_WAIT,
		ANIM_SDROP_HEAD,
		ANIM_SDROP_WAIT,
		ANIM_SDROP_WALK,
		ANIM_P_KOOPA_THROW,
		ANIM_P_KOOPA_H_WAIT,
		ANIM_P_KOOPA_HOLD,
		ANIM_FALL_SAND,
		ANIM_SWIM_DIE,
		ANIM_DROWN_DIE,
		ANIM_RETURN_STAR,
		ANIM_N_CARRY_START,
		ANIM_N_CARRY_WAIT,
		ANIM_N_CARRY_WALK,
		ANIM_N_CARRY_POSE,
		ANIM_N_CARRY_PUT,
		ANIM_N_CARRY_LOST,
		ANIM_DOOR_PUSH,
		ANIM_DOOR_PULL,
		ANIM_H_CARRY_START,
		ANIM_H_CARRY_WALK,
		ANIM_H_CARRY_WAIT,
		ANIM_H_CARRY_THROW,
		ANIM_STAR_OPEN,
		ANIM_KEY_OPEN,
		ANIM_KEY_GET,
		ANIM_COLD_WAIT_START,
		ANIM_COLD_WAIT,
		ANIM_COLD_WAIT_END,
		ANIM_PUTON_T_CAP,
		ANIM_FIRST_CHANGE,
		ANIM_SCALE_UP,
		ANIM_SU_JUMP_END,
		ANIM_SU_JUMP,
		ANIM_SU_WALK_END,
		ANIM_SU_WALK,
		ANIM_SU_WALK_START,
		ANIM_SU_WAIT,
		ANIM_SU_HIPED,
		ANIM_SU_HIPAT,
		ANIM_SU_HIPSR,
		ANIM_SU_RUN,
		ANIM_RETURN_NOCAP,
		ANIM_SWIM,
		ANIM_SWIM_IN,
		ANIM_SWIM_WAIT,
		ANIM_PADDLE_1,
		ANIM_PADDLE_2,
		ANIM_PADDLE_END,
		ANIM_SWIM_STAR_GET,
		ANIM_SWIM_DAMAGE,
		ANIM_SWIM_ATTACK,
		ANIM_SWIM_CARRY,
		ANIM_PADDLE_CARRY,
		ANIM_SWIM_THROW,
		ANIM_OP_GO,
		ANIM_L_OP_NOD = ANIM_OP_GO,
		ANIM_W_OP_NOD = ANIM_OP_GO,
		ANIM_Y_OP_LIE_TO_SIT = ANIM_OP_GO,
		ANIM_OP_WAIT,
		ANIM_Y_OP_SIT_TO_STAND = ANIM_OP_WAIT,
		ANIM_Y_OP_SIT_WAIT,
		ANIM_L_OP_TURN = ANIM_Y_OP_SIT_WAIT,
		ANIM_W_OP_TURN = ANIM_Y_OP_SIT_WAIT,
		ANIM_Y_OP_STAND_WAIT,
		ANIM_L_OP_LOOK_WARIO = ANIM_Y_OP_STAND_WAIT,
		ANIM_L_OP_LOOK_LUIGI = ANIM_Y_OP_STAND_WAIT,
		ANIM_W_OP_POINT,
		ANIM_ED_WAIT,
		ANIM_ED_LOOK,
		ANIM_ED_LOOK_WAIT,
		ANIM_ED_LOOK_END,
		ANIM_ED_NOD,
		ANIM_ED_PUTUP_WAIT,
		ANIM_ED_LOOKUP_WAIT = ANIM_ED_PUTUP_WAIT,
		ANIM_ED_CAP_OFF,
		ANIM_ED_CAP_OFF_WAIT,
		ANIM_Y_ED_SHY_TO_WAIT = ANIM_ED_CAP_OFF_WAIT,
		ANIM_ED_WAVE,
		ANIM_ED_FLY_START,
		ANIM_Y_ED_LOOK_CAM = ANIM_ED_FLY_START,
		ANIM_ED_FLY,
		ANIM_Y_ED_TURN = ANIM_ED_FLY,

		NUM_ANIMS,
	};

	enum TalkStates : s8
	{
		TK_NOT         = -1,
		TK_START       =  0,
		TK_TALKING     =  1, // +0x6e3 == anything but 3, 5, or 7
		TK_POST_CHOICE =  2, // +0x6e3 == 3; After selecting a dialog option
		TK_UNK3        =  3  // +0x6e3 == 5 or 7
	};

	enum HurtStates : s8
	{
		HT_NOT     = -1,
		HT_START   =  0,
		HT_TALKING =  1,
		HT_UNK2    =  2,
		HT_UNK3    =  3,
		HT_UNK4    =  4,
		HT_UNK5    =  5,
		HT_UNK6    =  6,
		HT_UNK7    =  7,
	};

	enum DeathStates : s8
	{
		DH_UNK0   	   =  0,
		DH_DEATH_PLANE =  1,
		DH_BURN 	   =  2,
		DH_QUICKSAND   =  3,
		DH_ELECTROCUTE =  4,
		DH_TOXIC_GAS   =  5,
		DH_WHIRLPOOL   =  6,
		DH_DROWN   	   =  7,
		DH_WATER       =  8,
		DH_UNK9    	   =  9,
	};

	enum ScaleStates : u8
	{
		SC_JUMPED_ON   =  0,
		SC_SQUISHED    =  1,
		SC_MEGA_GROW   =  2,
		SC_MEGA_SHRINK =  3,
	};

	enum OnWallStates : s8
	{
		OW_LEFT  = 0,
		OW_RIGHT = 1,
		OW_PUSH  = 2,
	};

	enum StuckInGroundStates : u8
	{
		SG_INIT = 0,
		SG_MAIN = 1,
		SG_END  = 2,
	};

	enum ClsnStateFlags
	{
		ON_GROUND  		  = 1 << 0,
		ON_WALL   		  = 1 << 1,
		ON_CEILING_CORNER = 1 << 2,
		ON_CEILING 		  = 1 << 3,
	};

	enum Flags2
	{
		F2_SLIDE_ON_SURFACE   = 1 << 0,
		F2_PLAYER_IN_MOUTH    = 1 << 1,
		F2_CAMERA_ZOOM_IN     = 1 << 2,
		F2_TELEPORT           = 1 << 3,



		F2_RESET_POSITION     = 1 << 7,
		F2_JUMP_BUFFERED	  = 1 << 8,
		F2_NO_WALL_SLIDE      = 1 << 9,
		F2_EXIT_LEVEL_IF_DEAD = 1 << 10,
		F2_NO_CONTROL         = 1 << 11,
		F2_START_FLOWER_POWER = 1 << 12
	};

	struct State
	{
		bool(Player::* init)();
		bool(Player::* main)();
		bool(Player::* cleanup)();
	}
	static
		ST_LEDGE_HANG,
		ST_LEDGE_GRAB,
		ST_CEILING_GRATE,
		ST_YOSHI_POWER, // tongue, spitting, throwing egg, breathing fire
		ST_SWALLOW,
		ST_IN_YOSHI_MOUTH,
		ST_SMALL_LAUNCH_UP, // never set? (1 call)
		ST_HURT,
		ST_HURT_WATER,
		ST_ELECTROCUTE,
		ST_BURN_FIRE,
		ST_BURN_LAVA,
		ST_DEAD_HIT,
		ST_DEAD_PIT,
		ST_WALK,
		ST_WAIT,
		ST_GRABBED,
		ST_TURN_AROUND,
		ST_JUMP,
		ST_FALL,
		ST_THROWN,
		ST_SIDE_FLIP,
		ST_SLIDE_KICK_RECOVER,
		ST_FLY,
		ST_NO_CONTROL, // includes caps
		ST_OWL,
		ST_DEBUG_FLY,
		ST_WIND_CARRY,
		ST_BALLOON,
		ST_TELEPORT,
		ST_TORNADO_SPIN,
		ST_CANNON,
		ST_SQUISH,
		ST_SHELL,
		ST_STOMACH_SLIDE,
		ST_BUTT_SLIDE,
		ST_DIZZY_STARS,
		ST_HOLD_LIGHT,
		ST_BONK,
		ST_HOLD_HEAVY,
		ST_WALL_SLIDE,
		ST_BOWSER_EARTHQUAKE,
		ST_WALL_JUMP,
		ST_SLOPE_JUMP,
		ST_STUCK_IN_GROUND,
		ST_LAND,
		ST_ON_WALL,
		ST_SPIN,
		ST_TALK,
		ST_CRAZED_CRATE,
		ST_WAIT_QUICKSAND,
		ST_LEVEL_ENTER,
		ST_JUMP_QUICKSAND,
		ST_CROUCH,
		ST_RESPAWN,
		ST_CRAWL,
		ST_BACK_FLIP,
		ST_OPENING_WAKE_UP,
		ST_LONG_JUMP,
		ST_PUNCH_KICK,
		ST_ENDING_FLY,
		ST_GROUND_POUND,
		ST_DIVE,
		ST_THROW,
		ST_SPIN_BOWSER,
		ST_SWING_PLAYER,
		ST_SWEEP_KICK,
		ST_SLIDE_KICK,
		ST_FIRST_PERSON,
		ST_NULL, // all its functions are "return 1,"
		ST_SWIM,
		ST_WATER_JUMP,
		ST_METAL_WATER_GROUND,
		ST_METAL_WATER_WATER,
		ST_CLIMB,
		ST_HEADSTAND,
		ST_POLE_JUMP,
		ST_HEADSTAND_JUMP;

	u32 unk0d4;
	u32 unk0d8;
	ModelAnim2* bodyModels[5]; //the fifth one is the Metal Wario model
	ModelAnim balloonModel;
	Model* headModels[4]; //Yoshi's is a ModelAnim
	Model* headNoCapModels[4]; //Yoshi's is the mouth-is-full model
	ModelAnim wings;
	u32 unk1d8;
	TextureSequence texSeq1dc;
	TextureSequence texSeq1f0;
	TextureSequence texSeq204;
	TextureSequence texSeq218;
	MaterialChanger matChg22c;
	MaterialChanger matChg240;
	TextureSequence texSeq254;
	TextureSequence texSeq268;
	char* unk27c[4];
	char* unk28c[4];
	char* unk29c[4];
	ShadowModel shadow;
	MovingCylinderClsnWithPos cylClsn;
	MovingCylinderClsnWithPos cylClsn2;
	Actor* shellPtr;
	Actor* actorInHands;
	Actor* holdingActor;
	Actor* actorInMouth;
	Actor* unk364;
	ActorBase* speaker;
	u32 unk36c;
	State* currState;
	State* prevState;
	State* nextState;
	CylinderClsn* climbedCylClsn; // null if the player isn't climbing on anything
	WithMeshClsn wmClsn;
	Vector3 spawnPos;
	Vector3 unk548; //mirrors the player's position?
	Vector3 floorNormal;
	Vector3 wallNormal;
	u32 unk56c;
	u32 unk570;
	u32 unk574;
	char* unk578;
	char* unk57c;
	Vector3_16 unk580;
	u16 unk586;
	Actor** eggPtrArr;
	u32 unk58c;
	u32 unk590;
	u32 unk594;
	u32 unk598;
	u32 unk59c;
	u32 unk5a0;
	u32 unk5a4;
	u32 unk5a8;
	u32 unk5ac;
	u32 unk5b0;
	u32 unk5b4;
	u32 unk5b8;
	Matrix4x3 unkMat5bc;
	Matrix4x3 eatMatrix;
	u32 unk61c;
	u32 uniqueSoundID; // play with unique ID
	u32 playLongUniqueID;
	u32 unk628;
	u32 unk62c;
	u32 unk630;
	u32 unk634;
	u32 unk638;
	u32 animID;
	Fix12i unk640;
	Fix12i floorY;
	u32 unk648;
	Fix12i unk64c;
	Fix12i unk650;
	u32 unk654;
	u32 floorTracID;
	u32 floorCamBehavID;
	u32 floorViewID;
	u32 floorBehavID;
	u32 unk668;
	u32 floorTexID;
	u32 floorWindID;
	u32 unk674;
	u32 prevMusicID;
	u32 nextMusicID;
	u32 currMusicID;
	Fix12i jumpPeakHeight; // 0x684
	union { s32 msgID; Fix12i yPosOnPole; /* zero at the bottom of the pole */ };
	Fix12i yVisualOffset;
	Fix12i unk690;
	Fix12i unk694;
	s16 spawnAngY;
	s16 unk69a;
	s16 spinningAngularVelY; // used for at least turning on poles and spinning Bowser
	s16 unk69e;
	u16 visibilityCounter; // the player is visible when this is even (except when the player is electrocuted the second bit is checked instead)
	u16 unk6a2;
	s16 stateTimer; // sleep, run charge, etc.
	u16 noControlTimer;
	union { u16 unk6a8; u16 jumpSequenceTimer;}; // underwater splash bubbles, tree particles, jump related, etc.
	u16 nextPunchKickDelay;
	u16 walkRunDecelTimer;
	s16 featherCapTimeRemaining; // 0x6AE
	u16 unk6b0;
	u16 squishedTimer;
	u16 unk6b4;
	u16 unk6b6; // climbing related
	u16 swimHealTimer;
	u16 waterRunTimer;
	u16 unk6bc;
	u16 powerupTimer;
	u16 balloonTimer;
	u16 superMushroomTimer;
	u16 unk6c4;
	u16 yoshiSwallowTimer;
	u16 warpTimer;
	u16 swimHurtTimer;
	s16 unk6cc;
	s16 flags2; // 0x6ce && 0x6cf
	s16 megaDestroyCounter;
	s16 inputAngle;
	s16 spinAngle;
	s16 unk6d6;
	u8 playerID; // always 0 in single player mode
	u8 realChar; // probably
	u8 unk6da;
	u8 renderedChar;
	u8 prevHatChar; // 0x6DC
	u8 currHatChar; // 0x6DD
	bool isInAir;
	bool landingSoundPlayed;
	bool isBraking;
	u8 currJumpNumber; // 0x6E1: 0 - first, 1 - second, 2 - triple jump   (also used for the Crazed Crate)
	u8 currPunchKickNumber; // 0x6E2: 0 - first, 1 - second, 2 - kick, 3 - sweepkick
	s8 stateState; // 0x6E3: the current state of the current state. How meta.
	bool isInSlidingState;
	union
	{
		u8 unk6e5;
		bool noControl;
		bool canFlutterJump;
		bool landedUnderwater;
		u8 runUpAnimCounter;
		u8 burnCounter;
		u8 buttSlideCounter;
		bool ceilingHangingLeft;
		bool slideKickBounced;
		u8 stuckInGroundState;
	};
	u8 slidingState;
	u8 unk6e7;
	u8 unk6e8;
	u8 currClsnState; // 0x06E9: 0 - not colliding, 1 - standing on ground, 2 - colliding with wall in water, 3 - colliding with wall on land
	bool canRunOnWater;
	u8 unk6eb;
	u8 unk6ec;
	u8 runUpCounter;
	u16 unk6ee; // related to eating; not sure if 0x6EE and 0x6EF are shared
	u16 unk6f0;
	u8 scaleIndex;
	u8 scaleState; // 0x6f3: 0 - jumped on, 1 - squished, 2 - mega grow, 3 - mega shrink
	bool hasFireInMouth;
	u8 opacity;
	bool powerupTimersFrozen;
	bool playingShellSwimMusic;
	bool isFireYoshi;       // 0x6f8
	bool isMetalWario;      // 0x6f9
	bool usesMetalModel;    // 0x6fa
	bool isVanishLuigi;     // 0x6fb
	bool usesVanishTexture; // 0x6fc
	bool isBalloonMario;    // 0x6fd
	bool usesBalloonModel;  // 0x6fe
	bool isWingMario;       // 0x6ff
	bool usesWingModel;     // 0x700
	u8 unk701;
	u8 powerupBlinkToggle; // used when your powerup timer is low. hide powerup if 0, show if 1
	bool isMega;
	u8 unk704;
	u8 unk705;
	bool isUnderwater;
	bool standingInPuddle;
	u8 isBeingHurt;
	bool isInvulnerable;
	u8 noControlState; // 0x70a
	u8 unk70b;
	u8 currGroundedState;
	bool isLongFalling;
	u8 onSlopedSurface;
	u8 unk70f;
	bool isWalking;
	bool unk711;
	bool isInAirIsh; // 0x712
	bool isTangible;
	bool unk714;
	u8 cameraZoomLevel;
	bool isIntangibleToMesh;
	u8 unk717;
	u16 unkFlags;
	bool collectingLostCap;
	bool quickSandJump;
	u8 unk71c;
	u8 unk71d;
	u8 unk71e;
	u8 unk71f;
	u16 unk720;
	bool unk722;
	bool unk723;
	u32 unk724;
	u32 unk728;
	u32 unk72c;
	u32 unk730;
	u32 unk734;
	u32 unk738;
	s16 toonStateAndFlag; //8 possible states, 0x8000 is the invincible-and-can't-collect-caps flag
	s16 unk73e;
	Fix12i toonIntensity;
	Vector3 lookAtPos;
	u32 unk750;
	u32 unk754;
	u32 unk758;
	s16 unk75c;
	s16 spineAngleOffsY; // is added to bodyModels[GetBodyModelID(param1 & 0xff, false)]->data.bones[8].rot.y
	s16 spineAngleOffsZ; // is added to bodyModels[GetBodyModelID(param1 & 0xff, false)]->data.bones[8].rot.z
	u8 unk762;
	u8 unk763;
	u32 unk764;
	
	static SharedFilePtr* ANIM_PTRS[s32{NUM_ANIMS} * NUM_CHARACTERS];
	static_assert(s32{NUM_ANIMS} * NUM_CHARACTERS == 0x308);

	Player();

	virtual s32 InitResources() override;
	virtual s32 CleanupResources() override;
	virtual s32 Behavior() override;
	virtual s32 Render() override;
	virtual void OnPendingDestroy() override;
	virtual ~Player() override;
	virtual u32 OnYoshiTryEat() override;
	
	void IncMegaKillCount();
	void SetNewHatCharacter(u32 character, u32 arg1, bool makeSfx);
	void SetRealCharacter(u32 character);
	void TurnOffToonShading(u32 character);
	void InitPlayerCylClsn();
	
	bool IsInState(const State& state);
	bool WasPreviousState(const State& state);
	void WarioLandCamShake();
	bool IsDiving();
	bool IsInsideOfCannon();
	bool ToonStateActive();
	bool IsCollectingCap();
	bool HasNoCap();
	void Unk_020c6a10(u32 arg0);
	bool Unk_020c4f40(u16 newUnk6a6);
	s32 Unk_020ca8f8();
	void ResetPlayerClsnAndClimbClsn();
	bool Unk_020c9e5c(u8 arg0);
	bool Unk_020ca488(); // calls Unk_020c9e5c(0xb);
	bool Unk_020ca150(u8 arg0);
	u32 GetBodyModelID(u32 character, bool checkMetalStateInsteadOfMetalModel) const;
	void HandleReturnLevelAndEntrance();
	ModelAnim2* GetBodyModel();
	void SetAnim(u32 animID, s32 flags, Fix12i animSpeed = 1._f, u32 startFrame = 0);
	void UpdateAnim();
	bool ShowMessage(ActorBase& speaker, u32 msgIndex, const Vector3* lookAt, u32 arg3, u32 arg4);
	bool ShowMessage2(ActorBase& speaker, u32 msgIndex, const Vector3* lookAt, u32 arg3, u32 arg4);
	bool StartTalk(ActorBase& speaker, bool noButtonNeeded); //true iff the talk actually started.
	bool Unk_020c5244(); // always returns false
	s32 GetTalkState();
	void PlayStuckInGroundParticles();
	bool HasFinishedTalking();
	bool HurtNoOverrideCheckDeath(u32 damage, bool dropHeldActor);
	s32 GetHurtState();
	bool IsOnShell(); // if not on shell, reset shell ptr
	bool IsEnteringLevel(); // entering entrance, not entering exit
	bool IsBeingShotOutOfCannon();
	bool CanPause();
	void Burn();
	void Shock(u32 damage);
	bool CheckSpitOutPlayer();
	bool TrySpitPlayerFromMouth();
	bool IsInYoshisMouth();
	void RegisterEggCoinCount(u32 numCoins, bool includeSilverStar, bool includeBlueCoin);
	//speed is multiplied by constant at 0x020ff128+charID*2 and divided by 50 (? could be 25, could be 100).
	void Hurt(const Vector3& source, u32 damage, Fix12i speed, u32 arg4, u32 presetHurt, u32 spawnOuchParticles); // speed is multiplied by constant at 0x020ff128+charID*2 and divided by 50 (? could be 25, could be 100).
	void Heal(s32 health);
	s32 GetHealth();
	void PlayMegaStompEffects();
	void Bounce(Fix12i bounceInitVel);
	void SpinBounce(Fix12i bounceInitVel);
	void HandleYoshiFlutterJump();
	void HandleLuigiFlutterJump();
	void HandleVariableJumpHeight();
	bool ChangeState(Player::State& state);
	bool JumpIntoBooCage(Vector3& cagePos);
	bool EnterWhirlpool();
	bool SetDeathState(u8 deathState);
	void HandleWalkOrRun();
	void BlowAway(s16 dir);
	bool IsInAirAndAirIsh();
	bool CanWarp();
	bool IsStateEnteringLevel();
	bool SetNoControlState(u8 arg0, s32 messageID, u8 arg2);
	bool TryTalkToKeyDoor();
	bool TryTalkToDoor(u8 arg0);
	void OpenBigDoor();
	bool CanEnterDoor(u8 newStateState);
	bool TryExitWhiteDoorWithStar();
	bool TryExitCharacterDoorWithIntro();
	bool IsOpeningDoorWithStar();
	bool TryEnterStarDoor(Vector3& doorPos, s16 doorAng);
	void PlayMammaMiaSound();
	bool TryDropHeldActor();
	bool TryGrab(Actor& actor);
	bool DropActor();
	bool FinishedAnim();
	void HandleRunningDust();
	void HandleFootsteps();
	bool ApproachHorzSpeedCheckSlope(Fix12i dest, Fix12i step);

	void Unk_020bf13c();
	bool UpdateBeingHeld(); // returns whether being held
	Fix12i ScaleHorzSpeedByMag(Fix12i baseSpeed, Fix12i minSpeed);
	Fix12i ScaleVertAccelByChar(Fix12i baseAccel);
	void SetSpeedYByChar(Fix12i baseSpeed);
	Fix12i ScaleHorzSpeedByChar(Fix12i baseSpeed);
	void UpdateSwimmingClsn(CylinderClsn& cylClsn);
	Fix12i ScaleHorzAccelByFloorTraction(Fix12i baseSpeed);
	void RunningDust();
	void SlidingDust();
	void PlayerLandingDust();
	bool Unk_020c0108(bool arg0);
	u32 GetFloorTractionID();
	Fix12i GetHangableCeilingHeight();
	void UpdateCeilingHang();
	bool CheckCanPullUp();
	bool RaycastActorClsnNoWarpPipe(const Vector3& pos0, const Vector3& pos1);
	bool CheckForcePullUp();
	void SetStomachOrButtSlide(u8 slideCondition);
	void ZeroVertAccelYSpeedHorzSpeed();
	bool ShouldSlide();
	bool CheckGroundNotSteep();
	void ApplySlopeAccel();
	bool DecelerateSlide(Fix12i minSlideSpeed);
	bool TrySnapToGroundFromSlide(); // Responsible for up/downwarps
	bool CheckShouldSlide();
	s16 GetFloorAngle(s16 offset);
	void HandleTilt(bool scaleByHorzSpeed);
	bool RaycastFromPos(u8 horzOffset, u8 vertOffset);
	bool CheckSideStep(s16 wallAngle);
	bool SetWallSlideOrBounceBack(s16 wallAngle);
	s32 ApplySlopeTransform();
	void InitBonk(s16 bonkAngle);
	bool ShouldBonk(s16 wallAngle);
	bool CheckBonkOrWallSlide();
	void UpdateFloorCollision();
	void PlayJumpLandSound();
	void IntroducePowerup(u8 powerupType);
	bool FaceLookAtPos();
	void RiseToWaterSurface();
	Fix12i ScaleRiseToSurfaceSpeedByChar();
	void MakePlayerInvulnerable();
	void SetFirstPerson();
	void WadingRipples(Fix12i speedToCompare);
	void UpdateCameraZoom();
	bool IsOnWaterSurface();
	bool HandleSwimHealthCheckDeath();
	bool IsHangingFromCeiling();
	bool TryLedgeHang(Fix12i maxGrabHeight, bool facingAway);
	bool ShouldLedgeHang();
	void AdjustLedgeHangPosAndFall();
	void SetPunchKickAttack(u8 punchKickNumber);
	void ClearActorInMouth();
	bool CheckLedgeHangOrGrab();
	bool CheckCeilingAbove();
	bool SetCrouchJumpAction();
	bool SetCrouchAttackAction();
	bool ChangeStateFromWait(Fix12i minMagForWalk);
	bool HandleWaitAnim();
	bool CheckTeleport();
	bool SetLandingState(bool disallowCrouchAction);
	bool HandleWalkAndRunCheckTurnAround();
	void StopBraking();
	bool CheckThrowHeldPlayer();
	void UpdateAirWithTurn();
	void InitDiveHitbox();
	void InitSlideKickHitbox();
	void UpdateAirWithoutTurn(Fix12i horzAccelInput, Fix12i horzAccelNeutral);
	bool CheckYoshiMakeEgg();
	bool CheckYoshiSwallow();
	void HandleYoshiAttack();
	bool CheckJumpOnPlayer();
	void HandleRunLean(s16 playerMotionAngY);
	void TrySetBrakeAnim();
	void GetThrown(Fix12i horizontalSpeed, Fix12i verticalSpeed, s16 angle);
	void UpdatePlayerScale();
	void ApplyScaleState(u8 newScaleState);
	void InitGroundPoundCylClsn2();
	void InitPunchKickCylClsn2();
	void AdjustSlideAngle();
	void Unk_020de3d0(s16 ang0, s16 ang1);
	void PlayBalloonBoundSound();
	bool CanBeHurt();
	bool TryMakeDizzy();
	void TryGroundPoundPlayer(); //Multiplayer only
	bool SetDiveOrKick();
	bool IsFlying();
	void TryRunningDustAfterLand();
	u32 GetJumpLandAnim();
	bool ShouldUseCrazedCrate(Actor* actor);
	void HandleCrazedCrateBounce(u8 bounceNumber);
	void PlayLandSuccessVoice();
	void PlayJumpVoice(u8 jumpNumber);
	bool SetMidairAction();
	void HandleSlowsandJump();
	bool ForceQuicksandJumpIfSunk();
	bool ForceJumpIfMega();
	bool CheckShouldSlopeJump();
	bool ShouldGetStuckInGround();
	u8 GetLandingType();
	void UpdatePlayerModel();
	static bool CheckCornerCorrectOnActor(WithMeshClsn& wmClsn, Actor& jumper);
	static bool CheckMegaPlayerCollisionWithActor(WithMeshClsn& wmClsn, Actor& megaPlayer);
	static bool CheckShotIntoActor(WithMeshClsn& wmClsn, Actor& shooter);
	static bool CheckPushActor(WithMeshClsn& wmClsn, Actor& pusher);
	static bool CheckKickOrSweepKickActor(WithMeshClsn& wmClsn, Actor& kicker);
	static bool CheckPunchActor(WithMeshClsn& wmClsn, Actor& puncher);
	static bool CheckGroundPoundOnActor(WithMeshClsn& wmClsn, Actor& groundpounder);
	static bool CheckOnWallOnActor(WithMeshClsn& wmClsn, Actor& actor);
	Fix12i Unk_020f030c(u32 floorTraction);
	static bool OnSlopedGround(u32 floorTraction, Fix12i floorNormalY);

	u16 GetBreakFreeBonus();
	
	bool IsInAnim(u32 animID);
	bool IsFrontSliding();
	bool LostGrabbedObject();

	s32 CallKuppaScriptInstruction(char* instruction, s16 minFrame, s16 maxFrame);

	void PlaySubMusic(u32 musicID);
	void EndSubMusic(u32 musicID);

	void EndPowerupMusic(u32 musicID);
	void PlayPowerupMusic(u32 musicID);

	bool InitKoopaShell();
	void InitSuperMushroom();
	void InitWingFeathers(bool shouldIntroduceWings);
	void InitBalloonMario();
	void InitVanishLuigi();
	void InitMetalWario();
	void InitFireYoshi();

	void ForceSwallowStartFlowerPower(); 

	void CleanupAllPowerups();
	void CleanupSuperMushroom();
	void CleanupMetalWario();
	void CleanupVanishLuigi();
	void CleanupKoopaShell();
	void CleanupFireYoshi();
	void CleanupBalloonMario();
	void CleanupWingFeathers();

	bool St_LedgeHang_Init();
	bool St_LedgeHang_Main();
	bool St_LedgeHang_Cleanup();
	bool St_LedgeGrab_Init();
	bool St_LedgeGrab_Main();
	bool St_CeilingGrate_Init();
	bool St_CeilingGrate_Main();
	bool St_YoshiPower_Init();
	bool St_YoshiPower_Main();
	bool St_YoshiPower_Cleanup();
	bool St_Swallow_Init();
	bool St_Swallow_Main();
	bool St_InYoshiMouth_Init();
	bool St_InYoshiMouth_Main();
	bool St_InYoshiMouth_Cleanup();
	bool St_SmallLaunchUp_Init();
	bool St_SmallLaunchUp_Main();
	bool St_Hurt_Init();
	bool St_Hurt_Main();
	bool St_Hurt_Cleanup();
	bool St_HurtWater_Init();
	bool St_HurtWater_Main();
	bool St_Electrocute_Init();
	bool St_Electrocute_Main();
	bool St_BurnFire_Init();
	bool St_BurnFire_Main();
	bool St_BurnLava_Init();
	bool St_BurnLava_Main();
	bool St_DeadHit_Init();
	bool St_DeadHit_Main();
	bool St_DeadPit_Init();
	bool St_DeadPit_Main();
	bool St_Walk_Init();
	bool St_Walk_Main();
	bool St_Wait_Init();
	bool St_Wait_Main();
	bool St_Wait_Cleanup();
	bool St_Grabbed_Init();
	bool St_Grabbed_Main();
	bool St_Grabbed_Cleanup();
	bool St_TurnAround_Init();
	bool St_TurnAround_Main();
	bool St_Jump_Init();
	bool St_Jump_Main();
	bool St_Fall_Init();
	bool St_Fall_Main();
	bool St_Thrown_Init();
	bool St_Thrown_Main();
	bool St_Thrown_Cleanup();
	bool St_SideFlip_Init();
	bool St_SideFlip_Main();
	bool St_SlideKickRecover_Init();
	bool St_SlideKickRecover_Main();
	bool St_Fly_Init();
	bool St_Fly_Main();
	bool St_NoControl_Init();
	bool St_NoControl_Main();
	bool St_NoControl_Cleanup();
	bool St_Owl_Init();
	bool St_Owl_Main();
	bool St_Owl_Cleanup();
	bool St_DebugFly_Init();
	bool St_DebugFly_Main();
	bool St_WindCarry_Init();
	bool St_WindCarry_Main();
	bool St_Balloon_Init();
	bool St_Balloon_Main();
	bool St_Balloon_Cleanup();
	bool St_Teleport_Init();
	bool St_Teleport_Main();
	bool St_TornadoSpin_Init();
	bool St_TornadoSpin_Main();
	bool St_Cannon_Init();
	bool St_Cannon_Main();
	bool St_Cannon_Cleanup();
	bool St_Squish_Init();
	bool St_Squish_Main();
	bool St_Squish_Cleanup();
	bool St_Shell_Init();
	bool St_Shell_Main();
	bool St_Shell_Cleanup();
	bool St_StomachSlide_Init();
	bool St_StomachSlide_Main();
	bool St_ButtSlide_Init();
	bool St_ButtSlide_Main();
	bool St_DizzyStars_Init();
	bool St_DizzyStars_Main();
	bool St_DizzyStars_Cleanup();
	bool St_HoldLight_Init();
	bool St_HoldLight_Main();
	bool St_HoldLight_Cleanup();
	bool St_Bonk_Init();
	bool St_Bonk_Main();
	bool St_HoldHeavy_Init();
	bool St_HoldHeavy_Main();
	bool St_WallSlide_Init();
	bool St_WallSlide_Main();
	bool St_BowserEarthquake_Init();
	bool St_BowserEarthquake_Main();
	bool St_WallJump_Init();
	bool St_WallJump_Main();
	bool St_SlopeJump_Init();
	bool St_SlopeJump_Main();
	bool St_StuckInGround_Init();
	bool St_StuckInGround_Main();
	bool St_Land_Init();
	bool St_Land_Main();
	bool St_OnWall_Init();
	bool St_OnWall_Main();
	bool St_Spin_Init();
	bool St_Spin_Main();
	bool St_Spin_Cleanup();
	bool St_Talk_Init();
	bool St_Talk_Main();
	bool St_Talk_Cleanup();
	bool St_CrazedCrate_Init();
	bool St_CrazedCrate_Main();
	bool St_CrazedCrate_Cleanup();
	bool St_WaitQuicksand_Init();
	bool St_WaitQuicksand_Main();
	bool St_LevelEnter_Init();
	bool St_LevelEnter_Main();
	bool St_LevelEnter_Cleanup();
	bool St_JumpQuicksand_Init();
	bool St_JumpQuicksand_Main();
	bool St_Crouch_Init();
	bool St_Crouch_Main();
	bool St_Respawn_Init();
	bool St_Respawn_Main();
	bool St_Crawl_Init();
	bool St_Crawl_Main();
	bool St_BackFlip_Init();
	bool St_BackFlip_Main();
	bool St_OpeningWakeUp_Init();
	bool St_OpeningWakeUp_Main();
	bool St_LongJump_Init();
	bool St_LongJump_Main();
	bool St_PunchKick_Init();
	bool St_PunchKick_Main();
	bool St_EndingFly_Init();
	bool St_EndingFly_Main();
	bool St_GroundPound_Init();
	bool St_GroundPound_Main();
	bool St_GroundPound_Cleanup();
	bool St_Dive_Init();
	bool St_Dive_Main();
	bool St_Throw_Init();
	bool St_Throw_Main();
	bool St_BowserSpin_Init();
	bool St_BowserSpin_Main();
	bool St_BowserSpin_Cleanup();
	bool St_SwingPlayer_Init();
	bool St_SwingPlayer_Main();
	bool St_SwingPlayer_Cleanup();
	bool St_SweepKick_Init();
	bool St_SweepKick_Main();
	bool St_SlideKick_Init();
	bool St_SlideKick_Main();
	bool St_FirstPerson_Init();
	bool St_FirstPerson_Main();
	bool St_FirstPerson_Cleanup();
	bool St_Null_Init();
	bool St_Null_Main();
	bool St_Null_Cleanup();
	bool St_Swim_Init();
	bool St_Swim_Main();
	bool St_Swim_Cleanup();
	bool St_WaterJump_Init();
	bool St_WaterJump_Main();
	bool St_MetalWaterGround_Init();
	bool St_MetalWaterGround_Main();
	bool St_MetalWaterGround_Cleanup();
	bool St_MetalWaterWater_Init();
	bool St_MetalWaterWater_Main();
	bool St_MetalWaterWater_Cleanup();
	bool St_Climb_Init();
	bool St_Climb_Main();
	bool St_Climb_Cleanup();
	bool St_Headstand_Init();
	bool St_Headstand_Main();
	bool St_Headstand_Cleanup();
	bool St_PoleJump_Init();
	bool St_PoleJump_Main();
	bool St_HeadstandJump_Init();
	bool St_HeadstandJump_Main();

	template<class ID>
	bool CustomStateFunc();

	void ChangeArea(s32 newAreaID)
	{
		areaID = newAreaID;
		::ChangeArea(newAreaID);
	}

	bool IsWarping() const
	{
		return currState == &ST_NO_CONTROL && stateState == 6;
	}
};

static_assert(sizeof(Player) == 0x768, "sizeof(Player) is incorrect!");
static_assert(Player::NUM_ANIMS == 194, "Player::NUM_ANIMS is incorrect!");
static_assert(Player::NUM_CHARACTERS == 4, "Player::NUM_CHARACTERS is incorrect!");
