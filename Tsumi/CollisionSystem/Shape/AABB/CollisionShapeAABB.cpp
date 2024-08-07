#include "CollisionShapeAABB.h"
#include "../Sphere/CollisionShapeSphere.h"


// 衝突判定処理
bool CollisionShapeAABB::Intersects(const CollisionShape& other) const
{
	return other.Intersects(*this);
}
bool CollisionShapeAABB::Intersects(const CollisionShapeSphere& other) const
{
	// AABB x Sphere
	AABB a1 = this->aabb_;
	Sphere s1 = other.GetData();

	return Collision::IsCollision(a1, s1);
}
bool CollisionShapeAABB::Intersects(const CollisionShapeAABB& other) const
{
	// AABB x AABB
	AABB a1 = this->aabb_;
	AABB a2 = other.GetData();

	return Collision::IsCollision(a1, a2);
}
