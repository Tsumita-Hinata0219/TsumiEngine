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
    // AABB x Sphere
    ColShapeData s1 = this->GetData();
    ColShapeData s2 = other.GetData();

    // 型が一致するか確認してデータを取り出す
    if (auto sphere1 = std::get_if<Col::AABB>(&s1)) {
        if (auto sphere2 = std::get_if<Col::Sphere>(&s2)) {
            return Detect::Collision(*sphere1, *sphere2);
        }
        else {
            throw std::invalid_argument("Other shape is not a Sphere");
        }
    }
    else {
        throw std::invalid_argument("This shape is not an AABB");
    }
}
bool CollisionShapeSphere::Intersects(const CollisionShapeAABB& other) const
{
    // Sphere x AABB
    ColShapeData a1 = other.GetData();
    ColShapeData s1 = this->GetData();

    // 型が一致するか確認してデータを取り出す
    if (auto aabb = std::get_if<Col::AABB>(&a1)) {
        if (auto sphere = std::get_if<Col::Sphere>(&s1)) {
            return Detect::Collision(*aabb, *sphere);
        }
        else {
            throw std::invalid_argument("Other shape is not a Sphere");
        }
    }
    else {
        throw std::invalid_argument("This shape is not an AABB");
    }
}
