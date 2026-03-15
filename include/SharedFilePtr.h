#pragma once

#include "Math.h"
#include <concepts>

struct BMD_File;
struct KCL_File;

struct SharedFilePtr
{
	u16 fileID = ~0;
	u8 numRefs = 0;
	char* filePtr = nullptr;

	struct IDs
	{
		u16 fileID;
		u16 ov0ID;

		static consteval IDs Get(const char* name);
	};

	consteval SharedFilePtr() = default;
	consteval SharedFilePtr(const SharedFilePtr&) = default;
	consteval SharedFilePtr(u16 fileID) : fileID(fileID) {}
	consteval SharedFilePtr(const std::same_as<char> auto* name):
		fileID(IDs::Get(name).fileID) {}
	
	void FromOv0ID(u32 ov0FileID);

	[[deprecated("'Construct' has been renamed to 'FromOv0ID'")]]
	SharedFilePtr& Construct(u32 ov0FileID)
	{
		return FromOv0ID(ov0FileID), *this;
	}

	// Loads the file if numRefs == 0, and increments it unless loading failed
	char* Load();
	char* LoadInternal(); // Doen't update numRefs; should not be called directly
	void Release(); // Decrements numRefs and unloads the file when it reaches zero
	u32 ReallocateModelFile();

	BMD_File& LoadBMD();
	BCA_File& LoadBCA();
	BTP_File& LoadBTP();
	KCL_File& LoadKCL();

	[[gnu::always_inline]] BMD_File*  BMD () const { return reinterpret_cast<BMD_File*> (filePtr); }
	[[gnu::always_inline]] BCA_File*  BCA () const { return reinterpret_cast<BCA_File*> (filePtr); }
	[[gnu::always_inline]] BMA_File*  BMA () const { return reinterpret_cast<BMA_File*> (filePtr); }
	[[gnu::always_inline]] BTA_File*  BTA () const { return reinterpret_cast<BTA_File*> (filePtr); }
	[[gnu::always_inline]] BTP_File*  BTP () const { return reinterpret_cast<BTP_File*> (filePtr); }
	[[gnu::always_inline]] KCL_File*  KCL () const { return reinterpret_cast<KCL_File*> (filePtr); }
	[[gnu::always_inline]] MESG_File* MESG() const { return reinterpret_cast<MESG_File*>(filePtr); }

#ifndef NO_DL_PATCH
	[[gnu::always_inline]] DYLB_File* DYLB() const { return reinterpret_cast<DYLB_File*>(filePtr); }
#endif
};

// temporary as these are static member variables
extern SharedFilePtr LUIGI_CAP_MODEL_PTR;
extern SharedFilePtr RED_NUMBER_MODEL_PTR;
extern SharedFilePtr POWER_FLOWER_OPEN_MODEL_PTR;
extern SharedFilePtr COIN_YELLOW_POLY32_MODEL_PTR;
extern SharedFilePtr WARIO_CAP_MODEL_PTR;
extern SharedFilePtr COIN_BLUE_POLY32_MODEL_PTR;
extern SharedFilePtr POWER_FLOWER_CLOSED_MODEL_PTR;
extern SharedFilePtr ONE_UP_MUSHROOM_MODEL_PTR;
extern SharedFilePtr BOB_OMB_MODEL_PTR;
extern SharedFilePtr NUMBER_TEXSEQ_PTR;
extern SharedFilePtr SNUFIT_BULLET_MODEL_PTR;
extern SharedFilePtr COIN_RED_POLY32_MODEL_PTR;
extern SharedFilePtr COIN_BLUE_POLY4_MODEL_PTR;
extern SharedFilePtr SILVER_NUMBER_TEXSEQ_PTR;
extern SharedFilePtr WATER_RING_MODEL_PTR;
extern SharedFilePtr SHELL_MODEL_PTRS[2];
extern SharedFilePtr SILVER_NUMBER_MODEL_PTR;
extern SharedFilePtr SUPER_MUSHROOM_MODEL_PTR;
extern SharedFilePtr WATER_BOMB_MODEL_PTR;
extern SharedFilePtr MARIO_CAP_MODEL_PTR;
extern SharedFilePtr COIN_YELLOW_POLY4_MODEL_PTR;
extern SharedFilePtr COIN_RED_POLY4_MODEL_PTR;
extern SharedFilePtr FEATHER_MODEL_PTR;
extern SharedFilePtr YOSHI_EGG_MODEL_PTR;
extern SharedFilePtr YOSHI_CUBE_EGG_MODEL_PTR;

extern SharedFilePtr* COIN_POLY4_MODEL_PTRS[3];
extern SharedFilePtr* COIN_POLY32_MODEL_PTRS[3];

extern SharedFilePtr BOWSER_KEY_MODEL_PTR;
extern SharedFilePtr* KEY_MODEL_PTRS[];

extern SharedFilePtr DOOR_OPEN_ANIM_PTR;
extern SharedFilePtr REGULAR_DOOR_MODEL_PTR;
extern SharedFilePtr REGULAR_DOOR_1_MODEL_PTR;
extern SharedFilePtr OLD_WOOD_DOOR_MODEL_PTR;
extern SharedFilePtr RUSTED_METAL_DOOR_MODEL_PTR;
extern SharedFilePtr HMC_STONE_DOOR_MODEL_PTR;
extern SharedFilePtr BBH_HAUNTED_DOOR_MODEL_PTR;
extern SharedFilePtr DOOR_STAR_0_MODEL_PTR;
extern SharedFilePtr DOOR_STAR_1_MODEL_PTR;
extern SharedFilePtr DOOR_STAR_3_MODEL_PTR;
extern SharedFilePtr DOOR_STAR_8_MODEL_PTR;
extern SharedFilePtr DOOR_KEY_HOLE_MODEL_PTR;
extern SharedFilePtr STAR_DOOR_MODEL_PTR;

extern SharedFilePtr STAR_SPHERE_MODEL_PTR;
extern SharedFilePtr STAR_BASE_MODEL_PTR;
extern SharedFilePtr POWER_STAR_MODEL_PTR;
extern SharedFilePtr SILVER_STAR_MODEL_PTR;
extern SharedFilePtr TRANSPARENT_STAR_MODEL_PTR;
extern SharedFilePtr BIG_1UP_NUMBER_MODEL_PTR;