#pragma once

#include "../../Project/Math/MyMath.h"
#include <variant>


namespace Col {

	struct Sphere {
		Vector3 center{}; // !< 中心座標
		float radius;	  // !< 半径
		int id;
	};
	struct AABB {
		Vector3 center{}; // !< 中心座標
		Vector3 min;      // !< 最少点
		Vector3 max;      // !< 最大点
		int id;
	};
	struct OBB {
		Vector3 center;			   // !< 中心点
		Vector3 rotate{};          // !< 姿勢
		Vector3 orientations[3]{}; // !< 座標軸。正規化・直交必須
		Vector3 size;              // !< 座標軸方向の長さの半分。中心から面までの距離
		int id;
	};
	struct Segment {
		Vector3 origin;	// !< 始点
		Vector3 diff;   // !< 終点への差分ベクトル
		int id;
	};
	// カプセル
	struct Capsule {
		Vector3 center;  // !< 中心座標
		Segment segment; // !< 始点と終点
		Vector3 rotate;  // !< オイラー角(姿勢) 
		float radius;    // !< 半径
		int id;
	};
}

// 異なる型を扱うためのVariant型
using ColShapeData = std::variant<Col::Sphere, Col::AABB, Col::OBB, Col::Segment, Col::Capsule>;


class CollisionShapeSphere;
class CollisionShapeAABB;

/* Shapeの抽象基底クラス */
class CollisionShape {

public:

	// 仮想デストラクタ
	virtual ~CollisionShape() = default;

	// 純粋仮想関数 : 異なるシェイプに応じた衝突判定処理
	virtual bool Intersects(const CollisionShape& other) const = 0;
	virtual bool Intersects(const CollisionShapeSphere& other) const = 0;
	virtual bool Intersects(const CollisionShapeAABB& other) const = 0;

	// 純粋仮想関数 : コライダーの境界ボックスを求める
	virtual void CalcBounding() = 0;


#pragma region Accessor アクセッサ

	// 各コライダーデータ
	virtual ColShapeData GetData() const = 0;
	virtual void SetData(const ColShapeData& data) = 0;

	// Bounding
	Col::AABB GetBounding() const { this->bounding_; }
	void SetBounding(const Col::AABB& setData) { this->bounding_ = setData; }

#pragma endregion 


protected:

	// どの空間に属しているかの境界ボックス
	Col::AABB bounding_{};

};

