#pragma once

#include "Scene.h"
#include "Actor/SpawnInfo.h"

struct MinimapChangeObject
{
	Fix12i posY;
	u8 param;
	MinimapChangeObject* prev;
	MinimapChangeObject* next;
};

struct Area
{
	TextureTransformer* texSRT;
	bool showing;
	u8 unk5;
	u16 unk6;
	MinimapChangeObject* minimapChanger;
};

struct Fog
{
	u8 table[32];
	bool enabled;
	u8 info;
	u16 offset;
	u16 color;
	u16 unk26; // unk992 / unk9ba

	void Init(u16 newColor, Fix12i startDist, Fix12i endDist);
};

struct Stage : Scene
{
	static constexpr u16 staticActorID = 3;

	enum LevelClearScreenStates
	{
		LC_ST_INIT,
		LC_ST_COUNT_COINS,
		LC_ST_INIT_BUTTONS,
		LC_ST_WAIT_FOR_INPUT,
		LC_ST_SAVE_INIT,
		LC_ST_SAVE,
		LC_ST_CLOSE,

		LC_NUM_STATES,
	};

	enum PauseScreenStates
	{
		PC_ST_MAIN_HUB_INIT         = 0,
		PC_ST_MAIN_HUB              = 1,
		PC_ST_MAIN_INIT             = 2,
		PC_ST_MAIN                  = 3,
		PC_ST_MAIN_VS_INIT          = 4,
		PC_ST_MAIN_VS               = 5,
		PC_ST_QUIT_VS               = 6,
		PC_ST_CONTROLLER_MODES_INIT = 7,
		PC_ST_CONTROLLER_MODES      = 8,
		PC_ST_OPTIONS_INIT          = 9,
		PC_ST_OPTIONS               = 10,
		PC_ST_MAIN_OPTIONLESS       = 11,
		PC_ST_QUIT_INIT             = 12,
		PC_ST_QUIT                  = 13,
		PC_ST_SAVE_INIT             = 14,
		PC_ST_SAVE                  = 15,
		PC_ST_DONT_SAVE_INIT        = 16,
		PC_ST_DONT_SAVE             = 17,
		PC_ST_DONT_SAVE_CLEANUP     = 18,
		PC_ST_EXIT_COURSE           = 19,

		PC_NUM_STATES               = 20,
	};

	Particle::SysTracker particleSysTracker; // 0x50
	Model model;               // 0x86c
	Area areas[8];             // 0x8bc
	MeshCollider clsn;         // 0x91c
	Fog fog[2];                // 0x96c
	Model* skyBox;             // 0x9bc
	u32 unk9c0;                // 0x9c0
	u32 unk9c4;                // 0x9c4

	static BaseSpawnInfo spawnData;

	Stage();
	virtual s32 InitResources() override;
	virtual bool BeforeInitResources() override;
	virtual s32 CleanupResources() override;
	virtual s32 Behavior() override;
	virtual s32 Render() override;
	virtual void OnPendingDestroy() override;
	virtual ~Stage() override;

	void LoadFog();
	void LoadModel();
	void LoadTextureTransformers();
	void LoadSkybox();
	void RenderFog();
	void RenderModel();
	void RenderModelTransparent();

	static void SetVramBanks();
	static void ResetMeshColliders(); // identical function at 0x02039218
	static void LoadClsnAndObjects(LevelOverlay& levelOverlay, u32 entranceID, MeshCollider& clsn);
	static void LoadGraphics2D(bool vsMode, s32 levelID);

	static u32 GetSkyboxID();
	static bool CanPause();
	static bool IsPauseDisabled();
	
	static void CheckCameraInput();
	static void CheckInput();
	static void UpdateMessage();

	static void RenderVsModeCountdown();
	static void RenderVsModeNewStar();
	static void RenderBouncingArrows();
	static void RenderNumber(u8 number, s32 x, s32 y, bool main, s32 palette);

	static void UpdateMenuButtons(bool unselectAll);

	static void LC_Update();
	static void LC_Render();

	static void VE_Init();
	static void VE_Update();

	static void PS_Init();
	static void PS_Update();
	static void PS_Cleanup();
	static void PS_Render();
	static void PS_UpdateOkAndBackButtons(bool unselectAll);
	static void PS_UpdateOptionsMenu();
	static void PS_UpdateSaveMenu(bool unselectAll);

