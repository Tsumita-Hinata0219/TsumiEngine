#pragma once

#include "../../../Shape/CollisionShape.h"
#include "../Object/OctreeObject.h"

#include <vector>
#include <memory>


/* 八分木のノードを管理するクラス */
class OctreeNode {

public:

	// コンストラクタ、デストラクタ
	OctreeNode() {};
	~OctreeNode() {
		for (auto child : children_) {
			delete child;
		}
	};

	// パラメータ付きコンストラクタ
	OctreeNode(const Col::AABB& setBounds, int setDepth) {
		this->bounds_ = setBounds;
		this->depth_ = setDepth;
	}

	// オブジェクトをノードに挿入
	void Insert(OctreeObject* object);

	// 指定された範囲内のオブジェクトをクリエする
	void Query(const Col::AABB& range, std::vector<OctreeObject*>& results);


private:

	// ノードを分割する
	void Subdivide();

	// ノード内のオブジェクトを子ノードに移動する
	void RelocationObjects();


public:

	static const int MAX_OBJECTS = 10;
	static const int MAX_DEPTH = 5;


private:

	// ノード範囲
	Col::AABB bounds_{};

	// このノードに格納されたオブジェクト
	std::vector<Col::AABB> objects_;

	// 子ノード
	std::vector<OctreeNode*> children_;

	// ノードの深さ
	int depth_ = 0;

};

