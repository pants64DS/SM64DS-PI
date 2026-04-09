#pragma once

struct CameraDef
{
	s32 unk00; // something to do with going behind the player...
	Fix12i unk04;
	s32 camVertAngIsh;
	u32 unk0c;
	Fix12i yOffset;
	Fix12i zOffset;
	u32 jumpWithPlayerIsh;
	s32 dist0; // ???
	s32 dist1;
	u16 fovOver2;
	u16 unk26;
};

//vtable at 0x02092720
struct View : ActorDerived // internal name: dView; done
{
	Matrix4x3 camMat; // View Matrix to use when rendering

	virtual s32 Render() override; // Sets the global view matrix to camMat and calculates the global inverse view matrix
	virtual ~View() override;
};

//vtable at 0x0208E730
struct Clipper
{
	Vector3 unk04[4]; // 0x4, 0x10, 0x1c, 0x28
	u32 unk34;
	u32 unk38;
	u32 unk3c;
	u32 unk40;
	u32 unk44;
	u32 unk48;
	Fix12i aspectRatio;
	Fix12i unk50;
	Fix12i unk54;
	u16 unk58;
	
	Clipper();
	virtual ~Clipper();

	Fix12i Func_020150E8(Vector3& arg1, Fix12i arg2, u8* arg3);
	Fix12i Func_02015560(Matrix4x3& arg1, Vector3& arg2, Fix12i arg3, Vector3& arg4);
	void Func_0201559C(); // no args
	void Func_020156DC();
};

//vtable at 0x02086F84, ctor at 0x0200E444
struct Camera : View // internal name: dCamera
{
	static constexpr u16 staticActorID = 0x14c;

	static constexpr u32 cameraDefTable = 0x02086FCC;

	enum Flags
	{
		UNDERWATER         = 1 << 0,
		ZOOMED_OUT         = 1 << 1,

		BOSS_TALK          = 1 << 3,
		STATE_LOCKED       = 1 << 4,
		ROTATING_LEFT      = 1 << 5,
		ROTATING_RIGHT     = 1 << 6,
		MEGA_CHARACTER     = 1 << 7,


		UNK_10             = 1 << 10,
		UNK_11             = 1 << 11,
		ARROWS_ALLOWED     = 1 << 12,
		LONG_IDLE_ZOOM_IN  = 1 << 13,
		TALK               = 1 << 14,
		ZOOM_OUT_FROM_TALK = 1 << 15,
		CEILING_HANG_ABOVE = 1 << 16,
		CEILING_HANG_BELOW = 1 << 17,

		ZOOMED_IN          = 1 << 19
	};

	struct State // Executes view specific camera behaviour
	{
		bool(Camera::* OnPlayerChangeState)(); // Nested call by Player::ChangeState()
		bool(Camera::* OnUpdate)();            // Nested call by Camera::Behaviour()
	}
	static
		ST_DEFAULT,
		ST_SWIM,
		ST_SURFACE_SWIM,
		ST_FLY, // feather, cannon shot
		ST_TOP_VIEW, // owl, tornado
		ST_SPIN,
		ST_DRIFT, // wind, balloon mario
		ST_CLIMB,
		ST_SLIDE,
		ST_ZOOM_IN,
		ST_VS_SILVER_STAR_GET,
		ST_CANNON_ENTER,
		ST_CANNON_AIM,
		ST_TALK,
		ST_DOOR_ENTER,
		ST_PAINTING_ZOOM_IN,
		ST_TALK_ZOOM_OUT,
		ST_CHARACTER_INTRO,
		ST_BOWSER_SPIN;

	Vector3 lookAt;
	Vector3 pos;            // 0x8c
	Vector3 ownerPos;       // 0x98
	Vector3 lookAtOffset;   // An offset from ownerPos to lookAt
	Vector3 savedLookAt;    // Saved to at talk
	Vector3 savedPos;       // Saved to at talk
	Vector3 unk0c8;         // Player's front lookAt?
	Vector3 unk0d4;         // Player's front pos?
	Vector3 unk0e0;         // Raycast result save (when the player becomes invisible to the camera)
	Vector3 unk0ec;         // Raycast result save (when the player becomes invisible to the camera)
	Fix12i aspectRatio;     // Aspect ratio, default = 1.33 (4:3)
	Fix12i unk0fc;          // Clipper related (near+far)
	Fix12i unk100;          // Clipper related
	Fix12i fovInvSin;             // Clipper related
	Fix12i fovInvCos;             // Clipper related
	u8 viewportLeft;        // Viewport x for left border
	u8 viewportBottom;      // Viewport y for bottom border
	u8 viewportRight;       // Viewport x for right border
	u8 viewportTop;         // Viewport y for top border
	Actor* owner;           // The player stalked by the camera
	Actor* unk114;          // Set at special camera scene? Set to King Bomb-Omb for example
	Actor* unk118;          // Another unknown actor
	Vector3* unk11c;        // Related to unk118, set to 0xDFE60 at 0x02009F3C
	Vector3 unk120;         // unk118's or (if unk118 == 0) unk114's position vector
	Fix12i unk12c;          // Distance to unk114?
	Fix12i unk130;          // Linear camera movement interpolator (only for unk114?) that (when entering a different camera view like at the top of BoB) interpolates from 0x0 to 0x100 and backwards when leaving. As a result, it also indicates whether the owner is in a special camera scene. unk114 is linked later during interpolation.
	Fix12i unk134;          // Ground pound camera jitter offset. Starts at 0xC000 and vibrates back and forth with alternating signs until it reaches 0.
	State* currState;       // Pointer to the current setting behaviour, which in turn sets the CameraDef's
	CameraDef* defaultCamDef;
	CameraDef* currCamDef;
	LevelOverlay::ViewObj* currView;
	Vector3* pausePos;
	u32 unk14c;
	u32 unk150;
	u32 flags;
	u32 rotationSoundUniqueID;
	u32 unk15c;
	u32 unk160;
	u32 unk164;
	Fix12i longIdleFovScale;
	u32 unk16c;
	u32 unk170;
	u32 unk174;
	s16 angZ;
	s16 fov;
	s16 angY; // ?
	s16 angX;
	s16 eightDirAngleY;
	s16 eightDirStartAngle;
	s16 eightDirDeltaAngle;
	s16 unk186;
	u16 unk188;
	s16 zShakeAngleOscillator;
	s16 zShakeMaxAngle;
	u16 unk18e;
	u32 unk190;
	u16 unk194;
	u16 unk196;
	u32 unk198;
	u32 unk19c;
	u32 unk1a0;
	u16 unk1a4;
	u8 unk1a6;
	u8 unk1a7;

