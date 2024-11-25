#include "PlayerMovementParticle.h"



/// <summary>
/// 初期化処理
/// </summary>
void PlayerMovementParticle::Init()
{
	// モデルの読み込み
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/MovementParticle1", "MovementParticle1.obj");
	model_ = modelManager_->GetModel("MovementParticle1");

	// トランスフォームの初期化
	trans_.Init();

}


/// <summary>
/// 更新処理
/// </summary>
void PlayerMovementParticle::Update()
{
}


/// <summary>
/// 描画処理
/// </summary>
void PlayerMovementParticle::Draw3D()
{
	model_->DrawN(trans_);
}

