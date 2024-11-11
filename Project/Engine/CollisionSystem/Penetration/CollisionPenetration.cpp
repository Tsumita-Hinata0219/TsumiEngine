#include "CollisionPenetration.h"
#include "../Util/CollisionUtilities.h"



// Sphere 同士の交差判定と押し出し
Vector3 Penetration::HandleSphereSpherePenetration(Col::Sphere& ownerSphere, Col::Sphere& hitSphere)
{
	Vector3 direction = ownerSphere.center - hitSphere.center;
	float distance = Length(direction);
	float overlap = ownerSphere.radius + hitSphere.radius - distance;

	if (overlap > 0.0f) {
		direction = Normalize(direction);
		return direction * overlap;  // 押し出し
	}
	return Vector3();
}


// Sphere と AABB の交差判定と押し出し
Vector3 Penetration::HandleSphereAABBPpenetration(Col::Sphere& ownerSphere, Col::AABB& hitAABB)
{
	Vector3 closestPoint = ColUtil::GetClosestPoint(hitAABB, ownerSphere.center);
	Vector3 direction = ownerSphere.center - closestPoint;
	float distance = Length(direction);
	float overlap = ownerSphere.radius - distance;

	if (overlap > 0.0f) {
		direction = Normalize(direction);
		return direction * overlap;  // 押し出し
	}
	return Vector3();
}


// Sphere と OBB の交差判定と押し出し
Vector3 Penetration::HandleSphereOBBPpenetration(Col::Sphere& ownerSphere, Col::OBB& hitOBB)
{
	Vector3 closestPoint = ColUtil::GetClosestPoint(hitOBB, ownerSphere.center);
	Vector3 direction = ownerSphere.center - closestPoint;
	float distance = Length(direction);
	float overlap = ownerSphere.radius - distance;

	if (overlap > 0.0f) {
		direction = Normalize(direction);
		return direction * overlap;  // 押し出し
	}
	return Vector3();
}


// AABB 同士の交差判定と押し出し
Vector3 Penetration::HandleAABBAABBPpenetration(Col::AABB& ownerAABB, Col::AABB& hitAABB)
{
	// AABB同士の押し出し処理（例：最小のオーバーラップを計算し、押し出す）
	Vector3 push = ColUtil::GetPenetrationPush(ownerAABB, hitAABB);
	return push;
}


// AABB と Sphere の交差判定と押し出し
Vector3 Penetration::HandleAABBSpherePenetration(Col::AABB& ownerAABB, Col::Sphere& hitSphere)
{
	Vector3 closestPoint = ColUtil::GetPenetrationPush(ownerAABB, hitSphere);
	Vector3 direction = hitSphere.center - closestPoint;
	float distance = Length(direction);
	float overlap = hitSphere.radius - distance;

	if (overlap > 0.0f) {
		direction = Normalize(direction);
		return direction * overlap;  // 押し出し
	}
	return Vector3();
}


// AABB と OBB の交差判定と押し出し
Vector3 Penetration::HandleAABBOBBPenetration(Col::AABB& ownerAABB, Col::OBB& hitOBB)
{
	// AABB と OBB の交差判定処理
	Vector3 push = ColUtil::GetPenetrationPush(ownerAABB, hitOBB);
	return push;
}


// OBB 同士の交差判定と押し出し
Vector3 Penetration::HandleOBBObbPenetration(Col::OBB& ownerOBB, Col::OBB& hitOBB)
{
	// OBB同士の交差判定処理
	Vector3 push = ColUtil::GetPenetrationPush(ownerOBB, hitOBB);
	return push;
}


// OBB と Sphere の交差判定と押し出し
Vector3 Penetration::HandleOBBSpherePenetration(Col::OBB& ownerOBB, Col::Sphere& hitSphere)
{
	// OBB と Sphere の交差判定処理
	Vector3 closestPoint = ColUtil::GetPenetrationPush(ownerOBB, hitSphere);
	Vector3 direction = hitSphere.center - closestPoint;
	float distance = Length(direction);
	float overlap = hitSphere.radius - distance;

	if (overlap > 0.0f) {
		direction = Normalize(direction);
		return direction * overlap;  // 押し出し
	}
	return Vector3();
}


// OBB と AABB の交差判定と押し出し
Vector3 Penetration::HandleOBBAABBPpenetration(Col::OBB& ownerOBB, Col::AABB& hitAABB)
{
	// OBB と AABB の交差判定処理
	Vector3 push = ColUtil::GetPenetrationPush(ownerOBB, hitAABB);
	return push;
}


// Segment と Sphere の交差判定と押し出し
Vector3 Penetration::HandleSegmentSpherePenetration(Col::Segment& ownerSegment, Col::Sphere& hitSphere)
{
	// Segment と Sphere の交差判定処理
	Vector3 push = ColUtil::GetPenetrationPush(ownerSegment, hitSphere);
	return push;
}


// Capsule と Sphere の交差判定と押し出し
Vector3 Penetration::HandleCapsuleSpherePenetration(Col::Capsule& ownerCapsule, Col::Sphere& hitSphere)
{
	// Capsule と Sphere の交差判定処理
	Vector3 push = ColUtil::GetPenetrationPush(ownerCapsule, hitSphere);
	return push;
}


// Segment と AABB の交差判定と押し出し
Vector3 Penetration::HandleSegmentAABBPpenetration(Col::Segment& ownerSegment, Col::AABB& hitAABB)
{
	// Segment と AABB の交差判定処理
	Vector3 push = ColUtil::GetPenetrationPush(ownerSegment, hitAABB);
	return push;
}


// Capsule と AABB の交差判定と押し出し
Vector3 Penetration::HandleCapsuleAABBPpenetration(Col::Capsule& ownerCapsule, Col::AABB& hitAABB)
{
	// Capsule と AABB の交差判定処理
	Vector3 push = ColUtil::GetPenetrationPush(ownerCapsule, hitAABB);
	return push;
}


// Capsule と Capsule の交差判定と押し出し
Vector3 Penetration::HandleCapsuleCapsulePenetration(Col::Capsule& ownerCapsule, Col::Capsule& hitCapsule)
{
	// Capsule と Capsule の交差判定処理
	Vector3 push = ColUtil::GetPenetrationPush(ownerCapsule, hitCapsule);
	return push;
}


// Segment と Segment の交差判定と押し出し
Vector3 Penetration::HandleSegmentSegmentPenetration(Col::Segment& ownerSegment, Col::Segment& hitSegment)
{
	// Segment と Segment の交差判定処理
	Vector3 push = ColUtil::GetPenetrationPush(ownerSegment, hitSegment);
	return push;
}
