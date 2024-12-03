#include "Floor.h"



// 初期化処理
void Floor::Init()
{
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/Floor", "Floor.obj");
	model_ = modelManager_->GetModel("Floor");

	trans_.Init();
}


// 更新処理
void Floor::Update()
{

#ifdef _DEBUG

	/*if (ImGui::TreeNode("Ground")) {
		ImGui::TreePop();
	}*/

#endif // _DEBUG
}


// 描画処理
void Floor::Draw3D()
{
	model_->DrawN(trans_);
}

void Floor::Draw2DFront()
{
}

void Floor::Draw2DBack()
{
}


// 衝突判定コールバック関数
void Floor::onCollision([[maybe_unused]] IObject* object)
{
}

