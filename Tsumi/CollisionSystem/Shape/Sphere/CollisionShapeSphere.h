#pragma once

#include "../CollisionShape.h"

/* CollisionShape TYPE : Sphere */
class CollisionShapeSphere : public CollisionShape {

public:

	// コンストラクタ
	CollisionShapeSphere() {}
	CollisionShapeSphere(Col::Sphere setData) : sphere_(setData) {};

	// 衝突判定処理
	bool Intersects(const CollisionShape& other) const override;
	bool Intersects(const CollisionShapeSphere& other) const override;
	bool Intersects(const CollisionShapeAABB& other) const override;


#pragma region Accessor

	// スフィアの情報
	Col::Sphere GetData() const { return this->sphere_; }
	void SetData(Col::Sphere setData) { this->sphere_ = setData; }

#pragma endregion 


private:

	// スフィアの情報
	Col::Sphere sphere_{};
};

