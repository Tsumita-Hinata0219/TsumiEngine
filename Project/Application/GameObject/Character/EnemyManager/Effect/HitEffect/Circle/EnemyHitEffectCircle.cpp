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

	// 初期カラーは白
	color_ = Samp::Color::WHITE;

	// 補間に使用するScaleの値
	scale_.first = 1.0f;
	scale_.second = 2.0f;

	// 補間に使用するAlpha値の設定。不透明->透明
	alpha_.first = 1.0f;
	alpha_.second = 0.0f;

}


/// <summary>
/// 更新処理
/// </summary>
void EnemyHitEffectCircle::Update()
{
	// タイマー更新
	timer_.Update();
	// タイマー終了で死亡フラグを立てる
	if (timer_.IsFinish()) {
		isDead_ = true;
	}

	// Scaleの計算
	CalcScale();

	// Alphaの計算
	CalcAlpha();
}


/// <summary>
/// 描画処理
/// </summary>
void EnemyHitEffectCircle::Draw3D()
{
	model_->SetColor(color_);
	model_->DrawN(trans_);
}


/// <summary>
/// Scaleの計算
/// </summary>
void EnemyHitEffectCircle::CalcScale()
{
	trans_.srt.scale.x =
		Interpolate(scale_.first, scale_.second, timer_.GetRatio(), Ease::OutSine);
	trans_.srt.scale.y =
		Interpolate(scale_.first, scale_.second, timer_.GetRatio(), Ease::OutSine);
	trans_.srt.scale.z =
		Interpolate(scale_.first, scale_.second, timer_.GetRatio(), Ease::OutSine);
}


/// <summary>
/// Alphaの計算
/// </summary>
void EnemyHitEffectCircle::CalcAlpha()
{
	color_.w =
		Interpolate(alpha_.first, alpha_.second, timer_.GetRatio(), Ease::InSine);
}

