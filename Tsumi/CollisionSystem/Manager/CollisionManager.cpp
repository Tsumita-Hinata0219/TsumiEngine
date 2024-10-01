#include "CollisionManager.h"
#include "../Component/CollisionComponent.h"


// 解放処理
void CollisionManager::Finalize()
{
}


// コリジョン判定を行う
void CollisionManager::CheckCollisions()
{
}


// コライダーの登録
void CollisionManager::Register(CollisionShape* shape)
{
	shapesMap_.push_back(shape);
}

