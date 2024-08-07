#pragma once

#include <vector>
#include <functional>
#include <unordered_map>

#include "../Event/CollisionEvent.h"


/* イベントの管理とリスナーへの配信 */
class ColEventManager {

public:

	using CollisionListener = std::function<void(const CollisionEvent&)>;


	// イベントリスナーの登録
	void RegisterCollisionListener(const CollisionListener& listener);

	// イベントリスナーの解除
	void UnregisterCollisionListener(const CollisionListener& listener);

	// コリジョンイベントの配信
	void DispatchCollisionEvent(const CollisionEvent& event);


private:

	// コリジョンイベントのリスナーリスト
	std::vector<CollisionListener> collisionListeners_;

};

