#include "RenderComponent.h"
#include "3D/Model/Manager/ModelManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
IRenderComponent::IRenderComponent()
{
	model_ = ModelManager::GetInstance()->GetModel("");
}


/// <summary>
/// 描画処理
/// </summary>
void IRenderComponent::Draw()
{
	
}
