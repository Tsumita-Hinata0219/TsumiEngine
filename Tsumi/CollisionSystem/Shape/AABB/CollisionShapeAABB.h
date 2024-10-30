#pragma once

#include "../CollisionShape.h"


// 前方宣言
class CollisionComponent;
class CollisionShapeSphere;


/* CollisionShape TYPE : AABB */
class CollisionShapeAABB : public CollisionShape {

public:

	// コンストラクタ
	CollisionShapeAABB() = default;

	// パラメータ付きコンストラクタ
	CollisionShapeAABB(CollisionComponent* comp);
	CollisionShapeAABB(CollisionComponent* comp, Col::AABB* setData);

	// 衝突判定処理
	bool Intersects(const CollisionShape& other) const override;
	bool Intersects(const CollisionShapeSphere& other) const override;
	bool Intersects(const CollisionShapeAABB& other) const override;

	// コライダーの境界ボックスを求める
	void CalcBounding() override;

	// ImGuiの描画
	void DrawImGui(const std::string& label = "") override;


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
	Col::ColData GetColData() const override {
		return this->aabb_;
	}
	void SetData(const Col::ColData& data) override {
		
		if (const auto* setData = dynamic_cast<const Col::AABB*>(&data)) {
			this->aabb_ = *setData;  // AABB型の場合、値をコピー
		}
		else {
			throw std::runtime_error("Invalid type: ColData is not AABB.");
		}
	}

#pragma endregion


private:

	// AABBの情報
	Col::AABB aabb_{};
};
