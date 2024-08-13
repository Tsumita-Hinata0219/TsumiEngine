#pragma once

#include "../../../Shape/CollisionShape.h"
#include "../../../Component/CollisionComponent.h"

#include <memory>
#include <vector>


/* 八分木に登録するオブジェクトの情報を保持するクラス */
class OctreeObject {

public:

	// コンストラクタ、デストラクタ
	OctreeObject() {};
	~OctreeObject() {};

	// パラメータ付きコンストラクタ
	OctreeObject(CollisionComponent* component) {
		this->component_ = component;
	}

	// シェイプの追加
	/*void AddShape(std::unique_ptr<CollisionShape> shape) {
		this->shapes_.push_back(std::move(shape));
	}*/


#pragma region Accessor アクセッサー

	// Component
	CollisionComponent* GetComponent() const {
		return this->component_;
	}

	// shape
	/*std::vector<std::unique_ptr<CollisionShape>> GetShape() const {
		return this->shapes_;
	}*/

#pragma endregion 


public:

	// オブジェクトの持つコンポーネント
	std::vector<std::unique_ptr<CollisionShape>> shapes_;

	// コンポーネントの持つシェイプのリスト
	CollisionComponent* component_;
};

