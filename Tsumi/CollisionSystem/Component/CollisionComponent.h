#pragma once

#include "../../Project/Math/MyMath.h"
#include "../Shape/CollisionShape.h"
#include "../Shape/Sphere/CollisionShapeSphere.h"
#include "../Shape/AABB/CollisionShapeAABB.h"


#include <memory>
#include <vector>
#include <typeindex>


// IObjectの前方宣言
class IObject;

// ファクトリ関数
using ShapeFactory = std::function<std::unique_ptr<CollisionShape>(CollisionComponent*, Col::ColData*)>;


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

	// コリジョンのチェック
	bool CheckCollision(const CollisionComponent& other) const;


#pragma region Accessor

	// IObject
	IObject* GetOwner() const { return this->owner_; }

#pragma endregion 


private:


	static const std::unordered_map<std::type_index, ShapeFactory>& GetFactoryMap();


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

