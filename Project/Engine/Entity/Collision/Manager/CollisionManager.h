#pragma once

#include "../Collider/IEntityCollider.h"
#include "../Collider/CollisionSphere.h"
#include "../Collider/CollisionAABB.h"


namespace Entity{
namespace Collision{


/* EnityのColliderを管理するクラス */
class CollisionManager {

private:

	std::list<std::weak_ptr<IEntityCollider>> colliders_;

private:

	// シングルトン
	CollisionManager() = default;
	~CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	const CollisionManager& operator=(const CollisionManager&) = delete;

public:

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	static CollisionManager* GetInstance() {
		static CollisionManager instance;
		return &instance;
	}

	/// <summary>
	/// Listに登録
	/// </summary>
	void Register(const std::weak_ptr<IEntityCollider>& col) {
		colliders_.push_back(col);
	
	}

	/// <summary>
	/// 衝突判定をとる
	/// </summary>
	void DetectAll() {
		for (auto itA = colliders_.begin(); itA != colliders_.end(); ++itA) {
			auto colliderA = itA->lock();
			if (!colliderA) continue;

			// itrAの一つ次がitrB
			auto& itB = itA;
			++itB;

			for (; itB != colliders_.end(); ++itB) {
				auto colliderB = itB->lock();
				if (!colliderB) continue;

				// 判定
				if (colliderA->Intersects(*colliderB)) {
					int a = 0;
					a;
				}
			}
		}
	}


	void DrawimGui() {
		if (ImGui::TreeNode("Entity Collision Manager")) {

			size_t colCount = colliders_.size();
			ImGui::Text("Collider Count = %d", int(colCount));


			ImGui::TreePop();
		}
	}


private:

};
}
}