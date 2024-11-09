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

	// ライトの初期設定
	light_.enable = true;
	light_.direction = Vector3::one;

	// Colliderの初期化
	colComp_->SetAttribute(ColliderAttribute::Enemy);
	colComp_->Register(sphere_);
	sphere_.center = trans_.GetWorldPos();
	sphere_.radius = 2.0f;

	// 回転スピード(ラジアン)
	addRadSpeed_ = 1.0f;
	
	// HPの設定
	hp_ = 10;
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
	sphere_.center = trans_.GetWorldPos();


#ifdef _DEBUG

#endif // _DEBUG
}


// 描画処理
void StaticEnemy::Draw3D()
{
	// BodyModelの描画
	//model_->SetLightData(light_);
	model_->DrawN(trans_);

	// Bulletsの描画
	for (std::shared_ptr<EnemyBullet> bullet : bulletList_) {
		bullet->Draw3D();
	}
}
void StaticEnemy::Draw2DFront() {}
void StaticEnemy::Draw2DBack() {}


// 衝突判定コールバック関数
void StaticEnemy::onCollision(IObject* object)
{
	if (object->GetAttribute() == ObjAttribute::PLAYER) {

		// HPを減らす
		hp_--;

		// HPが0以下なら死亡
		if (hp_ <= 0) {
			isDead_ = true;
			player_->AddKillCount();
		}
	}
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

