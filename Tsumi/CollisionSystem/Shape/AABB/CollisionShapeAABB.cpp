#include "CollisionShapeAABB.h"
#include "../Sphere/CollisionShapeSphere.h"


// 衝突判定処理
bool CollisionShapeAABB::Intersects(const CollisionShape& other) const
{
    // AABB x AABB
    if (const CollisionShapeAABB* aabb = dynamic_cast<const CollisionShapeAABB*>(&other)) {

        AABB a1 = this->aabb_;
        AABB a2 = aabb->GetData();

        return Collision::IsCollision(a1, a2);
    }
    // AABB x Sphere
    else if (const CollisionShapeSphere* sphere = dynamic_cast<const CollisionShapeSphere*>(&other)) {

        AABB a1 = this->aabb_;
        Sphere s1 = sphere->GetData();

        return Collision::IsCollision(a1, s1);
    }

    // TODO : 他のシェイプとの当たり判定

    return false;
}
