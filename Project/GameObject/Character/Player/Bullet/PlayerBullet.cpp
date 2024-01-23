#include "PlayerBullet.h"



// 初期化処理
void PlayerBullet::Initialize(Model& modelHD, Vector3 pos, Vector3 vel)
{
	// モデルの初期化
	model_ = make_unique<Model>();
	(*model_) = modelHD;

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translate = pos;

	// 加算速度
	velocity_ = Vector3::zero;

	// 移動量の設定
	move_ = vel;

	// サイズ
	this->size_ = 2.0f * worldTransform_.scale;

	// 寿命
	kLifeTimer_ = 60 * 5;;
	lifeTimer_ = kLifeTimer_;

	// コライダー
	OBBCollider::SetID(ObjectBit::PlayerBullet);
	OBBCollider::SetCollosionAttribute(ObjectFileter::Player);
	OBBCollider::SetCollisionMask(ObjectFileter::Player);
}


// 更新処理
void PlayerBullet::Update()
{
	// OBBの設定
	SettingOBBProperties();

	// 移動処理
	Move();

	// 寿命の処理
	UpdateLifeTimer();

	// ワールド座標の更新
	worldTransform_.UpdateMatrix();
}


// 描画処理
void PlayerBullet::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
}


// 衝突時コールバック関数
void PlayerBullet::OnCollision(uint32_t id)
{
	if (id == ObjectBit::Enemy) {
		isDead_ = true;
	}
	else if (id == ObjectBit::EnemyBullet) {
		isDead_ = true;
	}

}


// 移動処理
void PlayerBullet::Move()
{
	// 速度を常に加算
	velocity_ = move_;
	worldTransform_.translate += velocity_;
}


// OBBの設定
void PlayerBullet::SettingOBBProperties()
{
	OBBCollider::SetSize(this->size_);
	OBBCollider::SetRotate(this->worldTransform_.rotate);
}



// 寿命の処理
void PlayerBullet::UpdateLifeTimer()
{
	lifeTimer_--;

	if (lifeTimer_ <= 0.0f) {
		lifeTimer_ = 0;
		isDead_ = true;
	}
}