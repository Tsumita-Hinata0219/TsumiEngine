#include "IRenderComponent.h"
#include "3D/Model/Manager/ModelManager.h"


/// <summary>
/// 生成
/// </summary>
void IRenderComponent::Create()
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
