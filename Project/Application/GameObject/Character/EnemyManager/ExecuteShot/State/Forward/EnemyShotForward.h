#pragma once


#include "../IEnemyExecuteShot.h"

#include "../../../EnemyManager.h"
#include "../../../Enemy/IEnemy.h"


/* 前方射撃 */
class EnemyShotForward : public IEnemyExecuteShot {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyShotForward() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyShotForward() = default;

	/// <summary>
	/// 射撃処理
	/// </summary>
	void Execute(const float bulletSpeed) override 
	{
		AddNewBullet(Temp::Direction::Front, bulletSpeed);
	}
};