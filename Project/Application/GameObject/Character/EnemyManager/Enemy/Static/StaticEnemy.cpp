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
	trans_.srt = initSRT_;

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

	// 射撃処理クラス
	exeShot_ = std::make_unique<EnemyExecuteShot>(enemyManager_, this);
	// 射撃方法とバレット挙動
	exeShot_->Init(shotFuncData_);

	// 移動処理クラス
	movement_ = std::make_unique<EnemyMovement>(enemyManager_, this, player_);
	movement_->Init(movementData_);

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
	hp_ = 10;
}


// 更新処理
void StaticEnemy::Update()
{
	// オブジェクトの回転
	trans_.srt.rotate.y += ToRadians(addRadSpeed_);

	// 射撃処理
	exeShot_->Update();

	// 移動処理
	movement_->Update();

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


// マークを死亡状態に設定
void StaticEnemy::MarkAsDead()
{
	// 死亡フラグを立てる
	isDead_ = true;
}
