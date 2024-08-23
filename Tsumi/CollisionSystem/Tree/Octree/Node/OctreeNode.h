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
	OctreeNode(int depth);

	// データの挿入
	void Insert(const CollisionShape& shape);

	// データのクリエ
	void Query();


private:

	// レベルLの最初の要素番号を計算
	int LevelOffset(int level);

	// レベルLでのノード番号Nに対する配列インデックスの計算
	int GetIndex(int level, int nodeNum);


private:

	// 空間レベルの深さ
	int levelDepth_ = 0;

	// 線形配列
	std::vector <std::list<CollisionShape*>> nodes_;
};

