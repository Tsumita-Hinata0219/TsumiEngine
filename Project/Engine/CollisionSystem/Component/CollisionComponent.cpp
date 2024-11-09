#include "CollisionComponent.h"
#include "../Manager/CollisionManager.h"
#include "../Shape/CollisionShape.h"
#include "../Shape/Sphere/CollisionShapeSphere.h"
#include "../Shape/AABB/CollisionShapeAABB.h"


// コンストラクタ
CollisionComponent::CollisionComponent()
{
	// インデックスの初期化
	index_ = 0;
}


// パラメータ付きコンストラクタ
CollisionComponent::CollisionComponent(IObject* setObject)
{
	this->owner_ = setObject;
}


void CollisionComponent::Register(Col::ColData& colData)
{
	this->nextID_++; // IDの加算
	colData.id = this->nextID_; // IDの設定

	// マネージャーにポインタを渡す
	CollisionManager::GetInstance()->Register(attribute_, &colData, this);
}

