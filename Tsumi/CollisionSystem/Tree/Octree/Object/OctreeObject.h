#pragma once

#include "../../../Shape/CollisionShape.h"

#include <memory>


/* 八分木に登録するオブジェクトの情報を保持するクラス */
class OctreeObject {

public:

	// コンストラクタ、デストラクタ
	OctreeObject() {};
	~OctreeObject() {};

	// パラメータ付きコンストラクタ
	OctreeObject(std::unique_ptr<CollisionShape> setShape, void* setData) {
		this->shape_ = std::move(setShape);
		this->data_ = setData;
	}


#pragma region Accessor アクセッサー

	// shape
	const CollisionShape& GetShape() const { return *this->shape_; }

#pragma endregion 


public:

	// 八分木に登録するオブジェクト
	std::unique_ptr<CollisionShape> shape_;
	void* data_ = nullptr;

};

