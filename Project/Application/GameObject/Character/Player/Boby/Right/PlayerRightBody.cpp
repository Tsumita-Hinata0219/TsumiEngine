#include "PlayerRightBody.h"



// 初期化処理
void PlayerRightBody::Init()
{
	// Modelの設定
	modelManager_ = ModelManager::GetInstance();
	model_ = modelManager_->GetModel("Player_Right_Body");

	// Transformの初期化
	trans_.Init();

	// ライトの初期設定
	light_.enable = true;
	light_.direction = Vector3::one;
}


// 更新処理
void PlayerRightBody::Update() {}


// 描画処理
void PlayerRightBody::Draw3D()
{
	model_->SetLightData(light_);
	model_->DrawN(trans_);
}
void PlayerRightBody::Draw2DFront() {}
void PlayerRightBody::Draw2DBack() {}


// 衝突判定コールバック関数
void PlayerRightBody::onCollision([[maybe_unused]] IObject* object, [[maybe_unused]] Col::ColData colData)
{
}
