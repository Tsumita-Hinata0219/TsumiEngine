#include "EnemyBullet.h"
#include "Player/Player.h"



// 初期化処理
void EnemyBullet::Initialize(Model& modelHD, Vector3 pos, Vector3 vel)
{
	// モデルの初期化
	model_ = make_unique<Model>();
	(*model_) = modelHD;

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translate = pos;
	worldTransform_.scale = { 1.0f, 1.0f, 2.0f };

	// 加算速度
	velocity_ = Vector3::zero;

	// 移動量の設定
	move_ = vel;

	// サイズ
	size_ = 1.0f * worldTransform_.scale;

	// コライダー
	OBBCollider::SetID(ObjectBit::EnemyBullet);
	OBBCollider::SetCollosionAttribute(ObjectFileter::Enemy);
	OBBCollider::SetCollisionMask(ObjectFileter::Enemy);
}


// 更新処理
void EnemyBullet::Update()
{
	// 移動処理
	Move();

	// ワールド座標の更新
	worldTransform_.UpdateMatrix();
}


// 描画処理
void EnemyBullet::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
}


// 衝突時コールバック関数
void EnemyBullet::OnCollision(uint32_t id)
{
	if (id == ObjectBit::Player) {
		this->isDead_ = true;
	}
	else if (id == ObjectBit::Terrain) {
		this->isDead_ = true;
	}
}


// プレイヤーへのホーミング処理
void EnemyBullet::HomingToPlayer()
{
	// 敵弾から自キャラへのベクトル
	Vector3 toPlayer = worldTransform_.translate - player_->GetWorldTransform().translate;

	// ベクトルの正規化
	toPlayer = Normalize(toPlayer);
	move_ = Normalize(move_);

	// 球面線形補間により、今の速度を自キャラへのベクトルえお内挿し、新たな速度する
	move_ = SLerp(move_, toPlayer, 0.05f) * kbulletSpeed;

	// Y軸周り角度(θy)
	worldTransform_.rotate.y = std::atan2(move_.x, move_.z);

	float velZ = std::sqrt((move_.x * move_.x) + (move_.z * move_.z));
	float height = -move_.y;

	// X軸周り角度(θx)
	worldTransform_.rotate.x = std::atan2(height, velZ);
}


// 移動処理
void EnemyBullet::Move()
{
	// ホーミングの処理
	HomingToPlayer();

	// 速度を常に加算
	velocity_ = move_;
	worldTransform_.translate -= velocity_;
}


// OBBの設定
void EnemyBullet::SettingOBBProperties()
{
	OBBCollider::SetSize(this->size_);
	OBBCollider::SetRotate(this->worldTransform_.rotate);
}