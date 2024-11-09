#include "CollisionComponent.h"
#include "../Manager/CollisionManager.h"
#include "../Shape/CollisionShape.h"
#include "../Shape/Sphere/CollisionShapeSphere.h"
#include "../Shape/AABB/CollisionShapeAABB.h"


// コンストラクタ
CollisionComponent::CollisionComponent()
{
	// インデックスの初期化
	index_ = 0;
}


// パラメータ付きコンストラクタ
CollisionComponent::CollisionComponent(IObject* setObject)
{
	this->owner_ = setObject;
}


// シェイプの追加
//void CollisionComponent::RegisterCollider(Col::Sphere& sphere)
//{
//	this->nextID_++; // IDの加算
//	sphere.id = this->nextID_; // IDの設定
//
//	// 新しくシェイプを作成
//	std::unique_ptr<CollisionShapeSphere> shape =
//		std::make_unique<CollisionShapeSphere>(this, &sphere);
//
//	// Boundingの計算も求める
//	shape->CalcBounding();
//
//	// コライダーの空間レベルと所属空間を求める
//	shape->CalcSpaceLevel();
//
//	// シェイプコンテナに作ったシェイプを追加
//	this->shapeMap_[sphere.id] = std::move(shape);
//}

void CollisionComponent::Register(Col::ColData& colData)
{
	this->nextID_++; // IDの加算
	colData.id = this->nextID_; // IDの設定

	// マネージャーにポインタを渡す
	CollisionManager::GetInstance()->Register(attribute_, &colData, this);
}


// シェイプの更新
//void CollisionComponent::UpdateShape(const Col::Sphere& sphere)
//{
//	auto it = this->shapeMap_.find(sphere.id);
//
//	// IDが存在する場合
//	if (it != this->shapeMap_.end()) {
//
//		it->second->SetData(sphere);  // データ更新
//		it->second->CalcBounding();   // Bounding更新
//		it->second->CalcSpaceLevel(); // 八分木更新
//	}
//	else {
//		// IDが存在しない場合はエラー処理
//		Log("Error: Shape with ID :  not found.\n");
//		// 例外を投げる場合
//		throw std::runtime_error("Shape ID not found.");
//	}
//}
//
//void CollisionComponent::Update(const Col::ColData& colData)
//{
//	//auto it = this->shapes_.find(colData.id);
//
//	//// IDが存在する場合、データの更新
//	//if (it != this->shapes_.end()) {
//	//	it->second->SetData(colData); // データ更新
//	//	it->second->CalcBounding();	  // Bounding更新
//	//	it->second->CalcSpaceLevel(); // 八分木更新
//	//}
//	//else {
//	//	// IDが存在しない場合はエラー処理
//	//	Log("Error: Shape with ID :  not found.\n");
//	//	// 例外を投げる場合
//	//	throw std::runtime_error("Shape ID not found.");
//	//}
//}


// コリジョンのチェック
//bool CollisionComponent::CheckCollision(const CollisionComponent& other) const
//{
//	for (const auto& shapeA : shapeMap_) {
//		for (const auto& shapeB : other.shapeMap_) {
//			if (shapeA.second->Intersects(*shapeB.second)) {
//				return true; // 衝突が検出された
//			}
//		}
//	}
//	return false; // 衝突なし
//}
