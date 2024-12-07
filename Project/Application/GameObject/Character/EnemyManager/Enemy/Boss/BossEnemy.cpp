#include "BossEnemy.h"
#include "../../../Player/Player.h"
#include "../../EnemyManager.h"



/// <summary>
/// 初期化処理
/// </summary>
void BossEnemy::Init()
{
	// BodyModelのロードと初期化
	modelManager_->LoadModel("Obj/Enemys/Boss", "Boss.obj");
	model_ = modelManager_->GetModel("Boss");

	// ライトの初期設定
	light_.enable = true;
	light_.direction = Vector3::one;
	light_.intensity = 0.7f;
	model_->SetLightData(light_);

	// BodyTransformの初期化
	trans_.Init();

	// Colliderの初期化
	sphere_ = std::make_unique<SphereCollider>(this);
	sphere_->data_.center = trans_.GetWorldPos();
	sphere_->data_.radius = 2.0f;


}


/// <summary>
/// 更新処理
/// </summary>
void BossEnemy::Update()
{

	// ColliderのSRTの設定
	sphere_->data_.center = trans_.GetWorldPos();

}


/// <summary>
/// 描画処理
/// </summary>
void BossEnemy::Draw3D()
{
	// BodyModelの描画
	model_->SetColor(modelColor_);
	model_->DrawN(trans_);

	// Bulletsの描画
	for (std::shared_ptr<EnemyBullet> bullet : bulletList_) {
		bullet->Draw3D();
	}
}
void BossEnemy::Draw2DFront()
{
}
void BossEnemy::Draw2DBack()
{
}


/// <summary>
/// 衝突判定コールバック関数
/// </summary>
void BossEnemy::onCollision([[maybe_unused]] IObject* object)
{
	// 地形は押し出し
	if (object->GetCategory() == Attributes::Category::TERRAIN) {
		// 押し出しの処理
		trans_.srt.translate += Penetration::Execute(sphere_->GetData(), IObject::hitCollider_);
		trans_.UpdateMatrix();
	}
	if (object->GetCategory() == Attributes::Category::PLAYER &&
		object->GetType() == Attributes::Type::BULLET) {

		// HPを減らす
		hp_--;

		// HPが0以下なら死亡
		if (hp_ <= 0) {
			// 死亡状態に設定
			MarkAsDead();
			player_->AddKillCount();
		}
	}
}


/// <summary>
/// プールに返却前のリセット処理
/// </summary>
void BossEnemy::Reset()
{
	// コライダーを無効にしておく
	sphere_->Deactivate();
}


/// <summary>
/// 死亡状態に設定
/// </summary>
void BossEnemy::MarkAsDead()
{
	// 死亡フラグを立てる
	isDead_ = true;
}
