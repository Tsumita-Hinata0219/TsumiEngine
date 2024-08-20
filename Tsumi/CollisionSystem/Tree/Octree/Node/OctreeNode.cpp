#include "OctreeNode.h"
#include "../../../Shape/CollisionShape.h"


// パラメータ付きコンストラクタ
OctreeNode::OctreeNode(int depth)
{
    // 空間レベルの深さの設定
    levelDepth_ = depth;

    // 空間レベルの深さに応じたノード数を用意する
    int numNodes = 0;

    for (int i = 0; i <= levelDepth_ - 1; ++i) {
        numNodes += int(std::pow(4, i));  // 4^i 個のノード
    }

    // 線形配列のサイズを設定
    nodes_.resize(numNodes, 0);  // 初期値として 0 を設定
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


