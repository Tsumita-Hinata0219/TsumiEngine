#include "CollisionShapeSphere.h"
#include "../AABB/CollisionShapeAABB.h"
#include "../../Detect/CollisionDetect.h"


// 衝突判定処理
bool CollisionShapeSphere::Intersects(const CollisionShape& other) const
{
    return other.Intersects(*this);
}
bool CollisionShapeSphere::Intersects(const CollisionShapeSphere& other) const
{
    // Sphere x Sphere
    Col::Sphere s1 = this->GetData();
    Col::Sphere s2 = other.GetData();

    return Detect::Collision(s1, s2);
}
bool CollisionShapeSphere::Intersects(const CollisionShapeAABB& other) const
{
    // Sphere x AABB
    Col::AABB a1 = other.GetData();
    Col::Sphere s1 = this->GetData();

    return Detect::Collision(a1, s1);
}
