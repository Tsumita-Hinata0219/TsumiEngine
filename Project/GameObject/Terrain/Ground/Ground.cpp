#include "Ground.h"



// 初期化処理
void Ground::Init()
{
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/Ground", "Ground.obj");
	model_ = modelManager_->GetModel("Ground");

	trans_.Init();
	trans_.srt.scale = { 500.0f, 1.0f, 500.0f };
	trans_.srt.translate.y = -10.0f;
}


// 更新処理
void Ground::Update() 
{

#ifdef _DEBUG

	/*if (ImGui::TreeNode("Ground")) {
		ImGui::TreePop();
	}*/

#endif // _DEBUG
}


// 描画処理
void Ground::Draw3D()
{
	model_->DrawN(trans_);
}

void Ground::Draw2DFront()
{
}

void Ground::Draw2DBack()
{
}

