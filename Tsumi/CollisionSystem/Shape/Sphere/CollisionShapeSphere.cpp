#include "CollisionShapeSphere.h"
#include "../AABB/CollisionShapeAABB.h"


// 衝突判定処理
bool CollisionShapeSphere::Intersects(const CollisionShape& other) const
{
    return other.Intersects(*this);
}
bool CollisionShapeSphere::Intersects(const CollisionShapeSphere& other) const
{
    // Sphere x Sphere
    Sphere s1 = this->sphere_;
    Sphere s2 = other.GetData();

    return Collision::IsCollision(s1, s2);
}
bool CollisionShapeSphere::Intersects(const CollisionShapeAABB& other) const
{
    // Sphere x AABB
    AABB a1 = other.GetData();
    Sphere s1 = this->sphere_;

    return Collision::IsCollision(a1, s1);
}
