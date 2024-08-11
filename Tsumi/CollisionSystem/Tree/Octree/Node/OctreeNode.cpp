#include "OctreeNode.h"



// オブジェクトをノードに挿入
void OctreeNode::Insert(OctreeObject* object)
{
	// オブジェクトがノードの範囲に収まるか確認
}


// 指定された範囲内のオブジェクトをクリエする
void OctreeNode::Query(const Col::AABB& range, std::vector<OctreeObject*>& results)
{
}


// ノードを分割する
void OctreeNode::Subdivide()
{
}


// ノード内のオブジェクトを子ノードに移動する
void OctreeNode::RelocationObjects()
{

}
