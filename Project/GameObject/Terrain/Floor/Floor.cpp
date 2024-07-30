#include "Floor.h"



// 初期化処理
void Floor::Init()
{
	modelManager_ = ModelManager::GetInstance();
	model_ = modelManager_->GetModel("Floor");

	trans_.Initialize();
	trans_.srt.scale = { 500.0f, 1.0f, 500.0f };
	trans_.srt.translate.y = -10.0f;
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

