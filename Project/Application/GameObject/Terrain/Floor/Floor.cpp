#include "Floor.h"



// 初期化処理
void Floor::Init()
{
	modelManager_ = ModelManager::GetInstance();
	model_ = modelManager_->GetModel("Floor");
	uint32_t ddsFile = TextureManager::LoadTexture("Texture", "uvChecker.dds");
	model_->SetMaterialTexture(ddsFile);

	trans_.Init();
	trans_.srt.translate.y = -2.0f;
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

