#include "IEnemy.h"
#include "../../EnemyManager/EnemyManager.h"


/// <summary>
/// Bulletを新しく追加
/// </summary>
void IEnemy::AddNewBullet(EnemyBulletType setType, const Vector3& initPos, const Vector3& initVel)
{
	enemyManager_->AddNewEnemyBullet(setType, initPos, initVel);
}
