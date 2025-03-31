#include "IRenderComponent.h"
#include "3D/Model/Manager/ModelManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
IRenderComponent::IRenderComponent()
{
	renderState_ = std::make_unique<RenderSystem::RenderState>(owner_);
}


/// <summary>
/// 描画処理
/// </summary>
void IRenderComponent::Draw()
{
	renderState_->Draw3D();
}
