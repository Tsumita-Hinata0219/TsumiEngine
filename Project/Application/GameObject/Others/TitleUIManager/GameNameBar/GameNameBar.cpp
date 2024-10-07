#include "GameNameBar.h"



// 初期化処理
void GameNameBar::Init()
{
	// Modelの設定
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/GameNameBar", "GameNameBar");
	model_ = modelManager_->GetModel("GameNameBar");

	// Transformの初期化
	trans_.Init();
	trans_.srt.translate = Vector3::zero;
	trans_.srt.translate.z = 5.0f;
}


// 更新処理
void GameNameBar::Update()
{

#ifdef _DEBUG

	if (ImGui::TreeNode("GameNameBar")) {

		trans_.DrawImGui();
		ImGui::TreePop();
	}

#endif // _DEBUG
}


// 描画処理
void GameNameBar::Draw3D()
{
	model_->DrawN(trans_);
}
void GameNameBar::Draw2DFront() {}
void GameNameBar::Draw2DBack() {}


// 衝突判定コールバック関数
void GameNameBar::onCollision([[maybe_unused]] IObject* object)
{
}
