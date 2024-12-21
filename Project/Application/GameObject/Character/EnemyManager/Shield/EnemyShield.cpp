#include "EnemyShield.h"



/// <summary>
/// 初期化処理
/// </summary>
void EnemyShield::Init()
{
	// BodyModelのロードと初期化
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/Enemys/Boss", "Boss.obj");
	model_ = modelManager_->GetModel("Boss");

	// BodyTransfromの初期化
	trans_.Init();

	// Colliderの初期化
	sphere_ = std::make_unique<SphereCollider>(this);
	sphere_->data_.center = trans_.GetWorldPos();
	sphere_->data_.radius = 1.8f;

}


/// <summary>
/// 更新処理
/// </summary>
void EnemyShield::Update()
{
	sphere_->data_.center = trans_.GetWorldPos();
}


/// <summary>
/// 更新処理
/// </summary>
void EnemyShield::Draw3D()
{
	// BodyModelの描画
	model_->Draw(trans_);
}
void EnemyShield::Draw2DFront()
{
}
void EnemyShield::Draw2DBack()
{
}


/// <summary>
/// 衝突判定コールバック関数
/// </summary>
void EnemyShield::onCollision([[maybe_unused]]IObject* object)
{
}
