#pragma once

#include "../../Shape/CollisionShape.h"
#include "Node/OctreeNode.h"

/* クラスはルートノードを持って、シーン全体の空間を管理する */
class Octree {

public:

	// コンストラクタ、デストラクタ
	Octree() {};
	~Octree() {
		delete this->root_;
	};

	// パラメータ付きコンストラクタ
	Octree(const Col::AABB& worldBounds) {
		this->root_ = new OctreeNode(worldBounds, 0);
	}

	// オブジェクトを八分木に追加
	void Insert(OctreeObject* object) {
		this->root_->Insert(object);
	}

	void Query(const Col::AABB& range, std::vector<OctreeObject*>& results) const {
		this->root_->Query(range, results);
	}


private:

	OctreeNode* root_ = nullptr;

};

