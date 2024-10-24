#pragma once

#include <vector>
#include <functional>
#include <unordered_map>

#include "../Event/CollisionEvent.h"


/* イベントの管理とリスナーへの配信 */
class ColEventManager {

public:

	using CollisionListener = std::shared_ptr<std::function<void(const CollisionEvent&)>>;

	// インスタンス取得
	static ColEventManager* GetInstance() {
		static ColEventManager instance;
		return &instance;
	}

	// イベントリスナーの登録
	void RegisterListener(const CollisionListener& listener);

	// イベントリスナーの解除
	void UnregisterListener(const CollisionListener& listener);

	// コリジョンイベントの配信
	void Dispatch(const CollisionEvent& event);


private:

	// コリジョンイベントのリスナーリスト
	std::vector<CollisionListener> collisionListeners_;

};

