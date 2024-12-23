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
	shotFunc_ = std::bind(&EnemyExecuteShot::Shot_Forward, this);

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
/// 前方射撃
/// </summary>
void EnemyExecuteShot::Shot_Forward()
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

