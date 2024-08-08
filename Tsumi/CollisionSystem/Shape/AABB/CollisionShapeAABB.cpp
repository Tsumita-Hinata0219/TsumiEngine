#include "CollisionShapeAABB.h"
#include "../Sphere/CollisionShapeSphere.h"
#include "../../Detect/CollisionDetect.h"


// 衝突判定処理
bool CollisionShapeAABB::Intersects(const CollisionShape& other) const
{
	return other.Intersects(*this);
}
bool CollisionShapeAABB::Intersects(const CollisionShapeSphere& other) const
{
	// AABB x Sphere
	Col::AABB a1 = this->GetData();
	Col::Sphere s1 = other.GetData();

	return Detect::Collision(a1, s1);
}
bool CollisionShapeAABB::Intersects(const CollisionShapeAABB& other) const
{
	// AABB x AABB
	Col::AABB a1 = this->GetData();
	Col::AABB a2 = other.GetData();

	return Detect::Collision(a1, a2);
}
