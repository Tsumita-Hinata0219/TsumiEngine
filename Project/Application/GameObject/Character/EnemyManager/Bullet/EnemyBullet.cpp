#include "EnemyBullet.h"



// 初期化処理
void EnemyBullet::Init()
{
	// BodyModelのロードと初期化
	// 設定されているTypeで読み込むモデルを変える
	if (bulletType_ == EnemyBulletType::Normal) {
		modelManager_->LoadModel("Obj/EnemyBullet/Normal", "EnemyBullet_Normal.obj");
		model_ = modelManager_->GetModel("EnemyBullet_Normal");
	}
	else if (bulletType_ == EnemyBulletType::Resistant) {
		modelManager_->LoadModel("Obj/EnemyBullet/Resistant", "EnemyBullet_Resistant.obj");
		model_ = modelManager_->GetModel("EnemyBullet_Resistant");
	}

	// Transformの初期化。座標や姿勢の設定は呼び出し先でaccessorで設定
	trans_.Init();

	// 速度の設定。呼び出し先でaccessorで設定

	// 寿命のタイマーをスタート。10秒で設定
	life_.Init(0.0f, 3.0f * 60.0f);
	life_.Start();

	// Colliderの初期化
	/*sphere_ = std::make_unique<SphereCollider>(this);
	sphere_->data_.center = trans_.GetWorldPos();
	sphere_->data_.radius = 2.0f;*/

	// 死亡フラグは折っておく
	isDead_ = false;
}


// 更新処理
void EnemyBullet::Update()
{
	// Transformの更新処理
	trans_.UpdateMatrix();

	// 移動処理
	Move();

	// 寿命の処理
	RemoveAfterlifeTime();

	// ColliderのSRTの設定
	//sphere_->data_.center = trans_.GetWorldPos();

}


// 描画処理
void EnemyBullet::Draw3D()
{
	model_->DrawN(trans_);
}
void EnemyBullet::Draw2DFront() {}
void EnemyBullet::Draw2DBack() {}


// 衝突時コールバック関数
void EnemyBullet::onCollision([[maybe_unused]] IObject* object)
{
	if (object->GetCategory() == Attributes::Category::PLAYER) {

		// タイプが消えない弾ならreturn
		if (bulletType_ == EnemyBulletType::Resistant) { return; }
		// 死亡状態に設定
		MarkAsDead();
	}
	else if (object->GetCategory() == Attributes::Category::TERRAIN) {

		// 衝突相手が地形ならタイプ構わずフラグを立てる
		// 死亡状態に設定
		MarkAsDead();
	}
}


// 移動処理
void EnemyBullet::Move()
{
	trans_.srt.translate += velocity_;
}


// 寿命の処理
void EnemyBullet::RemoveAfterlifeTime()
{
	// 寿命の更新
	life_.Update();

	// タイマーが規定値になったら
	if (life_.IsFinish()) {

		// 死亡状態に設定
		MarkAsDead();
		// 寿命のタイマーをクリアしとく
		life_.Clear();
	}
}


// マークを死亡状態に設定
void EnemyBullet::MarkAsDead()
{
	// 死亡フラグを立てる
	isDead_ = true;
	// コライダーを無効化
	sphere_->Deactivate();
}