	Camera();
	virtual ~Camera() override;
	virtual s32  InitResources() override;
	virtual s32  CleanupResources() override;
	virtual s32  Behavior() override;
	virtual s32  Render() override;
	virtual void OnPendingDestroy() override;

	void SaveCameraStateBeforeTalk(); // Saves the current camera state
	s32 CallKuppaScriptInstruction(char* instruction, s16 minFrame, s16 maxFrame);
	Fix12i ScaleByFOVInvCos(Fix12i y);
	Fix12i ScaleByFOVInvSin(Fix12i z);
	void SetFlag_3();
	void ClearZoomOutFlag(u8 playerID);
	bool TryZoomOut(u8 playerID);
	void SetCameraDef(u32 type);
	void SetLookAt(const Vector3& lookAt);
	void SetPos(const Vector3& pos);
	void SetCamToOwner();
	void SetDefaults();
	bool IsUnderwater() const;
	void SetHurtZShakeAngle();
	s32 ChangeState(Camera::State& newState);
	void SetBowserSpinCam(u8 playerID);
	void SetCharacterIntroCam(u8 playerID);
	void SetPaintingZoomInCam(Actor& exit);
	void SetDoorEnterCam(u8 playerID);
	void SetCannonAimCam(u8 playerID);
	void SetCannonEnterCam(u8 playerID);
	void SetTalkCam(u8 playerID, Vector3* newUnk11c);
	void SetVsSilverStarGetCam(u8 playerID);
	void SetSlideCam(u8 playerID);
	void SetHeadstandCam(u8 playerID);
	void SetClimbCam(u8 playerID);
	void SetZoomedInClimbCam(u8 playerID);
	void SetDriftCam(u8 playerID);
	void SetSpinCam(u8 playerID);
	void SetTopViewCam(u8 playerID);
	void SetFlyCam(u8 playerID);
	void SetSurfaceSwimCam(u8 playerID);
	void SetSwimCam(u8 playerID);
	void SetTalkZoomOutCam(u8 playerID);
	void SetZoomInCam(u8 playerID);
	void SetCeilingHangCam(u8 playerID, u32 clpsCamBehavID);
	void SetDefaultCam(u8 playerID);
	void CameraShakeAt(const Vector3& source, Fix12i magnitude);
	void SetFOV(s16 newFov);

	// Func_0200D954
	// Func_0200D8C8
	// All funcs between Camera() and ~Camera() should belong to this object, but I couldn't prove it since they're never really called.

	bool St_Default_OnPlayerChangeState();
	bool St_Default_OnUpdate();
	bool St_Swim_OnPlayerChangeState();
	bool St_Swim_OnUpdate();
	bool St_SurfaceSwim_OnPlayerChangeState();
	bool St_SurfaceSwim_OnUpdate();
	bool St_Fly_OnPlayerChangeState();
	bool St_Fly_OnUpdate();
	bool St_TopView_OnPlayerChangeState();
	bool St_TopView_OnUpdate();
	bool St_Spin_OnPlayerChangeState();
	bool St_Spin_OnUpdate();
	bool St_Drift_OnPlayerChangeState();
	bool St_Drift_OnUpdate();
	bool St_Climb_OnPlayerChangeState();
	bool St_Climb_OnUpdate();
	bool St_Slide_OnPlayerChangeState();
	bool St_Slide_OnUpdate();
	bool St_ZoomIn_OnPlayerChangeState();
	bool St_ZoomIn_OnUpdate();
	bool St_VsSilverStarGet_OnPlayerChangeState();
	bool St_VsSilverStarGet_OnUpdate();
	bool St_CannonEnter_OnPlayerChangeState();
	bool St_CannonEnter_OnUpdate();
	bool St_CannonAim_OnPlayerChangeState();
	bool St_CannonAim_OnUpdate();
	bool St_Talk_OnPlayerChangeState();
	bool St_Talk_OnUpdate();
	bool St_DoorEnter_OnPlayerChangeState();
	bool St_DoorEnter_OnUpdate();
	bool St_PaintingZoomIn_OnPlayerChangeState();
	bool St_PaintingZoomIn_OnUpdate();
	bool St_TalkZoomOut_OnPlayerChangeState();
	bool St_TalkZoomOut_OnUpdate();
	bool St_CharacterIntro_OnPlayerChangeState();
	bool St_CharacterIntro_OnUpdate();
	bool St_BowserSpin_OnPlayerChangeState();
	bool St_BowserSpin_OnUpdate();
};

extern Clipper GLOBAL_CLIPPER;
extern CameraDef* UNK_0208715C;
