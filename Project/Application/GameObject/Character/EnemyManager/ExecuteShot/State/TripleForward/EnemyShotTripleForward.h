#pragma once


#include "../IEnemyExecuteShot.h"

#include "../../../EnemyManager.h"
#include "../../../Enemy/IEnemy.h"


/* 3Way前方射撃 */
class EnemyShotTripleForward : public IEnemyExecuteShot {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyShotTripleForward() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyShotTripleForward() = default;

	/// <summary>
	/// 射撃処理
	/// </summary>
	void Execute(const float bulletSpeed) override 
	{
		AddNewBullet(Temp::Direction::Front, bulletSpeed);
		AddNewBullet(Temp::Direction::FrontLeft, bulletSpeed);
		AddNewBullet(Temp::Direction::FrontRight, bulletSpeed);
	}
};