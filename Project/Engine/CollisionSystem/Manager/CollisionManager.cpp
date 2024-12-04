#include "CollisionManager.h"
#include "GameObject/IObject/IObject.h"


// ファクトリマップを作る関数
//std::unordered_map<std::type_index, ShapeFactory> CreateShapeFactoryMap() {
//	return {
//		{ typeid(Col::Sphere), [](CollisionComponent* self, Col::ColData* data) {
//			return std::make_unique<CollisionShapeSphere>(self, static_cast<Col::Sphere*>(data)); }},
//		{ typeid(Col::AABB), [](CollisionComponent* self, Col::ColData* data) {
//			return std::make_unique<CollisionShapeAABB>(self, static_cast<Col::AABB*>(data)); }},
//			/* 他の型も同様に追加 */
//	};
//}
//std::unordered_map<std::type_index, ShapeFactory> CreateColliderFactoryMap() {
//	return {
//		{ typeid(Collider::Sphere), [](IObject* owner) {
//			return std::make_unique<SphereCollider>(owner); }},
//			/* 他の型も同様に追加 */
//	};
//}



// 解放処理
void CollisionManager::Finalize()
{
}


// コライダー登録
void CollisionManager::Register(ICollider* collider)
{
	this->pColliders_.push_back(collider);
}

void CollisionManager::Register(Collider::ColliderData* data, IObject* owner)
{
	
}


// 更新処理
void CollisionManager::Update()
{
	// データの更新
	UpdateCollisionData();

	// コリジョン判定を行う
	CheckCollisions();


#ifdef _DEBUG
	DrawImGui(); // Debug表示
#endif // _DEBUG
}


// コリジョン判定を行う
void CollisionManager::CheckCollisions()
{
	//for (auto itr1 = shapeMap_.begin(); itr1 != shapeMap_.end(); ++itr1) {
	//	for (auto itr2 = std::next(itr1); itr2 != shapeMap_.end(); ++itr2) {

	//		// itr1とit2の属性が同じなら判定をスキップする
	//		if (itr1->second->GetAttribute() == itr2->second->GetAttribute()) {
	//			continue;
	//		}

	//		// 衝突を検出する
	//		if (itr1->second->Intersects(*itr2->second)) {
	//			itr1->second->OnCollision(*itr2->second, itr2->second->GetData());
	//			itr2->second->OnCollision(*itr1->second, itr1->second->GetData());
	//		}

	//		auto shape1 = itr1->second->GetData();
	//		auto shape2 = itr2->second->GetData();

	//		/*if (Detect::Intersects(shape1, shape2)) {

	//		}*/
	//	}
	//}
}

//
//// データの更新
//void CollisionManager::UpdateCollisionData()
//{
//	for (auto& element : shapeMap_) {
//		element.second->SetData(*element.first);
//	}
//}


// ImGuiの描画
void CollisionManager::DrawImGui()
{
	if (ImGui::TreeNode("CollisionManager")) {

		/*ImGui::Text("Collider Count = %d", shapeMap_.size());
		
		for (auto& element : shapeMap_) {
			element.second->DrawImGui();
		}*/

		ImGui::Text("Collider Ptr Count = %d", pColliders_.size());
		for (auto& element : pColliders_) {
			element->DrawImGui();
		}
		ImGui::Text("");

		ImGui::TreePop();
	}
}


// Shapeのインスタンスの取得
//const std::unordered_map<std::type_index, ShapeFactory>& CollisionManager::GetFactoryMap()
//{
//	static const std::unordered_map<std::type_index, ShapeFactory> factoryMap 
//		= CreateShapeFactoryMap();
//	return factoryMap;
//}
//
//const std::unordered_map<std::type_index, ColliderFactory>& CollisionManager::GetColliderFactoryMap()
//{
//	// TODO: return ステートメントをここに挿入します
//}
