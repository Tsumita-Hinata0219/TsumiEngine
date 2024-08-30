#include "PlayerLeftBody.h"



// 初期化処理
void PlayerLeftBody::Init()
{
	// Modelの設定
	modelManager_ = ModelManager::GetInstance();
	model_ = modelManager_->GetModel("Player_Left_Body");

	// Transformの初期化
	trans_.Init();

	// ライトの初期設定
	light_.enable = true;
	light_.direction = Vector3::one;
}


// 更新処理
void PlayerLeftBody::Update() {}


// 描画処理
void PlayerLeftBody::Draw3D()
{
	model_->SetLightData(light_);
	model_->DrawN(trans_);
}
void PlayerLeftBody::Draw2DFront() {}
void PlayerLeftBody::Draw2DBack() {}
