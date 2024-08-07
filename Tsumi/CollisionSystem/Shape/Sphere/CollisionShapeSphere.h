#pragma once

#include "../CollisionShape.h"

/* CollisionShape TYPE : Sphere */
class CollisionShapeSphere : public CollisionShape {

public:

	// コンストラクタ
	CollisionShapeSphere() {}
	CollisionShapeSphere(Sphere setData) : sphere_(setData) {};

	// 衝突判定処理
	bool Intersects(const CollisionShape& other) const override;


#pragma region Accessor

	// スフィアの情報
	Sphere GetData() const { return this->sphere_; }

#pragma endregion 


private:

	// スフィアの情報
	Sphere sphere_{};
};

