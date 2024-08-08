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
    ColShapeData a1 = this->GetData();
    ColShapeData s1 = other.GetData();

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
bool CollisionShapeAABB::Intersects(const CollisionShapeAABB& other) const
{
	// AABB x AABB
    ColShapeData a1 = this->GetData();
    ColShapeData a2 = other.GetData();

    // 型が一致するか確認してデータを取り出す
    if (auto aabb1 = std::get_if<Col::AABB>(&a1)) {
        if (auto aabb2 = std::get_if<Col::AABB>(&a2)) {
            return Detect::Collision(*aabb1, *aabb2);
        }
        else {
            throw std::invalid_argument("Other shape is not a AABB");
        }
    }
    else {
        throw std::invalid_argument("This shape is not an AABB");
    }
}
