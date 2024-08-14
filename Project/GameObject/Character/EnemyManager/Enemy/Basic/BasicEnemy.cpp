#include "BasicEnemy.h"
#include "../../../Player/Player.h"



// 初期化処理
void BasicEnemy::Init()
{
	// BodyModelのロードと初期化
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/Test", "Test.obj");
	model_ = modelManager_->GetModel("Test");

	// BodyTransformの初期化
	trans_.Init();
	// 0.0fだと行列計算でエラーが発生。限りなく0に近い数字で0.1f。
	trans_.srt.scale = { 0.1f, 0.1f, 0.1f };

	// ShotFrameにIntervalを入れておく
	shotFrame_ = kShotInterval_;

	/* ----- StatePattern ステートパターン ----- */
	// 各ステートをコンテナに保存
	stateVector_.resize(EnumSize<BasicEnemyStateType>::value);
	stateVector_[to_underlying(BasicEnemyStateType::SPAWN)] = std::make_unique<BasicEnemySpawnState>();
	//stateVector_[BasicEnemyStateType::APPROACH] = std::make_unique<BasicEnemyApproachState>();
	//stateVector_[BasicEnemyStateType::DEATH] = std::make_unique<IEnemyDeathState>();
	// 初期ステートの設定 && 初期ステートの初期化処理
	stateNo_ = to_underlying(BasicEnemyStateType::SPAWN);
	currentStateNo_ = stateNo_;
	stateVector_[currentStateNo_]->Enter(this);

	// Colliderの初期化
	collider_ = std::make_unique<OBBCollider>();
	collider_->Init();
	collider_->SetSize(size_);
}


// 更新処理
void BasicEnemy::Update()
{
	// ステートパターン処理
	FuncStatePattern();

	// Transformの更新処理
	trans_.UpdateMatrix();

	// アプローチ状態の時のみ入る処理
	if (stateNo_ == EnemyState::APPROACH) {

		// 戦闘状態の切り替え処理
		ToggleCombatState();

		// 戦闘状態に入っていたら入る処理
		if (isCombatActive_) {

			// 移動処理
			Move();

			// 射撃の処理
			ExecuteShot();
		}
	}

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
void BasicEnemy::Draw3D()
{
	// BodyModelの描画
	model_->SetColor(modelColor_);
	model_->DrawN(trans_);

	// Bulletsの描画
	for (std::shared_ptr<EnemyBullet> bullet : bulletList_) {
		bullet->Draw3D();
	}
}
void BasicEnemy::Draw2DFront() {}
void BasicEnemy::Draw2DBack() {}


// 衝突自コールバック関数
void BasicEnemy::OnCollisionWithPlayer()
{

}
void BasicEnemy::OnCollisionWithPlayerBullet()
{
	// スポーン&デス時には通らない
	if (stateNo_ != to_underlying(BasicEnemyStateType::SPAWN) && stateNo_ != to_underlying(BasicEnemyStateType::DEATH)) {

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
	}
	else {

		// 戦闘状態のフラグを折る
		isCombatActive_ = false;

		// 射撃までのフレームを設定
		shotFrame_ = kShotInterval_;
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


// 射撃の処理
void BasicEnemy::ExecuteShot()
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
void BasicEnemy::CreateNewBullet()
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

