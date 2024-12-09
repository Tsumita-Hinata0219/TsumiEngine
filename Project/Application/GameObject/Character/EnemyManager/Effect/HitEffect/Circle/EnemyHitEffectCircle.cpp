#include "EnemyHitEffectCircle.h"



/// <summary>
/// 初期化処理
/// </summary>
void EnemyHitEffectCircle::Init()
{
	// モデルの設定


	// トランスフォームの初期化
	trans_.Init();

	// タイマーの設定 (1秒)
	timer_.Init(0.0f, 1.0f * 60.0f);

	// 死亡フラグは折る
	isDead_ = false;

}


/// <summary>
/// 更新処理
/// </summary>
void EnemyHitEffectCircle::Update()
{
}


/// <summary>
/// 描画処理
/// </summary>
void EnemyHitEffectCircle::Draw3D()
{
	model_->DrawN(trans_);
}

