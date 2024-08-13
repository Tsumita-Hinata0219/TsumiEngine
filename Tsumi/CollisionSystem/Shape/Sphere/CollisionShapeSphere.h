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

	// コライダーの境界ボックスを求める
	void CalcBounding() override {

		// Col::AABBの各要素を求める
		Vector3 center = this->sphere_.center;
		float rad = this->sphere_.radius;
		Vector3 min = this->sphere_.center + Vector3(rad, rad, rad);
		Vector3 max = this->sphere_.center - Vector3(rad, rad, rad);
		int id = this->sphere_.id;
		
		// 境界ボックスに情報を挿入
		this->bounding_ = {
			center,
			min,
			max,
			id,
		};
	}


#pragma region Accessor

	// スフィアの情報
	ColShapeData GetData() const override {
		return this->sphere_;
	}
	void SetData(const ColShapeData& data) override {

		if (auto setData = std::get_if<Col::Sphere>(&data)) {
			this->sphere_ = *setData;
		}
		else {
			throw std::bad_variant_access(); // 型が一致しない場合のエラー処理
		}
	}

#pragma endregion 


private:

	// スフィアの情報
	Col::Sphere sphere_{};
};

