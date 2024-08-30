#include "PlayerMainBody.h"



// 初期化処理
void PlayerMainBody::Init()
{
	// Modelの設定
	modelManager_ = ModelManager::GetInstance();
	model_ = modelManager_->GetModel("Player_Main_Body");

	// Transformの初期化
	trans_.Init();

	// ライトの初期設定
	light_.enable = true;
	light_.direction = Vector3::one;
}


// 更新処理
void PlayerMainBody::Update() {}


// 描画処理
void PlayerMainBody::Draw3D()
{
	model_->SetLightData(light_);
	model_->DrawN(trans_);
}
void PlayerMainBody::Draw2DFront() {}
void PlayerMainBody::Draw2DBack() {}
