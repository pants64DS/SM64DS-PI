#pragma once

struct Star : Enemy // internal name: daStar_c
{
	enum States
	{ 
		ST_SPAWN_LAUNCH_OR_JUMP,
		ST_LAUNCH_AFTER_JUMP,
		ST_LAUNCH,
		ST_LAND_AT_HOME,
		ST_WAIT,
		ST_ABOVE_HEAD_THEN_COLLECTING,
		ST_COLLECTING_START,
		ST_COLLECTING,
		ST_BOUNCE,
		ST_VS_STAR_WAIT,
		ST_JUST_COLLECTED,
		ST_TALK,
		ST_STAR_DOOR_CUTSCENE,
		ST_COLLECTING_SILVER_STAR_ON_SHELL,

		NUM_STATES
	};

	using State = void(Star::*)();

	enum Types : u8
	{
		TYPE_STATIONARY    	  = 0,
		TYPE_BOUNCING 	   	  = 1,
		TYPE_JUMP_THEN_LAUNCH = 2,
		TYPE_VS       	   	  = 3,
		TYPE_LAUNCH_IMMEDIATE = 4,
		TYPE_UNCOLLECTABLE 	  = 5,
		TYPE_STAR_SPHERE   	  = 6,
		TYPE_MINIMAP 	  	  = 7,
		TYPE_STAR_DOOR     	  = 8,
		TYPE_WHITE_DOOR   	  = 9,

		NUM_TYPES,
	};

	struct StarFlags
	{
		enum WaterState
		{
			WS_NOT  	      = 0x0,
			WS_SUBMERGING 	  = 0x1,
			WS_UNDERWATER 	  = 0x2,
		};

		bool isCollected         	 : 1 = false;
		bool isVisible           	 : 1 = false;
		bool isTransparent       	 : 1 = false;
		bool isIntangible       	 : 1 = false;
		u16  waterState   	    	 : 2 = WS_NOT;
		bool isDroppedStar	     	 : 1 = false;
		bool inStarSphere        	 : 1 = false; // set true when spawned by StarMarker of TYPE_STAR_SPHERE_SWITCH_STAR
		bool isStarSwitchPressed 	 : 1 = false;
		bool isSwitchStarCollectible : 1 = false;
		u16  messageResult 	     	 : 2 = 0;
		bool isCoinStar    	     	 : 1 = false;
		u16  padding            	 : 3 = 0;
	};

	MovingCylinderClsnWithPos cylClsn;
	WithMeshClsn wmClsn;
	ModelAnim modelAnim1;
	ModelAnim modelAnim2;
	ShadowModel shadowModel;
	Matrix4x3 shadowMat;
	Fix12i floorY;
	u32 soundObjUniqueID;
	u32 starMarkerUniqueID;
	Player* collector;
	u32 type;
	States state;
	States spawnState;
	Vector3 backupPos;
	Vector3 respawnPos;
	Vector3 prevCameraLookAt;
	Vector3 prevCameraPos;
	Vector3 unk478; // set to pos in init but never used
	Fix12i minY;
	Fix12i waterSurfaceY;
	u32 collectMusicID;
	u16 collectTimer;
	u16 switchStarAppearTimer;
	u16 bouncingSparklesTimer;
	s16 spawnFrameCounter;
	s8 trackStarID;
	s8 trueAreaID;
	u8 starMarkerType;
	u8 talkState;
	bool playedCollectJingle;
	u8 starID;
	u8 appearJingleTimer;
	bool inIceBlock;
	bool searchedForIceBlock;
	u8 whiteDoorMusicMuteTimer;
	StarFlags starFlags;
	u32 unk4a4; // unused
	Vector3 rootBonePos;
	u32 sparklesTrailParticleID;
	u32 squareSparklesParticleID;
	u32 bouncingSparklesParticleID;
	u32 silverStarSparklesParticleID;

	virtual s32 InitResources() override;
	virtual s32 CleanupResources() override;
	virtual s32 Behavior() override;
	virtual s32 Render() override;
	virtual ~Star() override;
	virtual u32 OnYoshiTryEat() override;
	virtual void OnTurnIntoEgg(Player& player) override;

	void PlayCollectJingle(u32 volume);
	void DeactivateSwitchStar();
	void InitializeWhiteDoorStar();
	void InitializeStarDoorCutsceneStar();
	void SearchForIceBlock();
	void UpdateWhiteDoorStarCollect(Player& player);
	void UpdateSwitchStar(bool starSwitchPressed);
	void HandleDroppedStar(Player& player, bool spawnedFromEgg, bool isSilver); // isSilver is overwritten in the function
	u8   GetCollectNoControlType();
	void RespawnAtStarMarker();
	void LinkDroppedStarToStarMarker();
	void UpdateSpawnCamera();
	void SetSpawnCameraLookat(Camera& camera);
	bool SetStarCamera(Camera& camera);
	void SetFloorY();
	bool SetAppearJingleTimer();
	void PlayAppearJingle();
	void KillSoundObjIfNecessary();
	void Unk_020e7eb4(); // Does nothing but return
	void UpdateSilverStarParticles();
	void UpdateBouncingParticles();
	void UpdateStarDoorUnlockParticles();
	void UpdateCollectParticles();
	void UpdateSpawnParticles();
	static void GetRootBonePos(Vector3& vec, Star& Star);
	void DropShadow();
	void UpdateModelTransform();
	void KillIfFinishedAnim();
	void UpdateBounce();
	void UpdateWaterState();
	void Respawn();
	void CheckOutOfBounds();
	void AddStarMarker();
	void TryAddStarMarker();
	void UpdateTurnIntoEgg(Player& player);
	bool Collect(Player& player);
	void HandleClsn();
	void SetMoveDefaults();
	void StopMoving();
	void LaunchHome(Vector3& targetPos, Fix12i yStrength);	
	void LinkStarMarker();
	bool CheckStayInCourse();
	u32  GetStarCollectMusicID();

	void St_SpawnLaunchOrJump();
	void St_LaunchAfterJump();
	void St_Launch();
	void St_LandAtHome();
	void St_Wait();
	void St_AboveHeadThenCollecting();
	void St_CollectingStart();
	void St_Collecting();
	void St_Bounce();
	void St_VsStarWait();
	void St_JustCollected();
	void St_Talk();
	void St_StarDoorCutscene();
	void St_CollectingSilverStarOnShell();
};

struct PowerStar : Star
{
	static constexpr u16 staticActorID = 0xb2;

	static SpawnInfo spawnData;
};

struct SilverStar : Star
{
	static constexpr u16 staticActorID = 0xb3;

	static SpawnInfo spawnData;
};

static_assert(sizeof(Star) == 0x4c4, "sizeof(Star) is incorrect!");
static_assert(sizeof(PowerStar) == 0x4c4, "sizeof(PowerStar) is incorrect!");
static_assert(sizeof(SilverStar) == 0x4c4, "sizeof(SilverStar) is incorrect!");

extern Vector3 STAR_CYL_CLSN_OFFSET; // { 0._f, -50._f, 0._f }