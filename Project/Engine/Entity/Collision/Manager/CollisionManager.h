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

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	CollisionManager() = default;

	/// <summary>
	/// デストラク
	/// </summary>
	~CollisionManager() = default;

	/// <summary>
	/// Listに登録
	/// </summary>
	void Register(const std::shared_ptr<IEntityCollider>& col) {
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


private:

};
}
}