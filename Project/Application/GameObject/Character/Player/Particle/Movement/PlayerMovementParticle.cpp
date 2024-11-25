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

	// 補間に使用するAlpha値の設定。不透明->透明
	scale_.first = 0.7f;
	scale_.second = -0.01f;

	// 速度
	velocity_ = 0.07f;

	// Timerの初期化&スタート。(1秒)
	timer_.Init(0.0f, 1.0f * 60.0f);
	timer_.Start();
}


/// <summary>
/// 更新処理
/// </summary>
void PlayerMovementParticle::Update()
{
	// タイマーの更新
	timer_.Update();
	// タイマー終了で死亡フラグを立てる
	if (timer_.IsFinish()) {
		isDead_ = true;
	}

	// 軽く上に移動する
	trans_.srt.translate.y += velocity_;

	// Alpha値の計算
	CalcScale();
}


/// <summary>
/// 描画処理
/// </summary>
void PlayerMovementParticle::Draw3D()
{
	model_->SetColor(color_);
	model_->DrawN(trans_);
}


/// <summary>
/// Scale値の計算
/// </summary>
void PlayerMovementParticle::CalcScale()
{
	trans_.srt.scale.x =
		Interpolate(scale_.first, scale_.second, timer_.GetRatio(), Ease::OutSine);
	trans_.srt.scale.y =
		Interpolate(scale_.first, scale_.second, timer_.GetRatio(), Ease::OutSine);
	trans_.srt.scale.z =
		Interpolate(scale_.first, scale_.second, timer_.GetRatio(), Ease::OutSine);
}

