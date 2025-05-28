#include "IEntityCollider.h"
#include "../Manager/CollisionManager.h"


/// <summary>
/// 登録処理
/// </summary>
void Entity::Collision::IEntityCollider::OnRegister()
{
	if (!pManager_) {
		pManager_ = CollisionManager::GetInstance();
	}
	pManager_->Register(GetSharedPtr());
	isActive_ = true;
}
