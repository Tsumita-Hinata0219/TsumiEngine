#pragma once

#include "../CollisionShape.h"

/* CollisionShape TYPE : AABB */
class CollisionShapeAABB : public CollisionShape {

public:

	// コンストラクタ
	CollisionShapeAABB() {}
	CollisionShapeAABB(AABB setData) : aabb_(setData) {};

	// 衝突判定処理
	bool Intersects(const CollisionShape& other) const override;


#pragma region Accessor

	// スフィアの情報
	AABB GetData() const { return this->aabb_; }

#pragma endregion 


private:

	// スフィアの情報
	AABB aabb_{};
};
