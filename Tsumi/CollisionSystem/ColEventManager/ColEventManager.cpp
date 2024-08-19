#include "ColEventManager.h"



// イベントリスナーの登録
void ColEventManager::RegisterListener(const CollisionListener& listener)
{
	collisionListeners_.push_back(listener);
}


// イベントリスナーの解除
void ColEventManager::UnregisterListener(const CollisionListener& listener)
{
	auto it = std::remove_if(collisionListeners_.begin(), collisionListeners_.end(),
		[&listener](const CollisionListener& l) { return l == listener; });
	collisionListeners_.erase(it, collisionListeners_.end());
}


// コリジョンイベントの配信
void ColEventManager::Dispatch(const CollisionEvent& event)
{
	for (const auto& listener : collisionListeners_) {
		(*listener)(event);
	}
}


