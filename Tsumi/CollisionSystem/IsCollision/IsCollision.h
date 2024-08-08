#pragma once

#include "../../Project/Math/MyMath.h"
#include "../Structure/CollisionStructures.h"
#include "../Geometry/GeometryCollision.h"
//using namespace GeometryCollision;
#include "../Shape/CollisionShape.h"


namespace Collision {

	// 球と球の当たり判定
	bool IsCollision(const Sphere& s1, const Sphere& s2);

	// AABBとAABBの当たり判定
	bool IsCollision(const AABB& aabb1, const AABB& aabb2);

	// AABBと球の当たり判定
	bool IsCollision(const AABB& aabb, const Sphere& s);

	// AABBと線の当たり判定
	bool IsCollision(const AABB& aabb, const Segment& s);

	// OBBと球の当たり判定
	bool IsCollision(const OBB& obb, const Sphere& s);

	// OBBと線の当たり判定
	bool IsCollision(const OBB& obb, const Segment& s);

	// OBBとOBBの当たり判定
	bool IsCollision(const OBB& obb1, const OBB& obb2);

	// CapsuleとCapsuleの当たり判定
	bool IsCollision(const Capsule& capsule1, const Capsule& capsule2);
}


namespace Detect {

	// 球と球の当たり判定
	bool Collision(const Col::Sphere& s1, const Col::Sphere& s2) {

	}
	// AABBとAABBの当たり判定
	bool Collision(const Col::AABB& aabb1, const Col::AABB& aabb2) {

	}
	// AABBと球の当たり判定
	bool Collision(const Col::AABB& aabb, const Col::Sphere& s) {

	}
	// AABBと線の当たり判定
	bool Collision(const Col::AABB& aabb, const Col::Segment& s) {

	}
	// OBBと球の当たり判定
	bool Collision(const Col::OBB& obb, const Col::Sphere& s) {

	}
	// OBBと線の当たり判定
	bool Collision(const Col::OBB& obb, const Col::Segment& s) {

	}
	// OBBとOBBの当たり判定
	bool Collision(const Col::OBB& obb1, const Col::OBB& obb2) {

	}
	// CapsuleとCapsuleの当たり判定
	bool Collision(const Col::Capsule& capsule1, const Col::Capsule& capsule2) {

	}

}