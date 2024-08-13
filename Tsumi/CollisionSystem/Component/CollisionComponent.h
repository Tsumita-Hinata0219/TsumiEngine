#pragma once

#include "../../Project/Math/MyMath.h"
#include "../Shape/CollisionShape.h"
#include "../Shape/Sphere/CollisionShapeSphere.h"
#include "../Shape/AABB/CollisionShapeAABB.h"


#include <memory>
#include <vector>


// IObjectの前方宣言
class IObject;

//template <typename T>

/* コリジョンシェイプを保持するクラス */
class CollisionComponent {

public:

	// コンストラクタ、デストラクタ
	CollisionComponent() {};
	~CollisionComponent() {};

	// パラメータ付きコンストラクタ
	CollisionComponent(IObject* setObject) {
		this->owner_ = setObject;
	}

	// シェイプの追加
	void RegisterCollider(Col::Sphere& sphere) {
		this->nextID_++;
		sphere.id = this->nextID_;
		std::unique_ptr<CollisionShapeSphere> shape = std::make_unique<CollisionShapeSphere>(sphere);
		this->shapeMap_[sphere.id] = std::move(shape);
	}

	// シェイプの更新
	void UpdateShape(const Col::Sphere& sphere) {
		auto it = this->shapeMap_.find(sphere.id);
		if (it != this->shapeMap_.end()) {
			// IDが存在する場合はデータを更新
			it->second->SetData(sphere);
			// Boundingの値も更新しておく
			it->second->CalcBounding(); 
		}
		else {
			// IDが存在しない場合はエラー処理
			Log("Error: Shape with ID :  not found.\n");
			// 例外を投げる場合
			throw std::runtime_error("Shape ID not found.");
		}
	}

	// コリジョンのチェック
	bool CheckCollision(const CollisionComponent& other) const {
		for (const auto& shapeA : shapeMap_) {
			for (const auto& shapeB : other.shapeMap_) {
				if (shapeA.second->Intersects(*shapeB.second)) {
					return true; // コリジョンが検出された
				}
			}
		}
		return false; // コリジョンなし
	}


#pragma region Accessor

	// IObject
	IObject* GetOwner() const { return this->owner_; }


#pragma endregion 


private:

	// オーナー
	IObject* owner_ = nullptr;

	// シェイプと構造体を繋ぐID
	int nextID_ = 0;

	// コリジョンシェイプ
	std::map<int, std::unique_ptr<CollisionShape>> shapeMap_;
};

