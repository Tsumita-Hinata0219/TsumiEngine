#include "CollisionManager.h"
#include "GameObject/IObject/IObject.h"


/// <summary>
/// ファクトリマップを作る関数
/// </summary>
static std::unordered_map<std::type_index, ColliderFactory> CreateColliderFactoryMap() {
	return {
		{ typeid(Collider::Sphere), [](IObject* owner) {
			return std::make_unique<SphereCollider>(owner); }
		},

			/* 他の型も同様に追加 */
	};
}


/// <summary>
/// コライダー登録
/// </summary>
void CollisionManager::Register(Collider::ColliderData* data, IObject* owner)
{
	// データの火tらに基づいてコライダーを作る
	const auto& factoryMap = GetColliderFactoryMap();
	auto it = factoryMap.find(typeid(*data));

	if (it != factoryMap.end()) {

		// ユニークポインタでコライダーを作成
		std::unique_ptr<ICollider> newCollider = it->second(owner);

		// マップに追加
		pColliderMap_[data] = std::move(newCollider);
	}
	else {
		std::cerr << "Error : Unsupported collision collider type." << std::endl;
	}
}


/// <summary>
/// 登録されているShapeを削除する
/// </summary>
void CollisionManager::UnRegister(Collider::ColliderData* data)
{
	// ポインタが存在するか確認
	auto it = pColliderMap_.find(data);
	// 存在するならその要素を削除
	if (it != pColliderMap_.end()) {
		pColliderMap_.erase(it);
	}
}


/// <summary>
/// 更新処理
/// </summary>
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


/// <summary>
/// コリジョン判定を行う
/// </summary>
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


/// <summary>
/// データの更新
/// </summary>
void CollisionManager::UpdateCollisionData()
{
	for (auto& element : pColliderMap_) {
		element.second->SetData(*element.first);
	}
}


/// <summary>
/// ImGuiの描画
/// </summary>
void CollisionManager::DrawImGui()
{
	if (ImGui::TreeNode("CollisionManager")) {

		ImGui::Text("Collider Instance Count = %d", pColliderMap_.size());

		for (auto& element : pColliderMap_) {
			element.second->DrawImGui();
		}

		ImGui::TreePop();
	}
}


/// <summary>
/// Colliderのインスタンスの取得
/// </summary>

const std::unordered_map<std::type_index, ColliderFactory>& CollisionManager::GetColliderFactoryMap()
{
	static const std::unordered_map<std::type_index, ColliderFactory> factoryMap =
		CreateColliderFactoryMap();
	return factoryMap;
}