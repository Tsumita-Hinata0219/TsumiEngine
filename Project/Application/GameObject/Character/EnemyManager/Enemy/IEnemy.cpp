#include "IEnemy.h"
#include "../../EnemyManager/EnemyManager.h"


/// <summary>
/// Bulletを新しく追加
/// </summary>
void IEnemy::AddNewBullet(EnemyBulletType setType, const Vector3& initPos, const Vector3& initVel)
{
	enemyManager_->AddNewBullet(setType, initPos, initVel);
}


/// <summary>
/// ヒットリアクション
/// </summary>
void IEnemy::HitReaction()
{
	// フラグが折れていたら早期return
	if (!isHitReactioning_) { return; }

	// タイマー更新
	hitReactionTimer_.Update();
	// タイマー終了
	if (hitReactionTimer_.IsFinish()) {
		// リセット
		hitReactionTimer_.Reset();
		// リアクション中のフラグを折る
		isHitReactioning_ = false;
	}

	// スケール
	HitReaction_Scale();
	// カラー
	HitReaction_Color();
}


/// <summary>
/// スケールのリアクション
/// </summary>
void IEnemy::HitReaction_Scale()
{
	trans_.srt.scale.x =
		InterpolateWithPeak(hitReactionScale_.x, hitReactionScale_.y, hitReactionScale_.z, hitReactionTimer_.GetRatio(), Ease::WithPeak);
	trans_.srt.scale.y =
		InterpolateWithPeak(hitReactionScale_.x, hitReactionScale_.y, hitReactionScale_.z, hitReactionTimer_.GetRatio(), Ease::WithPeak);
	trans_.srt.scale.z =
		InterpolateWithPeak(hitReactionScale_.x, hitReactionScale_.y, hitReactionScale_.z, hitReactionTimer_.GetRatio(), Ease::WithPeak);
}


/// <summary>
/// 色のアクション
/// </summary>
void IEnemy::HitReaction_Color()
{
	colorAdd_.intensity =
		Interpolate(hitReactionColor_.first, hitReactionColor_.second, hitReactionTimer_.GetRatio(), Ease::OutQuint);
}
