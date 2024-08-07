#include "CollisionSystem.h"



// コンポーネント追加
void CollisionSystem::AAddComponent(CollisionComponent* component)
{
	components_.push_back(component);
}


// コリジョン判定を実行
void CollisionSystem::Update()
{
	this->CheckCollisions();
}


// コリジョン判定を行う
void CollisionSystem::CheckCollisions()
{
	// O(n^2)衝突判定
	size_t count = components_.size();

	for (size_t i = 0; i < count; ++i) {
		for (size_t j = i + 1; j < count; ++j) {

			CollisionComponent* comp1 = components_[i];
			CollisionComponent* comp2 = components_[j];

			// コリジョンが存在するか確認
			if (comp1->GetShape() && comp2->GetShape()) {
				if (comp1->GetShape()->Intersects(*comp2->GetShape())) {

					// 現段階の実装
					CollisionEvent event(comp1, comp2);
					ColEventManager::GetInstance()->Dispatch(event);

					// ここで衝突が検出された場合の処理
					// コンポーネントにIObjectを持たせてOnCollision()を返すのもいいかも
					// comp1->GetObject()->OnCollision(comp2->GetObject());
					// comp2->GetObject()->OnCollision(comp1->GetObject());
					// それぞれにそれぞれの持つオブジェクト情報を返す感じ
				}
			}
		}
	}

}
