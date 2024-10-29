#include "CollisionManager.h"
#include "../Component/CollisionComponent.h"
#include "../Shape/CollisionShape.h"
#include "../Collider/Segment/SegmentCollider.h"
#include "../Collider/Sphere/SphereCollider.h"
#include "../Collider/Box/AABBCollider.h"
#include "../Collider/Box/OBBCollider.h"
#include "../Collider/Segment/SegmentCollider.h"


// 解放処理
void CollisionManager::Finalize()
{
}


// コライダーの登録
void CollisionManager::Register(CollisionShape* shape)
{
	shapes_.push_back(shape);
}


// 登録されているShapeを削除する
void CollisionManager::UnRegister(CollisionShape* shape)
{
	shapes_.erase(std::remove(shapes_.begin(), shapes_.end(), shape), shapes_.end());
}


// 更新処理
void CollisionManager::Update()
{
	// 無効なポインタは削除
	//CheckAndCleanPointers();

	// コリジョン判定を行う
	CheckCollisions();

#ifdef _DEBUG
	DrawImGui(); // Debug表示
#endif // _DEBUG
}


// コリジョン判定を行う
void CollisionManager::CheckCollisions()
{

}


// 無効なポインタは削除
void CollisionManager::CheckAndCleanPointers()
{
	shapes_.erase(
		std::remove_if(shapes_.begin(), shapes_.end(),
			[](CollisionShape* ptr) {return ptr == nullptr; }),
		shapes_.end());
}


// ImGuiの描画
void CollisionManager::DrawImGui()
{
	if (ImGui::TreeNode("CollisionManager")) {
		
		for (auto& shape : shapes_) {
			shape->DrawImGui();
		}

		ImGui::TreePop();
	}
}

