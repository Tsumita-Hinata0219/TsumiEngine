#pragma once

#include "../../Project/Math/MyMath.h"
#include "../Tree/Octree/Octree.h"
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


class CollisionComponent;
class CollisionShapeSphere;
class CollisionShapeAABB;

/* Shapeの抽象基底クラス */
class CollisionShape {

public:

	// コンストラクタ
	CollisionShape(CollisionComponent* comp) : component_(comp) {};

	// 仮想デストラクタ
	virtual ~CollisionShape() = default;

	// 純粋仮想関数 : 異なるシェイプに応じた衝突判定処理
	virtual bool Intersects(const CollisionShape& other) const = 0;
	virtual bool Intersects(const CollisionShapeSphere& other) const = 0;
	virtual bool Intersects(const CollisionShapeAABB& other) const = 0;

	// 純粋仮想関数 : コライダーの境界ボックスを求める
	virtual void CalcBounding() = 0;

	// 境界ボックスからモートン番号を求める
	void CalcSpaceLevel() {

		/* ===================================================== */

		// 座標から左上と右下を求める
		std::pair<Vector2, Vector2> pos;
		pos.first = { // 左上
			bounding_.center.x + bounding_.min.x,
			bounding_.center.y + bounding_.max.y,
		};
		pos.second = { // 右下
			bounding_.center.x + bounding_.max.x,
			bounding_.center.y + bounding_.min.y,
		};

		// 座標と孫空間の一辺で割りintでキャストしたもの
		float U = (ROOT_EDGE_LENGTH / std::pow(2, 3));
		std::pair<int, int> leftTop = {
			static_cast<int>(pos.first.x / U),
			static_cast<int>(pos.first.y / U),
		};
		std::pair<int, int> rightDown = {
			static_cast<int>(pos.second.x / U),
			static_cast<int>(pos.second.y / U),
		};

		// AABBの二頂点の所属空間
		vertexSpaceID_ = {
			Get2DMortonNumber(leftTop.first, leftTop.second),	  // 左上
			Get2DMortonNumber(rightDown.first, rightDown.second), // 右下
		};

		/* ===================================================== */  // TODO : 現状2Dなので後で3D用に変える


		// 二頂点のXOR
		int XOR = vertexSpaceID_.first ^ vertexSpaceID_.second;

		// 最上位ビット位置
		int highestBitPos = findHighestBitPosition(XOR);

		// 空間レベル
		levelIndex = 3 - highestBitPos / 2;

		// 所属空間
		spaceIndex_ = vertexSpaceID_.first >> highestBitPos;
	}


#pragma region Accessor アクセッサ

	// 各コライダーデータ
	virtual ColShapeData GetData() const = 0;
	virtual void SetData(const ColShapeData& data) = 0;

	// Bounding
	Col::AABB GetBounding() const { this->bounding_; }
	void SetBounding(const Col::AABB& setData) { this->bounding_ = setData; }

#pragma endregion 


protected:

	// シェイプを持っているコンポーネント
	CollisionComponent* component_ = nullptr;

	// コライダーの境界ボックス
	Col::AABB bounding_{};

	// 空間レベル
	uint32_t levelIndex = 0;

	// どの空間に属しているかのモートン番号
	uint32_t spaceIndex_ = 0;

	// 二頂点の所属空間
	std::pair<int, int> vertexSpaceID_;
};
