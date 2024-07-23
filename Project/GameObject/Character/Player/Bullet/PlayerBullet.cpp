#include "PlayerBullet.h"



// 初期化処理
void PlayerBullet::Init()
{
	// BodyModelのロードと初期化
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("ball", "ball.obj");
	model_ = modelManager_->GetModel("ball");

	// Transformの初期化。座標や姿勢の設定は呼び出し先でaccessorで設定
	trans_.Initialize();

	// 速度の設定。呼び出し先でaccessorで設定

	// 寿命のタイマーをスタート。2秒で設定
	life_.Start(0.0f, 2.0f * 60.0f);
}


// 更新処理
void PlayerBullet::Update()
{
	// Transformの更新処理
	trans_.UpdateMatrix();

	// 移動処理
	Move();

	// 寿命の処理
	RemoveAfterlifeTime();
}


// 描画処理
void PlayerBullet::Draw3D()
{
	model_->DrawN(trans_);
}
void PlayerBullet::Draw2DFront() {}
void PlayerBullet::Draw2DBack() {}


// 衝突自コールバック関数
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