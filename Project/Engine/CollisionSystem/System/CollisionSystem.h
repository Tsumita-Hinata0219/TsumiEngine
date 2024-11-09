#pragma once

#include "../Component/CollisionComponent.h"
#include "../Shape/CollisionShape.h"
#include "../Event/CollisionEvent.h"
#include "../ColEventManager/ColEventManager.h"

#include <vector>

/* コリジョン判定のロジッククラス */
class CollisionSystem {

public:

	// コンストラクタ、デストラクタ
	CollisionSystem();
	~CollisionSystem() {};

	// 初期化処理
	void Init();

	// コンポーネント追加
	void AAddComponent(CollisionComponent* component);
	void AAddComponentN(CollisionComponent* component);

	// コンポーネントのクリア
	void ClearComponent();

	// コリジョン判定を実行
	void Update();

	// シェイプの追加
	void RegisterShape(ColShapeData& data);


private:

	// コリジョン判定を行う
	void CheckCollisions();


private:

	// 八分木ノードクラス
	//std::unique_ptr<OctreeNode> node_;

	// コンポーネントリスト
	std::vector<CollisionComponent*> components_;

	// シェイプリスト
	std::vector<CollisionShape*> shapes_;
	std::map<uint32_t, CollisionShape*> shapeMap_;
	// 追加したシェイプのインデックス
	uint32_t shapeIndex_ = 0;
};

