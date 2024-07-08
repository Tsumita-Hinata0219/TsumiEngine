#pragma once

#include "../../GameObject.h"
#include "../../../Tsumi/PostEffect/IPostEffect/IPostEffect.h"

#include "../../Tsumi/PostEffect/IPostEffect/Absent/AbsentEffect.h"
#include "../../Tsumi/PostEffect/IPostEffect/BoxFilter/BoxFilterEffect.h"
#include "../../Tsumi/PostEffect/IPostEffect/Dissolve/DissolveEffect.h"
#include "../../Tsumi/PostEffect/IPostEffect/BoxFilter/BoxFilterEffect.h"
#include "../../Tsumi/PostEffect/IPostEffect/ColorGrading/ColorGradingEffect.h"
#include "../../Tsumi/PostEffect/IPostEffect/Dissolve/DissolveEffect.h"
#include "../../Tsumi/PostEffect/IPostEffect/GaussianFilter/GaussianFilterEffect.h"
#include "../../Tsumi/PostEffect/IPostEffect/Grain/GrainEffect.h"
#include "../../Tsumi/PostEffect/IPostEffect/GrayScale/GrayScaleEffect.h"
#include "../../Tsumi/PostEffect/IPostEffect/LuminanceOutLine/LuminanceOutLineEffect.h"
#include "../../Tsumi/PostEffect/IPostEffect/RadialBlur/RadialBlurEffect.h"
#include "../../Tsumi/PostEffect/IPostEffect/Random/RandomEffect.h"
#include "../../Tsumi/PostEffect/IPostEffect/SepiaTone/SepiaToneEffect.h"
#include "../../Tsumi/PostEffect/IPostEffect/Vignetting/VignettingEffect.h"


enum EffectType {
	Absent = 0,
	BoxFilter = 1 << 0,
	ColorGrading = 1 << 1,
	Dissolve = 1 << 2,
	GauusianFilter = 1 << 3,
	Grain = 1 << 4,
	GrayScale = 1 << 5,
	LuminanceOutLine = 1 << 6,
	RadialBlur = 1 << 7,
	Random = 1 << 8,
	SepiaTone = 1 << 9,
	Vignetting = 1 << 10,
};


/* TestPostEffectクラス */
class TestPostEffect {

public:

	// コンストラクタ、デストラクタ
	TestPostEffect() {};
	~TestPostEffect() {};

	// 初期化処理、更新処理、描画処理
	void Initialize();
	void Update();
	void Draw(Camera* camera);


private:

	// ImGuiの描画
	void ChangeImGui();


private:

	// エフェクトのアクティブを管理する変数
	int activeEffects_ = EffectType::Absent;

	// Absent
	std::unique_ptr<AbsentEffect> absent_;

	// BoxFilter
	std::unique_ptr<BoxFilterEffect> boxFilter_;

	// ColorGrading
	std::unique_ptr<ColorGradingEffect> colorGrading_;

	// Dissolve
	std::unique_ptr<DissolveEffect> dissolve_;

	// GaussianFilter
	std::unique_ptr<GaussianFilterEffect> gaussianFilter_;

	// Grain
	std::unique_ptr<GrainEffect> grain_;

	// LuminanceOutLine
	std::unique_ptr<LuminanceOutLineEffect> luminanceOutLine_;

	// RadialBlur
	std::unique_ptr<RadialBlurEffect> radialBlur_;

	// Random
	std::unique_ptr<RandomEffect> random_;

	// SepiaTone
	std::unique_ptr<SepiaToneEffect> sepiaTone_;

	// Vignetting
	std::unique_ptr<VignettingEffect> vignetting_;

	// IPostEffect::Typeを表す文字
	std::vector<std::string> imguiEffectName_{};
	int imguiComboIndex_ = 0;
};

