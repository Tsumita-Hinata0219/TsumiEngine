#include "ICollisionComponent.h"



/// <summary>
/// コンストラクタ
/// </summary>
ICollisionComponent::ICollisionComponent()
{
	// 名前はdefaultで初期化
	name_ = "default";
}


/// <summary>
/// 生成
/// </summary>
void ICollisionComponent::Create(const std::string& name)
{
	name_ = name;
}
