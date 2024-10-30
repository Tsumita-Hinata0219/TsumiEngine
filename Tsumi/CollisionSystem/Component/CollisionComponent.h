#pragma once

#include "../../Project/Math/MyMath.h"
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
	void RegisterCollider(Col::Sphere& sphere);
	void Register(Col::ColData& colData);

	// シェイプの更新
	void UpdateShape(const Col::Sphere& sphere);
	void Update(const Col::ColData& colData);

	// コリジョンのチェック
	bool CheckCollision(const CollisionComponent& other) const;


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

	// コリジョンシェイプ
	std::map<int, std::unique_ptr<CollisionShape>> shapeMap_;
	////std::map<int, CollisionShape*> shapes_;
	//std::map<int, std::unique_ptr<CollisionShape>> shapes_;

	// インデックス
	uint32_t index_ = 0;

	// 識別
	uint32_t attribute_ = ColliderAttribute::None;
};

