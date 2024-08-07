#include "ColEventManager.h"



// イベントリスナーの登録
void ColEventManager::RegisterCollisionListener(const CollisionListener& listener)
{
	this->collisionListeners_.push_back(listener);
}


// イベントリスナーの解除
void ColEventManager::UnregisterCollisionListener(const CollisionListener& listener)
{
	auto it = std::remove(collisionListeners_.begin(), collisionListeners_.end(), listener);
	collisionListeners_.erase(it, collisionListeners_.end());
}


// コリジョンイベントの配信
void ColEventManager::DispatchCollisionEvent(const CollisionEvent& event)
{
	for (const auto& listerner : collisionListeners_) {
		listerner(event);
	}
}
