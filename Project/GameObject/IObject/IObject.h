#pragma once

#include "../GameObject.h"
#include "3D/Model/Model.h"
#include "3D/Model/ModelManager/ModelManager.h"
#include "Transform/Transform.h"
#include "CollisionSystem/Collider/Collider.h"

#include <unordered_set>


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

    // 衝突時コールバック関数
    virtual void onCollision([[maybe_unused]] IObject* object) = 0;


#pragma region Accessor アクセッサ

	// コライダー追加
	void AddCollider(ICollider<Sphere>* addCol) {
		this->sphereCol_.insert(addCol);
	}

	// コライダー取得
	const std::unordered_set<ICollider<Sphere>*>& GetCollider() const {
		return this->sphereCol_;
	}

#pragma endregion 


protected: // メンバ変数

	// ModelManager
	ModelManager* modelManager_ = nullptr;

	// コライダー
	std::unordered_set<ICollider<Sphere>*> sphereCol_;
	//std::unordered_set<Collider<Box>*> boxColliders_;
};

