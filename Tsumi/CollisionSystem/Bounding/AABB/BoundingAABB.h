#pragma once

#include "../../Shape/CollisionShape.h"


/* 3D空間内の境界を表現するクラス : AABB */
class BoundingAABB {

public:

	// コンストラクタ、デストラクタ
	BoundingAABB() = default;
	~BoundingAABB() {};

	// パラメータ付きコンストラクタ
	BoundingAABB(Col::AABB setData) {
		this->aabb_ = setData;
	}

	// 指定の範囲と重なっているかどうかを判定


	// 指定の点がこのBounding内にあるかどうか


private:

	Col::AABB aabb_{};

};

