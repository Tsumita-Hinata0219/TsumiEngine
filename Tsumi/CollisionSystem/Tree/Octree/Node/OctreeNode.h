#pragma once

#include "../Object/OctreeObject.h"
#include "../Node/OctreeNode.h"

#include <vector>
#include <memory>

// 前方宣言
class CollisionShape;

/* 八分木のノードを管理するクラス */
class OctreeNode {

public:

	// コンストラクタ、デストラクタ
	OctreeNode() = default;
	~OctreeNode() = default;

	// パラメータ付きコンストラクタ
	OctreeNode(int maxLevel);

	// データの挿入
	void Insert(const CollisionShape& shape);

	// データのクリエ
	void Query();


private:

	// 最大レベル
	int maxLevel_ = 0;

	// 線形配列
	std::vector<int> nodes_;

};

