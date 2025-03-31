#include "IComponent.h"



/// <summary>
/// コンストラクタ
/// </summary>
IComponent::IComponent()
{
	// 名前はdefaultで初期化
	name_ = "default";
}


/// <summary>
/// 更新処理
/// </summary>
void IComponent::Update([[maybe_unused]] float deltaTime) {}
