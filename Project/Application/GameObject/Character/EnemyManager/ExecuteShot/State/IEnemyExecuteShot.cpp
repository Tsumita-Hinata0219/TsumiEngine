#include "IEnemyExecuteShot.h"
#include "../../EnemyManager.h"
#include "../../Enemy/IEnemy.h"



/// <summary>
/// コンストラクタ
/// </summary>
IEnemyExecuteShot::IEnemyExecuteShot()
{
	// ランダム生成器作成
	std::random_device rd;
	randEngine_ = std::mt19937(rd());
	behabirDist_ = std::uniform_int_distribution<>(0, 1);
	directionDist_ = std::uniform_real_distribution<float>(-1.0f, 1.0f);
}


/// <summary>
/// 新しいバレットを追加
/// </summary>
void IEnemyExecuteShot::AddNewBullet(const Vector3& direction, const float bulletSpeed)
{
	// 弾を追加
	manager_->AddNewBullet(
		owner_->GetWorldPos(),
		TransformNormal(Normalize(direction) * bulletSpeed, 
		owner_->GetMatWorld()),
		GetBulletBehabir()
	);
}


/// <summary>
/// 多摩の状態の取得
/// </summary>
bool IEnemyExecuteShot::GetBulletBehabir()
{
	bool result = false;
	if (owner_->GetShotProperty().behavior == enemy::BulletBehavior::Random) {
		result = behabirDist_(randEngine_) == 1;
	}
	return result;
}
