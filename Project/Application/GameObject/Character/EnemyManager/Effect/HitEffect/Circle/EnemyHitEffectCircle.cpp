#include "EnemyHitEffectCircle.h"
#include "../../../Enemy/IEnemy.h"


/// <summary>
/// 初期化処理
/// </summary>
void EnemyHitEffectCircle::Init()
{
	// モデルの設定
	modelManager_->LoadModel("Obj/Enemys/Effect/HitCircle", "HitCircle.obj");
	model_ = modelManager_->GetModel("HitCircle");

	// トランスフォームの初期化
	trans_.Init();
	// 座標は親エネミーと同じ場所
	trans_.srt.translate = pEnemy_->GetTranslate();

	// 死亡フラグは折る
	isDead_ = false;

	// 初期カラーは白
	color_ = Samp::Color::WHITE;

	// 補間に使用するScaleの値
	scale_.first = 2.0f;
	scale_.second = 6.0f;

	// 補間に使用するAlpha値の設定。不透明->透明
	alpha_.first = 1.0f;
	alpha_.second = 0.0f;

	// タイマーの設定 (0.3秒)
	timer_.Init(0.0f, 0.5f * 60.0f);
	timer_.Start();
}


/// <summary>
/// 更新処理
/// </summary>
void EnemyHitEffectCircle::Update()
{
	// タイマー更新
	timer_.Update();
	// タイマー終了
	if (timer_.IsFinish()) {
		
		// 死亡フラグを立てる
		isDead_ = true;

	}

	// 座標は親エネミーと同じ場所
	trans_.srt.translate = pEnemy_->GetTranslate();

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

