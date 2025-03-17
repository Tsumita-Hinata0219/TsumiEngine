#include "IComponent.h"



/// <summary>
/// コンストラクタ
/// </summary>
IComponent::IComponent(std::weak_ptr<IActor> owner, int updateOrder)
	: owner(owner), updateOrder(updateOrder)
{
}
IComponent::IComponent(IComponent& component)
{
	this->owner = component.owner;
	this->updateOrder = component.updateOrder;
}


/// <summary>
/// 更新処理
/// </summary>
void IComponent::Update([[maybe_unused]] float deltaTime) {}
