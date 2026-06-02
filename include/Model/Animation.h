#pragma once

struct ModelComponents;

struct Animation // internal: FrameCtrl; done
{
	static constexpr s32 FLAG_MASK = 0xC0000000;

	enum Flags : s32
	{
		LOOP = 0x00000000,
		NO_LOOP = 0x40000000
	};

	//vtable
	Fix12i numFramesAndFlags;
	Fix12i currFrame;
	Fix12i speed;

	Animation();
	virtual ~Animation();

	Animation(const Animation&) = delete;
	Animation(Animation&&) = delete;

	void Advance();
	bool Finished();

	s32 GetFlags();
	void SetFlags(s32 flags);
	u16 GetFrameCount() const;
	void SetAnimation(u16 frames, s32 flags, Fix12i speed = 0x1000_f, u16 startFrame = 0);
	void Copy(const Animation& anim);
	bool WillHitFrame(s32 frameIndex) const;

	[[gnu::always_inline]]
	bool WillHitLastFrame() const { return WillHitFrame((u16)(GetFrameCount() - 1)); }

	[[gnu::always_inline]]
	u32 GetCurrFrame() const { return (u32)currFrame.val << 4 >> 16; }
};

struct MaterialChanger : Animation // internal: AnmMaterial; done
{
	BMA_File* file;

	MaterialChanger();
	virtual ~MaterialChanger();

	void SetFile(BMA_File& file, s32 flags, Fix12i speed, u32 startFrame);
	void Update(ModelComponents& modelData);
};

struct TextureTransformer : Animation // internal: AnmTexSRT; done
{
	BTA_File* file;

	TextureTransformer();
	virtual ~TextureTransformer();

	void SetFile(BTA_File& file, s32 flags, Fix12i speed, u32 startFrame);
	void Update(ModelComponents& modelData);
};

struct TextureSequence : Animation // internal: AnmTexPat; done
{
	BTP_File* file;

	TextureSequence();
	virtual ~TextureSequence();

	void SetFile(BTP_File& file, s32 flags, Fix12i speed, u32 startFrame);
	void Update(ModelComponents& modelData);
};
