#pragma once

#include "../Component/CollisionComponent.h"
#include "../Event/CollisionEvent.h"
#include "../ColEventManager/ColEventManager.h"

#include "../Tree/Octree/Node/OctreeNode.h"


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

	//// シェイプの追加
	//void AddShape(CollisionShape* shape);

	//// シェイプのクリア
	//void ClearShape();

	// コリジョン判定を実行
	void Update();


private:

	// コリジョン判定を行う
	void CheckCollisions();


private:

	// 八分木ノードクラス
	std::unique_ptr<OctreeNode> node_;

	// コンポーネントリスト
	std::vector<CollisionComponent*> components_;

	//// シェイプ配列
	//std::vector<CollisionShape*> shapes_;

	//// シェイプ配列のインデックス
	//uint32_t shapeIndex_ = 0;

};
