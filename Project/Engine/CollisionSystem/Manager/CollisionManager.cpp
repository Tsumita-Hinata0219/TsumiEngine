#include "CollisionManager.h"
#include "../Component/CollisionComponent.h"
#include "../Shape/CollisionShape.h"
#include "../Shape/Sphere/CollisionShapeSphere.h"
#include "../Shape/AABB/CollisionShapeAABB.h"


// ファクトリマップを作る関数
std::unordered_map<std::type_index, ShapeFactory> CreateShapeFactoryMap() {
	return {
		{ typeid(Col::Sphere), [](CollisionComponent* self, Col::ColData* data) {
			return std::make_unique<CollisionShapeSphere>(self, static_cast<Col::Sphere*>(data)); }},
		{ typeid(Col::AABB), [](CollisionComponent* self, Col::ColData* data) {
			return std::make_unique<CollisionShapeAABB>(self, static_cast<Col::AABB*>(data)); }},
			/* 他の型も同様に追加 */
	};
}


// 解放処理
void CollisionManager::Finalize()
{
}


// コライダーの登録
void CollisionManager::Register(uint32_t attribute, Col::ColData* data, CollisionComponent* component)
{
	// データの型に基づいてシェイプを生成する
	const auto& factoryMap = GetFactoryMap();
	auto it = factoryMap.find(typeid(*data));


	if (it != factoryMap.end()) {

		// std::unique_ptr でシェイプを生成
		std::unique_ptr<CollisionShape> shape = it->second(component, data);

		// コンポーネントに登録されている属性を設定する
		shape->SetAttribute(attribute);

		// シェイプのBoundingと空間レベルを求める
		shape->CalcBounding();
		shape->CalcSpaceLevel();

		// マップに保存
		this->shapeMap_[data] = std::move(shape);
	}
	else {
		std::cerr << "Error : Unsupported collision shape type." << std::endl;
	}
}


// 登録されているShapeを削除する
void CollisionManager::UnRegister(Col::ColData* data)
{
	// nullptrか指定されたポインタをキーとする要素が存在するか確認
	auto it = shapeMap_.find(data);
	if (it != shapeMap_.end()) {
		// 存在する場合はその要素を削除
		shapeMap_.erase(it);
	}
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
	for (auto itr1 = shapeMap_.begin(); itr1 != shapeMap_.end(); ++itr1) {
		for (auto itr2 = std::next(itr1); itr2 != shapeMap_.end(); ++itr2) {

			// itr1とit2の属性が同じなら判定をスキップする
			if (itr1->second->GetAttribute() == itr2->second->GetAttribute()) {
				continue;
			}

			// 衝突を検出する
			if (itr1->second->Intersects(*itr2->second)) {
				itr1->second->OnCollision(*itr2->second, itr2->second->GetData());
				itr2->second->OnCollision(*itr1->second, itr1->second->GetData());
			}

			auto shape1 = itr1->second->GetData();
			auto shape2 = itr2->second->GetData();

			/*if (Detect::Intersects(shape1, shape2)) {

			}*/
		}
	}
}


// データの更新
void CollisionManager::UpdateCollisionData()
{
	for (auto& element : shapeMap_) {
		element.second->SetData(*element.first);
	}
}


// ImGuiの描画
void CollisionManager::DrawImGui()
{
	if (ImGui::TreeNode("CollisionManager")) {

		ImGui::Text("Collider Count = %d", shapeMap_.size());
		
		for (auto& element : shapeMap_) {
			element.second->DrawImGui();
		}

		ImGui::TreePop();
	}
}


// Shapeのインスタンスの取得
const std::unordered_map<std::type_index, ShapeFactory>& CollisionManager::GetFactoryMap()
{
	static const std::unordered_map<std::type_index, ShapeFactory> factoryMap 
		= CreateShapeFactoryMap();
	return factoryMap;
}

