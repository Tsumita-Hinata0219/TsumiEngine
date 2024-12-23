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
void EnemyExecuteShot::Init()
{
	// 関数設定
	shotFunc_ = std::bind(&EnemyExecuteShot::Shot_Forward, this);
}


/// <summary>
/// 更新処理
/// </summary>
void EnemyExecuteShot::Update()
{
	// 射撃処理
	shotFunc_();
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
}

