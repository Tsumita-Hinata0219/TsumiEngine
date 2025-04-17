#pragma once

#include "IEntityCollider.h"
#include "../Detect/CollisionIntersects.h"


namespace Entity {
namespace Collision {

class AABBCollider : public IEntityCollider {

public:

	Vector3 m_Min{};
	Vector3 m_Max{};


public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	AABBCollider() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~AABBCollider() = default;

	/// <summary>
	/// 識別IDのGetter
	/// </summary>
	ColliderTypeID GetTypeID() const override {
		return ColliderTypeID::AABB;
	}

	/// <summary>
	/// 判定処理
	/// </summary>
	bool Intersects(const IEntityCollider& other) const override {
		return other.Intersects(*this);
	}

	/// <summary>
	/// ディスパッチ
	/// </summary>
	bool IntersectsWith(const SphereCollider& other) const override {
		return Detect::Intersects(*this, other);
	}
	bool IntersectsWith(const AABBCollider& other) const override {
		return Detect::Intersects(*this, other);
	}

};
}
}