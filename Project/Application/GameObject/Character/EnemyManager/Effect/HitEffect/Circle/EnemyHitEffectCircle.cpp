#include "EnemyHitEffectCircle.h"



/// <summary>
/// 初期化処理
/// </summary>
void EnemyHitEffectCircle::Init()
{
	// モデルの設定


	// トランスフォームの初期化
	trans_.Init();


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

