#include "EnemyExecuteShot.h"
#include "../EnemyManager.h"
#include "../Enemy/IEnemy.h"


/// <summary>
/// 初期化処理
/// </summary>
void EnemyExecuteShot::Init()
{
	// 関数設定
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
void EnemyExecuteShot::AddNewBullet(EnemyBulletType setType, const Vector3& direction)
{
	// 弾を追加
	manager_->AddNewBullet(
		setType,
		owner_->GetWorldPos(), 
		TransformNormal(Normalize(direction) * kBulletSpeed_, owner_->GetMatWorld())
	);
}


/// <summary>
/// 前方射撃
/// </summary>
void EnemyExecuteShot::Shot_Forward()
{
	AddNewBullet(EnemyBulletType::Normal, Temp::Direction::Front);
}

