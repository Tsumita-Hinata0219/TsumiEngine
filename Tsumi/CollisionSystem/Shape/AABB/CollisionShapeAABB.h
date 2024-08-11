#pragma once

#include "../CollisionShape.h"

/* CollisionShape TYPE : AABB */
class CollisionShapeAABB : public CollisionShape {

public:

	// コンストラクタ
	CollisionShapeAABB() {}
	CollisionShapeAABB(Col::AABB setData) : aabb_(setData) {};

	// 衝突判定処理
	bool Intersects(const CollisionShape& other) const override;
	bool Intersects(const CollisionShapeSphere& other) const override;
	bool Intersects(const CollisionShapeAABB& other) const override;


#pragma region Accessor

	// AABBの情報
	ColShapeData GetData() const override {
		return this->aabb_;
	}
	void SetData(const ColShapeData& data) override {

		if (auto setData = std::get_if<Col::AABB>(&data)) {
			this->aabb_ = *setData;
		}
		else {
			throw std::bad_variant_access(); // 型が一致しない場合のエラー処理
		}
	}

#pragma endregion


private:

	// AABBの情報
	Col::AABB aabb_{};
};
