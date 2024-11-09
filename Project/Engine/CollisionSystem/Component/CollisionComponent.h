#pragma once

#include "Math/MyMath.h"
#include "../Shape/CollisionShape.h"
#include "../Collider/ColliderConfig.h"

#include <memory>
#include <vector>
#include <functional>
#include <typeindex>


// IObjectの前方宣言
class IObject;

/* コリジョンシェイプを保持するクラス */
class CollisionComponent {

public:

	// コンストラクタ、デストラクタ
	CollisionComponent();
	~CollisionComponent() {};

	// パラメータ付きコンストラクタ
	CollisionComponent(IObject* setObject);

	// シェイプの追加
	void Register(Col::ColData& colData);


#pragma region Accessor

	// IObject
	IObject* GetOwner() const { return this->owner_; }

	// Attribute
	void SetAttribute(uint32_t setAttribute) { this->attribute_ = setAttribute; }

#pragma endregion 


private:

	// オーナー
	IObject* owner_ = nullptr;

	// シェイプと構造体を繋ぐID
	int nextID_ = 0;

	// インデックス
	uint32_t index_ = 0;

	// 識別
	uint32_t attribute_ = ColliderAttribute::None;
};

