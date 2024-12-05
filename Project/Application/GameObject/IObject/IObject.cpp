#include "IObject.h"
#include "CollisionSystem/Collider/Interface/ICollider.h"


/// <summary>
/// コンストラクタ
/// </summary>
IObject::IObject()
{
	modelManager_ = ModelManager::GetInstance();
}


/// <summary>
/// コライダーの登録処理
/// </summary>
void IObject::RegisterCollider(ICollider* pCollider)
{
	CollisionManager* collisionManager = CollisionManager::GetInstance();
	collisionManager->Register(pCollider);
}
