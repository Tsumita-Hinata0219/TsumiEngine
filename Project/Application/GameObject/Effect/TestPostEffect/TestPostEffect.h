#pragma once

#include "GameObject/GameObject.h"
#include "PostEffect/IPostEffect/IPostEffect.h"

#include "PostEffect/IPostEffect/Absent/AbsentEffect.h"
#include "PostEffect/IPostEffect/BoxFilter/BoxFilterEffect.h"
#include "PostEffect/IPostEffect/Dissolve/DissolveEffect.h"
#include "PostEffect/IPostEffect/BoxFilter/BoxFilterEffect.h"
#include "PostEffect/IPostEffect/ColorGrading/ColorGradingEffect.h"
#include "PostEffect/IPostEffect/Dissolve/DissolveEffect.h"
#include "PostEffect/IPostEffect/GaussianFilter/GaussianFilterEffect.h"
#include "PostEffect/IPostEffect/Grain/GrainEffect.h"
#include "PostEffect/IPostEffect/GrayScale/GrayScaleEffect.h"
#include "PostEffect/IPostEffect/HSV/HSVEffect.h"
#include "PostEffect/IPostEffect/LuminanceOutLine/LuminanceOutLineEffect.h"
#include "PostEffect/IPostEffect/RadialBlur/RadialBlurEffect.h"
#include "PostEffect/IPostEffect/Random/RandomEffect.h"
#include "PostEffect/IPostEffect/RetroCRT/RetroCRTEffect.h"
#include "PostEffect/IPostEffect/SepiaTone/SepiaToneEffect.h"
#include "PostEffect/IPostEffect/Vignetting/VignettingEffect.h"


enum EffectType {
	Absent = 0,
	BoxFilter = 1 << 0,
	ColorGrading = 1 << 1,
	Dissolve = 1 << 2,
	GauusianFilter = 1 << 3,
	Grain = 1 << 4,
	GrayScale = 1 << 5,
	HSV = 1 << 6,
	LuminanceOutLine = 1 << 7,
	RadialBlur = 1 << 8,
	Random = 1 << 9,
	RetroCRT = 1 << 10,
	SepiaTone = 1 << 11,
	Vignetting = 1 << 12,
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
	void Draw();


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

	// HSV
	std::unique_ptr<HSVEffect> hsv_;

	// LuminanceOutLine
	std::unique_ptr<LuminanceOutLineEffect> luminanceOutLine_;

	// RadialBlur
	std::unique_ptr<RadialBlurEffect> radialBlur_;

	// Random
	std::unique_ptr<RandomEffect> random_;

	// RetroCRT
	std::unique_ptr<RetroCRTEffect> retroCRT_;

	// SepiaTone
	std::unique_ptr<SepiaToneEffect> sepiaTone_;

	// Vignetting
	std::unique_ptr<VignettingEffect> vignetting_;

	// IPostEffect::Typeを表す文字
	std::vector<std::string> imguiEffectName_{};
	int imguiComboIndex_ = 0;
};

