#pragma once

struct ModelBase // internal: Model; done
{
	// vtable
	u32 unk04; // Pointer that is freed in all dtors

	ModelBase();
	virtual ~ModelBase();
	virtual bool DoSetFile(BMD_File& file, bool enableFog = false, s32 polygonID = -1) = 0;

	ModelBase(const ModelBase&) = delete;
	ModelBase(ModelBase&&) = delete;

	bool SetFile(BMD_File& file, bool enableFog = false, s32 polygonID = -1);
	void ApplyOpacity(u32 opacity, bool unkBool);
};

struct Model : ModelBase // internal: SimpleModel
{
	ModelComponents data;
	Matrix4x3 mat4x3;
	Matrix4x3* unkMatPtr;

	Model();
	virtual ~Model() override;
	virtual bool DoSetFile(BMD_File& file, bool enableFog = false, s32 polygonID = -1) override;
	virtual void UpdateVerts();
	virtual void Virtual10(Matrix4x3& arg0);
	virtual void Render(const Vector3* scale = nullptr);

	void Render(const Vector3& scale) { Render(&scale); }
	void Render(Fix12i scale) { Render({scale, scale, scale}); }

	void LoadAndSetFile(u16 ov0ID, s32 arg1, s32 arg2);
	void SetPolygonID(s32 polygonID);
	void SetPolygonMode(s32 polygonAttr);
	void ClearPolygonAttr(u32 polygonAttr);
	void SetPolygonAttr(u32 polygonAttr);
	void ShowMaterial(s32 boneID, s32 materialID);
	void HideMaterial(s32 boneID, s32 materialID);
	
	static CommonModelData* AddToCommonModelDataArr(BMD_File& file);
};

struct ModelAnim : Model, Animation	// internal: ModelAnm
{
	// vtable
	// Animation data
	BCA_File* file;

	ModelAnim();
	virtual ~ModelAnim() override;
	virtual void UpdateVerts() override;
	virtual void Virtual10(Matrix4x3& arg0) override;
	virtual void Render(const Vector3* scale = nullptr) override; // Calls UpdateVerts and then Model::Render
	virtual void Virtual18(u32 arg0, const Vector3* scale); // Calls Virtual10 and then Model::Render

	void SetAnim(BCA_File& animFile, s32 flags, Fix12i speed = 1._f, u32 startFrame = 0);
	void Copy(const ModelAnim& anim, BCA_File& newFile); // if newFile != nullptr, it gets copied instead of anim->file
};

struct ModelAnim2 : ModelAnim // internal: ModelAnm2
{
	u32 unk64;
	Animation otherAnim;

	ModelAnim2();
	virtual ~ModelAnim2() override;

	// 2 funcs missing before
	void Copy(const ModelAnim2& anim, BCA_File& newFile, u32 newUnk64); // copies anim to *this, otherAnim is set to anim's Animation base class
	void Func_0201628C(u32 arg0);
	void Func_020162A4(u32 arg0);
	void Func_020162C4(BCA_File& animFile, s32 animFlags, Fix12i speed, u16 startFrame); // always calls on otherAnim
};

struct ShadowModel : ModelBase // internal: ShadowModel; done
{
	ModelComponents* modelDataPtr;
	Matrix4x3* matPtr;
	Vector3 scale;
	u8 opacity;
	u8 unk1d;
	u8 unk1e;
	u8 unk1f;
	ShadowModel* prev;
	ShadowModel* next;

	ShadowModel();
	virtual ~ShadowModel() override;
	virtual bool DoSetFile(BMD_File& file, bool enableFog = false, s32 polygonID = -1) override;

	bool InitCylinder();
	bool InitCuboid();
	void InitModel(Matrix4x3* transform, Fix12i scaleX, Fix12i scaleY, Fix12i scaleZ, u32 opacity); // opacity is from 0 to 30

	static void RenderAll();
	static void CleanAll();
};

struct CommonModel : ModelBase // internal: CommonModel; done
{
	ModelComponents* data;
	Matrix4x3 mat4x3;

	CommonModel();
	virtual ~CommonModel() override;
	virtual bool DoSetFile(BMD_File& file, bool enableFog = false, s32 polygonID = -1) override;
	void Render(const Vector3* scale = nullptr);

	void Render(const Vector3& scale) { Render(&scale); }
	void Render(Fix12i scale) { Render({scale, scale, scale}); }

	void Func_0201609C(u32 arg0);
	void Func_020160AC(u32 arg0);
};

struct BlendModelAnim : ModelAnim // internal: BlendAnmModel
{
	Fix12i unk64;
	Fix12i unk68;
	u32 unk6C;

	// 0x0208E94C vtable, 0x020166D4 ctor
	BlendModelAnim();
	virtual ~BlendModelAnim() override;
	virtual bool DoSetFile(BMD_File& file, bool enableFog = false, s32 polygonID = -1) override;
	virtual void UpdateVerts() override;
	virtual void Virtual10(Matrix4x3& arg0) override;
	virtual void Render(const Vector3* scale = nullptr) override;
	virtual void Virtual18(u32 arg0, const Vector3* scale) override; // Calls Virtual10 and then Model::Render

	// 1 func missing(?)
	void Advance();
	void SetAnim(BCA_File& animFile, s32 arg2, s32 flags, Fix12i speed, u16 startFrame);
};
