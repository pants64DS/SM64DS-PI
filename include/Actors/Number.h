#pragma once

struct Number : Actor
{
	static constexpr u16 staticActorID = 0x14a;

	Model model;
	TextureSequence textureSequence;
	u32 unkActorUniqueID;
	Vector3 spawnPos;
	Fix12i unk148;
	u16 delay;
	u8 numTimesBounced;
	u8 unk14f;
};

static_assert(sizeof(Number) == 0x150, "Number is wrong size");
