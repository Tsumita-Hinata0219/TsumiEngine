#pragma once

#include "../GameObject.h"
#include "../Config/AppComfig.h"
#include "3D/Model/Model.h"
#include "3D/Model/ModelManager/ModelManager.h"
#include "Transform/Transform.h"

#include "CollisionSystem/Manager/CollisionManager.h"

#include <unordered_set>


// 前方宣言
class ICollider;


/* オブジェクトの基底クラス */
class IObject {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	IObject();

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~IObject() {};

	/// <summary>
	/// 初期化処理 : 純粋仮想関数
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 更新処理 : 純粋仮想関数
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画処理 : 純粋仮想関数
	/// </summary>
	virtual void Draw3D() = 0;
	virtual void Draw2DFront() = 0;
	virtual void Draw2DBack() = 0;

    /// <summary>
    /// 衝突時コールバック関数
    /// </summary>
    virtual void onCollision([[maybe_unused]] IObject* object) = 0;

#pragma region Accessor アクセッサ

	// ObjAttribute
	ObjCategory GetCategory() const { return this->attribute_.first; }
	ObjType GetType() const { return this->attribute_.second; }

#pragma endregion 


protected: // メンバ変数

	// ModelManager
	ModelManager* modelManager_ = nullptr;

	// オブジェクトの属性
	std::pair<ObjCategory, ObjType> attribute_ 
		= { ObjCategory::OTHER, ObjType::OTHER };
};