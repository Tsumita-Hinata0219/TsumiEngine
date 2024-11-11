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
void CollisionComponent::Penetration(Vector3* translate)
{
    // hitData_ が null でない場合のみ処理を行う
    if (hitData_.index() == 0) { 

        // 衝突相手のコライダーデータに基づいて処理を行う
        std::visit([&](auto&& shape) {
            using T = std::decay_t<decltype(shape)>;

            if constexpr (std::is_same_v<T, Col::Sphere>) {  // Sphere型のコリジョン処理
                Vector3 direction = *translate - shape.center;
                float distance = Length(direction);
                float overlap = shape.radius - distance;

                if (overlap > 0.0f) { // めり込みがある場合
                    direction = Normalize(direction);
                    *translate += direction * overlap; // 押し出し処理
                }
            }
            else if constexpr (std::is_same_v<T, Col::AABB>) { // AABB型のコリジョン処理
                Vector3 minTranslate = shape.min - *translate;
                Vector3 maxTranslate = shape.max - *translate;

                Vector3 push;
                push.x = std::fabs(minTranslate.x) < std::fabs(maxTranslate.x) ? minTranslate.x : maxTranslate.x;
                push.y = std::fabs(minTranslate.y) < std::fabs(maxTranslate.y) ? minTranslate.y : maxTranslate.y;
                push.z = std::fabs(minTranslate.z) < std::fabs(maxTranslate.z) ? minTranslate.z : maxTranslate.z;

                *translate += push; // 押し出し処理
            }
            else if constexpr (std::is_same_v<T, Col::OBB>) { // OBB型のコリジョン処理

            }
            else if constexpr (std::is_same_v<T, Col::Segment>) { // Segment型のコリジョン処理

            }
            else if constexpr (std::is_same_v<T, Col::Capsule>) { // Capsule型のコリジョン処理

            }
            }, hitData_); // std::variantに格納されたコライダーデータを処理

        // 処理が終わったら hitData_ を null に設定（std::variant を初期状態に戻す）
        hitData_ = {}; // 空の状態にする（全型におけるデフォルト値を設定）
    }
}

