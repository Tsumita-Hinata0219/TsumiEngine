#include "TestPostEffect.h"



// 初期化処理
void TestPostEffect::Initialize()
{
	// BoxFilter
	boxFilter_ = std::make_unique<BoxFilterEffect>();
	boxFilter_->Initialize();

	// ColorGrading
	colorGrading_ = std::make_unique<ColorGradingEffect>();
	colorGrading_->Initialize();

	// Dissolve
	dissolve_ = std::make_unique<DissolveEffect>();
	dissolve_->Initialize();

	// GaussianFilter
	gaussianFilter_ = std::make_unique<GaussianFilterEffect>();
	gaussianFilter_->Initialize();

	// Grain
	grain_ = std::make_unique<GrainEffect>();
	grain_->Initialize();

	// LuminanceOutLine
	luminanceOutLine_ = std::make_unique<LuminanceOutLineEffect>();
	luminanceOutLine_->Initialize();

	// RadialBlur
	radialBlur_ = std::make_unique<RadialBlurEffect>();
	radialBlur_->Initialize();

	// Random
	random_ = std::make_unique<RandomEffect>();
	random_->Initialize();

	// SepiaTone
	sepiaTone_ = std::make_unique<SepiaToneEffect>();
	sepiaTone_->Initialize();

	// Vignetting
	vignetting_ = std::make_unique<VignettingEffect>();
	vignetting_->Initialize();


}


// 更新処理
void TestPostEffect::Update()
{
#ifdef _DEBUG

	// ImGuiの描画
#if 0 // BoxFilter
	boxFilter_->DrawImGui();
#endif

#if 0 // ColorGrading
	colorGrading_->DrawImGui();
#endif

#if 0 // Dissolve
	dissolve_->DrawImGui();
#endif

#if 0 // GaussianFilter
	gaussianFilter_->DrawImGui();
#endif

#if 0 // Grain
	grain_->DrawImGui();
#endif

#if 0 // LuminanceOutLine
	luminanceOutLine_->DrawImGui();
#endif

#if 0 // RadialBlur
	radialBlur_->DrawImGui();
#endif

#if 0 // Random
	random_->DrawImGui();
#endif

#if 0 // SepiaTone
	sepiaTone_->DrawImGui();
#endif

#if 0 // Vignetting
	vignetting_->DrawImGui();
#endif

#endif // _DEBUG
}


// 描画処理
void TestPostEffect::Draw(Camera* camera)
{
	camera;

#if 0 // BoxFilter
	boxFilter_->Draw(camera);
#endif

#if 0 // ColorGrading
	colorGrading_->Draw(camera);
#endif

#if 0 // Dissolve
	dissolve_->Draw(camera);
#endif

#if 0 // GaussianFilter
	gaussianFilter_->Draw(camera);
#endif

#if 0 // Grain
	grain_->Draw(camera);
#endif

#if 0 // LuminanceOutLine
	luminanceOutLine_->Draw(camera);
#endif

#if 0 // RadialBlur
	radialBlur_->Draw(camera);
#endif

#if 0 // Random
	random_->Draw(camera);
#endif

#if 0 // SepiaTone
	sepiaTone_->Draw(camera);
#endif

#if 0 // Vignetting
	vignetting_->Draw(camera);
#endif

}
