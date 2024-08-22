#include "StaticEnemy.h"
#include "../../../Player/Player.h"



// 初期化処理
void StaticEnemy::Init()
{
	// BodyModelのロードと初期化
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/Enemys/Static", "Static.obj");
	model_ = modelManager_->GetModel("Static");

	// BodyTransfromの初期化
	trans_.Init();

	// Colliderの初期化
	collider_ = std::make_unique<OBBCollider>();
	collider_->Init();
	collider_->SetSize(size_);

	// 回転スピード(ラジアン)
	addRadSpeed_ = 1.0f;
}


// 更新処理
void StaticEnemy::Update()
{
	// オブジェクトの回転
	trans_.srt.rotate.y += ToRadians(addRadSpeed_);

	// 射撃の処理
	ExecutexShot();

	// Bullet更新処理
	for (std::shared_ptr<EnemyBullet> bullet : bulletList_) {
		bullet->Update();
	}

	// 死亡フラグが立っていたら削除
	bulletList_.remove_if([](std::shared_ptr<EnemyBullet> bullet) {
		if (bullet->IsDead()) {
			bullet.reset();
			return true;
		}
		return false;
		}
	);

	// ColliderのSRTの設定
	collider_->SetSrt(trans_.srt);

#ifdef _DEBUG

#endif // _DEBUG
}


// 描画処理
void StaticEnemy::Draw3D()
{
	// BodyModelの描画
	model_->DrawN(trans_);

	// Bulletsの描画
	for (std::shared_ptr<EnemyBullet> bullet : bulletList_) {
		bullet->Draw3D();
	}
}
void StaticEnemy::Draw2DFront() {}
void StaticEnemy::Draw2DBack() {}


// 衝突時コールバック関数
void StaticEnemy::OnCollision()
{
	isDead_ = true;
	player_->AddKillCount();
}


// 射撃の処理
void StaticEnemy::ExecutexShot()
{
	// タイマーをデクリメント
	shotFrame_--;

	// 0以下になったら射撃&タイマーリセット
	if (shotFrame_ <= 0) {

		// バレット生成
		CreateNewBullet();

		// タイマー再設定
		shotFrame_ = kShotInterval_;
	}
}


// 新しいバレットを生成する
void StaticEnemy::CreateNewBullet()
{
	// newBulletのインスタンス
	std::shared_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();

	// 初期座標
	Vector3 initPos = trans_.GetWorldPos();
	// 初期速度
	Vector3 initVel = Vector3::oneZ;
	initVel.z = 0.1f;
	initVel = TransformNormal(initVel, trans_.matWorld);

	// newBulletの初期化
	newBullet->Init();
	newBullet->SetPosition(initPos);
	newBullet->SetVelocity(initVel);
	newBullet->SetRotationFromVelocity();

	// リストに追加
	bulletList_.push_back(newBullet);
}

