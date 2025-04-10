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
/// 生成
/// </summary>
void IComponent::Create(const std::string& name)
{
	name_ = name;
}


/// <summary>
/// 更新処理
/// </summary>
void IComponent::Update([[maybe_unused]] float deltaTime) {}
