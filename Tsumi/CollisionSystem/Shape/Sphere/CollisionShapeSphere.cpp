#include "CollisionShapeSphere.h"
#include "../AABB/CollisionShapeAABB.h"


// 衝突判定処理
bool CollisionShapeSphere::Intersects(const CollisionShape& other) const
{
    // Sphere x Sphere
    if (const CollisionShapeSphere* sphere = dynamic_cast<const CollisionShapeSphere*>(&other)) {

        Sphere s1 = this->sphere_;
        Sphere s2 = sphere->GetData();

        return Collision::IsCollision(s1, s2);
    }
    // Sphere x AABB
    else if (const CollisionShapeAABB* aabb = dynamic_cast<const CollisionShapeAABB*>(&other)) {

        AABB a1 = aabb->GetData();
        Sphere s1 = this->sphere_;

        return Collision::IsCollision(a1, s1);
    }
    
    // TODO : 他のシェイプとの当たり判定

    return false;
}
