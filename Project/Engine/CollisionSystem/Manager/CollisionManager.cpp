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
void CollisionManager::Register(ICollider* pCollider)
{
	pColliders_.push_back(pCollider);
}


/// <summary>
/// 登録されているShapeを削除する
/// </summary>
void CollisionManager::UnRegister(Collider::ColliderData* data)
{
	data;
}


/// <summary>
/// 更新処理
/// </summary>
void CollisionManager::Update()
{
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
	for (auto itr1 = pColliders_.begin(); itr1 != pColliders_.end(); ++itr1) {
		for (auto itr2 = std::next(itr1); itr2 != pColliders_.end(); ++itr2) {

			// itr1とit2の属性が同じなら判定をスキップする
			if ((*itr1)->GetAttribute() == (*itr2)->GetAttribute()) {
				continue;
			}

			// 衝突判定をとる
			if ((*itr1)->Intersects((**itr2))) {
				
			}
		}
	}
}


/// <summary>
/// ImGuiの描画
/// </summary>
void CollisionManager::DrawImGui()
{
	if (ImGui::TreeNode("CollisionManager")) {

		ImGui::Text("Collider Instance Count = %d", pColliders_.size());

		for (auto& element : pColliders_) {
			element->DrawImGui();
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