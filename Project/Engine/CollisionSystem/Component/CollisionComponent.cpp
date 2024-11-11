#include "CollisionComponent.h"
#include "../Manager/CollisionManager.h"
#include "../Shape/CollisionShape.h"
#include "../Shape/Sphere/CollisionShapeSphere.h"
#include "../Shape/AABB/CollisionShapeAABB.h"


// コンストラクタ
CollisionComponent::CollisionComponent()
{
	// インデックスの初期化
	index_ = 0;
}


// パラメータ付きコンストラクタ
CollisionComponent::CollisionComponent(IObject* setObject)
{
	this->owner_ = setObject;
}


void CollisionComponent::Register(Col::ColData& colData)
{
	this->nextID_++; // IDの加算
	colData.id = this->nextID_; // IDの設定

	// マネージャーにポインタを渡す
	CollisionManager::GetInstance()->Register(attribute_, &colData, this);
}


// 押し出し処理
void CollisionComponent::Penetration(Vector3* translate, ColShapeData ownerCollider)
{
    // std::visit を使って、二つのコライダーの型に応じた処理を実行
    std::visit([&](auto&& ownerCollider, auto&& hitCollider_) {
        using T1 = std::decay_t<decltype(ownerCollider)>;
        using T2 = std::decay_t<decltype(hitCollider_)>;

        if constexpr (std::is_same_v<T1, Col::Sphere> && std::is_same_v<T2, Col::Sphere>) {
            // Sphere と Sphere の場合の処理
            *translate = HandleSphereSpherePenetration(ownerCollider, hitCollider_);
        }
        else if constexpr (std::is_same_v<T1, Col::Sphere> && std::is_same_v<T2, Col::AABB>) {
            // Sphere と AABB の場合の処理
            *translate = HandleSphereAABBPpenetration(ownerCollider, hitCollider_);
        }
        else if constexpr (std::is_same_v<T1, Col::Sphere> && std::is_same_v<T2, Col::OBB>) {
            // Sphere と OBB の場合の処理
            *translate = HandleSphereOBBPpenetration(ownerCollider, hitCollider_);
        }
        else if constexpr (std::is_same_v<T1, Col::AABB> && std::is_same_v<T2, Col::AABB>) {
            // AABB と AABB の場合の処理
            *translate = HandleAABBAABBPpenetration(ownerCollider, hitCollider_);
        }
        else if constexpr (std::is_same_v<T1, Col::AABB> && std::is_same_v<T2, Col::Sphere>) {
            // AABB と Sphere の場合の処理
            *translate = HandleAABBSpherePenetration(ownerCollider, hitCollider_);
        }
        // 他の組み合わせも必要に応じて追加
        }, ownerCollide, hitCollider);
}
