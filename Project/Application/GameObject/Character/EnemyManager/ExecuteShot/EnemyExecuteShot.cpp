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
void EnemyExecuteShot::Init(float shotInterval)
{
	// 関数設定
	//SetShotFunc(Direction::Forward);
	//SetShotFunc(Direction::TripleForward);
	//SetShotFunc(Direction::Cross);
	//SetShotFunc(Direction::Omni_Four);
	SetShotFunc(Direction::Omni_Five);
	//SetShotFunc(Direction::Omni_Eight);

	// 射撃タイマーの設定
	shotTimer_.Init(0.0f, shotInterval);
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
	// 弾を追加
	manager_->AddNewBullet(
		owner_->GetWorldPos(), 
		TransformNormal(Normalize(direction) * kBulletSpeed_, owner_->GetMatWorld())
	);
}


/// <summary>
/// 射撃関数の設定
/// </summary>
void EnemyExecuteShot::SetShotFunc(Direction direction)
{
	switch (direction)
	{
	case EnemyExecuteShot::Forward:
		shotFunc_ = std::bind(&EnemyExecuteShot::Shot_Forward, this);
		break;
	case EnemyExecuteShot::TripleForward:
		shotFunc_ = std::bind(&EnemyExecuteShot::Shot_TripleForward, this);
		break;
	case EnemyExecuteShot::Cross:
		shotFunc_ = std::bind(&EnemyExecuteShot::Shot_Cross, this);
		break;
	case EnemyExecuteShot::Omni_Four:
		shotFunc_ = std::bind(&EnemyExecuteShot::Shot_Omni_Four, this);
		break;
	case EnemyExecuteShot::Omni_Five:
		shotFunc_ = std::bind(&EnemyExecuteShot::Shot_Omni_Five, this);
		break;
	case EnemyExecuteShot::Omni_Eight:
		shotFunc_ = std::bind(&EnemyExecuteShot::Shot_Omni_Eight, this);
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

