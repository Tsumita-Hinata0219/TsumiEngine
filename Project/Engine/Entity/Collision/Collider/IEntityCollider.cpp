#include "IEntityCollider.h"
#include "../Manager/CollisionManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
Entity::Collision::IEntityCollider::IEntityCollider()
{
	pManager_ = CollisionManager::GetInstance();
	pManager_->Register(GetSharedPtr());
	isActive_ = true;
}
