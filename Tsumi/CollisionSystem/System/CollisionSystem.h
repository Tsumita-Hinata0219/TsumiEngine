#pragma once

#include "../Component/CollisionComponent.h"

#include <vector>

/* コリジョン判定のロジッククラス */
class CollisionSystem {

public:

	// コンストラクタ、デストラクタ
	CollisionSystem() {};
	~CollisionSystem() {};

	// コンポーネント追加
	void AAddComponent(CollisionComponent* component);

	// コリジョン判定を実行
	void Update();


private:

	// コリジョン判定を行う
	void CheckCollisions();


private:

	// コンポーネントリスト
	std::vector<CollisionComponent*> components_;

};

