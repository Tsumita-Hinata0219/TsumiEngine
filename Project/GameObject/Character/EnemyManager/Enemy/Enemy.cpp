#include "Enemy.h"
#include "GameManager.h"


// デストラクタ
Enemy::~Enemy() {

	// timedCalls_の解放
	ClearTimedCall();
}


// 初期化処理
void Enemy::Initialize(Model& modelEnemy, Vector3 pos, Vector3 move)
{
	// モデルの初期化
	model_ = make_unique<Model>();
	(*model_) = modelEnemy;

	// ワールドトランスフォームの初期化	
	worldTransform_.Initialize();
	worldTransform_.translate = pos;
	worldTransform_.rotate.y = 6.285f / 2.0f;

	// 加算速度
	velocity_ = Vector3::zero;

	// 移動量の設定
	move_ = move;

	// ムーブフェーズの初期化処理
	MovePhaseInit();


	// バレットモデルの初期化
	modelBullet_ = make_unique<Model>();
	modelBullet_->CreateFromObj("EnemyBullet");

	// バレットの移動速度
	bulletVelocity_ = { 0.0f, 0.0f, 1.0f };

	// 一回の処理で何発撃つか
	bulletsPerSpanw_ = 1;

	// TimedCallリストの登録
	PushBackTimedCall();
}


// 更新処理
void Enemy::Update()
{
	// バレットの更新処理
	BulletUpdate();

	// 移動のステートパターン処理
	MovePhaseUpdate();


	if (KeyInput::TriggerKey(DIK_B)) {
		Attack();
	}

	// ワールド座標の更新
	worldTransform_.UpdateMatrix();
}


// 描画処理
void Enemy::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
}


// 射撃処理
void Enemy::Attack() {

	for (int i = 0; i < bulletsPerSpanw_; i++) {
		PushBackBulletList();
	}
}


// バレットの更新処理
void Enemy::BulletUpdate() {

	// 終了したタイマーを削除
	timedCalls_.remove_if([](TimedCall* timedCall) {
		if (timedCall->IsFinished()) {
			delete timedCall;
			return true;
		}
		return false;
	});

	// 範囲forでリストの全要素について回す
	for (TimedCall* timedCall : timedCalls_) {
		timedCall->Update();
	}
}


// 射撃して、タイマーをリセットするコールバック関数
void Enemy::FireAndReset() 
{
	// 射撃
	Attack();

	// TimedCallリストの登録
	PushBackTimedCall();
}


// TimedCallリストの登録
void Enemy::PushBackTimedCall()
{
	// メンバ関数と呼び出し元をbindしてstd::functionに代入
	std::function<void(void)> callback = std::bind(&Enemy::FireAndReset, this);

	// 時限発動イベントを生成
	TimedCall* timedCall = new TimedCall(callback, 120);

	// 時限発動イベントを時限発動イベントリストに追加
	timedCalls_.push_back(timedCall);
}


// タイムコールリストを削除
void Enemy::ClearTimedCall()
{
	for (TimedCall* timedCall : timedCalls_) {
		delete timedCall;
	}
}


// バレットリストの登録
void Enemy::PushBackBulletList() 
{
	EnemyBullet* newBullet = new EnemyBullet();
	Vector3 newPos = worldTransform_.GetWorldPos();
	Vector3 newVel = TransformNormal(bulletVelocity_, worldTransform_.matWorld);

	newBullet->Initialize((*modelBullet_), newPos, newVel);

	GameScene_->AddEnemyBulletList(newBullet);
}


// 移動処理
void Enemy::MoveApproach()
{
	// 速度を常に加算
	velocity_ = move_;
	worldTransform_.translate += velocity_;
}
void Enemy::MoveLeave()
{
	// 速度を常に減算
	velocity_ = move_;
	worldTransform_.translate -= velocity_;
}


// ムーブフェーズの初期化処理
void Enemy::MovePhaseInit() {

	// 各ムーブフェーズの配列設定
	movePhaseArr_[Approach] = make_unique<IEnemyMoveApproachState>();
	movePhaseArr_[Leave] = make_unique<IEnemyMoveLeaveState>();
	movePhaseNum_ = Approach;
	movePhaseArr_[currMovePhase_]->InitState(this);
}

// ムーブフェーズの更新処理
void Enemy::MovePhaseUpdate() {

	// フェーズチェック
	prevMovePhase_ = currMovePhase_;
	currMovePhase_ = movePhaseNum_;

	// フェーズ変更チェック
	if (prevMovePhase_ != currMovePhase_) {

		// 変更していたら初期化処理
		movePhaseArr_[currMovePhase_]->InitState(this);
	}

	// 更新処理
	movePhaseArr_[currMovePhase_]->UpdateState();
}