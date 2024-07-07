#include "TestPostEffect.h"



// 初期化処理
void TestPostEffect::Initialize()
{
	// BoxFilter
	boxFilter_ = std::make_unique<BoxFilterEffect>();
	boxFilter_->Initialize();

	// Dissolve
	dissolve_ = std::make_unique<DissolveEffect>();
	dissolve_->Initialize();


}


// 更新処理
void TestPostEffect::Update()
{
#ifdef _DEBUG

	// ImGuiの描画
	//boxFilter_->DrawImGui();


#endif // _DEBUG
}


// 描画処理
void TestPostEffect::Draw(Camera* camera)
{
	camera;

#if 0 // BoxFilter
	boxFilter_->Draw(camera);
#endif


}
