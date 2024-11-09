#include "PlayerBullet.h"
#include "../Player.h"


// 初期化処理
void PlayerBullet::Init()
{
	// BodyModelのロードと初期化
	modelManager_ = ModelManager::GetInstance();
	model_ = modelManager_->GetModel("PlayerBullet");

	// Transformの初期化。座標や姿勢の設定は呼び出し先でaccessorで設定
	trans_.Init();

	// 速度の設定。呼び出し先でaccessorで設定

	// 寿命のタイマーをスタート。2秒で設定
	life_.Init(0.0f, 2.0f * 60.0f);
	life_.Start();

	// 回転速度の設定
	addRotateZ_ = 1.0f;

	// ライトの初期設定
	light_.enable = true;
	light_.direction = Vector3::one;

	//// Colliderの初期化
	colComp_->SetAttribute(ColliderAttribute::Player);
	colComp_->Register(sphere_);
	sphere_.center = trans_.GetWorldPos();
	sphere_.radius = 2.0f;
}


// 更新処理
void PlayerBullet::Update()
{
	// Transformの更新処理
	trans_.UpdateMatrix();

	// 移動処理
	Move();

	// Z軸を回転させる
	ZRotate();

	// 寿命の処理
	RemoveAfterlifeTime();

	// ColliderのSRTの設定
	sphere_.center = trans_.GetWorldPos();
}


// 描画処理
void PlayerBullet::Draw3D()
{
	//model_->SetLightData(light_);
	model_->DrawN(trans_);
}
void PlayerBullet::Draw2DFront() {}
void PlayerBullet::Draw2DBack() {}


// 衝突自コールバック関数
void PlayerBullet::onCollision([[maybe_unused]] IObject* object)
{
	if (object->GetAttribute() == ObjAttribute::ENEMY) {
		isDead_ = true;
	}
}
void PlayerBullet::OnCollisionWithEnemy()
{
	isDead_ = true;
}
void PlayerBullet::OnCollisionWithEnemyBullet()
{
	isDead_ = true;
}

// 移動処理
void PlayerBullet::Move()
{
	trans_.srt.translate += velocity_;
}


// Z軸を回転させる
void PlayerBullet::ZRotate()
{
	trans_.srt.rotate.z += ToRadians(addRotateZ_);
}


// 寿命の処理
void PlayerBullet::RemoveAfterlifeTime()
{
	// 寿命の更新
	life_.Update();

	// タイマーが規定値になったら
	if (life_.IsFinish()) {

		// 死亡フラグを立てる
		isDead_ = true;

		// 寿命のタイマーをクリアしとく
		life_.Clear();
	}
}