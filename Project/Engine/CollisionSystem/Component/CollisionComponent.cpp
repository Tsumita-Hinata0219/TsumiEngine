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
void CollisionComponent::Penetration(Vector3* translate, Col::ColData& colData)
{
    // Sphere型のコリジョン処理
    if (Col::Sphere* sphere = dynamic_cast<Col::Sphere*>(&colData)) {
        Vector3 direction = *translate - sphere->center;
        float distance = Length(direction);
        float overlap = sphere->radius - distance;

        if (overlap > 0.0f) { // めり込みがある場合
            direction = Normalize(direction);
            *translate += direction * overlap; // 押し出し処理
        }
    }
    // AABB型のコリジョン処理
    else if (Col::AABB* aabb = dynamic_cast<Col::AABB*>(&colData)) {
        Vector3 minTranslate = aabb->min - *translate;
        Vector3 maxTranslate = aabb->max - *translate;

        Vector3 push;
        push.x = std::fabs(minTranslate.x) < std::fabs(maxTranslate.x) ? minTranslate.x : maxTranslate.x;
        push.y = std::fabs(minTranslate.y) < std::fabs(maxTranslate.y) ? minTranslate.y : maxTranslate.y;
        push.z = std::fabs(minTranslate.z) < std::fabs(maxTranslate.z) ? minTranslate.z : maxTranslate.z;

        *translate += push; // 押し出し処理
    }
    // OBB型のコリジョン処理
    else if (Col::OBB* obb = dynamic_cast<Col::OBB*>(&colData)) {
        //// OBBとの押し出しには、OBBの軸方向への投影が必要
        //Vector3 direction = *translate - obb->center;
        //Vector3 projection;
        //for (int i = 0; i < 3; ++i) {
        //    float length = obb->orientations[i].Dot(direction);
        //    if (length > obb->size[i]) {
        //        projection += obb->orientations[i] * (length - obb->size[i]);
        //    }
        //    else if (length < -obb->size[i]) {
        //        projection += obb->orientations[i] * (length + obb->size[i]);
        //    }
        //}
        //*translate += projection; // 押し出し処理
    }
    // Segment型のコリジョン処理
    else if (Col::Segment* segment = dynamic_cast<Col::Segment*>(&colData)) {
        
    }
    // Capsule型のコリジョン処理
    else if (Col::Capsule* capsule = dynamic_cast<Col::Capsule*>(&colData)) {
        
    }

}

