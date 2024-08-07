#pragma once

#include<cstdint>

#include "../../Structure/CollisionStructures.h"
#include "../Collider.h"
#include "../ColliderConfig.h"

#include "Math/MyMath.h"
#include "Transform/Transform.h"


/* SphereColliderクラス */
class SphereCollider : public ICollider {

public:

	// コンストラクタ
	SphereCollider() { type_ = ICollider::Type::SPHERE; };
	SphereCollider(Sphere setData) : sphere_(setData) { type_ = ICollider::Type::SPHERE; };

	// データの書き込み
	void WriteData(Sphere setData) { this->sphere_ = setData; }

	// 衝突判定処理
	/*bool Detect(const ICollider& other) override {
		other;
		return 0;
	}*/


private:

	Sphere sphere_{};

};