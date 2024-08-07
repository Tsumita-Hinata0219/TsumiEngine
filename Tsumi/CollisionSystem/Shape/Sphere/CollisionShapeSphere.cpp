#include "CollisionShapeSphere.h"



// 衝突判定処理
bool CollisionShapeSphere::Intersects(const CollisionShape& other) const
{
    // Sphere x Sphere
    if (const CollisionShapeSphere* sphere = dynamic_cast<const CollisionShapeSphere*>(&other)) {

        return Collision::IsCollision(this->sphere_, sphere->GetData());
    }
    
    // TODO : 他のシェイプとの当たり判定

    return false;
}
