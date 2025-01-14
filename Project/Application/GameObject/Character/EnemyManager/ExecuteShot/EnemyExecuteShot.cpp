#include "EnemyExecuteShot.h"
	#include "../EnemyManager.h"
	#include "../Enemy/IEnemy.h"



/// <summary>
/// コンストラクタ
/// </summary>
EnemyExecuteShot::EnemyExecuteShot(EnemyManager* manager, IEnemy* owner)
{
	this->manager_ = manager;
	this->owner_ = owner;
}


/// <summary>
/// 初期化処理
/// </summary>
void EnemyExecuteShot::Init(enemy::ShotFuncData data)
{
	// 関数設定
	SetShotFunc(data.direction);

	// バレット挙動
	behavior_ = data.behavior;
	if (behavior_ == enemy::BulletBehavior::Common) {
		behabirState_ = false;
	}
	else if (behavior_ == enemy::BulletBehavior::Resistant) {
		behabirState_ = true;
	}

	// ランダム生成器作成
	std::random_device rd;
	randEngine_ = std::mt19937(rd());
	behabirDist_ = std::uniform_int_distribution<>(0, 1);
	directionDist_ = std::uniform_real_distribution<float>(-1.0f, 1.0f);

	// タイマーの設定はアクセッサでやってる
	// 射撃タイマー開始
	this->shotTimer_.Init(0.0f, data.shotInterval);
	shotTimer_.Start();
}


/// <summary>
/// 更新処理
/// </summary>
void EnemyExecuteShot::Update()
{
	// タイマー更新。終了してもループする
	shotTimer_.Update(true);

	// タイマー終了で射撃
	if (shotTimer_.IsFinish()) {
		// 射撃処理
		shotFunc_();
	}
}


/// <summary>
/// 新しいバレットを追加
/// </summary>
void EnemyExecuteShot::AddNewBullet(const Vector3& direction)
{
	if (behavior_ == enemy::BulletBehavior::Random) {
		behabirState_ = behabirDist_(randEngine_) == 1;
	}

	// 弾を追加
	manager_->AddNewBullet(
		owner_->GetWorldPos(), 
		TransformNormal(Normalize(direction) * kBulletSpeed_, owner_->GetMatWorld()),
		behabirState_
	);
}


/// <summary>
/// 射撃関数の設定
/// </summary>
void EnemyExecuteShot::SetShotFunc(enemy::ShotDirection direction)
{
	switch (direction)
	{
	case enemy::ShotDirection::Forward:
		shotFunc_ = std::bind(&EnemyExecuteShot::Shot_Forward, this);
		break;
	case enemy::ShotDirection::TripleForward:
		shotFunc_ = std::bind(&EnemyExecuteShot::Shot_TripleForward, this);
		break;
	case enemy::ShotDirection::Cross:
		shotFunc_ = std::bind(&EnemyExecuteShot::Shot_Cross, this);
		break;
	case enemy::ShotDirection::Omni_Four:
		shotFunc_ = std::bind(&EnemyExecuteShot::Shot_Omni_Four, this);
		break;
	case enemy::ShotDirection::Omni_Five:
		shotFunc_ = std::bind(&EnemyExecuteShot::Shot_Omni_Five, this);
		break;
	case enemy::ShotDirection::Omni_Eight:
		shotFunc_ = std::bind(&EnemyExecuteShot::Shot_Omni_Eight, this);
		break;
	case enemy::ShotDirection::Random:
		shotFunc_ = std::bind(&EnemyExecuteShot::Shot_Random, this);
		break;
	default:
		break;
	}
}


/// <summary>
/// 前方射撃
/// </summary>
void EnemyExecuteShot::Shot_Forward()
{
	AddNewBullet(Temp::Direction::Front);
}


/// <summary>
/// 3Way前方
/// </summary>
void EnemyExecuteShot::Shot_TripleForward()
{
	AddNewBullet(Temp::Direction::Front);
	AddNewBullet(Temp::Direction::FrontLeft);
	AddNewBullet(Temp::Direction::FrontRight);
}


/// <summary>
/// 4Way対角線
/// </summary>
void EnemyExecuteShot::Shot_Cross()
{
	AddNewBullet(Temp::Direction::FrontLeft);
	AddNewBullet(Temp::Direction::FrontRight);
	AddNewBullet(Temp::Direction::BackLeft);
	AddNewBullet(Temp::Direction::BackRight);
}


/// <summary>
/// 4Way全方位
/// </summary>
void EnemyExecuteShot::Shot_Omni_Four()
{
	AddNewBullet(Temp::Direction::Front);
	AddNewBullet(Temp::Direction::Back);
	AddNewBullet(Temp::Direction::Left);
	AddNewBullet(Temp::Direction::Right);
}


/// <summary>
/// 5Way全方位
/// </summary>
void EnemyExecuteShot::Shot_Omni_Five()
{
	AddNewBullet(Temp::Direction::Front);
	AddNewBullet(Temp::Direction::FrontLeft);
	AddNewBullet(Temp::Direction::FrontRight);
	AddNewBullet(Temp::Direction::Left);
	AddNewBullet(Temp::Direction::Right);
}


/// <summary>
/// 8Way全方位
/// </summary>
void EnemyExecuteShot::Shot_Omni_Eight()
{
	AddNewBullet(Temp::Direction::Front);
	AddNewBullet(Temp::Direction::Back);
	AddNewBullet(Temp::Direction::Left);
	AddNewBullet(Temp::Direction::Right);
	AddNewBullet(Temp::Direction::FrontLeft);
	AddNewBullet(Temp::Direction::FrontRight);
	AddNewBullet(Temp::Direction::BackLeft);
	AddNewBullet(Temp::Direction::BackRight);
}


/// <summary>
/// ランダム
/// </summary>
void EnemyExecuteShot::Shot_Random()
{
	Vector3 direction = Vector3::zero;
	direction.x = directionDist_(randEngine_);
	direction.z = directionDist_(randEngine_);
	AddNewBullet(direction);
}