	static s32 GraphCallback1(); // calls Particle::RenderAll
	static s32 GraphCallback2(SceneRelated* sceneRelated); // probably minimap related
};

static_assert(sizeof(Stage) == 0x9c8, "Size of Stage is incorrect.");

extern LevelOverlay* LEVEL_OVERLAY_PTR;

#ifndef NO_SM64DSe_PATCH
// pointed by LEVEL_OVERLAY_PTR, not in a fixed address in the vanilla game
extern LevelOverlay LEVEL_OVERLAY;
#endif

extern ModelComponents* LEVEL_MODEL_DATA;

extern u8 NUM_ENTRANCES;
extern u32 NUM_PATHS;
extern u8 NUM_VIEWS;
extern u8 NUM_TELEPORT_DEST_OBJS;
extern u8 NUM_FOG_OBJS;
extern u8 MAP_TILE_ARR_SIZE;
extern u8 NUM_MINIMAP_SCALE_OBJS;

extern LevelOverlay::EntranceObj* ENTRANCE_ARR_PTR;
extern LevelOverlay::PathNodeObj* PATH_NODE_ARR_PTR;
extern LevelOverlay::PathObj* PATH_ARR_PTR;
extern LevelOverlay::ViewObj* VIEW_ARR_PTR;
extern LevelOverlay::TeleportDestObj* TELEPORT_DEST_OBJS_PTR;
extern LevelOverlay::FogObj* FOG_OBJS_PTR;
extern LevelOverlay::MinimapScreenObj* MAP_TILE_ARR_PTR;
extern LevelOverlay::MinimapScaleObj* MINIMAP_SCALE_OBJS_PTR;
extern void* UNUSED_TYPE_13_OBJS_PTR;

extern u32 STAR_CAMERA_SETTINGS;

void LoadObjects(LevelOverlay::ObjTable& objTable, s32 areaID, u32 entranceID);

void LoadStandardObjects(LevelOverlay::ObjSubTable& objSubTable, s32 areaID, u32 entranceID);
void LoadEntranceObjects(LevelOverlay::ObjSubTable& objSubTable, s32 areaID, u32 entranceID);
void LoadPathNodeObjects(LevelOverlay::ObjSubTable& objSubTable, s32 areaID, u32 entranceID);
void LoadPathObjects(LevelOverlay::ObjSubTable& objSubTable, s32 areaID, u32 entranceID);
void LoadViewObjects(LevelOverlay::ObjSubTable& objSubTable, s32 areaID, u32 entranceID);
void LoadSimpleObjects(LevelOverlay::ObjSubTable& objSubTable, s32 areaID, u32 entranceID);
void LoadTeleportSourceObjects(LevelOverlay::ObjSubTable& objSubTable, s32 areaID, u32 entranceID);
void LoadTeleportDestObjects(LevelOverlay::ObjSubTable& objSubTable, s32 areaID, u32 entranceID);
void LoadFogObjects(LevelOverlay::ObjSubTable& objSubTable, s32 areaID, u32 entranceID);
void LoadDoorObjects(LevelOverlay::ObjSubTable& objSubTable, s32 areaID, u32 entranceID);
void LoadExitObjects(LevelOverlay::ObjSubTable& objSubTable, s32 areaID, u32 entranceID);
void LoadMinimapTileObjects(LevelOverlay::ObjSubTable& objSubTable, s32 areaID, u32 entranceID);
void LoadMinimapScaleObjects(LevelOverlay::ObjSubTable& objSubTable, s32 areaID, u32 entranceID);
void LoadUnusedType13Objects(LevelOverlay::ObjSubTable& objSubTable, s32 areaID, u32 entranceID);
void LoadStarCameraObjects(LevelOverlay::ObjSubTable& objSubTable, s32 areaID, u32 entranceID);

void LoadMinimapChangeObject(s32 areaID, Fix12i posY, u8 param1);

using LevelOverlayFunc = void(*)(s32);
void LoadLevelOverlays(s32 levelID);
void UnloadLevelOverlays(s32 levelID);
void LoadOrUnloadObjectOverlays(LevelOverlayFunc func, s32 levelID); // modified by the DL patch to load / unload DLs

// inserted by the DL patch
using DLFunc = void(*)();
char* DLLoad(s32 ov0FileID);
void DLCleanAllUsedByLevel();
void DLLoadAllUsedByLevel();
