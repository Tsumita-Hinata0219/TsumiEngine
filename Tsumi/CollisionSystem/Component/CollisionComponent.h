#pragma once

#include "../../Project/Math/MyMath.h"
#include "../Shape/CollisionShape.h"
#include "../Shape/Sphere/CollisionShapeSphere.h"
#include "../Shape/AABB/CollisionShapeAABB.h"


#include <memory>
#include <vector>


/* コリジョンシェイプを保持するクラス */
class CollisionComponent {

public:

	// コンストラクタ、デストラクタ
	CollisionComponent() {};
	~CollisionComponent() {};

	// パラメータ付きコンストラクタ
	CollisionComponent(std::vector<std::unique_ptr<CollisionShape>> addShape) {
		this->shapes_ = std::move(addShape);
	}

	// シェイプの追加
	void AddShape(std::unique_ptr<CollisionShape> addShape) {
		this->shapes_.emplace_back(std::move(addShape));
	}

	// コリジョンのチェック
	bool CheckCollision(const CollisionComponent& other) const {
		for (const auto& shapeA : shapes_) {
			for (const auto& shapeB : other.shapes_) {
				if (shapeA->Intersects(*shapeB)) {
					return true; // コリジョンが検出された
				}
			}
		}
		return false; // コリジョンなし
	}


#pragma region Accessor


#pragma endregion 


private:

	// コリジョンシェイプ
	std::vector<std::unique_ptr<CollisionShape>> shapes_;

	// ID
	int mectID_;
};

