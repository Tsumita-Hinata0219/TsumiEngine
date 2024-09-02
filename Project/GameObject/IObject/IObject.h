#pragma once

#include "../GameObject.h"
#include "3D/Model/Model.h"
#include "3D/Model/ModelManager/ModelManager.h"
#include "Transform/Transform.h"
#include "CollisionSystem/Collider/Collider.h"

#include "../Tsumi/CollisionSystem/Component/CollisionComponent.h"


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

	// CollisionComponent
	CollisionComponent* GetColComponent() const { return this->colComp_.get(); }

	// ObjAttribute
	ObjAttribute GetAttribute() const { return this->attribute_; }

#pragma endregion 


protected: // メンバ変数

	// ModelManager
	ModelManager* modelManager_ = nullptr;

	// コライダー
	std::unique_ptr<CollisionComponent> colComp_;

	// オブジェクトの属性
	ObjAttribute attribute_ = ObjAttribute::OTHER;
};

