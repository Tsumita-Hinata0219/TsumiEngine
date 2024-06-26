#include "PlayerBullet.h"



// 初期化処理
void PlayerBullet::Initialize(Model& modelHD)
{
	// Modelの初期化
	bulletModel_ = std::make_unique<Model>();
	//(*bulletModel_) = modelHD;
	modelHD;
	

	// Transformの初期化。座標や姿勢の設定はPlayer側でaccessorで設定
	bulletWt_.Initialize();

	// 速度の設定。Player側でaccessorで設定

	// 寿命のタイマーをスタート。2秒で設定
	life_.Start(0.0f, 2.0f * 60.0f);
}


// 更新処理
void PlayerBullet::Update()
{
	// Transformの更新処理
	bulletWt_.UpdateMatrix();

	// 移動処理
	Move();

	// 寿命の処理
	RemoveAfterlifeTime();
}


// 描画処理
void PlayerBullet::Draw3D(Camera* camera)
{
	bulletModel_->Draw(bulletWt_, camera);
}


// 移動処理
void PlayerBullet::Move()
{
	bulletWt_.srt.translate += velocity_;
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