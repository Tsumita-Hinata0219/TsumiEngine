#include "IComponent.h"



/// <summary>
/// コンストラクタ
/// </summary>
IComponent::IComponent(std::weak_ptr<IActor> owner)
	: owner(owner)
{
	// 名前はdefaultで初期化
	name = "default";
}


/// <summary>
/// 更新処理
/// </summary>
void IComponent::Update([[maybe_unused]] float deltaTime) {}
