#include "Enemy.h"
#include "../../Player/Player.h"


// 初期化処理
void Enemy::Initialize()
{
	// BodyModelのロードと初期化
	bodyModel_ = make_unique<Model>();
	bodyModel_->CreateFromObjAssimpVer("Test", "Test");

	// BodyTransformの初期化
	bodyWt_.Initialize();
	bodyWt_.srt.translate.z = 20.0f;
}


// 更新処理
void Enemy::Update()
{
	// Transformの更新処理
	bodyWt_.UpdateMatrix();

	// 移動処理
	Move();


#ifdef _DEBUG


#endif // _DEBUG
}


// 描画処理
void Enemy::Draw3D(Camera* camera)
{
	// BodyModelの描画
	bodyModel_->Draw(bodyWt_, camera);
}


// 移動処理
void Enemy::Move()
{
	// ある程度近ければ早期return
	if (std::abs(Length(player_->GetPosition() - bodyWt_.GetWorldPos())) <= minToPlayer_) {
		return;
	}

	// velocityを計算
	CalcVelocity();

	// 姿勢の計算
	CalcRotate();

	// 座標にvelocityを加算
	bodyWt_.srt.translate += velocity_;
}


// Velocityの計算処理
void Enemy::CalcVelocity()
{
	// 差分をNormalize
	Vector3 player2Enemy =
		Normalize(player_->GetPosition() - bodyWt_.GetWorldPos());

	// 差分Normalizeに速度をかけてvelocityに設定
	velocity_ = {
		player2Enemy.x * moveVector_,
		player2Enemy.y, // y軸は移動してほしくないのでそのまま
		player2Enemy.z * moveVector_,
	};
}


// 向きの計算処理
void Enemy::CalcRotate()
{
	// Y軸周り角度(θy)
	bodyWt_.srt.rotate.y = std::atan2(velocity_.x, velocity_.z);

	float velZ = std::sqrt((velocity_.x * velocity_.x) + (velocity_.z * velocity_.z));
	float height = -velocity_.y;

	// X軸周り角度(θx)
	bodyWt_.srt.rotate.x = std::atan2(height, velZ);
}


// 射撃の処理
void Enemy::ExecuteShot()
{
}

