#pragma once

#include<cstdint>

#include "../../Structure/CollisionStructures.h"
#include "../Collider.h"
#include "../ColliderConfig.h"
#include "../../IsCollision/IsCollision.h"

#include "Math/MyMath.h"
#include "Transform/Transform.h"


/* SphereColliderクラス */
class SphereCollider : public ICollider<Sphere> {

public:

	// コンストラクタ
	SphereCollider(IObject* owner) : ICollider(owner) { type_ = ICollider::Type::SPHERE; };

	// データの書き込み
	void WriteData(Sphere setData) { ICollider::SetShape(setData); }

	// 衝突判定処理
	bool Detect(const ICollider* other) const override {

		return Collision::IsCollision(this->GetShape(), other->GetShape());
	}

private:

};