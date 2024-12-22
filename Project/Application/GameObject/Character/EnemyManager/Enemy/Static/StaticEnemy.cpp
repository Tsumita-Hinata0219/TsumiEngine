#include "StaticEnemy.h"
#include "../../../Player/Player.h"
#include "../../EnemyManager.h"


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
	light_.direction = Vector3::oneY;
	light_.intensity = 0.7f;
	model_->SetLightData(light_);

	// 色加算の初期設定
	colorAdd_.enable = true;
	colorAdd_.addColor = Temp::Color::WHITE;
	colorAdd_.intensity = 0.0f;
	model_->SetColorAddition(colorAdd_);

	// ヒットリアクション関連数値の初期設定
	// ヒットリアクションフラグ
	isHitReactioning_ = false;
	// タイマー
	hitReactionTimer_.Init(0.0f, 0.4f * 60.0f);
	// スケール
	hitReactionScale_ = { 1.0f, 1.1f, 1.0f };
	// 色加算
	hitReactionColor_.first = 0.8f;
	hitReactionColor_.second = 0.0f;

	// Colliderの初期化
	sphere_ = std::make_unique<SphereCollider>(this);
	sphere_->data_.center = trans_.GetWorldPos();
	sphere_->data_.radius = 1.8f;

	// 回転スピード(ラジアン)
	addRadSpeed_ = 1.0f;
	
	// HPの設定
	hp_ = 25;
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

	// ヒットリアクション
	HitReaction();

	// ColliderのSRTの設定
	sphere_->data_.center = trans_.GetWorldPos();


#ifdef _DEBUG

#endif // _DEBUG
}


// 描画処理
void StaticEnemy::Draw3D()
{
	// BodyModelの描画
	model_->SetLightData(light_);
	model_->SetColorAddition(colorAdd_);
	model_->Draw(trans_);

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
	if (object->GetCategory() == Attributes::Category::PLAYER &&
		object->GetType() == Attributes::Type::BULLET) {

		// HPを減らす
		hp_--;

		// ヒットリアクション中にする
		isHitReactioning_ = true;

		// ヒットリアクションのタイマースタート
		hitReactionTimer_.Start();

		// エフェクトを出す
		enemyManager_->AddNewHitEffect(this);

		// HPが0以下なら死亡
		if (hp_ <= 0) {
			// 死亡状態に設定
			MarkAsDead();
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
		CreateNewBullet2();

		// タイマー再設定
		shotFrame_ = kShotInterval_;
	}
}


// 新しいバレットを生成する
void StaticEnemy::CreateNewBullet()
{
	// 初期座標
	Vector3 initPos = trans_.GetWorldPos();
	// 初期速度
	Vector3 initVel = Vector3::oneZ;
	initVel.z = kBulletSpeed_;
	initVel = TransformNormal(initVel, trans_.matWorld);
	enemyManager_->AddNewBullet(EnemyBulletType::Normal, initPos, initVel);
}


// 新しいバレットを生成する
void StaticEnemy::CreateNewBullet2()
{
	// 初期座標
	Vector3 initPos = trans_.GetWorldPos();
	// 初期速度
	Vector3 initVel = Vector3::oneZ;
	initVel.z = -kBulletSpeed_;
	initVel = TransformNormal(initVel, trans_.matWorld);
	enemyManager_->AddNewBullet(EnemyBulletType::Resistant, initPos, initVel);
}


// マークを死亡状態に設定
void StaticEnemy::MarkAsDead()
{
	// 死亡フラグを立てる
	isDead_ = true;
}
