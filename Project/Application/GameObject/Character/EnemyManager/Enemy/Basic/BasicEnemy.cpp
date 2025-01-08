#include "BasicEnemy.h"
#include "../../../Player/Player.h"
#include "../../EnemyManager.h"


// 初期化処理
void BasicEnemy::Init()
{
	// BodyModelのロードと初期化
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/Enemys/Basic", "Basic.obj");
	model_ = modelManager_->GetModel("Basic");

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

	// BodyTransformの初期化
	trans_.Init();
	// 0.0fだと行列計算でエラーが発生。限りなく0に近い数字で0.1f。
	//trans_.srt.scale = { 0.1f, 0.1f, 0.1f };

	// HPの設定
	hp_ = 5;

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

	/* ----- StatePattern ステートパターン ----- */
	// 各ステートをコンテナに保存
	stateVector_.resize(EnumSize<BasicEnemyStateType>::value);
	stateVector_[enum_val(BasicEnemyStateType::SPAWN)] = std::make_unique<BasicEnemySpawnState>();
	stateVector_[enum_val(BasicEnemyStateType::IDLE)] = std::make_unique<BasicEnemyIdleState>();
	stateVector_[enum_val(BasicEnemyStateType::APPROACH)] = std::make_unique<BasicEnemyApproachState>();
	stateVector_[enum_val(BasicEnemyStateType::DEATH)] = std::make_unique<BasicEnemyDeathState>();
	// 初期ステートの設定 && 初期ステートの初期化処理
	stateNo_ = enum_val(BasicEnemyStateType::IDLE);
	currentStateNo_ = stateNo_;
	stateVector_[currentStateNo_]->Enter(this);

	// Colliderの初期化
	sphere_ = std::make_unique<SphereCollider>(this);
	sphere_->data_.center = trans_.GetWorldPos();
	sphere_->data_.radius = 1.8f;
}


// 更新処理
void BasicEnemy::Update()
{
	// ステートパターン処理
	FuncStatePattern();

	// アプローチ状態の時のみ入る処理
	if (stateNo_ == int(BasicEnemyStateType::IDLE)) {

		// 戦闘状態の切り替え処理
		ToggleCombatState();
		return;
	}


	// 戦闘状態に入っていたら入る処理
	if (isCombatActive_) {

		// 移動処理
		Move();

		// 射撃処理
		exeShot_->Update();
	}

	// ヒットリアクション
	HitReaction();

	// ColliderのSRTの設定
	sphere_->data_.center = trans_.GetWorldPos();


#ifdef _DEBUG
	DrawImGui();
#endif // _DEBUG
}


// 描画処理
void BasicEnemy::Draw3D()
{
	// BodyModelの描画
	model_->SetMaterialColor(modelColor_);
	model_->SetColorAddition(colorAdd_);
	model_->Draw(trans_);
}
void BasicEnemy::Draw2DFront() {}
void BasicEnemy::Draw2DBack() {}


// 衝突自コールバック関数
void BasicEnemy::onCollision([[maybe_unused]] IObject* object)
{
	// 地形は押し出し
	if (object->GetCategory() == Attributes::Category::TERRAIN) {
		// 押し出しの処理
		trans_.srt.translate += Penetration::Execute(sphere_->GetData(), IObject::hitCollider_);
		trans_.UpdateMatrix();
	}
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
void BasicEnemy::OnCollisionWithPlayer()
{

}
void BasicEnemy::OnCollisionWithPlayerBullet()
{
	// スポーン&デス時には通らない
	if (stateNo_ != enum_val(BasicEnemyStateType::SPAWN) && stateNo_ != enum_val(BasicEnemyStateType::DEATH)) {

		// デスステートに移行	
		this->ChangeState(BasicEnemyStateType::DEATH);

		// プレイヤーのキルカウントを加算する
		player_->AddKillCount();
	}
}


// ステートパターン処理
void BasicEnemy::FuncStatePattern()
{
	// ステートチェック
	preStateNo_ = currentStateNo_;
	currentStateNo_ = stateNo_;

	// ステート変更チェック
	if (preStateNo_ != currentStateNo_) {

		///// 前回のステートの終了処理
		stateVector_[preStateNo_]->Exit();

		///// 新しいステートの初期化処理
		stateVector_[currentStateNo_]->Enter(this);
	}

	///// 更新処理
	stateVector_[currentStateNo_]->Update();
}


// 戦闘状態の切り替え処理
void BasicEnemy::ToggleCombatState()
{
	// プレイヤーとの距離で戦闘状態のフラグを管理する
	// 設定した距離よりも近くにいたらフラグを立てる
	if (std::abs(Length(player_->GetWorldPos() - trans_.GetWorldPos())) <= combatTriggerDistance_) {

		// 戦闘状態のフラグを立てる
		isCombatActive_ = true;
		ChangeState(BasicEnemyStateType::APPROACH);
	}
	else {

		ChangeState(BasicEnemyStateType::IDLE);

		// 戦闘状態のフラグを折る
		isCombatActive_ = false;
	}
}


// 移動処理
void BasicEnemy::Move()
{
	// ある程度近ければ早期return
	if (std::abs(Length(player_->GetWorldPos() - trans_.GetWorldPos())) <= minToPlayer_) {
		return;
	}

	// velocityを計算
	CalcVelocity();

	// 姿勢の計算
	CalcRotate();

	// 座標にvelocityを加算
	trans_.srt.translate += velocity_;
}


// Velocityの計算処理
void BasicEnemy::CalcVelocity()
{
	// 差分をNormalize
	Vector3 player2Enemy =
		Normalize(player_->GetWorldPos() - trans_.GetWorldPos());

	// 差分Normalizeに速度をかけてvelocityに設定
	velocity_ = {
		player2Enemy.x * moveVector_,
		player2Enemy.y, // y軸は移動してほしくないのでそのまま
		player2Enemy.z * moveVector_,
	};
}


// 向きの計算処理
void BasicEnemy::CalcRotate()
{
	// Y軸周り角度(θy)
	trans_.srt.rotate.y = std::atan2(velocity_.x, velocity_.z);

	float velZ = std::sqrt((velocity_.x * velocity_.x) + (velocity_.z * velocity_.z));
	float height = -velocity_.y;

	// X軸周り角度(θx)
	trans_.srt.rotate.x = std::atan2(height, velZ);
}


// マークを死亡状態に設定
void BasicEnemy::MarkAsDead()
{
	// 死亡フラグを立てる
	isDead_ = true;
}


// DrawImGuiの描画
void BasicEnemy::DrawImGui()
{
	if (ImGui::TreeNode("BasicEnemy")) {

		ImGui::Text("ColorAddition");
		colorAdd_.DrawImGui();
		ImGui::Text("");

		ImGui::TreePop();
	}
}

