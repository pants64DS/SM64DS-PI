#pragma once

#include "Math.h"

struct BMD_File;
struct BTP_File;
struct BCA_File;
struct BMA_File;
struct BTA_File;

#include "Model/Vram.h"
#include "Model/GXFIFO.h"
#include "Model/Animation.h"
#include "Model/ModelComponents.h"
#include "Model/Model.h"
#include "Model/Fader.h"

extern u16 CHANGE_CAP_TOON_COLORS[0x20];

struct Command30
{
	unsigned diffuse : 15;
	unsigned ambient : 15;
	bool setsVertexColor : 1 = false;

	constexpr operator u32() const
	{
		return diffuse | setsVertexColor << 15 | ambient << 16;
	}
};

struct Command31
{
	unsigned specular : 15;
	unsigned emission : 15;
	bool usesShininessTable : 1 = false;

	constexpr operator u32() const
	{
		return specular | usesShininessTable << 15 | emission << 16;
	}
};

enum Command2a
{
	VRAM_OFFSET_DIV_8        = 0xffff << 0,
	RepeatS                  = 0x1    << 16, // 0: Clamp Texture, 1: Repeat Texture
	RepeatT                  = 0x1    << 17, // 0: Clamp Texture, 1: Repeat Texture
	FlipS                    = 0x1    << 18, // 0: No, 1: Yes (requires Repeat)
	FlipT                    = 0x1    << 19, // 0: No, 1: Yes (requires Repeat) 
	S_SIZE                   = 0x7    << 20,
	T_SIZE                   = 0x7    << 23,
	FORMAT                   = 0x7    << 26,
		NO_TEXTURE           = 0x0    << 26,
		A3I5                 = 0x1    << 26,
		COLOR_4              = 0x2    << 26,
		COLOR_16             = 0x3    << 26,
		COLOT_256            = 0x4    << 26,
		TEXEL_4x4            = 0x5    << 26,
		A5I3                 = 0x6    << 26,
		DIRECT               = 0x7    << 26,
	COLOR_0_MODE             = 0x1    << 29, // 0: normal, 1: transparent
	TEX_COORD_TRANSFORM_MODE = 0x3    << 30,
		DONT_TRANSFORM       = 0x0    << 30,
		TEXCOORD_SOURCE      = 0x1    << 30,
		NORMAL_SOURCE        = 0x2    << 30,
		VERTEX_SOURCE        = 0x3    << 30,
};
