#pragma once

#include "../../Project/Math/MyMath.h"
#include "../Shape/CollisionShape.h"
#include "../Shape/Sphere/CollisionShapeSphere.h"
#include "../Shape/AABB/CollisionShapeAABB.h"


#include <memory>
#include <vector>


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
	void Register(ColShapeData& shape);

	// シェイプの更新
	void UpdateShape(const Col::Sphere& sphere);

	// コリジョンのチェック
	bool CheckCollision(const CollisionComponent& other) const;


#pragma region Accessor

	// IObject
	IObject* GetOwner() const { return this->owner_; }

#pragma endregion 


private:

	// 新しいシェイプを追加
	void CreateNewSphereShape();
	void CreateNewAABBShape();


private:

	// オーナー
	IObject* owner_ = nullptr;

	// シェイプと構造体を繋ぐID
	int nextID_ = 0;

	// コリジョンシェイプ
	std::map<int, std::unique_ptr<CollisionShape>> shapeMap_;
	std::map<int, CollisionShape*> shapes_;

	// インデックス
	uint32_t index_ = 0;
};

