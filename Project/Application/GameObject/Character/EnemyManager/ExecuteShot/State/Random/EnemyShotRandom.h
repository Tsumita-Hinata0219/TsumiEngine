#pragma once


#include "../IEnemyExecuteShot.h"

#include "../../../EnemyManager.h"
#include "../../../Enemy/IEnemy.h"

/* ランダム射撃 */
class EnemyShotRandom : public IEnemyExecuteShot {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyShotRandom() : IEnemyExecuteShot()
	{
		// ランダム生成器作成
		std::random_device rd;
		randEngine_ = std::mt19937(rd());
		behabirDist_ = std::uniform_int_distribution<>(0, 1);
		directionDist_ = std::uniform_real_distribution<float>(-1.0f, 1.0f);
	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyShotRandom() = default;

	/// <summary>
	/// 射撃処理
	/// </summary>
	void Execute(const float bulletSpeed) override
	{
		Vector3 direction = Vector3::zero;
		direction.x = directionDist_(randEngine_);
		direction.z = directionDist_(randEngine_);
		AddNewBullet(direction, bulletSpeed);
	}

private:

	std::mt19937 randEngine_; // ランダムエンジン
	std::uniform_int_distribution<> behabirDist_; // 0 or 1 の分布
	std::uniform_real_distribution<float> directionDist_; // -1 ~ +1 の分布
};