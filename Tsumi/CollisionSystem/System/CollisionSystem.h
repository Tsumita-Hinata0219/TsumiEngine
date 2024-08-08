#pragma once

#include "../Component/CollisionComponent.h"
#include "../Event/CollisionEvent.h"
#include "../ColEventManager/ColEventManager.h"

#include <vector>

/* コリジョン判定のロジッククラス */
class CollisionSystem {

public:

	// コンストラクタ、デストラクタ
	CollisionSystem() {};
	~CollisionSystem() {};

	// コンポーネント追加
	void AAddComponent(CollisionComponent* component);

	// コンポーネントのクリア
	void ClearComponent();

	// コリジョン判定を実行
	void Update();


private:

	// コリジョン判定を行う
	void CheckCollisions();


private:

	// コンポーネントリスト
	std::vector<CollisionComponent*> components_;

};

