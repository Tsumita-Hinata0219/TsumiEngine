#include "TestPostEffect.h"



// 初期化処理
void TestPostEffect::Initialize()
{
	boxFilter_ = std::make_unique<BoxFilterEffect>();
	boxFilter_->Initialize();
}


// 更新処理
void TestPostEffect::Update()
{
#ifdef _DEBUG

	// ImGuiの描画
	boxFilter_->DrawImGui();


#endif // _DEBUG
}


// 描画処理
void TestPostEffect::Draw(Camera* camera)
{
	boxFilter_->Draw(camera);

}
