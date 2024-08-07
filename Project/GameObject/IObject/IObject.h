#pragma once

#include "../GameObject.h"
#include "3D/Model/Model.h"
#include "3D/Model/ModelManager/ModelManager.h"
#include "Transform/Transform.h"
#include "CollisionSystem/Collider/Collider.h"


// オブジェクトの属性
enum class ObjAttribute {
    PLAYER,
    ENEMY,
    TERRAIN,
    OTHER,
};


/* オブジェクトの基底クラス */
class IObject {

public: // メンバ関数

	// デストラクタ
	virtual ~IObject() {};

	// 初期化、更新、描画
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw3D() = 0;
	virtual void Draw2DFront() = 0;
	virtual void Draw2DBack() = 0;


    //// コライダー追加
    //void addCollider(ICollider* collider) {
    //    colliders.push_back(collider);
    //}

    // 衝突判定
    /*bool DetectCollisions(const IObject& other) const {
        for (const auto& collider1 : colliders) {
            for (const auto& collider2 : other.colliders) {
                if (collider1->DetectCollision(*collider2)) {
                    return true;
                }
            }
        }
        return false;
    }*/

    // 衝突時コールバック関数
    virtual void onCollision([[maybe_unused]] IObject* object) = 0;


protected: // メンバ変数

	// ModelManager
	ModelManager* modelManager_ = nullptr;

    // コライダー
    //std::vector<ICollider*> colliders;
};

