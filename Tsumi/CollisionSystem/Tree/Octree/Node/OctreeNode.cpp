#include "OctreeNode.h"
#include "../../../component/CollisionComponent.h"
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
    nodes_.resize(numNodes);  // 初期値として 0 を設定
}


// データの挿入
void OctreeNode::Insert(const std::shared_ptr<CollisionShape>& shape)
{
    // shapeの空間レベルと所属空間から、挿入する配列のインデックスを求める
    int index = GetIndex(shape->GetLevelIndex(), shape->GetSpaceIndex());

    // 挿入可能なindexじゃなければエラー
    if (index < nodes_.size()) {
        nodes_[index].push_back(shape);
    }
    else {
        std::cerr << "Error : Index out of bounds" << std::endl;
    }
}
void OctreeNode::Insert(const CollisionComponent* comp)
{
    comp;
}


// データのクリア
void OctreeNode::Clear()
{
    nodes_.clear();
}


// レベルLの最初の要素番号を計算
int OctreeNode::LevelOffset(int level)
{
    if (level == 0) return 0;
    return int((int(pow(4.0f, level)) - 1) / 3);
}


// レベルLでのノード番号Nに対する配列インデックスの計算
int OctreeNode::GetIndex(int level, int nodeNum)
{
    return LevelOffset(level) + nodeNum;
}

