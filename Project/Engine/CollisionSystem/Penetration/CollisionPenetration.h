#pragma once
#include "Math/MyMath.h"
#include "../Shape/CollisionShape.h"




/* 衝突時の押し出し処理 */
namespace Penetration {

	// Sphere 同士の交差判定と押し出し
	Vector3 HandleSphereSpherePenetration(Col::Sphere& ownerSphere, Col::Sphere& hitSphere);

	// Sphere と AABB の交差判定と押し出し
	Vector3 HandleSphereAABBPpenetration(Col::Sphere& ownerSphere, Col::AABB& hitAABB);

	// Sphere と OBB の交差判定と押し出し
	Vector3 HandleSphereOBBPpenetration(Col::Sphere& ownerSphere, Col::OBB& hitOBB);

	// AABB 同士の交差判定と押し出し
	Vector3 HandleAABBAABBPpenetration(Col::AABB& ownerAABB, Col::AABB& hitAABB);

	// AABB と Sphere の交差判定と押し出し
	Vector3 HandleAABBSpherePenetration(Col::AABB& ownerAABB, Col::Sphere& hitSphere);

	// AABB と OBB の交差判定と押し出し
	Vector3 HandleAABBOBBPenetration(Col::AABB& ownerAABB, Col::OBB& hitOBB);

	// OBB 同士の交差判定と押し出し
	Vector3 HandleOBBObbPenetration(Col::OBB& ownerOBB, Col::OBB& hitOBB);

	// OBB と Sphere の交差判定と押し出し
	Vector3 HandleOBBSpherePenetration(Col::OBB& ownerOBB, Col::Sphere& hitSphere);

	// OBB と AABB の交差判定と押し出し
	Vector3 HandleOBBAABBPpenetration(Col::OBB& ownerOBB, Col::AABB& hitAABB);

	// Segment と Sphere の交差判定と押し出し
	Vector3 HandleSegmentSpherePenetration(Col::Segment& ownerSegment, Col::Sphere& hitSphere);

	// Capsule と Sphere の交差判定と押し出し
	Vector3 HandleCapsuleSpherePenetration(Col::Capsule& ownerCapsule, Col::Sphere& hitSphere);

	// Segment と AABB の交差判定と押し出し
	Vector3 HandleSegmentAABBPpenetration(Col::Segment& ownerSegment, Col::AABB& hitAABB);

	// Capsule と AABB の交差判定と押し出し
	Vector3 HandleCapsuleAABBPpenetration(Col::Capsule& ownerCapsule, Col::AABB& hitAABB);

	// Capsule と Capsule の交差判定と押し出し
	Vector3 HandleCapsuleCapsulePenetration(Col::Capsule& ownerCapsule, Col::Capsule& hitCapsule);

	// Segment と Segment の交差判定と押し出し
	Vector3 HandleSegmentSegmentPenetration(Col::Segment& ownerSegment, Col::Segment& hitSegment);

}

