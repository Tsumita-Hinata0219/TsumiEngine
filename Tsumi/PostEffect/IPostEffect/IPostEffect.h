#pragma once

#include "../../Base/WinApp/WinApp.h"
#include "../../BufferResource/BufferResource.h"
#include "../../CommandManager/CommandManager.h"
#include "../../../Project/Math/MyMath.h"
#include "../../CreateResource/CreateResource.h"
#include "../../DescriptorManager/DescriptorManager.h"
#include "../../PipeLineManager/PipeLineManager.h"
#include "../Materials/PostEffectMaterials.h"
#include "../PostEffectMaterial/PostEffectMaterial.h"
#include "../../Project/GameObject/Camera/Camera.h"


/* IPostEffectクラス */
class IPostEffect {

public: // メンバ関数

	// コンストラクタ、デストラクタ
	IPostEffect() {};
	virtual ~IPostEffect() {};

	// 初期化処理、更新処理、描画処理
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw(Camera* camera) = 0;

	// ImGuiの描画
	void DrawImGui();

public:

	enum class Type {
		Absent,
		BoxFilter,
		ColorGrading,
		Dissolve,
		GaussianFilter,
		Grain,
		GrayScale,
		OutLine,
		RadialBlur,
		Random,
		SepiaTone,
		Vignetting,
	};

protected: // メンバ関数

	// リソース作成
	void Create();

	// コマンドコール
	void CommandCall(Camera* camera);

	// PipeLineチェック
	void PipeLineCheck();


protected: // メンバ変数

	// IPostEffect::Typeを表す文字
	std::vector<std::string> imguiEffectName_{};
	int imguiComboIndex_ = 0;

	// マテリアル
	PostEffectMaterial material_;
	VignettingMaterial vignettingMtl_;

	// BoxFilter
	BoxFilterMtl boxFilterMtl_{};
	BufferResource<BoxFilterMtl> boxFilterBuffer_{};

	// ColorGrading
	ColorGradingMtl colorGradingMtl_{};
	BufferResource<ColorGradingMtl> colorGradingBuffer_{};

	// Dissolve
	DissolveMtl dissolveMtl_{};
	BufferResource<DissolveMtl> dissolveBuffer_{};

	// GaussianFilter
	GaussianFilterMtl gaussianFilterMtl_{};
	BufferResource<GaussianFilterMtl> gaussianFilterBuffer_{};

	// Grain
	GrainMtl grainMtl_{};
	BufferResource<GrainMtl> grainBuffer_{};

	// GrayScale
	GrayScaleMtl grayScaleMtl_{};
	BufferResource<GrayScaleMtl> grayScaleBuffer_{};

	// OutLine
	OutLineMtl outLineMtl_{};
	BufferResource<OutLineMtl> outLineBuffer_{};

	// RadialBlur
	RadialBlurMtl radialBlurMtl_{};
	BufferResource<RadialBlurMtl> radialBlurBuffer_{};

	// Random
	RandomMtl randomMtl_{};
	BufferResource<RandomMtl> randomBuffer_{};

	// SepiaTone
	SepiaToneMtl sepiaToneMtl_{};
	BufferResource<SepiaToneMtl> sepiaToneBuffer_{};

	// Vignttting
	VignettingMtl vignettingMtl2_{};
	BufferResource<VignettingMtl> vignettingBuffer_{};


	// SRV
	uint32_t srv_ = 0;

	// PostEffectTyepe
	IPostEffect::Type effectType_ = IPostEffect::Type::Absent;

};

