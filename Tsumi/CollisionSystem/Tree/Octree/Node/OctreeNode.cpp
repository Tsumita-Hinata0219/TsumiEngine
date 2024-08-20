#include "OctreeNode.h"
#include "../../../Shape/CollisionShape.h"


// パラメータ付きコンストラクタ
OctreeNode::OctreeNode(int maxLevel)
{
    maxLevel_ = maxLevel;
    int numNodes = 0;
    // ノード数を計算する
    for (int i = 0; i <= maxLevel_ - 1; ++i) {
        numNodes += int(std::pow(4, i));  // 4^i 個のノード
    }
    // 線形配列のサイズを設定
    nodes_.resize(numNodes, 0);  // 初期値として -1 を設定
}


// データの挿入
void OctreeNode::Insert(const CollisionShape& shape)
{
    shape;
}


// データのクリエ
void OctreeNode::Query()
{
}


