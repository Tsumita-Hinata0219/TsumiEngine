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
void CollisionManager::Register(uint32_t attribute, CollisionShape* shape)
{
	//shapes_.push_back(shape);
	shapes_[attribute].push_back(shape);
}


// 登録されているShapeを削除する
void CollisionManager::UnRegister(CollisionShape* shape)
{
	//shapes_.erase(std::remove(shapes_.begin(), shapes_.end(), shape), shapes_.end());
	// 各属性のリストをループ
	for (auto& pair : shapes_) {
		// 属性に関連するShapeのリストをループ
		auto& shapeList = pair.second;
		shapeList.remove_if([](CollisionShape* shape) {
			return shape == nullptr; // nullptrを削除
			});
	}
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
	/*shapes_.erase(
		std::remove_if(shapes_.begin(), shapes_.end(),
			[](CollisionShape* ptr) {return ptr == nullptr; }),
		shapes_.end());*/
}


// ImGuiの描画
void CollisionManager::DrawImGui()
{
	if (ImGui::TreeNode("CollisionManager")) {
		// 各属性のリストをループ
		for (const auto& pair : shapes_) {
			// 属性を文字列に変換
			std::string attributeName = "Attribute: " + std::to_string(pair.first);

			// 属性ごとにツリーを作成
			if (ImGui::TreeNode(attributeName.c_str())) { // 文字列をc_str()に変換して渡す
				// その属性に関連するShapeをループ
				for (const auto& shape : pair.second) {
					shape->DrawImGui(); // 各ShapeのImGui描画メソッドを呼び出す
				}
				ImGui::TreePop(); // ツリーを閉じる
			}
		}
		ImGui::TreePop();
	}
}

