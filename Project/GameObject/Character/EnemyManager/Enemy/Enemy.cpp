#include "Enemy.h"
#include "Player/Player.h"
#include "GameManager.h"


// デストラクタ
Enemy::~Enemy() {}


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

	// サイズ
	this->size_ = 2.0f * worldTransform_.scale;

	// ムーブフェーズの初期化処理
	MovePhaseInit();

	// コライダー
	OBBCollider::SetID(ObjectBit::Enemy);
	OBBCollider::SetCollosionAttribute(ObjectFileter::Enemy);
	OBBCollider::SetCollisionMask(ObjectFileter::Enemy);

	// バレットモデルの初期化
	modelBullet_ = make_unique<Model>();
	modelBullet_->CreateFromObj("EnemyBullet");

	// バレットの移動速度
	bulletVelocity_ = { 0.0f, 0.0f, 1.0f };

	// 一回の処理で何発撃つか
	bulletsPerSpanw_ = 1;
}


// 更新処理
void Enemy::Update()
{
	// バレットの更新処理
	BulletUpdate();

	// 移動のステートパターン処理
	MovePhaseUpdate();


	// ワールド座標の更新
	worldTransform_.UpdateMatrix();
}


// 描画処理
void Enemy::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
}


// 衝突時コールバック関数
void Enemy::OnCollision(uint32_t id)
{
	if (id == ObjectBit::PlayerBullet) {
		this->isDead_ = true;
	}
}


// 射撃処理
void Enemy::Attack() {

	CalcDirection();
	PushBackBulletList();
}


// バレットの初期化処理
void Enemy::BulletInit()
{
	FireInterval_ = 80;
	Scope scope = { 5.0f, 300.0f };
	FireTimer_ = int32_t(RandomGenerator::getRandom(scope));
}


// バレットの更新処理
void Enemy::BulletUpdate() {

	FireTimer_--;

	if (FireTimer_ <= 0) {

		Attack();
		FireTimer_ = FireInterval_;
	}

	if (KeysInput::TriggerKey(DIK_B)) {
		Attack();
	}

}


// バレットの進行方向の計算
Vector3 Enemy::CalcDirection()
{
	Vector3 PlayerPos = player_->GetWorldTransform().GetWorldPos();
	Vector3 EnemyPos = worldTransform_.GetWorldPos();
	Vector3 EneToPla = PlayerPos - EnemyPos;
	EneToPla = Normalize(EneToPla);
	return { EneToPla.x, EneToPla.y, EneToPla.z * kBulletSpeed_ };
}


// バレットリストの登録
void Enemy::PushBackBulletList()
{
	EnemyBullet* newBullet = new EnemyBullet();
	Vector3 newPos = worldTransform_.GetWorldPos();
	Vector3 newVel = CalcDirection();

	newBullet->SetPlayer(player_);
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


// OBBの設定
void Enemy::SettingOBBProperties()
{
	OBBCollider::SetSize(this->size_);
	OBBCollider::SetRotate(this->worldTransform_.rotate);
}
