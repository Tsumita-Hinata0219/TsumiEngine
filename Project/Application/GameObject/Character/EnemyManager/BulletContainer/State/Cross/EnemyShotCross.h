#pragma once

#include "../IEnemyExecuteShot.h"

#include "../../../EnemyManager.h"
#include "../../../Enemy/IEnemy.h"


/* 4Way対角線の射撃処理 */
class EnemyShotCross : public IEnemyExecuteShot {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyShotCross() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyShotCross() = default;

	/// <summary>
	/// 射撃処理
	/// </summary>
	void Execute(const float bulletSpeed) override 
	{
		AddNewBullet(Temp::Direction::FrontLeft, bulletSpeed);
		AddNewBullet(Temp::Direction::FrontRight, bulletSpeed);
		AddNewBullet(Temp::Direction::BackLeft, bulletSpeed);
		AddNewBullet(Temp::Direction::BackRight, bulletSpeed);
	}
};