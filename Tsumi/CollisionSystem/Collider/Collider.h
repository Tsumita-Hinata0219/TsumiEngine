#pragma once

//#include "../Detector/CollisionDetector.h"


// IObjectの前方宣言
class IObject;


/* 抽象的なコライダークラス */
class ICollider {

public:

	enum class Type {
		NONE,
		BOX,
		SPHERE,
	};

	// コンストラクタ
	ICollider() : id_(nextID_++) {};

	// 仮想デストラクタ
	virtual ~ICollider() = default;

	// 衝突判定処理
	virtual bool Detect(const ICollider& other) = 0;

#pragma region Accessor

	// ID
	int GetID() const { return this->id_; }

	// Type
	ICollider::Type GetType() const { return this->type_; }

#pragma endregion 


protected:

	// コライダーの持つID
	int id_ = 0;
	static int nextID_;

	// コライダーを所有するオブジェクト
	IObject* owner_ = nullptr;

	// コライダーのタイプ
	ICollider::Type type_ = ICollider::Type::NONE;
};