#pragma once


#include "../IEnemyExecuteShot.h"

#include "../../../EnemyManager.h"
#include "../../../Enemy/IEnemy.h"


/* 前方射撃 */
class EnemyShotOmniFour : public IEnemyExecuteShot {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyShotOmniFour() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyShotOmniFour() = default;

	/// <summary>
	/// 射撃処理
	/// </summary>
	void Execute(const float bulletSpeed) override
	{
		AddNewBullet(Temp::Direction::Front, bulletSpeed);
		AddNewBullet(Temp::Direction::Back, bulletSpeed);
		AddNewBullet(Temp::Direction::Left, bulletSpeed);
		AddNewBullet(Temp::Direction::Right, bulletSpeed);
	}
};