#include "SelectBar.h"



// 初期化処理
void SelectBar::Init()
{
	// Modelの設定
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/SelectBar", "SelectBar.obj");
	model_ = modelManager_->GetModel("SelectBar");

	// Transformの初期化
	trans_.Init();
	trans_.srt.scale.x = 2.0f;
	trans_.srt.scale.y = 0.4f;
	trans_.srt.translate.z = 20.0f;
}


// 更新処理
void SelectBar::Update()
{

#ifdef _DEBUG

	if (ImGui::TreeNode("SelectBar")) {

		trans_.DrawImGui();
		ImGui::TreePop();
	}

#endif // _DEBUG
}


// 描画処理
void SelectBar::Draw3D()
{
	model_->DrawN(trans_);
}
void SelectBar::Draw2DFront() {}
void SelectBar::Draw2DBack() {}


// 衝突判定コールバック関数
void SelectBar::onCollision([[maybe_unused]] IObject* object)
{
}
