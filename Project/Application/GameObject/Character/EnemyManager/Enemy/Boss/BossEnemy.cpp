#include "BossEnemy.h"
#include "../../../Player/Player.h"
#include "../../EnemyManager.h"


/// <summary>
/// 初期化処理
/// </summary>
void BossEnemy::Init()
{
	// BodyModelのロードと初期化
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/Enemys/Boss", "Boss.obj");
	model_ = modelManager_->GetModel("Boss");

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

	// 射撃処理クラス
	exeShot_ = std::make_unique<EnemyExecuteShot>(enemyManager_, this);
	exeShot_->SetTimer(shotInterval_);
	// 射撃方法とバレット挙動
	exeShot_->Init(shotDirection_, bulletBehavior_);

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

	// シールドの初期化処理
	shield_ = std::make_unique<EnemyShield>();
	shield_->Init();

	// Colliderの初期化
	sphere_ = std::make_unique<SphereCollider>(this);
	sphere_->data_.center = trans_.GetWorldPos();
	sphere_->data_.radius = 1.8f * 1.0f;

	// HPの設定
	hp_ = 15;

	// バリア関係まだちゃんと処理を作っていないので、ここで破壊しておく
	CollapseShield();
}


/// <summary>
/// 更新処理
/// </summary>
void BossEnemy::Update()
{
	// シールドの更新
	shield_->Update();

	// 射撃処理
	exeShot_->Update();

	// コライダーの更新
	sphere_->data_.center = trans_.GetWorldPos();


#ifdef _DEBUG
	DrawImGui();
#endif // _DEBUG
}


/// <summary>
/// 更新処理
/// </summary>
void BossEnemy::Draw3D()
{
	// BodyModelの描画
	model_->SetLightData(light_);
	model_->SetColorAddition(colorAdd_);
	model_->Draw(trans_);

	// シールドの描画処理
	shield_->Draw3D();
}
void BossEnemy::Draw2DFront()
{
}
void BossEnemy::Draw2DBack()
{
}


/// <summary>
/// 衝突判定コールバック関数
/// </summary>
void BossEnemy::onCollision([[maybe_unused]]IObject* object)
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


/// <summary>
/// バリアを壊す処理
/// </summary>
void BossEnemy::CollapseShield()
{
	// シールドが壊れた時の処理
	shield_->OnShieldBroken();
}


/// <summary>
/// マークを死亡状態に設定
/// </summary>
void BossEnemy::MarkAsDead()
{
	// 死亡フラグを立てる
	isDead_ = true;
}


/// <summary>
/// DrawImGuiの描画
/// </summary>
void BossEnemy::DrawImGui()
{
	if (ImGui::TreeNode("BossEnemy")) {

		trans_.DrawImGui();
		ImGui::Text("");

		if (ImGui::Button("Shield_Break")) {
			CollapseShield();
		}
		ImGui::Text("");

		ImGui::TreePop();
	}
}
