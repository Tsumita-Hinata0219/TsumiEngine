#include "OctreeNode.h"
#include "../../../Shape/CollisionShape.h"


// パラメータ付きコンストラクタ
OctreeNode::OctreeNode(int maxLevel)
{
    int numNodes = 0;
    for (int i = 0; i <= maxLevel; ++i) {
        numNodes += 4 * (1 << (2 * i));  // 4^i 個のノード
    }
    nodes_.resize(numNodes, -1);  // 初期値として -1 を設定
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


