#pragma once

struct Material
{
	enum POLYGON_ATTR
	{
		LIGHT_1_ENABLED           = 0x1  << 0,
		LIGHT_2_ENABLED           = 0x1  << 1,
		LIGHT_3_ENABLED           = 0x1  << 2,
		LIGHT_4_ENABLED           = 0x1  << 3,
		POLYGON_MODE              = 0x3  << 4,
		RENDER_POLYGON_BACK       = 0x1  << 6,
		RENDER_POLYGON_FRONT      = 0x1  << 7,
		// bits 8-10 aren't used
		SET_NEW_DEPTH_VALUE       = 0x1  << 11, // for translucent pixels
		RENDER_INTERSECTING_POLYS = 0x1  << 12,
		RENDER_1_DOT_POLYS        = 0x1  << 13, // behind DISP_1DOT_DEPTH
		DEPTH_EQUAL               = 0x1  << 14, // usually 0
		FOG_ENABLE                = 0x1  << 15,
		ALPHA                     = 0x1f << 16,
		// bits 21-23 aren't used
		POLYGON_ID                = 0x3f << 24,
		// bits 30-31 aren't used
	};

	enum TextureTransformMode
	{
		NO_CHANGE,
		TEXCOORD_SOURCE,
		NORMAL_SOURCE,
		VERTEX_SOURCE
	};

	u32 unk00;
	u32 unk04;
	Fix12i texScaleX;
	Fix12i texScaleY;
	s16 texRot; //then alignment
	Fix12i texTransX;
	Fix12i texTransY;
	u32 teximageParam; //gx command 0x2a
	u32 paletteInfo;
	u32 polygonAttr; //gx command 0x29
	u32 difAmb; //gx command 0x30
	u32 speEmi; //gx command 0x31

	constexpr u32 GetTransformMode() const
	{
		return teximageParam >> 30;
	}

	constexpr void SetTransformMode(u32 transformMode)
	{
		teximageParam &= ~(3 << 30);
		teximageParam |= transformMode << 30;
	}

	constexpr u32 GetAlpha() const // from 0 to 31
	{
		return (polygonAttr >> 16) & 0b11111;
	}

	constexpr void SetAlpha(u32 alpha) // from 0 to 31
	{
		polygonAttr &= ~(0b11111 << 16);
		polygonAttr |= (alpha & 0b11111) << 16;
	}

	constexpr u32 GetPolygonID() const // from 0 to 63
	{
		return (polygonAttr >> 24) & 0x3f;
	}

	constexpr void SetPolygonID(u32 polygonID) // from 0 to 63
	{
		polygonAttr &= ~(0x3f << 24);
		polygonAttr |= (polygonID & 0x3f) << 24;
	}

	inline void Show()
	{
		polygonAttr &= ~0x80000000;
	}

	inline void Hide()
	{
		polygonAttr |= 0x80000000;
	}
};

struct Bone
{
	u32 unk00;
	u32 unk04;
	u32 unk08;
	Vector3 scale;
	u16 unk18;
	Vector3_16 rot;
	Vector3 pos;
	u32 unk2c;
	u32 unk30;
};

struct ModelComponents
{
	BMD_File* modelFile;
	Material* materials;
	Bone* bones;
	Matrix4x3* transforms;
	char* unk10;

	void UpdateBones(BCA_File* animFile, s32 frame);
	void UpdateVertsUsingBones();
	void Render(Matrix4x3* mat = nullptr, Vector3* scale = nullptr);
};

struct CommonModelData
{
	BMD_File* file;
	ModelComponents* modelComponents;
	char* unk08;
};

extern "C"
{
	extern u32 numCommonModelData;
	extern CommonModelData commonModelDataArr[];

	void CleanCommonModelDataArr();
}
